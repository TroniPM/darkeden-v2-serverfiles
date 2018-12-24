//////////////////////////////////////////////////////////////////////////////
// Filename    : ChargingAttack.cpp
// Written by  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "SuddenBlast.h"
#include "RankBonus.h"
#include "Vampire.h"
#include "SkillUtil.h"
#include "Zone.h"
#include "HitRoll.h"
#include "CrossCounter.h"
#include "EffectSuddenBlast.h"

#include "Gpackets/GCSkillToObjectOK1.h"
#include "Gpackets/GCSkillToObjectOK2.h"
#include "Gpackets/GCStatusCurrentHP.h"

//////////////////////////////////////////////////////////////////////////////
// �ƿ콺���� ������Ʈ �ڵ鷯
//////////////////////////////////////////////////////////////////////////////
void SuddenBlast::execute(Ousters * pOusters, ObjectID_t TargetObjectID, OustersSkillSlot * pOustersSkillSlot, CEffectID_t CEffectID)
	throw(Error)
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin" << endl;

	Assert(pOusters != NULL);
	Assert(pOustersSkillSlot != NULL);

	try 
	{
		Player* pPlayer = pOusters->getPlayer();
		Zone* pZone = pOusters->getZone();
		Assert(pPlayer != NULL);
		Assert(pZone != NULL);

		Creature* pTargetCreature = pZone->getCreature(TargetObjectID);
		//Assert(pTargetCreature != NULL);

		// NoSuch����. by sigi. 2002.5.2
		// NPC�� ������ ���� ����.
		if (pTargetCreature==NULL
			|| pTargetCreature->isNPC())
		{
			executeSkillFailException(pOusters, getSkillType());
			//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;
			return;
		}

		// �����ϰ� �ִ� ���Ⱑ ���̰ų�, ���� �ƴ϶�� ����� ����� �� ����.
		Item* pItem = pOusters->getWearItem(Ousters::WEAR_RIGHTHAND);
		if (pItem == NULL)
		{
			executeSkillFailException(pOusters, getSkillType());
			//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;
			return;
		}

		GCSkillToObjectOK1 _GCSkillToObjectOK1;
		GCSkillToObjectOK2 _GCSkillToObjectOK2;

		SkillType_t       SkillType  = pOustersSkillSlot->getSkillType();
		SkillInfo*        pSkillInfo = g_pSkillInfoManager->getSkillInfo(SkillType);
		SkillLevel_t      SkillLevel = pOustersSkillSlot->getExpLevel();

		SkillInput input(pOusters, pOustersSkillSlot);
		SkillOutput output;
		computeOutput(input, output);

		int  RequiredMP  = (int)pSkillInfo->getConsumeMP();
		bool bManaCheck  = hasEnoughMana(pOusters, RequiredMP);
		bool bTimeCheck  = verifyRunTime(pOustersSkillSlot);
		bool bRangeCheck = verifyDistance(pOusters, pTargetCreature, output.Range);
		bool bHitRoll    = HitRoll::isSuccess(pOusters, pTargetCreature, SkillLevel/2);
		bool bCanHit     = canHit(pOusters, pTargetCreature, SkillType) && canAttack(pOusters, pTargetCreature);
		bool bPK         = verifyPK(pOusters, pTargetCreature);
		bool bEffected	 = pOusters->hasRelicItem() 
							|| pOusters->isFlag(Effect::EFFECT_CLASS_HAS_FLAG)
							|| pOusters->isFlag(Effect::EFFECT_CLASS_HAS_SWEEPER);

		if (bManaCheck && bTimeCheck && bRangeCheck && bHitRoll && bCanHit && bPK && !bEffected )
		{
			// ������ PC�� �������ش�.
			if (pZone->moveFastPC(pOusters, pOusters->getX(), pOusters->getY(), pTargetCreature->getX(), pTargetCreature->getY(), getSkillType())) 
			{
				decreaseMana(pOusters, RequiredMP, _GCSkillToObjectOK1);

				bool bCriticalHit = false;

				// �������� �ش�.
				Damage_t Damage = computeDamage(pOusters, pTargetCreature, 0, bCriticalHit) + output.Damage;
				setDamage(pTargetCreature, Damage, pOusters, SkillType, &_GCSkillToObjectOK2, &_GCSkillToObjectOK1);
				computeAlignmentChange(pTargetCreature, Damage, pOusters, &_GCSkillToObjectOK2, &_GCSkillToObjectOK1);
				decreaseDurability( pOusters, pTargetCreature, pSkillInfo, &_GCSkillToObjectOK1, &_GCSkillToObjectOK2 );

				EffectSuddenBlast* pEffect = new EffectSuddenBlast(pTargetCreature);
				pEffect->setDamage(Damage);
				pEffect->setTick(4);
				pEffect->setNextTime(4);
				pEffect->setTimes(2);
				pEffect->setCasterOID( pOusters->getObjectID() );
				pTargetCreature->addEffect( pEffect );

				// ��Ŷ�� �غ��ϰ� ������.
				_GCSkillToObjectOK1.setSkillType(SkillType);
				_GCSkillToObjectOK1.setCEffectID(CEffectID);
				_GCSkillToObjectOK1.setTargetObjectID(TargetObjectID);
				_GCSkillToObjectOK1.setDuration(0);

				pPlayer->sendPacket(&_GCSkillToObjectOK1);
				_GCSkillToObjectOK2.setObjectID(pOusters->getObjectID());
				_GCSkillToObjectOK2.setSkillType(SkillType);
				_GCSkillToObjectOK2.setDuration(0);

				if (pTargetCreature->isPC()) 
				{
					Player* pTargetPlayer = pTargetCreature->getPlayer();
					Assert(pTargetPlayer != NULL);
					pTargetPlayer->sendPacket(&_GCSkillToObjectOK2);
				} 
				else 
				{
					Monster * pMonster = dynamic_cast<Monster*>(pTargetCreature);
					pMonster->addEnemy(pOusters);
				}

				pOustersSkillSlot->setRunTime(output.Delay);

			} 
			else 
			{
				executeSkillFailNormal(pOusters, getSkillType(), pTargetCreature);
			}
		} 
		else 
		{
			executeSkillFailNormal(pOusters, getSkillType(), pTargetCreature);
		}
	} 
	catch (Throwable & t) 
	{
		executeSkillFailException(pOusters, getSkillType());
	}

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;

	__END_CATCH
}

SuddenBlast g_SuddenBlast;
