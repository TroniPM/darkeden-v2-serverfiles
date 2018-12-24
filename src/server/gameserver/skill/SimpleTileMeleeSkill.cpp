//////////////////////////////////////////////////////////////////////////////
// Filename    : SimpleTileMeleeSkill.cpp
// Written by  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "SimpleTileMeleeSkill.h"
#include "CrossCounter.h"
#include "ZoneUtil.h"

#include "Gpackets/GCSkillToTileOK1.h"
#include "Gpackets/GCSkillToTileOK2.h"
#include "Gpackets/GCSkillToTileOK5.h"

SimpleTileMeleeSkill g_SimpleTileMeleeSkill;

//////////////////////////////////////////////////////////////////////////////
// class SimpleTileMeleeSkill member methods
//////////////////////////////////////////////////////////////////////////////

void SimpleTileMeleeSkill::execute(Slayer* pSlayer, int X, int Y, SkillSlot* pSkillSlot,
	const SIMPLE_SKILL_INPUT& param, SIMPLE_SKILL_OUTPUT& result,
	CEffectID_t CEffectID, bool bForceKnockback) throw (Error)
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
		GCSkillToTileOK5 _GCSkillToTileOK5;

		SkillInfo*        pSkillInfo = g_pSkillInfoManager->getSkillInfo(param.SkillType);
		SkillDomainType_t DomainType = pSkillInfo->getDomainType();
		SkillLevel_t      SkillLevel = pSkillSlot->getExpLevel();

		int  RequiredMP  = (int)pSkillInfo->getConsumeMP();
		bool bManaCheck  = hasEnoughMana(pSlayer, RequiredMP);
		bool bTimeCheck  = verifyRunTime(pSkillSlot);
		bool bRangeCheck = verifyDistance(pSlayer, X, Y, pSkillInfo->getRange());

		// ������ �־�� �ϰ�, �ð��� �Ÿ� üũ�� �����ϰ�,
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
			bool        bHit         = false;

			Level_t maxEnemyLevel = 0;
			uint EnemyNum = 0;

			VSRect rect(0, 0, pZone->getWidth()-1, pZone->getHeight()-1);

			list<Creature*> cList;

			list<TILE_MASK>::const_iterator itr = param.MaskList.begin();
			for (; itr != param.MaskList.end(); itr++)
			{
				TILE_MASK mask = (*itr);

				int tileX   = X + mask.x;
				int tileY   = Y + mask.y;
				int penalty = mask.penalty;

				// ���� Ÿ���� �� �����̰�, �������밡 �ƴ϶��, ���� Ȯ���� �ִ�.
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

						if (pTargetCreature->getObjectID() != pSlayer->getObjectID())
						{
							bool bMoveModeCheck  = (pTargetCreature->getMoveMode() == Creature::MOVE_MODE_WALKING) ? true : false;
							bool bRaceCheck      = pTargetCreature->isNPC() || pTargetCreature->isSlayer();
							bool bHitRoll        = false;
							bool bCanHit         = canHit(pSlayer, pTargetCreature, param.SkillType);
							bool bPK             = verifyPK(pSlayer, pTargetCreature);
							bool bZoneLevelCheck = checkZoneLevelToHitTarget(pTargetCreature);
							bool bSetMinDamage	 = false;

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
							||	pTargetCreature->isFlag(Effect::EFFECT_CLASS_COMA)) // 2003.3.14
							{
								bHitRoll = false; 
							}

							if (bMoveModeCheck && !bRaceCheck && bHitRoll && bCanHit && bPK && bZoneLevelCheck)
							{
								CheckCrossCounter(pSlayer, pTargetCreature, Damage, pSkillInfo->getRange());

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

								// ���Ƽ�� �⺻������ 100�̴�.
								Damage = getPercentValue(Damage, penalty);

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
								if (bCriticalHit || bForceKnockback)
								{
									knockbackCreature(pZone, pTargetCreature, pSlayer->getX(), pSlayer->getY());
								}

								// ������ �����̾ �ƴ� ��쿡�� ���� �ɷ� �����Ѵ�. 
								if (!pTargetCreature->isSlayer())
								{
									bHit = true;
									if ( maxEnemyLevel < pTargetCreature->getLevel() ) maxEnemyLevel = pTargetCreature->getLevel();
									EnemyNum++;
								}
							}
						}
					} //for (; itr != objectList.end(); itr++) 
				} // if (rect.ptInRect(tileX, tileY) && ...
			} // for (int count=0; count<3; count++)


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

			pZone->broadcastPacket(myX, myY, &_GCSkillToTileOK5 , cList);

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

void SimpleTileMeleeSkill::execute(Vampire* pVampire, int X, int Y, VampireSkillSlot* pVampireSkillSlot, 
	const SIMPLE_SKILL_INPUT& param,  SIMPLE_SKILL_OUTPUT& result,
	CEffectID_t CEffectID, bool bForceKnockback) throw (Error)
{
	__BEGIN_TRY

	Assert(pVampire != NULL);
	Assert(pVampireSkillSlot != NULL);

	try 
	{
		Player* pPlayer = pVampire->getPlayer();
		Zone* pZone = pVampire->getZone();
		Assert(pPlayer != NULL);
		Assert(pZone != NULL);

		GCSkillToTileOK1 _GCSkillToTileOK1;
		GCSkillToTileOK2 _GCSkillToTileOK2;
		GCSkillToTileOK5 _GCSkillToTileOK5;

		SkillInfo* pSkillInfo = g_pSkillInfoManager->getSkillInfo(param.SkillType);

		int  RequiredMP  = (int)pSkillInfo->getConsumeMP();
		bool bManaCheck  = hasEnoughMana(pVampire, RequiredMP);
		bool bTimeCheck  = verifyRunTime(pVampireSkillSlot);
		bool bRangeCheck = verifyDistance(pVampire, X, Y, pSkillInfo->getRange());

		// ������ �־�� �ϰ�, �ð��� �Ÿ� üũ�� �����ϰ�,
		if (bManaCheck && bTimeCheck && bRangeCheck)
		{
			// MP�� ����߸���.
			decreaseMana(pVampire, RequiredMP, _GCSkillToTileOK1);

			// ��ǥ�� ������ ���Ѵ�.
			ZoneCoord_t myX          = pVampire->getX();
			ZoneCoord_t myY          = pVampire->getY();	
			Dir_t       dir          = calcDirection(myX, myY, X, Y);
			Damage_t    Damage       = 0;
			Damage_t    MaxDamage    = 0;
			bool        bCriticalHit = false;

			VSRect rect(0, 0, pZone->getWidth()-2, pZone->getHeight()-2);

			list<Creature*> cList;

			list<TILE_MASK>::const_iterator itr = param.MaskList.begin();
			for (; itr != param.MaskList.end(); itr++)
			{
				TILE_MASK mask = (*itr);

				int tileX   = X + mask.x;
				int tileY   = Y + mask.y;
				int penalty = mask.penalty;

				// ���� Ÿ���� �� �����̰�, �������밡 �ƴ϶��, ���� Ȯ���� �ִ�.
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

						if (pTargetCreature->getObjectID() != pVampire->getObjectID())
						{
							bool bMoveModeCheck  = (pTargetCreature->getMoveMode() == Creature::MOVE_MODE_WALKING) ? true : false;
							bool bRaceCheck      = pTargetCreature->isNPC() || pTargetCreature->isVampire();
							bool bHitRoll        = false;
							bool bCanHit         = canHit(pVampire, pTargetCreature, param.SkillType);
							bool bPK             = verifyPK(pVampire, pTargetCreature);
							bool bZoneLevelCheck = checkZoneLevelToHitTarget(pTargetCreature);

							if ( param.SkillType == SKILL_VIOLENT_PHANTOM  && mask.x == 0 && mask.y == 0 )
							{
								bRaceCheck = pTargetCreature->isNPC();
							}
							
							if(param.SkillType == SKILL_Deadly_Claw && mask.x == 0 && mask.y == 0)
							{
								bRaceCheck = pTargetCreature->isNPC();
							}
							if(param.SkillType == SKILL_CHAOS_SPLITTER && mask.x == 0 && mask.y == 0)
							{
								bRaceCheck = pTargetCreature->isNPC();
							}

							if (param.bMagicHitRoll)
							{
								bHitRoll = HitRoll::isSuccessMagic(pVampire, pSkillInfo, pVampireSkillSlot);
							}
							else
							{
								bHitRoll = HitRoll::isSuccess(pVampire, pTargetCreature, 0);
							}

							if ( !canAttack( pVampire, pTargetCreature ) 
								||	pTargetCreature->isFlag(Effect::EFFECT_CLASS_COMA)) // 2003.3.14
							{
								bHitRoll = false; 
							}

							if (bMoveModeCheck && !bRaceCheck && bHitRoll && bCanHit && bPK && bZoneLevelCheck)
							{
								CheckCrossCounter(pVampire, pTargetCreature, Damage, pSkillInfo->getRange());

								bCriticalHit = false;
								Damage       = 0;

								if (param.bAdd)
								{
									Damage += computeDamage(pVampire, pTargetCreature, 0, bCriticalHit);
								}

								if (param.bMagicDamage)
								{
									Damage += computeMagicDamage(pTargetCreature, param.SkillDamage, param.SkillType, true, pVampire);
								}
								else
								{
									Damage += param.SkillDamage;
								}

								MaxDamage = max(Damage, MaxDamage);

								// ���Ƽ�� �⺻������ 100�̴�.
								Damage = getPercentValue(Damage, penalty);

								ObjectID_t targetObjectID = pTargetCreature->getObjectID();
								cList.push_back(pTargetCreature);

								_GCSkillToTileOK1.addCListElement(targetObjectID);
								_GCSkillToTileOK2.addCListElement(targetObjectID);
								_GCSkillToTileOK5.addCListElement(targetObjectID);

								// �ϴ� �´� ���� ���� ��Ŷ�� �� ���·� �� ä��, �������� �ش�.
								setDamage(pTargetCreature, Damage, pVampire, param.SkillType, NULL, &_GCSkillToTileOK1);
								computeAlignmentChange(pTargetCreature, Damage, pVampire, NULL, &_GCSkillToTileOK1);

								increaseAlignment(pVampire, pTargetCreature, _GCSkillToTileOK1);

								// ũ��Ƽ�� ��Ʈ��� ������ �ڷ� �������� �Ѵ�.
								if (bCriticalHit || bForceKnockback)
								{
									knockbackCreature(pZone, pTargetCreature, pVampire->getX(), pVampire->getY());
								}

								if (pTargetCreature->isDead())
								{
									int exp = computeCreatureExp(pTargetCreature, KILL_EXP);
									shareVampExp(pVampire, exp, _GCSkillToTileOK1);
								}
							}
						}
					} //for (; itr != objectList.end(); itr++) 
				} // if (rect.ptInRect(tileX, tileY) && ...
			} // for (int count=0; count<3; count++)

			decreaseDurability(pVampire, NULL, pSkillInfo, &_GCSkillToTileOK1, NULL);

			_GCSkillToTileOK1.setSkillType(param.SkillType);
			_GCSkillToTileOK1.setCEffectID(CEffectID);
			_GCSkillToTileOK1.setX(X);
			_GCSkillToTileOK1.setY(Y);
			_GCSkillToTileOK1.setRange(dir);
			_GCSkillToTileOK1.setDuration(0);
		
			_GCSkillToTileOK2.setObjectID(pVampire->getObjectID());
			_GCSkillToTileOK2.setSkillType(param.SkillType);
			_GCSkillToTileOK2.setX(X);
			_GCSkillToTileOK2.setY(Y);
			_GCSkillToTileOK2.setRange(dir);
			_GCSkillToTileOK2.setDuration(0);
		
			_GCSkillToTileOK5.setObjectID(pVampire->getObjectID());
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
					if (pTargetCreature->isVampire()) targetHP = (dynamic_cast<Vampire*>(pTargetCreature))->getHP(ATTR_CURRENT);
					else if (pTargetCreature->isSlayer()) targetHP = (dynamic_cast<Slayer*>(pTargetCreature))->getHP(ATTR_CURRENT);
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
					pMonster->addEnemy(pVampire);
				}
			}

			cList.push_back(pVampire);

			pZone->broadcastPacket(myX, myY, &_GCSkillToTileOK5 , cList);

			// set Next Run Time
			pVampireSkillSlot->setRunTime(param.Delay);

			result.bSuccess = true;
		} 
		else 
		{
			executeSkillFailNormal(pVampire, param.SkillType, NULL);
		}
	} 
	catch (Throwable & t) 
	{
		executeSkillFailException(pVampire, param.SkillType);
	}

	__END_CATCH
}

void SimpleTileMeleeSkill::execute(Ousters* pOusters, int X, int Y, OustersSkillSlot* pOustersSkillSlot,
	const SIMPLE_SKILL_INPUT& param, SIMPLE_SKILL_OUTPUT& result,
	CEffectID_t CEffectID, bool bForceKnockback) throw (Error)
{
	__BEGIN_TRY

	Assert(pOusters != NULL);
	Assert(pOustersSkillSlot != NULL);

	try 
	{
		Player* pPlayer = pOusters->getPlayer();
		Zone* pZone = pOusters->getZone();
		Assert(pPlayer != NULL);
		Assert(pZone != NULL);

		// ���� �� ����� Ư���� ���Ⱑ �־�� ������ �� �ִ� ����̶��...
		// �� �迭�� ���⸦ ��� �ִ����� üũ�ؼ� �ƴ϶�� ���д�.
		if (param.ItemClass != Item::ITEM_CLASS_MAX)
		{
			Item* pItem = pOusters->getWearItem(Ousters::WEAR_RIGHTHAND);
			if (pItem == NULL || pItem->getItemClass() != param.ItemClass)
			{
				executeSkillFailException(pOusters, param.SkillType);
				return;
			}

		}

		GCSkillToTileOK1 _GCSkillToTileOK1;
		GCSkillToTileOK2 _GCSkillToTileOK2;
		GCSkillToTileOK5 _GCSkillToTileOK5;

		SkillInfo*        pSkillInfo = g_pSkillInfoManager->getSkillInfo(param.SkillType);
		SkillLevel_t      SkillLevel = pOustersSkillSlot->getExpLevel();

		int  RequiredMP  = (int)pSkillInfo->getConsumeMP();
		bool bManaCheck  = hasEnoughMana(pOusters, RequiredMP);
		bool bTimeCheck  = verifyRunTime(pOustersSkillSlot);
		bool bRangeCheck = verifyDistance(pOusters, X, Y, pSkillInfo->getRange());

		// ������ �־�� �ϰ�, �ð��� �Ÿ� üũ�� �����ϰ�,
		if (bManaCheck && bTimeCheck && bRangeCheck)
		{
			// MP�� ����߸���.
			decreaseMana(pOusters, RequiredMP, _GCSkillToTileOK1);

			// ��ǥ�� ������ ���Ѵ�.
			ZoneCoord_t myX          = pOusters->getX();
			ZoneCoord_t myY          = pOusters->getY();	
			Dir_t       dir          = calcDirection(myX, myY, X, Y);
			Damage_t    Damage       = 0;
			Damage_t    MaxDamage    = 0;
			bool        bCriticalHit = false;
			bool        bHit         = false;

			VSRect rect(0, 0, pZone->getWidth()-1, pZone->getHeight()-1);

			list<Creature*> cList;

			list<TILE_MASK>::const_iterator itr = param.MaskList.begin();
			for (; itr != param.MaskList.end(); itr++)
			{
				TILE_MASK mask = (*itr);

				int tileX   = X + mask.x;
				int tileY   = Y + mask.y;
				int penalty = mask.penalty;

				// ���� Ÿ���� �� �����̰�, �������밡 �ƴ϶��, ���� Ȯ���� �ִ�.
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

						if (pTargetCreature->getObjectID() != pOusters->getObjectID())
						{
							bool bMoveModeCheck  = (pTargetCreature->getMoveMode() == Creature::MOVE_MODE_WALKING) ? true : false;
							bool bRaceCheck      = pTargetCreature->isNPC() || pTargetCreature->isOusters();
							bool bHitRoll        = false;
							bool bCanHit         = canHit(pOusters, pTargetCreature, param.SkillType);
							bool bPK             = verifyPK(pOusters, pTargetCreature);
							bool bZoneLevelCheck = checkZoneLevelToHitTarget(pTargetCreature);
							bool bSetMinDamage	 = false;

							if (param.bMagicHitRoll)
							{
								bHitRoll = HitRoll::isSuccessMagic(pOusters, pSkillInfo, pOustersSkillSlot);
							}
							else
							{
								bHitRoll = HitRoll::isSuccess(pOusters, pTargetCreature, SkillLevel/2);
							}

							if ( !canAttack( pOusters, pTargetCreature )
							||	pTargetCreature->isFlag(Effect::EFFECT_CLASS_COMA)) // 2003.3.14
							{
								bHitRoll = false; 
							}

							if (bMoveModeCheck && !bRaceCheck && bHitRoll && bCanHit && bPK && bZoneLevelCheck)
							{
								CheckCrossCounter(pOusters, pTargetCreature, Damage, pSkillInfo->getRange());

								bCriticalHit = false;
								Damage       = 0;

								if (param.bAdd)
								{
									Damage += computeDamage(pOusters, pTargetCreature, SkillLevel/5, bCriticalHit);
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

								// ���Ƽ�� �⺻������ 100�̴�.
								Damage = getPercentValue(Damage, penalty);

								ObjectID_t targetObjectID = pTargetCreature->getObjectID();
								cList.push_back(pTargetCreature);

								_GCSkillToTileOK1.addCListElement(targetObjectID);
								_GCSkillToTileOK2.addCListElement(targetObjectID);
								_GCSkillToTileOK5.addCListElement(targetObjectID);

								// �ϴ� �´� ���� ���� ��?��?�� ���·� �� ä��, �������� �ش�.
								setDamage(pTargetCreature, Damage, pOusters, param.SkillType, NULL, &_GCSkillToTileOK1);
								computeAlignmentChange(pTargetCreature, Damage, pOusters, NULL, &_GCSkillToTileOK1);

								increaseAlignment(pOusters, pTargetCreature, _GCSkillToTileOK1);

								// ũ��Ƽ�� ��Ʈ��� ������ �ڷ� �������� �Ѵ�.
								if (bCriticalHit || bForceKnockback)
								{
									knockbackCreature(pZone, pTargetCreature, pOusters->getX(), pOusters->getY());
								}

								// ������ �ƿ콺��� �ƴ� ��쿡�� ���� �ɷ� �����Ѵ�. 
								if (!pTargetCreature->isOusters())
								{
									bHit = true;
								}

								if (pTargetCreature->isDead())
								{
//									int exp = computeCreatureExp(pTargetCreature, 100, pOusters);
									int exp = computeCreatureExp(pTargetCreature, 70, pOusters);
									shareOustersExp(pOusters, exp, _GCSkillToTileOK1);
								}
							}
						}
					} //for (; itr != objectList.end(); itr++) 
				} // if (rect.ptInRect(tileX, tileY) && ...
			} // for (int count=0; count<3; count++)


			decreaseDurability(pOusters, NULL, pSkillInfo, &_GCSkillToTileOK1, NULL);

			_GCSkillToTileOK1.setSkillType(param.SkillType);
			_GCSkillToTileOK1.setCEffectID(CEffectID);
			_GCSkillToTileOK1.setX(X);
			_GCSkillToTileOK1.setY(Y);
			_GCSkillToTileOK1.setRange(dir);
			_GCSkillToTileOK1.setDuration(0);
		
			_GCSkillToTileOK2.setObjectID(pOusters->getObjectID());
			_GCSkillToTileOK2.setSkillType(param.SkillType);
			_GCSkillToTileOK2.setX(X);
			_GCSkillToTileOK2.setY(Y);
			_GCSkillToTileOK2.setRange(dir);
			_GCSkillToTileOK2.setDuration(0);
		
			_GCSkillToTileOK5.setObjectID(pOusters->getObjectID());
			_GCSkillToTileOK5.setSkillType(param.SkillType);
			_GCSkillToTileOK5.setX(X);
			_GCSkillToTileOK5.setY(Y);
			_GCSkillToTileOK5.setRange(dir);
			_GCSkillToTileOK5.setDuration(0);
		
			pPlayer->sendPacket(&_GCSkillToTileOK1);
		
			// �� ����� ���� ������ �޴� ��鿡�� ��Ŷ??������� �Ѵ�.
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
					pMonster->addEnemy(pOusters);
				}
			}

			cList.push_back(pOusters);

			pZone->broadcastPacket(myX, myY, &_GCSkillToTileOK5 , cList);

			// set Next Run Time
			pOustersSkillSlot->setRunTime(param.Delay);

			result.bSuccess = true;
		} 
		else 
		{
			executeSkillFailNormal(pOusters, param.SkillType, NULL);
		}
	} 
	catch (Throwable & t) 
	{
		executeSkillFailException(pOusters, param.SkillType);
	}

	__END_CATCH
}

void SimpleTileMeleeSkill::execute(Monster* pMonster, int X, int Y,
	const SIMPLE_SKILL_INPUT& param,  SIMPLE_SKILL_OUTPUT& result,
	CEffectID_t CEffectID, bool bForceKnockback) throw (Error)
{
	__BEGIN_TRY

	Assert(pMonster != NULL);

	try 
	{
		Zone* pZone = pMonster->getZone();
		Assert(pZone != NULL);

		GCSkillToTileOK2 _GCSkillToTileOK2;
		GCSkillToTileOK5 _GCSkillToTileOK5;

		SkillInfo* pSkillInfo = g_pSkillInfoManager->getSkillInfo(param.SkillType);

		bool bRangeCheck = verifyDistance(pMonster, X, Y, pSkillInfo->getRange());

		// ������ �־�� �ϰ�, �ð��� �Ÿ� üũ�� �����ϰ�,
		if (bRangeCheck)
		{
			// ��ǥ�� ������ ���Ѵ�.
			ZoneCoord_t myX          = pMonster->getX();
			ZoneCoord_t myY          = pMonster->getY();	
			Dir_t       dir          = calcDirection(myX, myY, X, Y);
			Damage_t    Damage       = 0;
			Damage_t    MaxDamage    = 0;
			bool        bCriticalHit = false;

			VSRect rect(0, 0, pZone->getWidth()-1, pZone->getHeight()-1);

			list<Creature*> cList;

			list<TILE_MASK>::const_iterator itr = param.MaskList.begin();
			for (; itr != param.MaskList.end(); itr++)
			{
				TILE_MASK mask = (*itr);

				int tileX   = X + mask.x;
				int tileY   = Y + mask.y;
				int penalty = mask.penalty;

				// ���� Ÿ���� �� �����̰�, �������밡 �ƴ϶��, ���� Ȯ���� �ִ�.
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

						// ���� ����� �´��� Ȯ���Ѵ�.
						if (pMonster->isEnemyToAttack( pTargetCreature ))
						{
							bool bMoveModeCheck  = (pTargetCreature->getMoveMode() == Creature::MOVE_MODE_WALKING) ? true : false;
							bool bRaceCheck      = pTargetCreature->isNPC();// || pTargetCreature->isMonster();
							bool bHitRoll        = 0;
							bool bCanHit         = canHit(pMonster, pTargetCreature, param.SkillType) && canAttack( pMonster, pTargetCreature );
							bool bPK             = verifyPK(pMonster, pTargetCreature);
							bool bZoneLevelCheck = checkZoneLevelToHitTarget(pTargetCreature);

							if (param.bMagicHitRoll)
							{
								bHitRoll = HitRoll::isSuccessMagic(pMonster, pSkillInfo);
							}
							else
							{
								bHitRoll = HitRoll::isSuccess(pMonster, pTargetCreature, 0);
							}

							// bMoveModeCheck �ϴ°� ���⼭�� ����. ���Ͽ� �ִ� ��鵵 �������. 2003.10.27
							if (!bRaceCheck && bHitRoll && bCanHit && bPK && bZoneLevelCheck)
							{
								CheckCrossCounter(pMonster, pTargetCreature, Damage, pSkillInfo->getRange());

								bCriticalHit = false;
								Damage       = 0;

								if (param.bAdd)
								{
									Damage += computeDamage(pMonster, pTargetCreature, 0, bCriticalHit);
								}

								if (param.bMagicDamage)
								{
									Damage += computeMagicDamage(pTargetCreature, param.SkillDamage, param.SkillType);
								}
								else
								{
									Damage += param.SkillDamage;
								}

								MaxDamage = max(Damage, MaxDamage);

								// ���Ƽ�� �⺻������ 100�̴�.
								Damage = getPercentValue(Damage, penalty);

								ObjectID_t targetObjectID = pTargetCreature->getObjectID();
								cList.push_back(pTargetCreature);

								_GCSkillToTileOK2.addCListElement(targetObjectID);
								_GCSkillToTileOK5.addCListElement(targetObjectID);

								// �ϴ� �´� ���� ���� ��Ŷ�� �� ���·� �� ä��, �������� �ش�.
								setDamage(pTargetCreature, Damage, pMonster, param.SkillType, NULL, NULL);

								// ũ��Ƽ�� ��Ʈ��� ������ �ڷ� �������� �Ѵ�.
								// �ɾ�ٴϴ� ��鸸 knockback��Ų��.
								if ( bMoveModeCheck && (bCriticalHit || bForceKnockback) )
								{
									knockbackCreature(pZone, pTargetCreature, pMonster->getX(), pMonster->getY());
								}
							}
						}
					} //for (; itr != objectList.end(); itr++) 
				} // if (rect.ptInRect(tileX, tileY) && ...
			} // for (int count=0; count<3; count++)

			_GCSkillToTileOK2.setObjectID(pMonster->getObjectID());
			_GCSkillToTileOK2.setSkillType(param.SkillType);
			_GCSkillToTileOK2.setX(X);
			_GCSkillToTileOK2.setY(Y);
			_GCSkillToTileOK2.setRange(dir);
			_GCSkillToTileOK2.setDuration(0);
		
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
					Monster* pTargetMonster = dynamic_cast<Monster*>(pTargetCreature);
					pTargetMonster->addEnemy(pMonster);
				}
			}

			cList.push_back(pMonster);

			pZone->broadcastPacket(myX, myY, &_GCSkillToTileOK5 , cList);

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
