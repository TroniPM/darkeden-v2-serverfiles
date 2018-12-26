//////////////////////////////////////////////////////////////////////////////
// Filename    : HeadShot.cpp
// Written by  : elca@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "HeadShot.h"
#include "Gpackets/GCSkillToObjectOK1.h"
#include "Gpackets/GCSkillToObjectOK2.h"
#include "Gpackets/GCSkillToObjectOK3.h"
#include "Gpackets/GCSkillToObjectOK4.h"
#include "Gpackets/GCSkillToObjectOK5.h"
#include "Gpackets/GCSkillToTileOK1.h"
#include "Gpackets/GCSkillToTileOK2.h"
#include "Gpackets/GCSkillToTileOK3.h"
#include "Gpackets/GCSkillToTileOK4.h"
#include "Gpackets/GCSkillToTileOK5.h"
#include "ItemUtil.h"

//////////////////////////////////////////////////////////////////////////////
// �����̾� ������Ʈ �ڵ鷯
//////////////////////////////////////////////////////////////////////////////
void HeadShot::execute(Slayer* pSlayer, ObjectID_t TargetObjectID, SkillSlot* pSkillSlot, CEffectID_t CEffectID)
	
{
	__BEGIN_TRY
	__BEGIN_DEBUG

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
			|| !canAttack( pSlayer, pTargetCreature )
			|| pTargetCreature->isNPC()) 
		{
			executeSkillFailException(pSlayer, getSkillType());
			//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;
			return;
		}

		bool bIncreaseDomainExp = pSlayer->isRealWearingEx(Slayer::WEAR_RIGHTHAND);

		GCSkillToObjectOK1 _GCSkillToObjectOK1;
		GCSkillToObjectOK2 _GCSkillToObjectOK2;
		GCSkillToObjectOK3 _GCSkillToObjectOK3;
		GCSkillToObjectOK4 _GCSkillToObjectOK4;
		GCSkillToObjectOK5 _GCSkillToObjectOK5;

		// �����ϰ� �ִ� ���Ⱑ ���̰ų�, ���� �ƴϰų�, SR�̶�� �� ����� �� �� ����.
		Item* pWeapon = pSlayer->getWearItem(Slayer::WEAR_RIGHTHAND);
		if (pWeapon == NULL 
			|| !isArmsWeapon(pWeapon))
			// SR�� ��밡���ϰ� �Ѵ�. by sigi. 2002.12.3
			//|| pWeapon->getItemClass() == Item::ITEM_CLASS_SR) 
		{
			executeSkillFailException(pSlayer, getSkillType());
			//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;
			return;
		}

		SkillType_t       SkillType  = pSkillSlot->getSkillType();
		SkillInfo*        pSkillInfo = g_pSkillInfoManager->getSkillInfo(SkillType);
		SkillDomainType_t DomainType = pSkillInfo->getDomainType();
		SkillLevel_t      SkillLevel = pSkillSlot->getExpLevel();

		int  RequiredMP   = (int)pSkillInfo->getConsumeMP();
		bool bManaCheck   = hasEnoughMana(pSlayer, RequiredMP);
		bool bTimeCheck   = verifyRunTime(pSkillSlot);
		bool bRangeCheck  = verifyDistance(pSlayer, pTargetCreature, pSkillInfo->getRange());// �����Ÿ� 3���� ����
		bool bBulletCheck = (getRemainBullet(pWeapon) > 0) ? true : false;

		// �Ѿ� ���ڴ� ������ ����߸���.
		Bullet_t RemainBullet = 0;
		if (bBulletCheck)
		{
			decreaseBullet(pWeapon);
			// �ѹ߾������� ������ �ʿ� ����. by sigi. 2002.5.9
			//pWeapon->save(pSlayer->getName(), STORAGE_GEAR, 0, Slayer::WEAR_RIGHTHAND, 0);
			RemainBullet = getRemainBullet(pWeapon);
		}

		// ������, ���� ���ʽ�, ��ǥ�� ������ ���Ѵ�.
		int               ToHitBonus  = 0;
		int               DamageBonus = 0;
		ZoneCoord_t       myX         = pSlayer->getX();
		ZoneCoord_t       myY         = pSlayer->getY();
		ZoneCoord_t       targetX     = pTargetCreature->getX();
		ZoneCoord_t       targetY     = pTargetCreature->getY();
		Dir_t             dir         = calcDirection(myX, myY, targetX, targetY);

		int Splash = computeArmsWeaponSplashSize(pWeapon, myX, myY, targetX, targetY);

		// �Ÿ��� ���� ������ ���ʽ��� ����Ѵ�.
		SkillInput input(pSlayer, pSkillSlot);
		SkillOutput output;
		input.Range = getDistance(pSlayer->getX(), pSlayer->getY(), pTargetCreature->getX(), pTargetCreature->getY());
		computeOutput(input, output);

		////////////////////////////////////////////////////////////////////////////////
		// SG�� �ƴ� �ٸ� ���� ���
		////////////////////////////////////////////////////////////////////////////////
		if (Splash == 0)
		{
			ToHitBonus  = computeArmsWeaponToHitBonus(pWeapon, myX, myY, targetX, targetY);
			DamageBonus = computeArmsWeaponDamageBonus(pWeapon, myX, myY, targetX, targetY);

			bool bHitRoll = HitRoll::isSuccess(pSlayer, pTargetCreature, ToHitBonus);
			bool bPK      = verifyPK(pSlayer, pTargetCreature);

			if (bManaCheck && bTimeCheck && bRangeCheck && bHitRoll && bBulletCheck && bPK)
			{
				decreaseMana(pSlayer, RequiredMP, _GCSkillToObjectOK1);

				bool bCriticalHit = false;

				Damage_t Damage = computeDamage(pSlayer, pTargetCreature, SkillLevel/5, bCriticalHit) + output.Damage + DamageBonus;
				setDamage(pTargetCreature, Damage, pSlayer, SkillType, &_GCSkillToObjectOK2, &_GCSkillToObjectOK1);
				computeAlignmentChange(pTargetCreature, Damage, pSlayer, &_GCSkillToObjectOK2, &_GCSkillToObjectOK1);

				// ũ��Ƽ�� ��Ʈ��� ������ �ڷ� �������� �Ѵ�.
				if (bCriticalHit)
				{
					knockbackCreature(pZone, pTargetCreature, pSlayer->getX(), pSlayer->getY());
				}

				if (!pTargetCreature->isSlayer())
				{
					// ����ġ�� �÷��ش�.
					if ( bIncreaseDomainExp )
					{
						shareAttrExp(pSlayer, Damage , 1, 8, 1, _GCSkillToObjectOK1);
						increaseDomainExp(pSlayer, DomainType, pSkillInfo->getPoint(), _GCSkillToObjectOK1, pTargetCreature->getLevel());
						increaseSkillExp(pSlayer, DomainType, pSkillSlot, pSkillInfo, _GCSkillToObjectOK1);
					}
					increaseAlignment(pSlayer, pTargetCreature, _GCSkillToObjectOK1);
				}

				// �Ѿ� ���� ����߸���, ���̺��ϰ�, ���� �Ѿ��� �ް�, �������� ����߸���.
				decreaseDurability(pSlayer, pTargetCreature, pSkillInfo, &_GCSkillToObjectOK1, &_GCSkillToObjectOK2);

				// ���� �������� �����ִٸ�, �Ѿ� ���ڸ� ����߸����, Ŭ���̾�Ʈ���� �˷��ش�.
				if (pSlayer->getWearItem(Slayer::WEAR_RIGHTHAND) != NULL) 
					_GCSkillToObjectOK1.addShortData(MODIFY_BULLET, RemainBullet);

				Coord_t targetX = pTargetCreature->getX();
				Coord_t targetY = pTargetCreature->getY();
				Coord_t myX     = pSlayer->getX();
				Coord_t myY     = pSlayer->getY();

				_GCSkillToObjectOK1.setSkillType(SkillType);
				_GCSkillToObjectOK1.setCEffectID(CEffectID);
				_GCSkillToObjectOK1.setTargetObjectID(TargetObjectID);
				_GCSkillToObjectOK1.setDuration(0);

				_GCSkillToObjectOK2.setObjectID(pSlayer->getObjectID());
				_GCSkillToObjectOK2.setSkillType(SkillType);
				_GCSkillToObjectOK2.setDuration(0);

				_GCSkillToObjectOK3.setObjectID(pSlayer->getObjectID());
				_GCSkillToObjectOK3.setSkillType(SkillType);
				_GCSkillToObjectOK3.setTargetXY (targetX, targetY);

				_GCSkillToObjectOK4.setSkillType(SkillType);
				_GCSkillToObjectOK4.setTargetObjectID(TargetObjectID);
				_GCSkillToObjectOK4.setDuration(0);

				_GCSkillToObjectOK5.setObjectID(pSlayer->getObjectID());
				_GCSkillToObjectOK5.setSkillType(SkillType);
				_GCSkillToObjectOK5.setTargetObjectID (TargetObjectID);
				_GCSkillToObjectOK5.setDuration(0);

				// Send Packet
				pPlayer->sendPacket(&_GCSkillToObjectOK1);

				if (pTargetCreature->isPC()) 
				{
					Player* pTargetPlayer = pTargetCreature->getPlayer();
					Assert(pTargetPlayer != NULL);
					pTargetPlayer->sendPacket(&_GCSkillToObjectOK2);
				} 
				else if (pTargetCreature->isMonster())
				{
					Monster* pMonster = dynamic_cast<Monster*>(pTargetCreature);
					pMonster->addEnemy(pSlayer);
				}

				list<Creature *> cList;
				cList.push_back(pTargetCreature);
				cList.push_back(pSlayer);
				cList = pZone->broadcastSkillPacket(myX, myY, targetX, targetY, &_GCSkillToObjectOK5, cList);
				pZone->broadcastPacket(myX, myY, &_GCSkillToObjectOK3, cList);
				pZone->broadcastPacket(targetX, targetY, &_GCSkillToObjectOK4, cList);

				pSkillSlot->setRunTime(output.Delay);
			} 
			else 
			{
				executeSkillFailNormalWithGun(pSlayer, getSkillType(), pTargetCreature, RemainBullet);
			}
		}
		////////////////////////////////////////////////////////////////////////////////
		// SG�� ��� ��弦 ���� ��������...
		////////////////////////////////////////////////////////////////////////////////
		else 
		{
			if (bManaCheck && bTimeCheck && bRangeCheck && bBulletCheck)
			{
				GCSkillToTileOK1  _GCSkillToTileOK1;
				GCSkillToTileOK2  _GCSkillToTileOK2;
				GCSkillToTileOK3  _GCSkillToTileOK3;
				GCSkillToTileOK4  _GCSkillToTileOK4;
				GCSkillToTileOK5  _GCSkillToTileOK5;
	
				decreaseMana(pSlayer, RequiredMP, _GCSkillToTileOK1);

				Damage_t Damage = 0;     // ���������� ���� �������� �����ϱ� ���� ����
				bool     bHit   = false; // �� ���̶� �¾Ҵ°��� �����ϱ� ���� ����

				Level_t maxEnemyLevel = 0;
				uint EnemyNum = 0;
			
				list<Creature*> creatureList;
				list<Creature*> cList;
				getSplashVictims(pZone, targetX, targetY, pTargetCreature->getCreatureClass(), creatureList, Splash);

				list<Creature*>::iterator itr = creatureList.begin();
				for (; itr != creatureList.end(); itr++)
				{
					Creature* pEnemy = (*itr);
					Assert(pEnemy != NULL);

					ToHitBonus  = computeArmsWeaponToHitBonus(pWeapon, myX, myY, pEnemy->getX(), pEnemy->getY());
					DamageBonus = computeArmsWeaponDamageBonus(pWeapon, myX, myY, pEnemy->getX(), pEnemy->getY());

					bool bInvokerCheck   = (pEnemy->getObjectID() == pSlayer->getObjectID()) ? true : false;
					bool bHitRoll        = HitRoll::isSuccess(pSlayer, pEnemy, ToHitBonus);
					bool bPK             = verifyPK(pSlayer, pEnemy);
					bool bZoneLevelCheck = checkZoneLevelToHitTarget(pEnemy);

					if (!bInvokerCheck && bHitRoll && bPK && bZoneLevelCheck)
					{
						bool bCriticalHit = false;

						Damage = computeDamage(pSlayer, pEnemy, SkillLevel/5, bCriticalHit) + output.Damage + DamageBonus;

						// ���� Ÿ���� �����ϰ��, ���÷��� �������� �Դµ�,
						// ���÷��� �������� �Ϲ� �������� 50%�̴�.
						if (pTargetCreature != pEnemy)
						{
							Damage = Damage/2;
						}

						ObjectID_t targetObjectID = pEnemy->getObjectID();
						cList.push_back(pEnemy);
						_GCSkillToTileOK1.addCListElement(targetObjectID);
						_GCSkillToTileOK2.addCListElement(targetObjectID);
						_GCSkillToTileOK5.addCListElement(targetObjectID);

						setDamage(pEnemy, Damage, pSlayer, getSkillType(), NULL, &_GCSkillToTileOK1);
						computeAlignmentChange(pEnemy, Damage, pSlayer, NULL, &_GCSkillToTileOK1);

						increaseAlignment(pSlayer, pEnemy, _GCSkillToTileOK1);

						// ũ��Ƽ�� ��Ʈ��� ������ �ڷ� �������� �Ѵ�.
						if (bCriticalHit)
						{
							knockbackCreature(pZone, pEnemy, myX, myY);
						}

						// �����̾ �ƴ� ��쿡�� hit�� �ɷ� �����Ѵ�.
						if (!pEnemy->isSlayer())
						{
							bHit = true;
							if ( maxEnemyLevel < pEnemy->getLevel() ) maxEnemyLevel = pEnemy->getLevel();
							EnemyNum++;
						}
					}
				}

				// �ϳ��� �¾��� ��쿡�� ����ġ�� �÷��ش�.
				if (bHit)
				{
					shareAttrExp(pSlayer, Damage , 1, 8, 1, _GCSkillToTileOK1);
					increaseDomainExp(pSlayer, DomainType, pSkillInfo->getPoint(), _GCSkillToTileOK1, maxEnemyLevel, EnemyNum);
					increaseSkillExp(pSlayer, DomainType, pSkillSlot, pSkillInfo, _GCSkillToTileOK1);
					increaseAlignment(pSlayer, pTargetCreature, _GCSkillToTileOK1);
				}

				// �Ѿ� ���ڸ� ���̰�, �Ѿ� ���ڸ� �����ϰ�, ���� �Ѿ� ���ڸ� ���� ������ �������� ����߸���.
				_GCSkillToTileOK1.addShortData(MODIFY_BULLET, RemainBullet);

				decreaseDurability(pSlayer, NULL, pSkillInfo, &_GCSkillToTileOK1, NULL);

				_GCSkillToTileOK1.setSkillType(SKILL_MULTI_SHOT);
				_GCSkillToTileOK1.setCEffectID(0);
				_GCSkillToTileOK1.setX(targetX);
				_GCSkillToTileOK1.setY(targetX);
				_GCSkillToTileOK1.setRange(dir);
				_GCSkillToTileOK1.setDuration(0);

				_GCSkillToTileOK2.setObjectID(pSlayer->getObjectID());
				_GCSkillToTileOK2.setSkillType(SKILL_MULTI_SHOT);
				_GCSkillToTileOK2.setX(targetX);
				_GCSkillToTileOK2.setY(targetY);
				_GCSkillToTileOK2.setRange(dir);
				_GCSkillToTileOK2.setDuration(0);

				_GCSkillToTileOK3.setObjectID(pSlayer->getObjectID());
				_GCSkillToTileOK3.setSkillType(SKILL_MULTI_SHOT);
				_GCSkillToTileOK3.setX(targetX);
				_GCSkillToTileOK3.setY(targetY);

				_GCSkillToTileOK4.setSkillType(SKILL_MULTI_SHOT);
				_GCSkillToTileOK4.setX(targetX);
				_GCSkillToTileOK4.setY(targetY);
				_GCSkillToTileOK4.setDuration(0);
				_GCSkillToTileOK4.setRange(dir);

				_GCSkillToTileOK5.setObjectID(pSlayer->getObjectID());
				_GCSkillToTileOK5.setSkillType(SKILL_MULTI_SHOT);
				_GCSkillToTileOK5.setX(targetX);
				_GCSkillToTileOK5.setY(targetY);
				_GCSkillToTileOK5.setRange(dir);
				_GCSkillToTileOK5.setDuration(0);

				pPlayer->sendPacket(&_GCSkillToTileOK1);

				// �� ����� ���� ������ �޴� ��鿡�� ��Ŷ�� ������� �Ѵ�.
				for(list<Creature*>::const_iterator itr = cList.begin(); itr != cList.end(); itr++)
				{
					Creature* pVictim = *itr;
					Assert(pVictim != NULL);

					if (pVictim->isPC())
					{
						_GCSkillToTileOK2.clearList();

						HP_t targetHP = 0;
						if (pVictim->isSlayer())
						{
							targetHP = (dynamic_cast<Slayer*>(pVictim))->getHP(ATTR_CURRENT);
						}
						else if (pVictim->isVampire())
						{
							targetHP = (dynamic_cast<Vampire*>(pVictim))->getHP(ATTR_CURRENT);
						}

						_GCSkillToTileOK2.addShortData(MODIFY_CURRENT_HP, targetHP);

						decreaseDurability(NULL, pVictim, NULL, NULL, &_GCSkillToTileOK2);

						Player* pPlayer = pVictim->getPlayer();
						Assert(pPlayer != NULL);
						pPlayer->sendPacket(&_GCSkillToTileOK2);
					}
					else if (pVictim->isMonster())
					{
						Monster* pMonster = dynamic_cast<Monster*>(pVictim);
						pMonster->addEnemy(pSlayer);
					}
				}

				cList.push_back(pSlayer);

				cList = pZone->broadcastSkillPacket(myX, myY, targetX, targetY, &_GCSkillToTileOK5, cList);

				pZone->broadcastPacket(myX, myY, &_GCSkillToTileOK3, cList);
				pZone->broadcastPacket(targetX, targetY,  &_GCSkillToTileOK4, cList);
			}
			else
			{
				executeSkillFailNormalWithGun(pSlayer, getSkillType(), pTargetCreature, RemainBullet);
			}
		}
	} 
	catch (Throwable &t) 
	{
		executeSkillFailException(pSlayer, getSkillType());
	}

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;

	__END_DEBUG 
	__END_CATCH
}

HeadShot g_HeadShot;
