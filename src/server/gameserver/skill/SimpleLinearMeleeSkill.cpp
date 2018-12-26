//////////////////////////////////////////////////////////////////////////////
// Filename    : SimpleLinearMeleeSkill.cpp
// Written by  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "SimpleLinearMeleeSkill.h"
#include "Geometry.h"

#include "Gpackets/GCSkillToTileOK1.h"
#include "Gpackets/GCSkillToTileOK2.h"
#include "Gpackets/GCSkillToTileOK3.h"
#include "Gpackets/GCSkillToTileOK4.h"
#include "Gpackets/GCSkillToTileOK5.h"

SimpleLinearMeleeSkill g_SimpleLinearMeleeSkill;

//////////////////////////////////////////////////////////////////////////////
// class SimpleLinearMeleeSkill member methods
//////////////////////////////////////////////////////////////////////////////

void SimpleLinearMeleeSkill::execute(Slayer* pSlayer, int X, int Y, SkillSlot* pSkillSlot,
	const SIMPLE_SKILL_INPUT& param, SIMPLE_SKILL_OUTPUT& result,
	CEffectID_t CEffectID=0) 
{
	__BEGIN_TRY

	Assert(pSlayer != NULL);
	Assert(pSkillSlot != NULL);

	try 
	{
		Player* pPlayer = pSlayer->getPlayer();
		Zone* pZone = pSlayer->getZone();

		Assert(pPlayer != NULL);
		Assert(pZone != NULL);

		// ���� �� ����� Ư���� ���Ⱑ �־�� ������ �� �ִ� ����̶��...
		// �� �迭�� ���⸦ ��� �ִ����� üũ�ؼ� �ƴ϶�� ���д�.
		bool bIncreaseExp = true;
		if (param.ItemClass != Item::ITEM_CLASS_MAX)
		{
			Item* pItem = pSlayer->getWearItem(Slayer::WEAR_RIGHTHAND);
			if (pItem == NULL || pItem->getItemClass() != param.ItemClass)
			{
				executeSkillFailException(pSlayer, param.SkillType);
				return;
			}

			bIncreaseExp = pSlayer->isRealWearingEx(Slayer::WEAR_RIGHTHAND);
		}

		GCSkillToTileOK1 _GCSkillToTileOK1;
		GCSkillToTileOK2 _GCSkillToTileOK2;
		GCSkillToTileOK3 _GCSkillToTileOK3;
		GCSkillToTileOK4 _GCSkillToTileOK4;
		GCSkillToTileOK5 _GCSkillToTileOK5;

		SkillInfo*        pSkillInfo = g_pSkillInfoManager->getSkillInfo(param.SkillType);
		SkillDomainType_t DomainType = pSkillInfo->getDomainType();
		Level_t           SkillLevel = pSkillSlot->getExpLevel();

		int  RequiredMP  = (int)pSkillInfo->getConsumeMP();
		bool bManaCheck  = hasEnoughMana(pSlayer, RequiredMP);
		bool bTimeCheck  = verifyRunTime(pSkillSlot);
		bool bRangeCheck = verifyDistance(pSlayer, X, Y, pSkillInfo->getRange());

		if (bManaCheck && bTimeCheck && bRangeCheck)
		{
			// MP�� ����߸���.
			decreaseMana(pSlayer, RequiredMP, _GCSkillToTileOK1);

			// ��ǥ�� ������ ���Ѵ�.
			ZoneCoord_t myX          = pSlayer->getX();
			ZoneCoord_t myY          = pSlayer->getY();
			Dir_t       dir          = calcDirection(myX, myY, X, Y);
			Damage_t    Damage       = 0;
			Damage_t    MaxDamage    = 0;
			bool        bCriticalHit = false;

			list<POINT> ptList;
			getPointsFromLineEx(myX, myY, X, Y, pSkillInfo->getRange(), ptList);

			VSRect rect(1, 1, pZone->getWidth()-2, pZone->getHeight()-2);

			list<Creature*> cList;

			Level_t maxEnemyLevel = 0;
			uint EnemyNum = 0;

			bool bHit = false;

			list<POINT>::iterator ptitr = ptList.begin();
			for (; ptitr != ptList.end(); ptitr++)
			{
				int tileX   = (*ptitr).x;
				int tileY   = (*ptitr).y;

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

						bool bMoveModeCheck  = (pTargetCreature->getMoveMode() == Creature::MOVE_MODE_WALKING) ? true : false;

						bool bCanHit         = canHit(pSlayer, pTargetCreature, param.SkillType);
						if( ( pTargetCreature->getMoveMode() == Creature::MOVE_MODE_FLYING ) &&  param.Level == 1 ) {
							bMoveModeCheck = true;
							bCanHit = true;
						}
						if( ( pTargetCreature->getMoveMode() == Creature::MOVE_MODE_BURROWING) &&  param.Level == 2 ) {
							bMoveModeCheck = true;
							bCanHit = true;
						}

						bool bRaceCheck      = pTargetCreature->isOusters() || pTargetCreature->isVampire() || pTargetCreature->isMonster();
						bool bHitRoll        = false;
						bool bPK             = verifyPK(pSlayer, pTargetCreature);
						bool bZoneLevelCheck = checkZoneLevelToHitTarget(pTargetCreature);
						bool bSetMinDamage   = false;

						if ( param.SkillType == SKILL_SPIT_STREAM || param.SkillType == SKILL_Cut_Storm && tileX == X && tileY == Y )
						{
							bRaceCheck = !pTargetCreature->isNPC();
						}

						if (param.bMagicHitRoll)
						{
							bHitRoll = HitRoll::isSuccessMagic(pSlayer, pSkillInfo, pSkillSlot);
						}
						else
						{
							bHitRoll = HitRoll::isSuccess(pSlayer, pTargetCreature, SkillLevel/2);
						}

						// �� �迭�� ����� ���� �ʴ��� 7%�� �������� ������ - by bezz
						if ( param.ItemClass == Item::ITEM_CLASS_BLADE && !bHitRoll )
						{
							bHitRoll = true;
							bSetMinDamage = true;
						}

						if ( !canAttack( pSlayer, pTargetCreature )
							|| pTargetCreature->isFlag(Effect::EFFECT_CLASS_COMA) )
						{
							bHitRoll = false; 
						}

						if (bMoveModeCheck && bRaceCheck && bHitRoll && bCanHit && bPK && bZoneLevelCheck)
						{
							bCriticalHit = false;
							Damage       = 0;

							if (param.bAdd)
							{
								Damage += computeDamage(pSlayer, pTargetCreature, SkillLevel/5, bCriticalHit);
							}

							if (param.bMagicDamage)
							{
								Damage += computeMagicDamage(pTargetCreature, param.SkillDamage, param.SkillType);
							}
							else
							{
								Damage += param.SkillDamage;
							}

							// HitRoll ���� ������ �� �迭�� ����� ��� 7%�� �������� ������ �Ѵ� - by bezz
							if ( bSetMinDamage )
							{
								Damage = getPercentValue( Damage, 7 );
							}

							MaxDamage = max(Damage, MaxDamage);

							ObjectID_t targetObjectID = pTargetCreature->getObjectID();
							cList.push_back(pTargetCreature);

							_GCSkillToTileOK1.addCListElement(targetObjectID);
							_GCSkillToTileOK2.addCListElement(targetObjectID);
							_GCSkillToTileOK5.addCListElement(targetObjectID);

							// �ϴ� �´� ���� ���� ��Ŷ�� �� ���·� �� ä��, �������� �ش�.
							setDamage(pTargetCreature, Damage, pSlayer, param.SkillType, NULL, &_GCSkillToTileOK1);
							computeAlignmentChange(pTargetCreature, Damage, pSlayer, NULL, &_GCSkillToTileOK1);

							increaseAlignment(pSlayer, pTargetCreature, _GCSkillToTileOK1);

							// ũ��Ƽ�� ��Ʈ��� ������ �ڷ� �������� �Ѵ�.
							if (bCriticalHit)
							{
								knockbackCreature(pZone, pTargetCreature, pSlayer->getX(), pSlayer->getY());
							}

							// Ÿ���� �����̾ �ƴ� ��쿡�� ���� �ɷ� �����Ѵ�.
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
					shareAttrExp(pSlayer, MaxDamage, param.STRMultiplier, param.DEXMultiplier, param.INTMultiplier, _GCSkillToTileOK1);
					increaseDomainExp(pSlayer, DomainType, pSkillInfo->getPoint(), _GCSkillToTileOK1, maxEnemyLevel, EnemyNum);
					increaseSkillExp(pSlayer, DomainType,  pSkillSlot, pSkillInfo, _GCSkillToTileOK1);
				}
			}

			decreaseDurability(pSlayer, NULL, pSkillInfo, &_GCSkillToTileOK1, NULL);

			_GCSkillToTileOK1.setSkillType(param.SkillType);
			_GCSkillToTileOK1.setCEffectID(CEffectID);
			_GCSkillToTileOK1.setX(X);
			_GCSkillToTileOK1.setY(Y);
			_GCSkillToTileOK1.setRange(dir);
			_GCSkillToTileOK1.setDuration(0);

			_GCSkillToTileOK2.setObjectID(pSlayer->getObjectID());
			_GCSkillToTileOK2.setSkillType(param.SkillType);
			_GCSkillToTileOK2.setX(X);
			_GCSkillToTileOK2.setY(Y);
			_GCSkillToTileOK2.setRange(dir);
			_GCSkillToTileOK2.setDuration(0);

			_GCSkillToTileOK3.setObjectID(pSlayer->getObjectID());
			_GCSkillToTileOK3.setSkillType(param.SkillType);
			_GCSkillToTileOK3.setX(X);
			_GCSkillToTileOK3.setY(Y);

			_GCSkillToTileOK4.setSkillType(param.SkillType);
			_GCSkillToTileOK4.setX(X);
			_GCSkillToTileOK4.setY(Y);
			_GCSkillToTileOK4.setRange(dir);
			_GCSkillToTileOK4.setDuration(0);

			_GCSkillToTileOK5.setObjectID(pSlayer->getObjectID());
			_GCSkillToTileOK5.setSkillType(param.SkillType);
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
					if (pTargetCreature->isSlayer())
					{
						targetHP = (dynamic_cast<Slayer*>(pTargetCreature))->getHP(ATTR_CURRENT);
					}
					else if (pTargetCreature->isVampire())
					{
						targetHP = (dynamic_cast<Vampire*>(pTargetCreature))->getHP(ATTR_CURRENT);
					}
					else if (pTargetCreature->isOusters())
					{
						targetHP = (dynamic_cast<Ousters*>(pTargetCreature))->getHP(ATTR_CURRENT);
					}
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
			pSkillSlot->setRunTime(param.Delay);

			result.bSuccess = true;
		}
		else
		{
			executeSkillFailNormal(pSlayer, param.SkillType, NULL);
		}
	}
	catch (Throwable & t)
	{
		executeSkillFailException(pSlayer, param.SkillType);
	}

	__END_CATCH
}

/*
void SimpleLinearMeleeSkill::execute(Vampire* pVampire, int X, int Y, VampireSkillSlot* pVampireSkillSlot, 
	const SIMPLE_SKILL_INPUT& param,  SIMPLE_SKILL_OUTPUT& result,
	CEffectID_t CEffectID=0) 
{
	__BEGIN_TRY
	__END_CATCH
}
*/

void SimpleLinearMeleeSkill::execute(Monster* pMonster, int X, int Y,
	const SIMPLE_SKILL_INPUT& param,  SIMPLE_SKILL_OUTPUT& result,
	CEffectID_t CEffectID=0) 
{
	__BEGIN_TRY

	Assert(pMonster != NULL);

	try 
	{
		Zone* pZone = pMonster->getZone();

		Assert(pZone != NULL);

		// ���� �� ����� Ư���� ���Ⱑ �־�� ������ �� �ִ� ����̶��...
		// �� �迭�� ���⸦ ��� �ִ����� üũ�ؼ� �ƴ϶�� ���д�.
		bool bIncreaseExp = true;

		GCSkillToTileOK1 _GCSkillToTileOK1;
		GCSkillToTileOK2 _GCSkillToTileOK2;
		GCSkillToTileOK3 _GCSkillToTileOK3;
		GCSkillToTileOK4 _GCSkillToTileOK4;
		GCSkillToTileOK5 _GCSkillToTileOK5;

		SkillInfo*        pSkillInfo = g_pSkillInfoManager->getSkillInfo(param.SkillType);
		SkillDomainType_t DomainType = pSkillInfo->getDomainType();

		int  RequiredMP  = (int)pSkillInfo->getConsumeMP();
		bool bManaCheck  = hasEnoughMana(pMonster, RequiredMP);
		bool bRangeCheck = verifyDistance(pMonster, X, Y, pSkillInfo->getRange());

		if (bManaCheck && bRangeCheck)
		{
			// MP�� ����߸���.
			//decreaseMana(pMonster, RequiredMP, _GCSkillToTileOK1);

			// ��ǥ�� ������ ���Ѵ�.
			ZoneCoord_t myX          = pMonster->getX();
			ZoneCoord_t myY          = pMonster->getY();
			Dir_t       dir          = calcDirection(myX, myY, X, Y);
			Damage_t    Damage       = 0;
			Damage_t    MaxDamage    = 0;
			bool        bCriticalHit = false;

			list<POINT> ptList;
			getPointsFromLineEx(myX, myY, X, Y, pSkillInfo->getRange(), ptList);

			VSRect rect(1, 1, pZone->getWidth()-2, pZone->getHeight()-2);

			list<Creature*> cList;

			Level_t maxEnemyLevel = 0;
			uint EnemyNum = 0;

			bool bHit = false;

			list<POINT>::iterator ptitr = ptList.begin();
			for (; ptitr != ptList.end(); ptitr++)
			{
				int tileX   = (*ptitr).x;
				int tileY   = (*ptitr).y;

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

						bool bMoveModeCheck  = (pTargetCreature->getMoveMode() == Creature::MOVE_MODE_WALKING) ? true : false;

						bool bCanHit         = canHit(pMonster, pTargetCreature, param.SkillType);
						if( ( pTargetCreature->getMoveMode() == Creature::MOVE_MODE_FLYING ) &&  param.Level == 1 ) {
							bMoveModeCheck = true;
							bCanHit = true;
						}
						if( ( pTargetCreature->getMoveMode() == Creature::MOVE_MODE_BURROWING) &&  param.Level == 2 ) {
							bMoveModeCheck = true;
							bCanHit = true;
						}

						bool bRaceCheck      = pTargetCreature->isOusters() || pTargetCreature->isVampire() || pTargetCreature->isSlayer();
						bool bHitRoll        = false;
						bool bPK             = verifyPK(pMonster, pTargetCreature);
						bool bZoneLevelCheck = checkZoneLevelToHitTarget(pTargetCreature);
						bool bSetMinDamage   = false;

						if ( param.SkillType == SKILL_SPIT_STREAM || param.SkillType == SKILL_Cut_Storm && tileX == X && tileY == Y )
						{
							bRaceCheck = !pTargetCreature->isNPC();
						}

						if (param.bMagicHitRoll)
						{
							bHitRoll = HitRoll::isSuccessMagic(pMonster, pSkillInfo);
						}
						else
						{
							bHitRoll = HitRoll::isSuccess(pMonster, pTargetCreature, 100/2);
						}

						// �� �迭�� ����� ���� �ʴ��� 7%�� �������� ������ - by bezz
						if ( param.ItemClass == Item::ITEM_CLASS_BLADE && !bHitRoll )
						{
							bHitRoll = true;
							bSetMinDamage = true;
						}

						if ( !canAttack( pMonster, pTargetCreature )
							|| pTargetCreature->isFlag(Effect::EFFECT_CLASS_COMA) )
						{
							bHitRoll = false; 
						}

						if (bMoveModeCheck && bRaceCheck && bHitRoll && bCanHit && bPK && bZoneLevelCheck)
						{
							bCriticalHit = false;
							Damage       = 0;

							if (param.bAdd)
							{
								Damage += computeDamage(pMonster, pTargetCreature, 100/5, bCriticalHit);
							}

							if (param.bMagicDamage)
							{
								Damage += computeMagicDamage(pTargetCreature, param.SkillDamage, param.SkillType);
							}
							else
							{
								Damage += param.SkillDamage;
							}

							// HitRoll ���� ������ �� �迭�� ����� ��� 7%�� �������� ������ �Ѵ� - by bezz
							if ( bSetMinDamage )
							{
								Damage = getPercentValue( Damage, 7 );
							}

							MaxDamage = max(Damage, MaxDamage);

							ObjectID_t targetObjectID = pTargetCreature->getObjectID();
							cList.push_back(pTargetCreature);

							_GCSkillToTileOK1.addCListElement(targetObjectID);
							_GCSkillToTileOK2.addCListElement(targetObjectID);
							_GCSkillToTileOK5.addCListElement(targetObjectID);

							// �ϴ� �´� ���� ���� ��Ŷ�� �� ���·� �� ä��, �������� �ش�.
							setDamage(pTargetCreature, Damage, pMonster, param.SkillType, NULL, &_GCSkillToTileOK1);

							// ũ��Ƽ�� ��Ʈ��� ������ �ڷ� �������� �Ѵ�.
							if (bCriticalHit)
							{
								knockbackCreature(pZone, pTargetCreature, pMonster->getX(), pMonster->getY());
							}
						}
					} 
				} 
			}

			_GCSkillToTileOK2.setObjectID(pMonster->getObjectID());
			_GCSkillToTileOK2.setSkillType(param.SkillType);
			_GCSkillToTileOK2.setX(X);
			_GCSkillToTileOK2.setY(Y);
			_GCSkillToTileOK2.setRange(dir);
			_GCSkillToTileOK2.setDuration(0);

			_GCSkillToTileOK3.setObjectID(pMonster->getObjectID());
			_GCSkillToTileOK3.setSkillType(param.SkillType);
			_GCSkillToTileOK3.setX(X);
			_GCSkillToTileOK3.setY(Y);

			_GCSkillToTileOK4.setSkillType(param.SkillType);
			_GCSkillToTileOK4.setX(X);
			_GCSkillToTileOK4.setY(Y);
			_GCSkillToTileOK4.setRange(dir);
			_GCSkillToTileOK4.setDuration(0);

			_GCSkillToTileOK5.setObjectID(pMonster->getObjectID());
			_GCSkillToTileOK5.setSkillType(param.SkillType);
			_GCSkillToTileOK5.setX(X);
			_GCSkillToTileOK5.setY(Y);
			_GCSkillToTileOK5.setRange(dir);
			_GCSkillToTileOK5.setDuration(0);

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
					if (pTargetCreature->isSlayer())
					{
						targetHP = (dynamic_cast<Slayer*>(pTargetCreature))->getHP(ATTR_CURRENT);
					}
					else if (pTargetCreature->isVampire())
					{
						targetHP = (dynamic_cast<Vampire*>(pTargetCreature))->getHP(ATTR_CURRENT);
					}
					else if (pTargetCreature->isOusters())
					{
						targetHP = (dynamic_cast<Ousters*>(pTargetCreature))->getHP(ATTR_CURRENT);
					}
					_GCSkillToTileOK2.addShortData(MODIFY_CURRENT_HP, targetHP);

					// ��Ŷ�� �����ش�.
					pTargetCreature->getPlayer()->sendPacket(&_GCSkillToTileOK2);
				}
				else if (pTargetCreature->isMonster())
				{
					// ��� ������ �ν��Ѵ�.
					Monster* pMonster = dynamic_cast<Monster*>(pTargetCreature);
					pMonster->addEnemy(pMonster);
				}
			}

			cList.push_back(pMonster);

			cList = pZone->broadcastSkillPacket(myX, myY, X, Y, &_GCSkillToTileOK5 , cList);

			pZone->broadcastPacket(myX, myY,  &_GCSkillToTileOK3 , cList);
			pZone->broadcastPacket(X, Y,  &_GCSkillToTileOK4 , cList);

			// set Next Run Time
			result.bSuccess = true;
		}
		else
		{
			executeSkillFailNormal(pMonster, param.SkillType, NULL);
		}
	}
	catch (Throwable & t)
	{
		executeSkillFailException(pMonster, param.SkillType);
	}

	__END_CATCH
}



