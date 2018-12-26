//////////////////////////////////////////////////////////////////////////////
// Filename    : LightningHand.cpp
// Written by  : elca@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "LightningHand.h"
#include "Gpackets/GCSkillToObjectOK1.h"
#include "Gpackets/GCSkillToObjectOK2.h"
#include "Gpackets/GCSkillToObjectOK5.h"
#include "CrossCounter.h"

//////////////////////////////////////////////////////////////////////////////
// �����̾� ������Ʈ �ڵ鷯
//////////////////////////////////////////////////////////////////////////////
void LightningHand::execute(Slayer * pSlayer, ObjectID_t TargetObjectID, SkillSlot * pSkillSlot, CEffectID_t CEffectID)
	
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin" << endl;

	Assert(pSlayer != NULL);
	Assert(pSkillSlot != NULL);

	try 
	{
		Player* pPlayer = pSlayer->getPlayer();
		Zone* pZone = pSlayer->getZone();
		Assert(pPlayer != NULL);
		Assert(pZone != NULL);

		Creature* pTargetCreature = pZone->getCreature(TargetObjectID);
		//Assert(pTargetCreature != NULL);
		
		// NPC�� ������ ���� ����.
		// NoSuch����. by sigi. 2002.5.2
		if (pTargetCreature==NULL
			|| pTargetCreature->isNPC())
		{
			executeSkillFailException(pSlayer, getSkillType());
			//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;
			return;
		}

		// �����ϰ� �ִ� ���Ⱑ ���̰ų�, SWORD�� �ƴ϶�� �� �� ����.
		Item* pItem = pSlayer->getWearItem(Slayer::WEAR_RIGHTHAND);
		if (pItem == NULL || pItem->getItemClass() != Item::ITEM_CLASS_SWORD)
		{
			executeSkillFailException(pSlayer, getSkillType());
			//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;
			return;
		}

		bool bIncreaseExp = pSlayer->isRealWearingEx(Slayer::WEAR_RIGHTHAND);

		GCSkillToObjectOK1 _GCSkillToObjectOK1;
		GCSkillToObjectOK2 _GCSkillToObjectOK2;
		GCSkillToObjectOK5 _GCSkillToObjectOK5;

		SkillType_t       SkillType  = pSkillSlot->getSkillType();
		SkillInfo*        pSkillInfo = g_pSkillInfoManager->getSkillInfo(SkillType);
		SkillDomainType_t DomainType = pSkillInfo->getDomainType();
		SkillLevel_t      SkillLevel = pSkillSlot->getExpLevel();

		bool bCriticalHit = false;

		// �⺻ �������� ��ų �������� ���Ѵ�.
		SkillInput input(pSlayer, pSkillSlot);
		SkillOutput output;
		computeOutput(input, output);

		Damage_t Damage = computeDamage(pSlayer, pTargetCreature, SkillLevel/5, bCriticalHit);
		Damage += output.Damage;

		int  RequiredMP         = (int)pSkillInfo->getConsumeMP();
		bool bManaCheck         = hasEnoughMana(pSlayer, RequiredMP);
		bool bTimeCheck         = verifyRunTime(pSkillSlot);
		bool bRangeCheck        = verifyDistance(pSlayer, pTargetCreature, pSkillInfo->getRange());
		bool bHitRoll           = HitRoll::isSuccess(pSlayer, pTargetCreature, SkillLevel / 2);
		bool bCanHit            = canHit(pSlayer, pTargetCreature, SkillType) && canAttack( pSlayer, pTargetCreature );
		bool bPK                = verifyPK(pSlayer, pTargetCreature);

		// ������ �־�� �ϰ�, �ð��� �Ÿ� üũ�� �����ϰ�,
		// hitroll�� �����ϰ�, ũ�ν� ī���Ͱ� �ɷ����� �ʴٸ�, �����̴�.
		if (bManaCheck && bTimeCheck && bRangeCheck && bHitRoll && bCanHit && bPK)
		{
			CheckCrossCounter(pSlayer, pTargetCreature, Damage, pSkillInfo->getRange());

			decreaseMana(pSlayer, RequiredMP, _GCSkillToObjectOK1);

//			Exp_t Point = pSkillInfo->getPoint();

			// �������� �ְ�, �������� ����߸���.
			setDamage(pTargetCreature, Damage, pSlayer, SkillType, &_GCSkillToObjectOK2, &_GCSkillToObjectOK1);
			computeAlignmentChange(pTargetCreature, Damage, pSlayer, &_GCSkillToObjectOK2, &_GCSkillToObjectOK1);
			decreaseDurability(pSlayer, pTargetCreature, pSkillInfo, &_GCSkillToObjectOK1, &_GCSkillToObjectOK2);

			// ũ��Ƽ�� ��Ʈ��� ������ �ڷ� �������� �Ѵ�.
			if (bCriticalHit)
			{
				knockbackCreature(pZone, pTargetCreature, pSlayer->getX(), pSlayer->getY());
			}

			// Ÿ���� �����̾ �ƴ� ��쿡�� ����ġ�� �÷��ش�.
			if (!pTargetCreature->isSlayer())
			{
				
				if (bIncreaseExp)
				{
					shareAttrExp(pSlayer, Damage, 8, 1, 1, _GCSkillToObjectOK1);
					increaseDomainExp(pSlayer, DomainType, pSkillInfo->getPoint(), _GCSkillToObjectOK1, pTargetCreature->getLevel());
					increaseSkillExp(pSlayer, DomainType,  pSkillSlot, pSkillInfo, _GCSkillToObjectOK1);
				}
				increaseAlignment(pSlayer, pTargetCreature, _GCSkillToObjectOK1);
			}

			// ��Ŷ�� �غ��ϰ�, ������. 
			_GCSkillToObjectOK1.setSkillType(SkillType);
			_GCSkillToObjectOK1.setCEffectID(CEffectID);
			_GCSkillToObjectOK1.setTargetObjectID(TargetObjectID);
			_GCSkillToObjectOK1.setDuration(0);
		
			_GCSkillToObjectOK2.setObjectID(pSlayer->getObjectID());
			_GCSkillToObjectOK2.setSkillType(SkillType);
			_GCSkillToObjectOK2.setDuration(0);
		
			_GCSkillToObjectOK5.setObjectID(pSlayer->getObjectID());
			_GCSkillToObjectOK5.setSkillType(SkillType);
			_GCSkillToObjectOK5.setTargetObjectID (TargetObjectID);
			_GCSkillToObjectOK5.setDuration(0);
		
			pPlayer->sendPacket(&_GCSkillToObjectOK1);
		
			if (pTargetCreature->isPC()) 
			{
				Player* pTargetPlayer = pTargetCreature->getPlayer();
				Assert(pTargetPlayer != NULL);
				pTargetPlayer->sendPacket(&_GCSkillToObjectOK2);
			} 
			else 
			{
				Monster * pMonster = dynamic_cast<Monster*>(pTargetCreature);
				pMonster->addEnemy(pSlayer);
			}

			list< Creature*> cList;
			cList.push_back(pSlayer);
			cList.push_back(pTargetCreature);

			pZone->broadcastPacket(pSlayer->getX(), pSlayer->getY(),  &_GCSkillToObjectOK5, cList);

			pSkillSlot->setRunTime(output.Delay);
		} 
		else 
		{
			executeSkillFailNormal(pSlayer, getSkillType(), pTargetCreature);
		}
	} 
	catch (Throwable & t) 
	{
		executeSkillFailException(pSlayer, getSkillType());
	}

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;

	__END_CATCH
}

LightningHand g_LightningHand;
