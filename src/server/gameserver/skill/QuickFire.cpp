//////////////////////////////////////////////////////////////////////////////
// Filename    : QuickFire.cpp
// Written by  : elca@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "QuickFire.h"
#include "Gpackets/GCAttackArmsOK1.h"
#include "Gpackets/GCAttackArmsOK2.h"
#include "Gpackets/GCAttackArmsOK3.h"
#include "Gpackets/GCAttackArmsOK4.h"
#include "Gpackets/GCAttackArmsOK5.h"
#include "ItemUtil.h"

//////////////////////////////////////////////////////////////////////////////
// �����̾� ������Ʈ
//////////////////////////////////////////////////////////////////////////////
void QuickFire::execute (Slayer* pSlayer, ObjectID_t TargetObjectID,  SkillSlot* pSkillSlot, CEffectID_t CEffectID)
	throw (Error)
{
	__BEGIN_TRY __BEGIN_DEBUG

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

		// NoSuch����. by sigi. 2002.5.2
		if (pTargetCreature==NULL
			|| !canAttack( pSlayer, pTargetCreature )
			|| pTargetCreature->isNPC()) 
		{
			executeSkillFailException(pSlayer, getSkillType());
			//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;
			return;
		}

		GCAttackArmsOK1 _GCAttackArmsOK1;
		GCAttackArmsOK2 _GCAttackArmsOK2;
		GCAttackArmsOK3 _GCAttackArmsOK3;
		GCAttackArmsOK4 _GCAttackArmsOK4;
		GCAttackArmsOK5 _GCAttackArmsOK5;

		// ��� �ִ� ���Ⱑ ���ų�, �� �迭 ���Ⱑ �ƴ϶�� ����� �� �� ����.
		// �� �迭 ���� �߿����� SG�� SR�� QuickFire�� �� ���� ����.
		// SG, SR �� ���� �� �� �ִ�.
		// 2003. 1. 14  by bezz
		Item* pWeapon = pSlayer->getWearItem(Slayer::WEAR_RIGHTHAND);
		if (pWeapon == NULL || isArmsWeapon(pWeapon) == false )
//			pWeapon->getItemClass() == Item::ITEM_CLASS_SG || 
//			pWeapon->getItemClass() == Item::ITEM_CLASS_SR)
		{
			executeSkillFailException(pSlayer, getSkillType());
			//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;
			return;
		}

		bool bIncreaseExp = pSlayer->isRealWearingEx(Slayer::WEAR_RIGHTHAND);

		SkillType_t       SkillType  = pSkillSlot->getSkillType();
		SkillInfo*        pSkillInfo = g_pSkillInfoManager->getSkillInfo(SkillType);
		SkillDomainType_t DomainType = pSkillInfo->getDomainType();
		SkillLevel_t      SkillLevel = pSkillSlot->getExpLevel();

		SkillInput input(pSlayer, pSkillSlot);
		SkillOutput output;
		computeOutput(input, output);

		// ���Ƽ ���� ����Ѵ�.
		int ToHitPenalty = getPercentValue(pSlayer->getToHit(), output.ToHit); 

		int  RequiredMP  = (int)pSkillInfo->getConsumeMP();
		bool bManaCheck   = hasEnoughMana(pSlayer, RequiredMP);
		bool bTimeCheck   = verifyRunTime(pSkillSlot);
		bool bRangeCheck  = verifyDistance(pSlayer, pTargetCreature, pWeapon->getRange());
		bool bBulletCheck = (getRemainBullet(pWeapon) > 0) ? true : false;
		bool bHitRoll     = HitRoll::isSuccess(pSlayer, pTargetCreature, ToHitPenalty);
		bool bPK          = verifyPK(pSlayer, pTargetCreature);

		// �Ѿ� ���ڴ� ������ ����߸���.
		Bullet_t RemainBullet = 0;
		if (bBulletCheck)
		{
			// �Ѿ� ���ڸ� ����߸���, �����ϰ�, ���� �Ѿ� ���ڸ� �޾ƿ´�.
			decreaseBullet(pWeapon);
			// �ѹ߾������� ������ �ʿ� ����. by sigi. 2002.5.9
			//pWeapon->save(pSlayer->getName(), STORAGE_GEAR, 0, Slayer::WEAR_RIGHTHAND, 0);
			RemainBullet = getRemainBullet(pWeapon);
		}

		if (bManaCheck && bTimeCheck && bRangeCheck && bBulletCheck && bHitRoll && bPK)
		{
			//cout << pSlayer->getName().c_str() << " Attack OK" << endl;
			decreaseMana(pSlayer, RequiredMP, _GCAttackArmsOK1);

			_GCAttackArmsOK5.setSkillSuccess(true);
			_GCAttackArmsOK1.setSkillSuccess(true);

			bool bCriticalHit = false;

			// �������� ����ϰ�, quickfire ���Ƽ�� ���Ѵ�.
			// output.Damage�� �����̱� ������, %���� ���� ���ϸ� �ᱹ ���� ���� �ȴ�.
			int Damage = computeDamage(pSlayer, pTargetCreature, SkillLevel/5, bCriticalHit);
			Damage += getPercentValue(Damage, output.Damage);
			Damage = max(0, Damage);

			//cout << "QuickFireDamage:" << Damage << endl;

			// �������� �����Ѵ�.
			setDamage(pTargetCreature, Damage, pSlayer, SkillType, &_GCAttackArmsOK2, &_GCAttackArmsOK1);
			computeAlignmentChange(pTargetCreature, Damage, pSlayer, &_GCAttackArmsOK2, &_GCAttackArmsOK1);

			// ũ��Ƽ�� ��Ʈ��� ������ �ڷ� �������� �Ѵ�.
			if (bCriticalHit)
			{
				knockbackCreature(pZone, pTargetCreature, pSlayer->getX(), pSlayer->getY());
			}

			/*
			// 80% Ȯ���θ� �ɷ�ġ�� ����Ѵ�.
			// ������ �����̾ �ƴ� ��쿡�� ����ġ�� ����Ѵ�.
			if (Random(1, 100) < 80 && !pTargetCreature->isSlayer())
			{
			*/
			if( !pTargetCreature->isSlayer() ) 
			{
				if (bIncreaseExp)
				{
					shareAttrExp(pSlayer, Damage , 1, 8, 1, _GCAttackArmsOK1);
					increaseDomainExp(pSlayer, DomainType, pSkillInfo->getPoint(), _GCAttackArmsOK1, pTargetCreature->getLevel());
					increaseSkillExp(pSlayer, DomainType,  pSkillSlot, pSkillInfo, _GCAttackArmsOK1);
				}

				increaseAlignment(pSlayer, pTargetCreature, _GCAttackArmsOK1);
			}
			//}

			if (pTargetCreature->isPC()) 
			{
				Player* pTargetPlayer = pTargetCreature->getPlayer();
				if (pTargetPlayer != NULL) 
				{ 
					_GCAttackArmsOK2.setSkillType(getSkillType());
					_GCAttackArmsOK2.setObjectID(pSlayer->getObjectID());
					pTargetPlayer->sendPacket(&_GCAttackArmsOK2);
				}
			} 
			else if (pTargetCreature->isMonster())
			{
				Monster* pMonster = dynamic_cast<Monster*>(pTargetCreature);
				pMonster->addEnemy(pSlayer);
			}

			// �����ڿ� ����� ������ ������ ����Ʈ��.
			decreaseDurability(pSlayer, pTargetCreature, NULL, &_GCAttackArmsOK1, &_GCAttackArmsOK2);

			ZoneCoord_t targetX = pTargetCreature->getX();
			ZoneCoord_t targetY = pTargetCreature->getY();
			ZoneCoord_t myX     = pSlayer->getX();
			ZoneCoord_t myY     = pSlayer->getY();
			
			_GCAttackArmsOK1.setSkillType(getSkillType());
			_GCAttackArmsOK1.setObjectID(TargetObjectID);
			_GCAttackArmsOK1.setBulletNum(RemainBullet);

			_GCAttackArmsOK3.setSkillType(getSkillType());
			_GCAttackArmsOK3.setObjectID(pSlayer->getObjectID());
			_GCAttackArmsOK3.setTargetXY (targetX, targetY);
			
			_GCAttackArmsOK4.setSkillType(getSkillType());
			_GCAttackArmsOK4.setTargetObjectID (TargetObjectID);
			
			_GCAttackArmsOK5.setSkillType(getSkillType());
			_GCAttackArmsOK5.setObjectID(pSlayer->getObjectID());
			_GCAttackArmsOK5.setTargetObjectID (TargetObjectID);

			pPlayer->sendPacket(&_GCAttackArmsOK1);

			list<Creature *> cList;
			cList.push_back(pTargetCreature);
			cList.push_back(pSlayer);
			cList = pZone->broadcastSkillPacket(myX, myY, targetX, targetY, &_GCAttackArmsOK5, cList);
			pZone->broadcastPacket(myX, myY, &_GCAttackArmsOK3, cList);
			pZone->broadcastPacket(targetX, targetY, &_GCAttackArmsOK4, cList);

			pSkillSlot->setRunTime(output.Delay);
		} 
		else 
		{
			executeSkillFailNormalWithGun(pSlayer, getSkillType(), pTargetCreature, RemainBullet);
			//cout << pSlayer->getName().c_str() << " Fail : " 
			//	<< (int)bManaCheck << (int)bTimeCheck << (int)bRangeCheck 
			//	<< (int)bBulletCheck << (int)bHitRoll << (int)bPK << endl;
		}
	} 
	catch (Throwable &t) 
	{
		executeSkillFailException(pSlayer, getSkillType());
	}

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;

	__END_DEBUG __END_CATCH
}

void QuickFire::execute(Monster* pMonster, Creature* pEnemy) 
	throw(Error)
{
	__BEGIN_TRY __BEGIN_DEBUG

	//cout << "QuickFire::executeMonster" << endl;

	try 
	{
		BYTE RemainBullet = 0;

		Zone* pZone = pMonster->getZone();
		Assert(pZone != NULL);

		// NoSuch����. by sigi. 2002.5.2
		if (pEnemy==NULL
			|| pEnemy->isNPC()) 
		{
			//cout << "WrongEnemy" << endl;
			executeSkillFailNormalWithGun(pMonster, getSkillType(), pEnemy, RemainBullet);
			return;
		}

		GCAttackArmsOK2 _GCAttackArmsOK2;
		GCAttackArmsOK3 _GCAttackArmsOK3;
		GCAttackArmsOK4 _GCAttackArmsOK4;
		GCAttackArmsOK5 _GCAttackArmsOK5;

		SkillType_t       SkillType  = getSkillType();
		SkillInfo*        pSkillInfo = g_pSkillInfoManager->getSkillInfo(SkillType);

		SkillInput input(pMonster);
		SkillOutput output;
		computeOutput(input, output);

		// ���Ƽ ���� ����Ѵ�.
		int ToHitPenalty = getPercentValue(pMonster->getToHit(), output.ToHit); 

		bool bRangeCheck  = verifyDistance(pMonster, pEnemy, pSkillInfo->getRange());
		bool bHitRoll     = HitRoll::isSuccess(pMonster, pEnemy, ToHitPenalty);

		if (bRangeCheck && bHitRoll)
		{
			_GCAttackArmsOK5.setSkillSuccess(true);

			ObjectID_t TargetObjectID = pEnemy->getObjectID();

			bool bCriticalHit = false;

			// �������� ����ϰ�, quickfire ���Ƽ�� ���Ѵ�.
			// output.Damage�� �����̱� ������, %���� ���� ���ϸ� �ᱹ ���� ���� �ȴ�.
			int Damage = computeDamage(pMonster, pEnemy, 0, bCriticalHit);
			Damage += getPercentValue(Damage, output.Damage);
			Damage = max(0, Damage);

			//cout << "QuickFireDamage:" << Damage << endl;

			// �������� �����Ѵ�.
			setDamage(pEnemy, Damage, pMonster, SkillType, &_GCAttackArmsOK2);
			//computeAlignmentChange(pEnemy, Damage, pMonster, &_GCAttackArmsOK2, &_GCAttackArmsOK1);

			// ũ��Ƽ�� ��Ʈ��� ������ �ڷ� �������� �Ѵ�.
			if (bCriticalHit)
			{
				knockbackCreature(pZone, pEnemy, pMonster->getX(), pMonster->getY());
			}

			if (pEnemy->isPC()) 
			{
				Player* pTargetPlayer = pEnemy->getPlayer();
				if (pTargetPlayer != NULL) 
				{ 
					_GCAttackArmsOK2.setSkillType(getSkillType());
					_GCAttackArmsOK2.setObjectID(pMonster->getObjectID());
					pTargetPlayer->sendPacket(&_GCAttackArmsOK2);
				}
			} 
			else if (pEnemy->isMonster())
			{
				Monster* pOtherMonster = dynamic_cast<Monster*>(pEnemy);
				pOtherMonster->addEnemy(pMonster);
			}

			// �����ڿ� ����� ������ ������ ����Ʈ��.
			decreaseDurability(pMonster, pEnemy, NULL, NULL, &_GCAttackArmsOK2);

			ZoneCoord_t targetX = pEnemy->getX();
			ZoneCoord_t targetY = pEnemy->getY();
			ZoneCoord_t myX     = pMonster->getX();
			ZoneCoord_t myY     = pMonster->getY();
			
			_GCAttackArmsOK3.setSkillType(getSkillType());
			_GCAttackArmsOK3.setObjectID(pMonster->getObjectID());
			_GCAttackArmsOK3.setTargetXY (targetX, targetY);
			
			_GCAttackArmsOK4.setSkillType(getSkillType());
			_GCAttackArmsOK4.setTargetObjectID (TargetObjectID);
			
			_GCAttackArmsOK5.setSkillType(getSkillType());
			_GCAttackArmsOK5.setObjectID(pMonster->getObjectID());
			_GCAttackArmsOK5.setTargetObjectID (TargetObjectID);

			list<Creature *> cList;
			cList.push_back(pEnemy);
			cList.push_back(pMonster);
			cList = pZone->broadcastSkillPacket(myX, myY, targetX, targetY, &_GCAttackArmsOK5, cList);
			pZone->broadcastPacket(myX, myY, &_GCAttackArmsOK3, cList);
			pZone->broadcastPacket(targetX, targetY, &_GCAttackArmsOK4, cList);

			//pSkillSlot->setRunTime(output.Delay);
		} 
		else 
		{
			//cout << "Failed: " << (int)bRangeCheck << ", " << (int)bHitRoll << endl;
			executeSkillFailNormalWithGun(pMonster, getSkillType(), pEnemy, RemainBullet);
		}
	} 
	catch (Throwable &t) 
	{
		//cout << t.toString().c_str() << endl;
		executeSkillFailException(pMonster, getSkillType());
	}


	//cout << "QuickFire::executeMonster OK" << endl;

	__END_DEBUG __END_CATCH
}

QuickFire g_QuickFire;
