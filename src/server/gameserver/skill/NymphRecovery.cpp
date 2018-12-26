//////////////////////////////////////////////////////////////////////////////
// Filename    : NymphRecovery.cpp
// Written by  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "NymphRecovery.h"
#include "EffectYellowPoisonToCreature.h"

#include "Gpackets/GCSkillToObjectOK1.h"
#include "Gpackets/GCSkillToObjectOK2.h"
#include "Gpackets/GCSkillToObjectOK5.h"
#include "Gpackets/GCSkillToSelfOK1.h"
#include "Gpackets/GCSkillToSelfOK2.h"
#include "Gpackets/GCStatusCurrentHP.h"
#include "Gpackets/GCRemoveEffect.h"

//////////////////////////////////////////////////////////////////////////////
// �����̾� ������Ʈ �ڵ鷯
//////////////////////////////////////////////////////////////////////////////
void NymphRecovery::execute(Ousters* pOusters, ObjectID_t TargetObjectID, OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID)
	
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << "begin " << endl;

	Assert(pOusters != NULL);
	Assert(pOustersSkillSlot != NULL);

	BYTE Grade = 0;
	if ( pOustersSkillSlot->getExpLevel() < 15 ) Grade = 0;
	else if ( pOustersSkillSlot->getExpLevel() < 30 ) Grade = 1;
	else Grade = 2;

	try 
	{
		Player* pPlayer = pOusters->getPlayer();
		Zone* pZone = pOusters->getZone();
		Assert(pPlayer != NULL);
		Assert(pZone != NULL);

		Item* pWeapon = pOusters->getWearItem(Ousters::WEAR_RIGHTHAND);
		if (pWeapon == NULL || pWeapon->getItemClass() != Item::ITEM_CLASS_OUSTERS_WRISTLET || !pOusters->isRealWearingEx(Ousters::WEAR_RIGHTHAND))
		{
			executeSkillFailException(pOusters, pOustersSkillSlot->getSkillType(), Grade);
			return;
		}

		Creature* pTargetCreature = pZone->getCreature(TargetObjectID);
		//Assert(pTargetCreature != NULL);

		// NoSuch����. by sigi. 2002.5.2
		if (pTargetCreature==NULL
			|| !pTargetCreature->isOusters())
		{
			executeSkillFailException(pOusters, getSkillType(), Grade);
			//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " end " << endl;
			return;
		}

		Ousters* pTargetOusters = dynamic_cast<Ousters*>(pTargetCreature);

		GCSkillToObjectOK1 _GCSkillToObjectOK1;
		GCSkillToObjectOK2 _GCSkillToObjectOK2;
		GCSkillToObjectOK5 _GCSkillToObjectOK5;

		SkillType_t       SkillType  = pOustersSkillSlot->getSkillType();
		SkillInfo*        pSkillInfo = g_pSkillInfoManager->getSkillInfo(SkillType);

		int  RequiredMP  = (int)pSkillInfo->getConsumeMP() + pOustersSkillSlot->getExpLevel();
		bool bManaCheck  = hasEnoughMana(pOusters, RequiredMP);
		bool bTimeCheck  = verifyRunTime(pOustersSkillSlot);
		bool bRangeCheck = verifyDistance(pOusters, pTargetCreature, pSkillInfo->getRange()) && canHit( pOusters, pTargetCreature, SkillType, pOustersSkillSlot->getExpLevel() );
		bool bHitRoll    = HitRoll::isSuccessMagic(pOusters, pSkillInfo, pOustersSkillSlot);
		bool bSatisfyRequire	= pOusters->satisfySkillRequire( pSkillInfo );
		bool bHPCheck	= pTargetOusters->getHP(ATTR_MAX) > pTargetOusters->getHP() || pTargetOusters->getMP(ATTR_MAX) > pTargetOusters->getMP();

		ZoneCoord_t targetX = pTargetCreature->getX();
		ZoneCoord_t targetY = pTargetCreature->getY();
		bool bEffected       = false; // �ƹ� ���̳� �ɷ������� �Ҵ�.
		bool bYellowPoison   = false; // YellowPoison�� ġ���ұ��� ����

		EffectYellowPoisonToCreature* pEffectYellowPoisonToCreature = NULL;

		if (pTargetCreature->isEffect(Effect::EFFECT_CLASS_YELLOW_POISON_TO_CREATURE)) 
		{
			pEffectYellowPoisonToCreature = (EffectYellowPoisonToCreature*)pTargetCreature->findEffect(Effect::EFFECT_CLASS_YELLOW_POISON_TO_CREATURE);
			Assert(pEffectYellowPoisonToCreature != NULL);

			bYellowPoison = HitRoll::isSuccessCurePoison(60, 100, 20, pEffectYellowPoisonToCreature->getLevel());
			bEffected = true;
		}

		if (bManaCheck && bTimeCheck && bRangeCheck && bHitRoll && bSatisfyRequire && bHPCheck)
		{
			// ������ ���δ�.
			decreaseMana(pOusters, RequiredMP, _GCSkillToObjectOK1);

			// ����Ʈ�� ȿ���� ���ӽð��� ����Ѵ�.
			SkillInput input(pOusters, pOustersSkillSlot);
			SkillOutput output;
			input.TargetType = SkillInput::TARGET_OTHER;
			computeOutput(input, output);

			GCRemoveEffect gcRemoveEffect;
			gcRemoveEffect.setObjectID(pTargetCreature->getObjectID());
			if (bYellowPoison)
			{
				pEffectYellowPoisonToCreature->setDeadline(0);
				pTargetCreature->removeFlag(Effect::EFFECT_CLASS_YELLOW_POISON_TO_CREATURE);
				gcRemoveEffect.addEffectList(Effect::EFFECT_CLASS_YELLOW_POISON_TO_CREATURE);
			}

			HP_t final = min( (int)pTargetOusters->getHP(ATTR_MAX), pTargetOusters->getHP() + output.Damage );
			if ( final > pTargetOusters->getHP(ATTR_MAX) - pTargetOusters->getSilverDamage() )
			{
				pTargetOusters->setSilverDamage( pTargetOusters->getHP(ATTR_MAX) - final );
				_GCSkillToObjectOK2.addShortData(MODIFY_SILVER_DAMAGE, pTargetOusters->getSilverDamage());
			}

			if ( pTargetOusters->getHP() != final )
			{
				pTargetOusters->setHP( final );
				_GCSkillToObjectOK2.addShortData(MODIFY_CURRENT_HP, final);
			}

			GCStatusCurrentHP gcHP;
			gcHP.setObjectID( pTargetOusters->getObjectID() );
			gcHP.setCurrentHP( final );

			if ( pTargetOusters->getMP(ATTR_MAX) > pTargetOusters->getMP() )
			{
				final = min( (int)pTargetOusters->getMP(ATTR_MAX), pTargetOusters->getMP() + output.Damage );
				if ( pTargetOusters->getMP() != final )
				{
					pTargetOusters->setMP( final );
					_GCSkillToObjectOK2.addShortData(MODIFY_CURRENT_MP, final);
				}
			}

			// ��Ŷ�� �غ��ؼ� ������.
			_GCSkillToObjectOK1.setSkillType(SkillType);
			_GCSkillToObjectOK1.setCEffectID(CEffectID);
			_GCSkillToObjectOK1.setTargetObjectID(TargetObjectID);
			_GCSkillToObjectOK1.setGrade(Grade);

			_GCSkillToObjectOK2.setObjectID(pOusters->getObjectID());
			_GCSkillToObjectOK2.setSkillType(SkillType);
			_GCSkillToObjectOK2.setGrade(Grade);

			_GCSkillToObjectOK5.setObjectID(pOusters->getObjectID());
			_GCSkillToObjectOK5.setSkillType(SkillType);
			_GCSkillToObjectOK5.setTargetObjectID (TargetObjectID);
			_GCSkillToObjectOK5.setGrade(Grade);

			// Send Packet
			pPlayer->sendPacket(&_GCSkillToObjectOK1);

			if (pOusters != pTargetCreature && pTargetCreature->isPC()) 
			{
				Player* pTargetPlayer = pTargetCreature->getPlayer();
				Assert(pTargetPlayer != NULL);
				pTargetPlayer->sendPacket(&_GCSkillToObjectOK2);
			}

			list<Creature*> cList;
			cList.push_back(pOusters);
			cList.push_back(pTargetCreature);

			pZone->broadcastPacket(targetX, targetY, &gcRemoveEffect);
		
			pZone->broadcastPacket(pOusters->getX(), pOusters->getY(),  &_GCSkillToObjectOK5 , cList);
			pZone->broadcastPacket(pTargetOusters->getX(), pTargetOusters->getY(),  &gcHP, pTargetOusters);

			pOustersSkillSlot->setRunTime(output.Delay);
		} 
		else 
		{
			executeSkillFailNormal(pOusters, getSkillType(), pTargetCreature, Grade);
		}
	} 
	catch (Throwable & t) 
	{
		executeSkillFailException(pOusters, getSkillType(), Grade);
	}

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " end " << endl;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// �����̾� ���� �ڵ鷯
//////////////////////////////////////////////////////////////////////////////
void NymphRecovery::execute(Ousters* pOusters, OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID)
	
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << "begin " << endl;

	Assert(pOusters != NULL);
	Assert(pOustersSkillSlot != NULL);

	BYTE Grade = 0;
	if ( pOustersSkillSlot->getExpLevel() < 15 ) Grade = 0;
	else if ( pOustersSkillSlot->getExpLevel() < 30 ) Grade = 1;
	else Grade = 2;

	try 
	{
		Player* pPlayer = pOusters->getPlayer();
		Zone* pZone = pOusters->getZone();

		Assert(pPlayer != NULL);
		Assert(pZone != NULL);

		Item* pWeapon = pOusters->getWearItem(Ousters::WEAR_RIGHTHAND);
		if (pWeapon == NULL || pWeapon->getItemClass() != Item::ITEM_CLASS_OUSTERS_WRISTLET || !pOusters->isRealWearingEx(Ousters::WEAR_RIGHTHAND))
		{
			executeSkillFailException(pOusters, pOustersSkillSlot->getSkillType(), Grade);
			return;
		}

		GCSkillToSelfOK1 _GCSkillToSelfOK1;
		GCSkillToSelfOK2 _GCSkillToSelfOK2;

		SkillType_t       SkillType  = pOustersSkillSlot->getSkillType();
		SkillInfo*        pSkillInfo = g_pSkillInfoManager->getSkillInfo(SkillType);

		int  RequiredMP  = (int)pSkillInfo->getConsumeMP() + pOustersSkillSlot->getExpLevel();
		bool bManaCheck  = hasEnoughMana(pOusters, RequiredMP);
		bool bTimeCheck  = verifyRunTime(pOustersSkillSlot);
		bool bRangeCheck = checkZoneLevelToUseSkill(pOusters);
		bool bHitRoll    = HitRoll::isSuccessMagic(pOusters, pSkillInfo, pOustersSkillSlot);
		bool bSatisfyRequire	= pOusters->satisfySkillRequire( pSkillInfo );
		bool bHPCheck	= pOusters->getHP(ATTR_MAX) > pOusters->getHP() || pOusters->getMP(ATTR_MAX) > pOusters->getMP();

		if (bManaCheck && bTimeCheck && bRangeCheck && bHitRoll && bSatisfyRequire && bHPCheck)
		{
			decreaseMana(pOusters, RequiredMP, _GCSkillToSelfOK1);

			// ����Ʈ�� ȿ���� ���ӽð��� ����Ѵ�.
			SkillInput input(pOusters, pOustersSkillSlot);
			SkillOutput output;
			input.TargetType = SkillInput::TARGET_SELF;
			computeOutput(input, output);

			HP_t final = min( (int)pOusters->getHP(ATTR_MAX), pOusters->getHP() + output.Damage );
			if ( final > pOusters->getHP(ATTR_MAX) - pOusters->getSilverDamage() )
			{
				pOusters->setSilverDamage( pOusters->getHP(ATTR_MAX) - final );
				_GCSkillToSelfOK1.addShortData(MODIFY_SILVER_DAMAGE, pOusters->getSilverDamage());
			}

			if ( pOusters->getHP() != final )
			{
				pOusters->setHP( final );
				_GCSkillToSelfOK1.addShortData(MODIFY_CURRENT_HP, final);
			}

			GCStatusCurrentHP gcHP;
			gcHP.setObjectID( pOusters->getObjectID() );
			gcHP.setCurrentHP( final );

			if ( pOusters->getMP(ATTR_MAX) > pOusters->getMP() )
			{
				final = min( (int)pOusters->getMP(ATTR_MAX), pOusters->getMP() + output.Damage );
				if ( pOusters->getMP() != final )
				{
					pOusters->setMP( final );
					_GCSkillToSelfOK1.addShortData(MODIFY_CURRENT_MP, final);
				}
			}

			// ��Ŷ�� �غ��ؼ� ������.
			ZoneCoord_t myX = pOusters->getX();
			ZoneCoord_t myY = pOusters->getY();

			_GCSkillToSelfOK1.setSkillType(SkillType);
			_GCSkillToSelfOK1.setCEffectID(CEffectID);
			_GCSkillToSelfOK1.setGrade(Grade);
			
			_GCSkillToSelfOK2.setObjectID(pOusters->getObjectID());
			_GCSkillToSelfOK2.setSkillType(SkillType);
			_GCSkillToSelfOK2.setGrade(Grade);

			pPlayer->sendPacket(&_GCSkillToSelfOK1);
			pZone->broadcastPacket(myX, myY, &_GCSkillToSelfOK2, pOusters);
			pZone->broadcastPacket(myX, myY, &gcHP, pOusters);

			pOustersSkillSlot->setRunTime(output.Delay);
		} 
		else 
		{
			executeSkillFailNormal(pOusters, getSkillType(), NULL, Grade);
		}
	} 
	catch (Throwable & t) 
	{
		executeSkillFailException(pOusters, getSkillType(), Grade);
	}

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " end " << endl;

	__END_CATCH
}

NymphRecovery g_NymphRecovery;
