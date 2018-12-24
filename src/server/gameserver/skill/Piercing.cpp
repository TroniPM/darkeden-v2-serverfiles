//////////////////////////////////////////////////////////////////////////////
// Filename    : Piercing.cpp
// Written by  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "Piercing.h"
#include "ItemUtil.h"
#include "Geometry.h"
#include "Effect.h"

#include "Gpackets/GCSkillToTileOK1.h"
#include "Gpackets/GCSkillToTileOK2.h"
#include "Gpackets/GCSkillToTileOK3.h"
#include "Gpackets/GCSkillToTileOK4.h"
#include "Gpackets/GCSkillToTileOK5.h"

//////////////////////////////////////////////////////////////////////////////
// �����̾� ������Ʈ �ڵ鷯
//////////////////////////////////////////////////////////////////////////////
void Piercing::execute(Slayer* pSlayer, ObjectID_t TargetObjectID, SkillSlot* pSkillSlot, CEffectID_t CEffectID)
	throw(Error)
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin" << endl;

	Assert(pSlayer != NULL);
	Assert(pSkillSlot != NULL);

	try 
	{
		Zone* pZone = pSlayer->getZone();
		Creature* pTargetCreature = pZone->getCreature(TargetObjectID);

		// NoSuch����. by sigi. 2002.5.2
		if (pTargetCreature==NULL)
		{
			executeSkillFailException(pSlayer, getSkillType());
			return;
		}

		execute(pSlayer, pTargetCreature->getX(), pTargetCreature->getY(), pSkillSlot, CEffectID);
	} 
	catch (Throwable & t) 
	{
		executeSkillFailException(pSlayer, getSkillType());
	}

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// �����̾� ���� �ڵ鷯
//////////////////////////////////////////////////////////////////////////////
void Piercing::execute(Slayer* pSlayer, ZoneCoord_t X, ZoneCoord_t Y, SkillSlot* pSkillSlot, CEffectID_t CEffectID)
	throw(Error)
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

		// �����ϰ� �ִ� ���Ⱑ NULL�̰ų�, �� �迭�� �ƴ϶�� ����� �� ����.
		// �� �迭 �߿����� SG�� �� ����� ����� �� ����.
		Item* pWeapon = pSlayer->getWearItem(Slayer::WEAR_RIGHTHAND);
		if (pWeapon == NULL || !isArmsWeapon(pWeapon) || pWeapon->getItemClass() == Item::ITEM_CLASS_SG)
		{
			executeSkillFailException(pSlayer, getSkillType());
			//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " end" << endl;
			return;
		}

		bool bIncreaseExp = pSlayer->isRealWearingEx(Slayer::WEAR_RIGHTHAND);

		GCSkillToTileOK1 _GCSkillToTileOK1;
		GCSkillToTileOK2 _GCSkillToTileOK2;
		GCSkillToTileOK3 _GCSkillToTileOK3;
		GCSkillToTileOK4 _GCSkillToTileOK4;
		GCSkillToTileOK5 _GCSkillToTileOK5;

		SkillType_t       SkillType  = pSkillSlot->getSkillType();
		SkillInfo*        pSkillInfo = g_pSkillInfoManager->getSkillInfo(SkillType);
		SkillDomainType_t DomainType = pSkillInfo->getDomainType();
		Level_t           SkillLevel = pSkillSlot->getExpLevel();

		// �ѿ� �Ѿ��� �����ִٸ�...
		if (getRemainBullet(pWeapon) > 0)
		{
			// ���� ���� �Ѿ� ���ڸ� ����߸���.
			decreaseBullet(pWeapon);
			// �ѹ߾������� ������ �ʿ� ����. by sigi. 2002.5.9
			//pWeapon->save(pSlayer->getName(), STORAGE_GEAR, 0, Slayer::WEAR_RIGHTHAND, 0);
			Bullet_t RemainBullet = getRemainBullet(pWeapon);

			int  RequiredMP  = (int)pSkillInfo->getConsumeMP();
			bool bManaCheck  = hasEnoughMana(pSlayer, RequiredMP);
			bool bTimeCheck  = verifyRunTime(pSkillSlot);
			bool bRangeCheck = verifyDistance(pSlayer, X, Y, pWeapon->getRange());

			if (bManaCheck && bTimeCheck && bRangeCheck)
			{
				// MP�� ����߸���.
				decreaseMana(pSlayer, RequiredMP, _GCSkillToTileOK1);

				// ��ǥ�� ������ ���Ѵ�.
				ZoneCoord_t myX = pSlayer->getX();
				ZoneCoord_t myY = pSlayer->getY();
				Dir_t       dir = calcDirection(myX, myY, X, Y);

				list<POINT> ptList;
				getPointsFromLineEx(myX, myY, X, Y, pWeapon->getRange(), ptList);

				// ������, ���ӽð� ���� ����Ѵ�.
				SkillInput input(pSlayer, pSkillSlot);
				SkillOutput output;
				computeOutput(input, output);

				Damage_t SkillDamage = output.Damage, Damage = 0;

//				Exp_t Point = pSkillInfo->getPoint();

				VSRect rect(1, 1, pZone->getWidth()-2, pZone->getHeight()-2);

				list<Creature*> cList;
				
				bool bHit = false;

				Level_t maxEnemyLevel = 0;
				uint EnemyNum = 0;

				list<POINT>::iterator ptitr = ptList.begin();
				for (; ptitr != ptList.end(); ptitr++)
				{
					int tileX = (*ptitr).x;
					int tileY = (*ptitr).y;

					// �� �����̰�, �������밡 �ƴ϶�� ���� Ȯ���� �ִ�.
					if (rect.ptInRect(tileX, tileY))
					{
						// Ÿ���� �޾ƿ´�.
						Tile& tile = pZone->getTile(tileX, tileY);

						list<Creature*> targetList;
						if (tile.hasCreature(Creature::MOVE_MODE_WALKING))
						{
							Creature* pCreature = tile.getCreature(Creature::MOVE_MODE_WALKING);
							targetList.push_back(pCreature);
						}
						if (tile.hasCreature(Creature::MOVE_MODE_FLYING))
						{
							Creature* pCreature = tile.getCreature(Creature::MOVE_MODE_FLYING);
							targetList.push_back(pCreature);
						}
						if (tile.hasCreature(Creature::MOVE_MODE_BURROWING))
						{
							Creature* pCreature = tile.getCreature(Creature::MOVE_MODE_BURROWING);
							targetList.push_back(pCreature);
						}

						list<Creature*>::iterator itr = targetList.begin();
						for(; itr != targetList.end(); itr++)
						{
							Creature* pTargetCreature = (*itr);
							Assert(pTargetCreature != NULL);

							// �� �迭 ����� �� ���� ������ �������� ������ ���� �ִ�.
							bool bMoveModeCheck  = (pTargetCreature->getMoveMode() == Creature::MOVE_MODE_BURROWING) ? false : true;
							bool bRaceCheck      = pTargetCreature->isNPC() || pTargetCreature->isSlayer();
							bool bHitRoll        = HitRoll::isSuccess(pSlayer, pTargetCreature, SkillLevel/2);
							bool bCanHit         = canHit(pSlayer, pTargetCreature, SkillType) && canAttack(pSlayer, pTargetCreature);
							bool bPK             = verifyPK(pSlayer, pTargetCreature);
							bool bZoneLevelCheck = checkZoneLevelToHitTarget(pTargetCreature);

							if (bMoveModeCheck && !bRaceCheck && bHitRoll && bCanHit && bPK && bZoneLevelCheck
							&& !pTargetCreature->isFlag(Effect::EFFECT_CLASS_COMA) )	// ���� ������ �ɸ��� �� �¾ƾ� �ȴ�. -_-; 2003.3.14
							{
								bool bCriticalHit = false;

								Damage = computeDamage(pSlayer, pTargetCreature, SkillLevel/5, bCriticalHit) + SkillDamage;

								ObjectID_t targetObjectID = pTargetCreature->getObjectID();
								cList.push_back(pTargetCreature);

								_GCSkillToTileOK1.addCListElement(targetObjectID);
								_GCSkillToTileOK2.addCListElement(targetObjectID);
								_GCSkillToTileOK4.addCListElement(targetObjectID);
								_GCSkillToTileOK5.addCListElement(targetObjectID);

								// �ϴ� �´� ���� ���� ��Ŷ�� �� ���·� �� ä��, �������� �ش�.
								setDamage(pTargetCreature, Damage, pSlayer, SkillType, NULL, &_GCSkillToTileOK1);
								computeAlignmentChange(pTargetCreature, Damage, pSlayer, NULL, &_GCSkillToTileOK1);

								increaseAlignment(pSlayer, pTargetCreature, _GCSkillToTileOK1);

								// ũ��Ƽ�� ��Ʈ��� ������ �ڷ� �������� �Ѵ�.
								if (bCriticalHit)
								{
									knockbackCreature(pZone, pTargetCreature, pSlayer->getX(), pSlayer->getY());
								}

								// �����̾ �ƴ� ��쿡�� ���� �ɷ� �����Ѵ�.
								if (!pTargetCreature->isSlayer())
								{
									bHit = true;
									if ( maxEnemyLevel < pTargetCreature->getLevel() ) maxEnemyLevel = pTargetCreature->getLevel();
									EnemyNum++;
								}
							}
						} 
					} 
				}

				if (bHit)
				{
					if (bIncreaseExp)
					{
						shareAttrExp(pSlayer, Damage , 1, 8, 1, _GCSkillToTileOK1);
						increaseDomainExp(pSlayer, DomainType, pSkillInfo->getPoint(), _GCSkillToTileOK1, maxEnemyLevel, EnemyNum);
						increaseSkillExp(pSlayer, DomainType, pSkillSlot, pSkillInfo, _GCSkillToTileOK1);
					}
				}

				// �������� ������ �������� ����߸���.
				decreaseDurability(pSlayer, NULL, pSkillInfo, &_GCSkillToTileOK1, NULL);

				_GCSkillToTileOK1.setSkillType(SkillType);
				_GCSkillToTileOK1.setCEffectID(CEffectID);
				_GCSkillToTileOK1.setX(X);
				_GCSkillToTileOK1.setY(Y);
				_GCSkillToTileOK1.setRange(dir);
				_GCSkillToTileOK1.setDuration(0);
				_GCSkillToTileOK1.addShortData(MODIFY_BULLET, RemainBullet);

				_GCSkillToTileOK2.setObjectID(pSlayer->getObjectID());
				_GCSkillToTileOK2.setSkillType(SkillType);
				_GCSkillToTileOK2.setX(X);
				_GCSkillToTileOK2.setY(Y);
				_GCSkillToTileOK2.setRange(dir);
				_GCSkillToTileOK2.setDuration(0);

				_GCSkillToTileOK3.setObjectID(pSlayer->getObjectID());
				_GCSkillToTileOK3.setSkillType(SkillType);
				_GCSkillToTileOK3.setX(X);
				_GCSkillToTileOK3.setY(Y);

				_GCSkillToTileOK4.setSkillType(SkillType);
				_GCSkillToTileOK4.setX(X);
				_GCSkillToTileOK4.setY(Y);
				_GCSkillToTileOK4.setDuration(0);
				_GCSkillToTileOK4.setRange(dir);

				_GCSkillToTileOK5.setObjectID(pSlayer->getObjectID());
				_GCSkillToTileOK5.setSkillType(SkillType);
				_GCSkillToTileOK5.setX(X);
				_GCSkillToTileOK5.setY(Y);
				_GCSkillToTileOK5.setRange(dir);
				_GCSkillToTileOK5.setDuration(0);

				pPlayer->sendPacket(&_GCSkillToTileOK1);

				// �� ����� ���� ������ �޴� ��鿡�� ��Ŷ�� ������� �Ѵ�.
				for (list<Creature*>::const_iterator itr = cList.begin(); itr != cList.end(); itr++)
				{
					Creature * pTargetCreature = *itr;
					Assert(pTargetCreature != NULL);

					if (pTargetCreature->isPC())
					{
						_GCSkillToTileOK2.clearList();

						// HP�� ��������� ��Ŷ���� ����Ѵ�.
						HP_t targetHP = 0;
						if (pTargetCreature->isSlayer()) targetHP = (dynamic_cast<Slayer*>(pTargetCreature))->getHP(ATTR_CURRENT);
						else if (pTargetCreature->isVampire()) targetHP = (dynamic_cast<Vampire*>(pTargetCreature))->getHP(ATTR_CURRENT);
						else if (pTargetCreature->isOusters()) targetHP = (dynamic_cast<Ousters*>(pTargetCreature))->getHP(ATTR_CURRENT);
						_GCSkillToTileOK2.addShortData(MODIFY_CURRENT_HP, targetHP);

						// �������� �������� ����߸���.
						decreaseDurability(NULL, pTargetCreature, pSkillInfo, NULL, &_GCSkillToTileOK2);

						// ��Ŷ�� �����ش�.
						pTargetCreature->getPlayer()->sendPacket(&_GCSkillToTileOK2);
					}
					else if (pTargetCreature->isMonster())
					{
						// ��� ������ �ν��Ѵ�.
						Monster* pMonster = dynamic_cast<Monster*>(pTargetCreature);
						pMonster->addEnemy(pSlayer);
					}
				}

				cList.push_back(pSlayer);

				cList = pZone->broadcastSkillPacket(myX, myY, X, Y, &_GCSkillToTileOK5 , cList);

				pZone->broadcastPacket(myX, myY,  &_GCSkillToTileOK3 , cList);
				pZone->broadcastPacket(X, Y,  &_GCSkillToTileOK4 , cList);

				// set Next Run Time
				pSkillSlot->setRunTime(output.Delay);
			}
			else
			{
				executeSkillFailNormalWithGun(pSlayer, getSkillType(), NULL, RemainBullet);
			}
		}
		else
		{
			executeSkillFailException(pSlayer, getSkillType());
		}
	}
	catch (Throwable & t)
	{
		executeSkillFailException(pSlayer, getSkillType());
	}

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;

	__END_CATCH
}

Piercing g_Piercing;
