//////////////////////////////////////////////////////////////////////////////
// Filename    : Seduction.cpp
// Written by  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "Seduction.h"
#include "EffectSeduction.h"
#include "RankBonus.h"
#include "PlayerCreature.h"
#include "Gpackets/GCSkillToObjectOK1.h"
#include "Gpackets/GCSkillToObjectOK2.h"
#include "Gpackets/GCSkillToObjectOK3.h"
#include "Gpackets/GCSkillToObjectOK4.h"
#include "Gpackets/GCSkillToObjectOK5.h"
#include "Gpackets/GCSkillToObjectOK6.h"
#include "Gpackets/GCAddEffect.h"
#include "Reflection.h"

//////////////////////////////////////////////////////////////////////////////
// �����̾� ������Ʈ �ڵ鷯
//////////////////////////////////////////////////////////////////////////////
void Seduction::execute(Vampire* pVampire, ObjectID_t TargetObjectID, VampireSkillSlot* pSkillSlot, CEffectID_t CEffectID)
	
{
	__BEGIN_TRY
		
	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << "begin " << endl;

	Assert(pVampire != NULL);
	Assert(pSkillSlot != NULL);
	
	try 
	{
		Player* pPlayer = pVampire->getPlayer();
		PlayerCreature* pAPC = dynamic_cast<PlayerCreature*>(pVampire);
		Zone* pZone = pVampire->getZone();
		Assert(pPlayer != NULL);
		Assert(pZone != NULL);

		Creature* pTargetCreature = pZone->getCreature(TargetObjectID);
		//Assert(pTargetCreature != NULL);

		// NPC�� ������ �� ����.
		// ���� �鿪. by sigi. 2002.9.13
		// NoSuch����. by sigi. 2002.5.2
		if (pTargetCreature==NULL
			|| pTargetCreature->isFlag(Effect::EFFECT_CLASS_IMMUNE_TO_CURSE)
			|| !canAttack( pVampire, pTargetCreature )
			|| pTargetCreature->isNPC())
		{
			executeSkillFailException(pVampire, getSkillType());
			//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " end " << endl;
			return;
		}

		GCSkillToObjectOK1 _GCSkillToObjectOK1;
		GCSkillToObjectOK2 _GCSkillToObjectOK2;
		GCSkillToObjectOK3 _GCSkillToObjectOK3;
		GCSkillToObjectOK4 _GCSkillToObjectOK4;
		GCSkillToObjectOK5 _GCSkillToObjectOK5;
		GCSkillToObjectOK6 _GCSkillToObjectOK6;

		SkillType_t SkillType  = pSkillSlot->getSkillType();
		SkillInfo*  pSkillInfo = g_pSkillInfoManager->getSkillInfo(SkillType);

		// Knowledge of Curse �� �ִٸ� hit bonus 10
		int HitBonus = 0;
		if ( pVampire->hasRankBonus( RankBonus::RANK_BONUS_KNOWLEDGE_OF_CURSE ) )
		{
			RankBonus* pRankBonus = pVampire->getRankBonus( RankBonus::RANK_BONUS_KNOWLEDGE_OF_CURSE );
			Assert( pRankBonus != NULL );

			HitBonus = pRankBonus->getPoint();
		}

		int  RequiredMP  = decreaseConsumeMP(pVampire, pSkillInfo);
		bool bManaCheck  = hasEnoughMana(pVampire, RequiredMP);
		bool bTimeCheck  = verifyRunTime(pSkillSlot);
		bool bRangeCheck = verifyDistance(pVampire, pTargetCreature, pSkillInfo->getRange());
		bool bHitRoll    = HitRoll::isSuccessVampireCurse(pSkillInfo->getLevel(), pTargetCreature->getResist(MAGIC_DOMAIN_CURSE)-pAPC->getYouReg());
		bool bHitRoll2   = HitRoll::isSuccessMagic(pVampire, pSkillInfo, pSkillSlot, HitBonus);
		bool bCanHit     = canHit(pVampire, pTargetCreature, SkillType);
		bool bEffected   = pTargetCreature->isFlag(Effect::EFFECT_CLASS_SEDUCTION);
		bool bPK         = verifyPK(pVampire, pTargetCreature);

		ZoneCoord_t targetX = pTargetCreature->getX();
		ZoneCoord_t targetY = pTargetCreature->getY();
		ZoneCoord_t myX     = pVampire->getX();
		ZoneCoord_t myY     = pVampire->getY();

		if (bManaCheck && bTimeCheck && bRangeCheck && bHitRoll && bHitRoll2 && bCanHit && !bEffected && bPK)
		{
			decreaseMana(pVampire, RequiredMP, _GCSkillToObjectOK1);

        	bool bCanSeeCaster = canSee(pTargetCreature, pVampire);

			SkillInput input(pVampire);
			SkillOutput output;
			computeOutput(input, output);

			// pTargetCreature�� ���ָ����� �ݻ��ϴ� ���
			if (CheckReflection(pVampire, pTargetCreature, getSkillType()))
			{
				pTargetCreature = (Creature*)pVampire;
				TargetObjectID = pVampire->getObjectID();
			}


			// ����Ʈ ������Ʈ�� ������ ���δ�.
			EffectSeduction* pEffect = new EffectSeduction(pTargetCreature);
			pEffect->setDeadline(output.Duration);
			pEffect->setLevel(pSkillInfo->getLevel()/2);
			pEffect->setToHitPenalty(output.Damage);
			pEffect->setDamagePenalty(output.Damage);
			pTargetCreature->setFlag(Effect::EFFECT_CLASS_SEDUCTION);
			pTargetCreature->addEffect(pEffect);

			// �ɷ�ġ�� ����ؼ� �����ش�.
			if (pTargetCreature->isSlayer())
			{
				Slayer* pTargetSlayer = dynamic_cast<Slayer*>(pTargetCreature);

				if (bCanSeeCaster) 
				{
					SLAYER_RECORD prev;
					pTargetSlayer->getSlayerRecord(prev);
					pTargetSlayer->initAllStat();
					pTargetSlayer->addModifyInfo(prev, _GCSkillToObjectOK2);
				} 
				else 
				{
					SLAYER_RECORD prev;
					pTargetSlayer->getSlayerRecord(prev);
					pTargetSlayer->initAllStat();
					pTargetSlayer->addModifyInfo(prev, _GCSkillToObjectOK6);
				}
			}
			else if (pTargetCreature->isVampire())
			{
				Vampire* pTargetVampire = dynamic_cast<Vampire*>(pTargetCreature);
				VAMPIRE_RECORD prev;

				pTargetVampire->getVampireRecord(prev);
				pTargetVampire->initAllStat();
				pTargetVampire->addModifyInfo(prev, _GCSkillToObjectOK2);
			}
			else if (pTargetCreature->isOusters())
			{
				Ousters* pTargetOusters = dynamic_cast<Ousters*>(pTargetCreature);
				OUSTERS_RECORD prev;

				pTargetOusters->getOustersRecord(prev);
				pTargetOusters->initAllStat();
				pTargetOusters->addModifyInfo(prev, _GCSkillToObjectOK2);
			}
			else if (pTargetCreature->isMonster())
			{
				Monster* pTargetMonster = dynamic_cast<Monster*>(pTargetCreature);
				pTargetMonster->initAllStat();
			}
			else Assert(false);
								
			_GCSkillToObjectOK1.setSkillType(SkillType);
			_GCSkillToObjectOK1.setCEffectID(CEffectID);
			_GCSkillToObjectOK1.setTargetObjectID(TargetObjectID);
			_GCSkillToObjectOK1.setDuration(output.Duration);
		
			_GCSkillToObjectOK2.setObjectID(pVampire->getObjectID());
			_GCSkillToObjectOK2.setSkillType(SkillType);
			_GCSkillToObjectOK2.setDuration(output.Duration);
		
			_GCSkillToObjectOK3.setObjectID(pVampire->getObjectID());
			_GCSkillToObjectOK3.setSkillType(SkillType);
			_GCSkillToObjectOK3.setTargetXY (targetX, targetY);
			
			_GCSkillToObjectOK4.setSkillType(SkillType);
			_GCSkillToObjectOK4.setTargetObjectID(TargetObjectID);
			_GCSkillToObjectOK4.setDuration(output.Duration);
			
			_GCSkillToObjectOK5.setObjectID(pVampire->getObjectID());
			_GCSkillToObjectOK5.setSkillType(SkillType);
			_GCSkillToObjectOK5.setTargetObjectID (TargetObjectID);
			_GCSkillToObjectOK5.setDuration(output.Duration);
			
			_GCSkillToObjectOK6.setXY(myX, myY);
			_GCSkillToObjectOK6.setSkillType(SkillType);
			_GCSkillToObjectOK6.setDuration(output.Duration);

			if (bCanSeeCaster) // 10�� ���� ��ġ��.
			{
				computeAlignmentChange(pTargetCreature, 10, pVampire, &_GCSkillToObjectOK2, &_GCSkillToObjectOK1);
			}
			else // 10�� ���� ��ġ��.
			{
				computeAlignmentChange(pTargetCreature, 10, pVampire, &_GCSkillToObjectOK6, &_GCSkillToObjectOK1);
			}
								
			list<Creature *> cList;
			cList.push_back(pTargetCreature);
			cList.push_back(pVampire);
			cList = pZone->broadcastSkillPacket(myX, myY, targetX, targetY, &_GCSkillToObjectOK5, cList);

			pZone->broadcastPacket(myX, myY, &_GCSkillToObjectOK3, cList);
			pZone->broadcastPacket(targetX, targetY, &_GCSkillToObjectOK4, cList);

			// Send Packet
			pPlayer->sendPacket(&_GCSkillToObjectOK1);

			if (pTargetCreature->isPC()) 
			{
				Player* pTargetPlayer = pTargetCreature->getPlayer();
				if (pTargetPlayer == NULL)
				{
					//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " end " << endl;
					return;
				}

				if (bCanSeeCaster) pTargetPlayer->sendPacket(&_GCSkillToObjectOK2);
				else pTargetPlayer->sendPacket(&_GCSkillToObjectOK6);
			}
			else if (pTargetCreature->isMonster())
			{
				Monster* pTargetMonster = dynamic_cast<Monster*>(pTargetCreature);
				pTargetMonster->addEnemy(pVampire);
			}

			GCAddEffect gcAddEffect;
			gcAddEffect.setObjectID(TargetObjectID);
			gcAddEffect.setEffectID(Effect::EFFECT_CLASS_SEDUCTION);
			gcAddEffect.setDuration(output.Duration);
			pZone->broadcastPacket(targetX, targetY, &gcAddEffect);
			
			pSkillSlot->setRunTime(output.Delay);
		} 
		else 
		{
			executeSkillFailNormal(pVampire, getSkillType(), pTargetCreature);
		}
	}
	catch (Throwable & t) 
	{
		executeSkillFailException(pVampire, getSkillType());
	}

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " end " << endl;

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// ���� ������Ʈ �ڵ鷯
//////////////////////////////////////////////////////////////////////////////
void Seduction::execute(Monster* pMonster, Creature* pEnemy)
	
{
	__BEGIN_TRY
		
	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << "begin " << endl;

	Assert(pMonster != NULL);
	
	try 
	{
		Zone* pZone = pMonster->getZone();
		Assert(pZone != NULL);

		if (pMonster->isFlag(Effect::EFFECT_CLASS_HIDE))
		{
			//cout << "Monster cannot use skill while hiding." << endl;
			//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End(monster)" << endl;
			return;
		}
		if (pMonster->isFlag(Effect::EFFECT_CLASS_INVISIBILITY))
		{
			addVisibleCreature(pZone, pMonster, true);
		}

		if (pMonster->isMaster())
		{
			int x = pMonster->getX();
			int y = pMonster->getY();
			int Splash = 3 + rand()%5; // 3~7 ����
			int range = 2;	// 5x5
			list<Creature*> creatureList;
			getSplashVictims(pMonster->getZone(), x, y, Creature::CREATURE_CLASS_MAX, creatureList, Splash, range);

			list<Creature*>::iterator itr = creatureList.begin();
			for (; itr != creatureList.end(); itr++)
			{
				Creature* pTargetCreature = (*itr);
				Assert(pTargetCreature != NULL);
			
				if (pMonster!=pTargetCreature)
					executeMonster(pZone, pMonster, pTargetCreature);
			}
		}
		else
		{
			executeMonster(pZone, pMonster, pEnemy);
		}
	}
	catch (Throwable & t) 
	{
		executeSkillFailException(pMonster, getSkillType());
	}

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " end " << endl;

	__END_CATCH
}

void Seduction::executeMonster(Zone* pZone, Monster* pMonster, Creature* pEnemy)
	
{
	__BEGIN_TRY

	if (!pMonster->isEnemyToAttack(pEnemy))
	{
		return;
	}

	GCSkillToObjectOK2 _GCSkillToObjectOK2;
	GCSkillToObjectOK3 _GCSkillToObjectOK3;
	GCSkillToObjectOK4 _GCSkillToObjectOK4;
	GCSkillToObjectOK5 _GCSkillToObjectOK5;
	GCSkillToObjectOK6 _GCSkillToObjectOK6;

	SkillType_t SkillType  = SKILL_SEDUCTION;
	SkillInfo*  pSkillInfo = g_pSkillInfoManager->getSkillInfo(SkillType);

	bool bRangeCheck = verifyDistance(pMonster, pEnemy, pSkillInfo->getRange());
	bool bHitRoll    = HitRoll::isSuccessCurse(pSkillInfo->getLevel()/2, pEnemy->getResist(MAGIC_DOMAIN_CURSE));
	bool bHitRoll2   = HitRoll::isSuccessMagic(pMonster, pSkillInfo);
	bool bCanHit     = canHit(pMonster, pEnemy, SkillType);
	bool bEffected   = pEnemy->isFlag(Effect::EFFECT_CLASS_SEDUCTION)
						|| pEnemy->isFlag(Effect::EFFECT_CLASS_IMMUNE_TO_CURSE);

	ZoneCoord_t targetX = pEnemy->getX();
	ZoneCoord_t targetY = pEnemy->getY();
	ZoneCoord_t myX     = pMonster->getX();
	ZoneCoord_t myY     = pMonster->getY();

	if (bRangeCheck && bHitRoll && bHitRoll2 && bCanHit && !bEffected)
	{
		bool bCanSeeCaster = canSee(pEnemy, pMonster);

		SkillInput input(pMonster);
		SkillOutput output;
		computeOutput(input, output);

		// pTargetCreature�� ���ָ����� �ݻ��ϴ� ���
		if (CheckReflection(pMonster, pEnemy, getSkillType()))
		{
			pEnemy = (Creature*)pMonster;
		}


		// ����Ʈ ������Ʈ�� ������ ���δ�.
		EffectSeduction* pEffect = new EffectSeduction(pEnemy);
		pEffect->setDeadline(output.Duration);
		pEffect->setLevel(pSkillInfo->getLevel()/2);
		pEffect->setToHitPenalty(output.Damage);
		pEffect->setDamagePenalty(output.Damage);
		pEnemy->setFlag(Effect::EFFECT_CLASS_SEDUCTION);
		pEnemy->addEffect(pEffect);

		// �ɷ�ġ�� ����ؼ� �����ش�.
		if (pEnemy->isSlayer())
		{
			Slayer* pTargetSlayer = dynamic_cast<Slayer*>(pEnemy);

			if (bCanSeeCaster) 
			{
				SLAYER_RECORD prev;
				pTargetSlayer->getSlayerRecord(prev);
				pTargetSlayer->initAllStat();
				pTargetSlayer->addModifyInfo(prev, _GCSkillToObjectOK2);
			} 
			else 
			{
				SLAYER_RECORD prev;
				pTargetSlayer->getSlayerRecord(prev);
				pTargetSlayer->initAllStat();
				pTargetSlayer->addModifyInfo(prev, _GCSkillToObjectOK6);
			}
		}
		else if (pEnemy->isVampire())
		{
			Vampire* pTargetVampire = dynamic_cast<Vampire*>(pEnemy);
			VAMPIRE_RECORD prev;

			pTargetVampire->getVampireRecord(prev);
			pTargetVampire->initAllStat();
			pTargetVampire->addModifyInfo(prev, _GCSkillToObjectOK2);
		}
		else if (pEnemy->isOusters())
		{
			Ousters* pTargetOusters = dynamic_cast<Ousters*>(pEnemy);
			OUSTERS_RECORD prev;

			pTargetOusters->getOustersRecord(prev);
			pTargetOusters->initAllStat();
			pTargetOusters->addModifyInfo(prev, _GCSkillToObjectOK2);
		}
		else if (pEnemy->isMonster())
		{
			Monster* pTargetMonster = dynamic_cast<Monster*>(pEnemy);
			pTargetMonster->initAllStat();
		}
		else Assert(false);
	
		_GCSkillToObjectOK2.setObjectID(pMonster->getObjectID());
		_GCSkillToObjectOK2.setSkillType(SkillType);
		_GCSkillToObjectOK2.setDuration(output.Duration);
	
		_GCSkillToObjectOK3.setObjectID(pMonster->getObjectID());
		_GCSkillToObjectOK3.setSkillType(SkillType);
		_GCSkillToObjectOK3.setTargetXY (targetX, targetY);
		
		_GCSkillToObjectOK4.setSkillType(SkillType);
		_GCSkillToObjectOK4.setTargetObjectID(pEnemy->getObjectID());
		_GCSkillToObjectOK4.setDuration(output.Duration);
		
		_GCSkillToObjectOK5.setObjectID(pMonster->getObjectID());
		_GCSkillToObjectOK5.setSkillType(SkillType);
		_GCSkillToObjectOK5.setTargetObjectID(pEnemy->getObjectID());
		_GCSkillToObjectOK5.setDuration(output.Duration);
		
		_GCSkillToObjectOK6.setXY(myX, myY);
		_GCSkillToObjectOK6.setSkillType(SkillType);
		_GCSkillToObjectOK6.setDuration(output.Duration);
							
		list<Creature *> cList;
		cList.push_back(pEnemy);
		cList.push_back(pMonster);
		cList = pZone->broadcastSkillPacket(myX, myY, targetX, targetY, &_GCSkillToObjectOK5, cList);
		pZone->broadcastPacket(myX, myY, &_GCSkillToObjectOK3, cList);
		pZone->broadcastPacket(targetX, targetY, &_GCSkillToObjectOK4, cList);

		if (pEnemy->isPC()) 
		{
			Player* pTargetPlayer = pEnemy->getPlayer();
			if (pTargetPlayer == NULL)
			{
				//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " end " << endl;
				return;
			}

			if (bCanSeeCaster) pTargetPlayer->sendPacket(&_GCSkillToObjectOK2);
			else pTargetPlayer->sendPacket(&_GCSkillToObjectOK6);
		}
		else if (pEnemy->isMonster())
		{
			Monster* pTargetMonster = dynamic_cast<Monster*>(pEnemy);
			pTargetMonster->addEnemy(pMonster);
		}

		GCAddEffect gcAddEffect;
		gcAddEffect.setObjectID(pEnemy->getObjectID());
		gcAddEffect.setEffectID(Effect::EFFECT_CLASS_SEDUCTION);
		gcAddEffect.setDuration(output.Duration);
		pZone->broadcastPacket(targetX, targetY, &gcAddEffect);
	} 
	else 
	{
		executeSkillFailNormal(pMonster, getSkillType(), pEnemy);
	}

	__END_CATCH
}

Seduction g_Seduction;
