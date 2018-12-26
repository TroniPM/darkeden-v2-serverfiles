//////////////////////////////////////////////////////////////////////////////
// Filename    : SimpleMeleeSkill.cpp
// Written by  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "SimpleMeleeSkill.h"
#include "CrossCounter.h"

#include "Gpackets/GCSkillToObjectOK1.h"
#include "Gpackets/GCSkillToObjectOK2.h"
#include "Gpackets/GCSkillToObjectOK5.h"

SimpleMeleeSkill g_SimpleMeleeSkill;

//////////////////////////////////////////////////////////////////////////////
// class SimpleMeleeSkill member methods
//////////////////////////////////////////////////////////////////////////////

void SimpleMeleeSkill::execute(
	Slayer* pSlayer, ObjectID_t TargetObjectID, SkillSlot* pSkillSlot, 
	const SIMPLE_SKILL_INPUT& param, SIMPLE_SKILL_OUTPUT& result,
	CEffectID_t CEffectID)
	
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

		Creature* pTargetCreature = pZone->getCreature(TargetObjectID);
		//Assert(pTargetCreature != NULL);

		// NPC�� ������ ���� ����.
		// NoSuch����. by sigi. 2002.5.2
		if (pTargetCreature==NULL
			|| !canAttack( pSlayer, pTargetCreature )
			|| pTargetCreature->isNPC())
		{
			executeSkillFailException(pSlayer, param.SkillType);
			return;
		}

		result.pTargetCreature = pTargetCreature;

		// ���� �� ����� Ư���� ���Ⱑ �־�߸� ������ �� �ִ� ����̶��...
		// �� �Կ��� ���⸦ ��� �ִ����� üũ�ؼ� �ƴ϶�� ���д�.
		bool bIncreaseDomainExp = true;
		if (param.ItemClass != Item::ITEM_CLASS_MAX)
		{
			Item* pItem = pSlayer->getWearItem(Slayer::WEAR_RIGHTHAND);
			if (pItem == NULL || pItem->getItemClass() != param.ItemClass)
			{
				executeSkillFailException(pSlayer, param.SkillType);
				return;
			}

			bIncreaseDomainExp = pSlayer->isRealWearingEx(Slayer::WEAR_RIGHTHAND);
		}

		GCSkillToObjectOK1 _GCSkillToObjectOK1;
		GCSkillToObjectOK2 _GCSkillToObjectOK2;
		GCSkillToObjectOK5 _GCSkillToObjectOK5;

		SkillInfo*        pSkillInfo   = g_pSkillInfoManager->getSkillInfo(param.SkillType);
		SkillDomainType_t DomainType   = pSkillInfo->getDomainType();
		SkillLevel_t      SkillLevel   = pSkillSlot->getExpLevel();
		bool              bCriticalHit = false;
		Damage_t          Damage       = 0;

		if (param.bAdd)
		{
			// �Ķ���ͷ� ���޵� ������ ���� �������� ���������, 
			// �Ϲ� �������� ��� ��, �������� ���ؾ� �Ѵ�.
			// �Ķ���ͷ� ���޵� ������ ���� ���������� ���̴� ���������,
			// �� �κб��� ������ �����Ƿ�, ���� �κб��� 0���� ���޵ȴ�.
			Damage += computeDamage(pSlayer, pTargetCreature, SkillLevel/5, bCriticalHit);
		}

		if (param.bMagicDamage)
		{
			// ���� ��ų �������� ���� ���������, ���� ������ ��� �Լ��� �̿��� ����� ���ش�.
			Damage += computeMagicDamage(pTargetCreature, param.SkillDamage, param.SkillType);
		}
		else
		{
			Damage += param.SkillDamage;
		}

		int  RequiredMP  = (int)pSkillInfo->getConsumeMP();
		bool bManaCheck  = hasEnoughMana(pSlayer, RequiredMP);
		bool bTimeCheck  = verifyRunTime(pSkillSlot);
		bool bRangeCheck = verifyDistance(pSlayer, pTargetCreature, pSkillInfo->getRange());
		bool bHitRoll    = false;
		bool bCanHit     = canHit(pSlayer, pTargetCreature, param.SkillType);
		bool bPK         = verifyPK(pSlayer, pTargetCreature);

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
			Damage = getPercentValue( Damage, 7 );
			bHitRoll = true;
		}

		// ������ �־�� �ϰ�, �ð��� �Ÿ� üũ�� �����ϰ�,
		// hitroll�� �����ϰ�, ũ�ν� ī���Ͱ� �ɷ����� �ʴٸ�, �����̴�.
		if (bManaCheck && bTimeCheck && bRangeCheck && bHitRoll && bCanHit && bPK)
		{
			CheckCrossCounter(pSlayer, pTargetCreature, Damage, pSkillInfo->getRange());

			decreaseMana(pSlayer, RequiredMP, _GCSkillToObjectOK1);

			// �������� �ְ�, �������� ����߸���.
			setDamage(pTargetCreature, Damage, pSlayer, param.SkillType, &_GCSkillToObjectOK2, &_GCSkillToObjectOK1);
			computeAlignmentChange(pTargetCreature, Damage, pSlayer, &_GCSkillToObjectOK2, &_GCSkillToObjectOK1);
			decreaseDurability(pSlayer, pTargetCreature, pSkillInfo, &_GCSkillToObjectOK1, &_GCSkillToObjectOK2);

			// ũ��Ƽ�� ��Ʈ��� ������ �ڷ� �������� �Ѵ�.
			if (bCriticalHit)
			{
				knockbackCreature(pZone, pTargetCreature, pSlayer->getX(), pSlayer->getY());
			}

			// �����̾ �ƴ� ��쿡�� ����ġ�� �ö󰣴�.
			if (!pTargetCreature->isSlayer())
			{
				if (bIncreaseDomainExp)
				{
					shareAttrExp(pSlayer, Damage, param.STRMultiplier, param.DEXMultiplier, param.INTMultiplier, _GCSkillToObjectOK1);
					increaseDomainExp(pSlayer, DomainType, pSkillInfo->getPoint(), _GCSkillToObjectOK1, pTargetCreature->getLevel());
					increaseSkillExp(pSlayer, DomainType, pSkillSlot, pSkillInfo, _GCSkillToObjectOK1);
				}

				increaseAlignment(pSlayer, pTargetCreature, _GCSkillToObjectOK1);
			}

			// ��Ŷ�� �غ��ϰ�, ������. 
			_GCSkillToObjectOK1.setSkillType(param.SkillType);
			_GCSkillToObjectOK1.setCEffectID(CEffectID);
			_GCSkillToObjectOK1.setTargetObjectID(TargetObjectID);
			_GCSkillToObjectOK1.setDuration(0);
		
			_GCSkillToObjectOK2.setObjectID(pSlayer->getObjectID());
			_GCSkillToObjectOK2.setSkillType(param.SkillType);
			_GCSkillToObjectOK2.setDuration(0);
		
			_GCSkillToObjectOK5.setObjectID(pSlayer->getObjectID());
			_GCSkillToObjectOK5.setSkillType(param.SkillType);
			_GCSkillToObjectOK5.setTargetObjectID (TargetObjectID);
			_GCSkillToObjectOK5.setDuration(0);

			if ( param.SkillType == SKILL_TYPHOON )
			{
				if ( !pTargetCreature->isMonster() )
				{
					int TargetLevel = 0;

					if ( pTargetCreature->isSlayer() )
					{
						Slayer* pTargetSlayer = dynamic_cast<Slayer*>(pTargetCreature);
						Assert( pTargetSlayer != NULL );

						TargetLevel = pTargetSlayer->getHighestSkillDomainLevel();
					}
					else if ( pTargetCreature->isVampire() )
					{
						Vampire* pTargetVampire = dynamic_cast<Vampire*>(pTargetCreature);
						Assert( pTargetVampire != NULL );

						TargetLevel = pTargetVampire->getLevel();
					}
					else if ( pTargetCreature->isOusters() )
					{
						Ousters* pTargetOusters = dynamic_cast<Ousters*>(pTargetCreature);
						Assert( pTargetOusters != NULL );

						TargetLevel = pTargetOusters->getLevel();
					}
					
					int LevelDiff = pSlayer->getSkillDomainLevel( SKILL_DOMAIN_BLADE ) - TargetLevel;
					int Ratio = 0;

					if ( LevelDiff >= 10 )
					{
						Ratio = 100;
					}
					else if ( LevelDiff > 0 )
					{
						Ratio = 80;
					}
					else if ( LevelDiff == 0 )
					{
						Ratio = 60;
					}
					else if ( LevelDiff > -10 )
					{
						Ratio = 40;
					}
					else
					{
						Ratio = 20;
					}

					if ( (rand()%100)<Ratio )
					{
						// ���� ���ػѵ�!
						_GCSkillToObjectOK1.setGrade(1);
						_GCSkillToObjectOK2.setGrade(1);
						_GCSkillToObjectOK5.setGrade(1);
					}
				}
				else //������ ���
				{
					_GCSkillToObjectOK1.setGrade(1);
					_GCSkillToObjectOK2.setGrade(1);
					_GCSkillToObjectOK5.setGrade(1);
				}
			}
		
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

			list<Creature*> cList;
			cList.push_back(pSlayer);
			cList.push_back(pTargetCreature);

			pZone->broadcastPacket(pSlayer->getX(), pSlayer->getY(), &_GCSkillToObjectOK5, cList);

			pSkillSlot->setRunTime(param.Delay);

			result.bSuccess = true;
		} 
		else 
		{
			executeSkillFailNormal(pSlayer, param.SkillType, pTargetCreature );
		}
	} 
	catch (Throwable & t) 
	{
		executeSkillFailException(pSlayer, param.SkillType);
	}

	__END_CATCH
}

void SimpleMeleeSkill::execute(
	Vampire* pVampire, ObjectID_t TargetObjectID, VampireSkillSlot* pVampireSkillSlot,
	const SIMPLE_SKILL_INPUT& param, SIMPLE_SKILL_OUTPUT& result, 
	CEffectID_t CEffectID, int HitBonus) 
	
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

		Creature* pTargetCreature = pZone->getCreature(TargetObjectID);
		//Assert(pTargetCreature != NULL);

		// NPC�� ������ ���� ����.
		// NoSuch����. by sigi. 2002.5.2
		if (pTargetCreature==NULL
			|| !canAttack( pVampire, pTargetCreature )
			|| pTargetCreature->isNPC())
		{
			executeSkillFailException(pVampire, param.SkillType);
			return;
		}

		result.pTargetCreature = pTargetCreature;

		GCSkillToObjectOK1 _GCSkillToObjectOK1;
		GCSkillToObjectOK2 _GCSkillToObjectOK2;
		GCSkillToObjectOK5 _GCSkillToObjectOK5;

		SkillInfo* pSkillInfo   = g_pSkillInfoManager->getSkillInfo(param.SkillType);
		bool       bCriticalHit = false;
		Damage_t   Damage       = 0;

		if (param.bAdd)
		{
			// �Ķ���ͷ� ���޵� ������ ���� �������� ���������, 
			// �Ϲ� �������� ��� ��, �������� ���ؾ� �Ѵ�.
			// �Ķ���ͷ� ���޵� ������ ���� ���������� ���̴� ���������,
			// �� �κб��� ������ �����Ƿ�, ���� �κб��� 0���� ���޵ȴ�.
			Damage += computeDamage(pVampire, pTargetCreature, 0, bCriticalHit);
		}

		if (param.bMagicDamage)
		{
			// ���� ��ų �������� ���� ���������, ���� ������ ��� �Լ��� �̿��� ����� ���ش�.
			Damage += computeMagicDamage(pTargetCreature, param.SkillDamage, param.SkillType, true, pVampire);
		}
		else
		{
			Damage += param.SkillDamage;
		}

		int  RequiredMP         = decreaseConsumeMP(pVampire, pSkillInfo);
		bool bManaCheck         = hasEnoughMana(pVampire, RequiredMP);
		bool bTimeCheck         = verifyRunTime(pVampireSkillSlot);
		bool bRangeCheck        = verifyDistance(pVampire, pTargetCreature, pSkillInfo->getRange());
		bool bHitRoll           = false;
		bool bCanHit            = canHit(pVampire, pTargetCreature, param.SkillType);
		bool bPK                = verifyPK(pVampire, pTargetCreature);

		if (param.bMagicHitRoll)
		{
			bHitRoll = HitRoll::isSuccessMagic(pVampire, pSkillInfo, pVampireSkillSlot, HitBonus);
		}
		else 
		{
			bHitRoll = HitRoll::isSuccess(pVampire, pTargetCreature);
		}

		if (bManaCheck && bTimeCheck && bRangeCheck && bHitRoll && bCanHit && bPK)
		{
			CheckCrossCounter(pVampire, pTargetCreature, Damage);

			// ������ ��´�.
			decreaseMana(pVampire, RequiredMP, _GCSkillToObjectOK1);
		
			// �������� ���ϰ�, ������ �������� ����߸���.
			setDamage(pTargetCreature, Damage, pVampire, param.SkillType, &_GCSkillToObjectOK2, &_GCSkillToObjectOK1);
			computeAlignmentChange(pTargetCreature, Damage, pVampire, &_GCSkillToObjectOK2, &_GCSkillToObjectOK1);
			decreaseDurability(pVampire, pTargetCreature, pSkillInfo, &_GCSkillToObjectOK1, &_GCSkillToObjectOK2);

			// ũ��Ƽ�� ��Ʈ��� ������ �ڷ� �������� �Ѵ�.
			if (bCriticalHit)
			{
				knockbackCreature(pZone, pTargetCreature, pVampire->getX(), pVampire->getY());
			}

			// �̹� �������� ��밡 �׾��ٸ� ����ġ�� �ö󰣴�.
			if (pTargetCreature->isDead())
			{
				int exp = computeCreatureExp(pTargetCreature, KILL_EXP);
				shareVampExp(pVampire, exp, _GCSkillToObjectOK1);
			}

			increaseAlignment(pVampire, pTargetCreature, _GCSkillToObjectOK1);

			// ��Ŷ�� ������.
			_GCSkillToObjectOK1.setSkillType(param.SkillType);
			_GCSkillToObjectOK1.setCEffectID(CEffectID);
			_GCSkillToObjectOK1.setTargetObjectID(TargetObjectID);
			_GCSkillToObjectOK1.setDuration(0);

			_GCSkillToObjectOK2.setObjectID(pVampire->getObjectID());
			_GCSkillToObjectOK2.setSkillType(param.SkillType);
			_GCSkillToObjectOK2.setDuration(0);

			_GCSkillToObjectOK5.setObjectID(pVampire->getObjectID());
			_GCSkillToObjectOK5.setTargetObjectID(TargetObjectID);
			_GCSkillToObjectOK5.setSkillType(param.SkillType);

			pPlayer->sendPacket(&_GCSkillToObjectOK1);

			Player* pTargetPlayer = NULL;

			if (pTargetCreature->isPC()) 
			{
				pTargetPlayer = pTargetCreature->getPlayer();
				Assert(pTargetPlayer != NULL);
				pTargetPlayer->sendPacket(&_GCSkillToObjectOK2);
			} 
			else 
			{
				Monster* pMonster = dynamic_cast<Monster*>(pTargetCreature);
				pMonster->addEnemy(pVampire);
			}

			list<Creature*> cList;
			cList.push_back(pVampire);
			cList.push_back(pTargetCreature);

			cList = pZone->broadcastSkillPacket(pVampire->getX(), pVampire->getY(),
				pTargetCreature->getX(), pTargetCreature->getY(), &_GCSkillToObjectOK5, cList);

			pVampireSkillSlot->setRunTime(param.Delay);

			result.bSuccess = true;
		} 
		else
		{
			executeSkillFailNormal(pVampire, param.SkillType, pTargetCreature );
		}
	} 
	catch(Throwable & t) 
	{
		executeSkillFailException(pVampire, param.SkillType);
	}

	__END_CATCH
}


void SimpleMeleeSkill::execute(
	Ousters* pOusters, ObjectID_t TargetObjectID, OustersSkillSlot* pOustersSkillSlot,
	const SIMPLE_SKILL_INPUT& param, SIMPLE_SKILL_OUTPUT& result, 
	CEffectID_t CEffectID, int HitBonus) 
	
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

		Creature* pTargetCreature = pZone->getCreature(TargetObjectID);

		// NPC�� ������ ���� ����.
		// NoSuch����. by sigi. 2002.5.2
		if (pTargetCreature==NULL
			|| !canAttack( pOusters, pTargetCreature )
			|| pTargetCreature->isNPC())
		{
			executeSkillFailException(pOusters, param.SkillType, param.Grade);
			return;
		}

		result.pTargetCreature = pTargetCreature;

		GCSkillToObjectOK1 _GCSkillToObjectOK1;
		GCSkillToObjectOK2 _GCSkillToObjectOK2;
		GCSkillToObjectOK5 _GCSkillToObjectOK5;

		if (param.ItemClass != Item::ITEM_CLASS_MAX)
		{
			Item* pItem = pOusters->getWearItem(Ousters::WEAR_RIGHTHAND);
			if (pItem == NULL || pItem->getItemClass() != param.ItemClass || !pOusters->isRealWearingEx(Ousters::WEAR_RIGHTHAND))
			{
				executeSkillFailException(pOusters, param.SkillType, param.Grade);
				return;
			}
		}

		SkillInfo* pSkillInfo   = g_pSkillInfoManager->getSkillInfo(param.SkillType);
		bool       bCriticalHit = false;
		Damage_t   Damage       = 0;

		if (param.bAdd)
		{
			// �Ķ���ͷ� ���޵� ������ ���� �������� ���������, 
			// �Ϲ� �������� ��� ��, �������� ���ؾ� �Ѵ�.
			// �Ķ���ͷ� ���޵� ������ ���� ���������� ���̴� ���������,
			// �� �κб��� ������ �����Ƿ�, ���� �κб��� 0���� ���޵ȴ�.
			Damage += computeDamage(pOusters, pTargetCreature, 0, bCriticalHit);
		}

		if (param.bMagicDamage)
		{
			// ���� ��ų �������� ���� ���������, ���� ������ ��� �Լ��� �̿��� ����� ���ش�.
			//Damage += computeMagicDamage(pTargetCreature, param.SkillDamage, param.SkillType, true);
			Damage += computeOustersMagicDamage( pOusters, pTargetCreature, param.SkillDamage, param.SkillType );
		}
		else
		{
			Damage += param.SkillDamage;
		}

		computeCriticalBonus(pOusters, param.SkillType, Damage, bCriticalHit);

		int  RequiredMP         = (int)pSkillInfo->getConsumeMP();
		bool bManaCheck         = hasEnoughMana(pOusters, RequiredMP);
		bool bTimeCheck         = verifyRunTime(pOustersSkillSlot);
		bool bRangeCheck        = verifyDistance(pOusters, pTargetCreature, pSkillInfo->getRange());
		bool bHitRoll           = false;
		bool bCanHit            = canHit(pOusters, pTargetCreature, param.SkillType);
		bool bPK                = verifyPK(pOusters, pTargetCreature);
		bool bSatisfyRequire	= pOusters->satisfySkillRequire( pSkillInfo );

		if (param.bMagicHitRoll)
		{
			bHitRoll = HitRoll::isSuccessMagic(pOusters, pSkillInfo, pOustersSkillSlot, HitBonus);
		}
		else 
		{
			int Bonus = 0;
			if ( pSkillInfo->getType() == SKILL_FATAL_SNICK )
			{
				OustersSkillSlot* pMastery = pOusters->hasSkill( SKILL_FATAL_SNICK_MASTERY );
				if ( pMastery != NULL )
				{
					Bonus = pMastery->getExpLevel();
				}
			}

			bHitRoll = HitRoll::isSuccess(pOusters, pTargetCreature, Bonus);
		}

		if (bManaCheck && bTimeCheck && bRangeCheck && bHitRoll && bCanHit && bPK && bSatisfyRequire )
		{
			if ( pSkillInfo->getElementalDomain() == ELEMENTAL_DOMAIN_COMBAT )
				Damage += computeElementalCombatSkill( pOusters, pTargetCreature, _GCSkillToObjectOK1 );
			CheckCrossCounter(pOusters, pTargetCreature, Damage);

			// ������ ��´�.
			decreaseMana(pOusters, RequiredMP, _GCSkillToObjectOK1);
		
			// �������� ���ϰ�, ������ �������� ����߸���.
			setDamage(pTargetCreature, Damage, pOusters, param.SkillType, &_GCSkillToObjectOK2, &_GCSkillToObjectOK1);
			computeAlignmentChange(pTargetCreature, Damage, pOusters, &_GCSkillToObjectOK2, &_GCSkillToObjectOK1);
			decreaseDurability(pOusters, pTargetCreature, pSkillInfo, &_GCSkillToObjectOK1, &_GCSkillToObjectOK2);

			// ũ��Ƽ�� ��Ʈ��� ������ �ڷ� �������� �Ѵ�.
			if (bCriticalHit)
			{
				knockbackCreature(pZone, pTargetCreature, pOusters->getX(), pOusters->getY());
			}

			// �̹� �������� ��밡 �׾��ٸ� ����ġ�� �ö󰣴�.
			if (pTargetCreature->isDead())
			{
				int exp = computeCreatureExp(pTargetCreature, 100, pOusters);
				shareOustersExp(pOusters, exp, _GCSkillToObjectOK1);
			}

			increaseAlignment(pOusters, pTargetCreature, _GCSkillToObjectOK1);

			// ��Ŷ�� ������.
			_GCSkillToObjectOK1.setSkillType(param.SkillType);
			_GCSkillToObjectOK1.setCEffectID(CEffectID);
			_GCSkillToObjectOK1.setTargetObjectID(TargetObjectID);
			_GCSkillToObjectOK1.setDuration(0);
			_GCSkillToObjectOK1.setGrade(param.Grade);

			_GCSkillToObjectOK2.setObjectID(pOusters->getObjectID());
			_GCSkillToObjectOK2.setSkillType(param.SkillType);
			_GCSkillToObjectOK2.setDuration(0);
			_GCSkillToObjectOK2.setGrade(param.Grade);

			_GCSkillToObjectOK5.setObjectID(pOusters->getObjectID());
			_GCSkillToObjectOK5.setTargetObjectID(TargetObjectID);
			_GCSkillToObjectOK5.setSkillType(param.SkillType);
			_GCSkillToObjectOK5.setGrade(param.Grade);

			pPlayer->sendPacket(&_GCSkillToObjectOK1);

			Player* pTargetPlayer = NULL;

			if (pTargetCreature->isPC()) 
			{
				pTargetPlayer = pTargetCreature->getPlayer();
				Assert(pTargetPlayer != NULL);
				pTargetPlayer->sendPacket(&_GCSkillToObjectOK2);
			} 
			else 
			{
				Monster* pMonster = dynamic_cast<Monster*>(pTargetCreature);
				pMonster->addEnemy(pOusters);
			}

			list<Creature*> cList;
			cList.push_back(pOusters);
			cList.push_back(pTargetCreature);

			cList = pZone->broadcastSkillPacket(pOusters->getX(), pOusters->getY(),
				pTargetCreature->getX(), pTargetCreature->getY(), &_GCSkillToObjectOK5, cList);

			pOustersSkillSlot->setRunTime(param.Delay);

			result.bSuccess = true;
		} 
		else
		{
			executeSkillFailNormal(pOusters, param.SkillType, pTargetCreature, param.Grade );
		}
	} 
	catch(Throwable & t) 
	{
		executeSkillFailException(pOusters, param.SkillType, param.Grade);
	}

	__END_CATCH
}

void SimpleMeleeSkill::execute(
	Monster* pMonster, Creature* pEnemy, 
	const SIMPLE_SKILL_INPUT& param, SIMPLE_SKILL_OUTPUT& result, 
	CEffectID_t CEffectID) 
	
{
	__BEGIN_TRY

	Assert(pMonster != NULL);
	Assert(pEnemy != NULL);

	try
	{
		Zone* pZone = pMonster->getZone();
		Assert(pZone != NULL);

		if (pMonster->isFlag(Effect::EFFECT_CLASS_HIDE))
		{
			return;
		}
		if (pMonster->isFlag(Effect::EFFECT_CLASS_INVISIBILITY))
		{
			addVisibleCreature(pZone, pMonster, true);
		}

		result.pTargetCreature = pEnemy;

		GCSkillToObjectOK2 _GCSkillToObjectOK2;
		GCSkillToObjectOK5 _GCSkillToObjectOK5;

		SkillInfo* pSkillInfo   = g_pSkillInfoManager->getSkillInfo(param.SkillType);
		bool       bCriticalHit = false;
		Damage_t   Damage       = 0;

		if (param.bAdd)
		{
			// �Ķ���ͷ� ���޵� ������ ���� �������� ���������, 
			// �Ϲ� �������� ��� ��, �������� ���ؾ� �Ѵ�.
			// �Ķ���ͷ� ���޵� ������ ���� ���������� ���̴� ���������,
			// �� �κб��� ������ �����Ƿ�, ���� �κб��� 0���� ���޵ȴ�.
			Damage += computeDamage(pMonster, pEnemy, 0, bCriticalHit);
		}

		if (param.bMagicDamage)
		{
			// ���� ��ų �������� ���� ���������, ���� ������ ��� �Լ��� �̿��� ����� ���ش�.
			Damage += computeMagicDamage(pEnemy, param.SkillDamage, param.SkillType);
		}
		else
		{
			Damage += param.SkillDamage;
		}

		bool bRangeCheck = verifyDistance(pMonster, pEnemy, pMonster->getMeleeRange());
		bool bHitRoll    = false;
		bool bCanHit     = canHit(pMonster, pEnemy, param.SkillType);

		if (param.bMagicHitRoll)
		{
			bHitRoll = HitRoll::isSuccessMagic(pMonster, pSkillInfo);
		}
		else 
		{
			bHitRoll = HitRoll::isSuccess(pMonster, pEnemy);
		}

		// ��������� ����.
		if (bRangeCheck && bHitRoll && bCanHit) 
		{
			CheckCrossCounter(pMonster, pEnemy, Damage);

			// �������� ���ϰ�, ������ �������� ����߸���.
			setDamage(pEnemy, Damage, pMonster, param.SkillType, &_GCSkillToObjectOK2);
			decreaseDurability(pMonster, pEnemy, pSkillInfo, NULL, &_GCSkillToObjectOK2);

			// ũ��Ƽ�� ��Ʈ��� ������ �ڷ� �������� �Ѵ�.
			if (bCriticalHit)
			{
				knockbackCreature(pZone, pEnemy, pMonster->getX(), pMonster->getY());
			}

			// ��Ŷ�� ������.
			_GCSkillToObjectOK2.setObjectID(pMonster->getObjectID());
			_GCSkillToObjectOK2.setSkillType(param.SkillType);
			_GCSkillToObjectOK2.setDuration(0);

			_GCSkillToObjectOK5.setObjectID(pMonster->getObjectID());
			_GCSkillToObjectOK5.setTargetObjectID(pEnemy->getObjectID());
			_GCSkillToObjectOK5.setSkillType(param.SkillType);

			if (pEnemy->isPC()) 
			{
				Player* pTargetPlayer = pEnemy->getPlayer();
				Assert(pTargetPlayer != NULL);
				pTargetPlayer->sendPacket(&_GCSkillToObjectOK2);
			} 
			else if (pEnemy->isMonster())
			{
				Monster* pTargetMonster = dynamic_cast<Monster*>(pEnemy);
				pTargetMonster->addEnemy(pMonster);
			}

			list<Creature*> cList;
			cList.push_back(pMonster);
			cList.push_back(pEnemy);

			cList = pZone->broadcastSkillPacket(pMonster->getX(), pMonster->getY(), pEnemy->getX(), pEnemy->getY(), &_GCSkillToObjectOK5, cList);

			result.bSuccess = true;
		} 
		else
		{
			executeSkillFailNormal(pMonster, param.SkillType, pEnemy);
		}
	}
	catch (Throwable & t)
	{
		executeSkillFailException(pMonster, param.SkillType);
	}

	__END_CATCH
}
