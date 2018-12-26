//////////////////////////////////////////////////////////////////////////////
// Filename    : Paralyze.cpp
// Written by  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "Paralyze.h"
#include "EffectParalyze.h"
#include "Gpackets/GCSkillToObjectOK1.h"
#include "Gpackets/GCSkillToObjectOK2.h"
#include "Gpackets/GCSkillToObjectOK3.h"
#include "Gpackets/GCSkillToObjectOK4.h"
#include "Gpackets/GCSkillToObjectOK5.h"
#include "Gpackets/GCSkillToObjectOK6.h"
#include "Gpackets/GCSkillToSelfOK1.h"
#include "Gpackets/GCSkillToSelfOK2.h"
#include "Gpackets/GCStatusCurrentHP.h"
#include "Gpackets/GCAddEffect.h"
#include "Gpackets/GCRemoveEffect.h"
#include "Vampire.h"
#include "Ousters.h"
#include "Reflection.h"
#include "Tile.h"
#include "RankBonus.h"
#include "PlayerCreature.h"
//////////////////////////////////////////////////////////////////////////////
// �����̾� ������Ʈ �ڵ鷯
//////////////////////////////////////////////////////////////////////////////
void Paralyze::execute(Vampire* pVampire, ObjectID_t TargetObjectID, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID)
	
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << "begin " << endl;

	Assert(pVampire != NULL);
	Assert(pVampireSkillSlot != NULL);

	try 
	{
		Player* pPlayer = pVampire->getPlayer();
		PlayerCreature* pAPC = dynamic_cast<PlayerCreature*>(pVampire);
		Zone* pZone = pVampire->getZone();
		Assert(pPlayer != NULL);
		Assert(pZone != NULL);

		Creature* pTargetCreature = pZone->getCreature(TargetObjectID);
		SkillType_t       SkillType  = pVampireSkillSlot->getSkillType();

		// NPC�� ������ ���� ����.
		// �鿪�̰ų�. by sigi. 2002.9.13
		// NoSuch����. by sigi. 2002.5.2
		if (pTargetCreature==NULL
			|| pTargetCreature->isFlag(Effect::EFFECT_CLASS_IMMUNE_TO_PARALYZE)
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

		SkillInfo* pSkillInfo = g_pSkillInfoManager->getSkillInfo(SkillType);

		// Knowledge of Curse �� �ִٸ� hit bonus 10
		int HitBonus = 0;
		if ( pVampire->hasRankBonus( RankBonus::RANK_BONUS_KNOWLEDGE_OF_CURSE ) )
		{
			RankBonus* pRankBonus = pVampire->getRankBonus( RankBonus::RANK_BONUS_KNOWLEDGE_OF_CURSE );
			Assert( pRankBonus != NULL );

			HitBonus = pRankBonus->getPoint();
		}

		Tile& rTile = pZone->getTile( pTargetCreature->getX(), pTargetCreature->getY() );

		int  RequiredMP  = decreaseConsumeMP(pVampire, pSkillInfo);
		bool bManaCheck  = hasEnoughMana(pVampire, RequiredMP);
		bool bTimeCheck  = verifyRunTime(pVampireSkillSlot);
		bool bRangeCheck = verifyDistance(pVampire, pTargetCreature, pSkillInfo->getRange());
		bool bHitRoll    = HitRoll::isSuccessVampireCurse(pSkillInfo->getLevel(), pTargetCreature->getResist(MAGIC_DOMAIN_CURSE)-pAPC->getYouReg());
		bool bHitRoll2   = HitRoll::isSuccessMagic(pVampire, pSkillInfo, pVampireSkillSlot, HitBonus);
		bool bCanHit     = canHit(pVampire, pTargetCreature, SkillType);
		bool bEffected   = pTargetCreature->isFlag(Effect::EFFECT_CLASS_PARALYZE) || rTile.getEffect(Effect::EFFECT_CLASS_TRYING_POSITION)!=NULL;
		bool bPK         = verifyPK(pVampire, pTargetCreature);

		ZoneCoord_t vampX   = pVampire->getX();
		ZoneCoord_t vampY   = pVampire->getY();
		ZoneCoord_t targetX = pTargetCreature->getX();
		ZoneCoord_t targetY = pTargetCreature->getY();

		//if (bManaCheck && bTimeCheck && bRangeCheck && bHitRoll && bHitRoll2 && bCanHit && !bEffected && bPK)
		if (bManaCheck && bTimeCheck && bRangeCheck && bHitRoll && bHitRoll2 && bCanHit && !bEffected && bPK && pTargetCreature->getCompetence() == 3)
		{
			decreaseMana(pVampire, RequiredMP, _GCSkillToObjectOK1);

			bool bCanSeeCaster = canSee(pTargetCreature, pVampire);

			SkillInput input(pVampire);
			SkillOutput output;
			computeOutput(input, output);

			// Wisdom of Silence �� �ִٸ� ���ӽð� 20% ����
			if ( pVampire->hasRankBonus( RankBonus::RANK_BONUS_WISDOM_OF_SILENCE ) )
			{
				RankBonus* pRankBonus = pVampire->getRankBonus( RankBonus::RANK_BONUS_WISDOM_OF_SILENCE );
				Assert( pRankBonus != NULL );

				output.Duration += getPercentValue( output.Duration, pRankBonus->getPoint() );
			}

			// pTargetCreature�� ���ָ����� �ݻ��ϴ� ���
			if (CheckReflection(pVampire, pTargetCreature, getSkillType()))
			{
				pTargetCreature = (Creature*)pVampire;
				TargetObjectID = pVampire->getObjectID();
			}

			Resist_t resist = pTargetCreature->getResist( MAGIC_DOMAIN_CURSE );
			if ( resist > output.Duration ) resist = output.Duration;
			output.Duration -= resist;

			if ( output.Duration < 20 ) output.Duration = 20;

			// ����Ʈ ������Ʈ�� �����ؼ� ���δ�.
			EffectParalyze* pEffectParalyze = new EffectParalyze(pTargetCreature);
			pEffectParalyze->setLevel(pSkillInfo->getLevel()/2);
//			pEffectParalyze->setDefensePenalty(output.Damage);
			pEffectParalyze->setDeadline(output.Duration);
			pTargetCreature->addEffect(pEffectParalyze);
			pTargetCreature->setFlag(Effect::EFFECT_CLASS_PARALYZE);

			if ( pTargetCreature->isFlag( Effect::EFFECT_CLASS_BURNING_SOL_CHARGE_1 ) )
			{
				Effect* pEffect = pTargetCreature->findEffect( Effect::EFFECT_CLASS_BURNING_SOL_CHARGE_1 );
				if ( pEffect != NULL ) pEffect->setDeadline(0);
			}

			// ���ֿ� �ɸ��� ���潺�� ��������.
			// ���潺 ���Ƽ�� ������. 2002.05.09 - by bezz
/*			if (pTargetCreature->isSlayer()) 
			{
				Slayer* pTargetSlayer = dynamic_cast<Slayer*>(pTargetCreature);
				SLAYER_RECORD prev;
				pTargetSlayer->getSlayerRecord(prev);
				pTargetSlayer->initAllStat();
				pTargetSlayer->addModifyInfo(prev, _GCSkillToObjectOK2);
			} 
			else if (pTargetCreature->isVampire()) 
			{
				Vampire* pTargetVampire = dynamic_cast<Vampire*>(pTargetCreature);
				VAMPIRE_RECORD prev;
				pTargetVampire->getVampireRecord(prev);
				pTargetVampire->initAllStat();
				pTargetVampire->addModifyInfo(prev, _GCSkillToObjectOK2);
			} 
			else if (pTargetCreature->isMonster())
			{
				Monster* pTargetMonster = dynamic_cast<Monster*>(pTargetCreature);
				pTargetMonster->initAllStat();
			}
			else Assert(false);
*/
			// ����Ʈ�� �پ��ٴ� ���� ��ε�ĳ�������ش�.
			GCAddEffect gcAddEffect;
			gcAddEffect.setObjectID(pTargetCreature->getObjectID());
			gcAddEffect.setEffectID(Effect::EFFECT_CLASS_PARALYZE);
			gcAddEffect.setDuration(output.Duration);
			pZone->broadcastPacket(targetX, targetY, &gcAddEffect);

			_GCSkillToObjectOK1.setSkillType(SkillType);
			_GCSkillToObjectOK1.setCEffectID(CEffectID);
			_GCSkillToObjectOK1.setTargetObjectID(TargetObjectID);
			_GCSkillToObjectOK1.setDuration(output.Duration);
			
			_GCSkillToObjectOK2.setObjectID(pVampire->getObjectID());
			_GCSkillToObjectOK2.setSkillType(SkillType);
			_GCSkillToObjectOK2.setDuration(output.Duration);
											
			_GCSkillToObjectOK3.setObjectID(pVampire->getObjectID());
			_GCSkillToObjectOK3.setSkillType(SkillType);
			_GCSkillToObjectOK3.setTargetXY(targetX, targetY);
															
			_GCSkillToObjectOK4.setSkillType(SkillType);
			_GCSkillToObjectOK4.setTargetObjectID(TargetObjectID);

			_GCSkillToObjectOK5.setObjectID(pVampire->getObjectID());
			_GCSkillToObjectOK5.setTargetObjectID(TargetObjectID);
			_GCSkillToObjectOK5.setSkillType(SkillType);
			_GCSkillToObjectOK5.setDuration(output.Duration);

			_GCSkillToObjectOK6.setXY(vampX, vampY);
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

			pPlayer->sendPacket(&_GCSkillToObjectOK1);

			if (pTargetCreature->isPC())
			{
				Player* pTargetPlayer = pTargetCreature->getPlayer();
				Assert(pTargetPlayer != NULL);

				if (bCanSeeCaster) pTargetPlayer->sendPacket(&_GCSkillToObjectOK2);
				else pTargetPlayer->sendPacket(&_GCSkillToObjectOK6);
			}
			else
			{
				Monster* pTargetMonster = dynamic_cast<Monster*>(pTargetCreature);
				pTargetMonster->addEnemy(pVampire);
			}

			list<Creature*> cList;
			cList.push_back(pVampire);
			cList.push_back(pTargetCreature);

			cList = pZone->broadcastSkillPacket(vampX, vampY, targetX, targetY, &_GCSkillToObjectOK5, cList);

			pZone->broadcastPacket(vampX, vampY,  &_GCSkillToObjectOK3 , cList);
			pZone->broadcastPacket(targetX, targetY,  &_GCSkillToObjectOK4 , cList);

			pVampireSkillSlot->setRunTime(output.Delay);
		} 
		else
		{
			executeSkillFailNormal(pVampire, getSkillType(), pTargetCreature);
		}
	} 
	catch(Throwable & t) 
	{
		executeSkillFailException(pVampire, getSkillType());
	}

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " end " << endl;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// ���� ������Ʈ �ڵ鷯
//////////////////////////////////////////////////////////////////////////////
void Paralyze::execute(Monster* pMonster, Creature* pEnemy)
	
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << "begin " << endl;

	Assert(pMonster != NULL);
	Assert(pEnemy != NULL);

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
	catch(Throwable & t) 
	{
		executeSkillFailException(pMonster, getSkillType());
	}

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " end " << endl;

	__END_CATCH
}

void Paralyze::executeMonster(Zone* pZone, Monster* pMonster, Creature* pEnemy)
	    
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

	SkillType_t       SkillType  = SKILL_PARALYZE;
	SkillInfo*        pSkillInfo = g_pSkillInfoManager->getSkillInfo(SkillType);

	bool bRangeCheck = verifyDistance(pMonster, pEnemy, pSkillInfo->getRange());
	bool bHitRoll    = HitRoll::isSuccessCurse(pSkillInfo->getLevel()/2, pEnemy->getResist(MAGIC_DOMAIN_CURSE));
	bool bHitRoll2   = HitRoll::isSuccessMagic(pMonster, pSkillInfo);
	bool bCanHit     = canHit(pMonster, pEnemy, SkillType);
	bool bEffected   = pEnemy->isFlag(Effect::EFFECT_CLASS_PARALYZE) 
						|| pEnemy->isFlag(Effect::EFFECT_CLASS_IMMUNE_TO_PARALYZE);

	ZoneCoord_t  vampX   = pMonster->getX();
	ZoneCoord_t  vampY   = pMonster->getY();
	ZoneCoord_t  targetX = pEnemy->getX();
	ZoneCoord_t  targetY = pEnemy->getY();

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

		Resist_t resist = pEnemy->getResist( MAGIC_DOMAIN_CURSE );
		if ( resist > output.Duration ) resist = output.Duration;
		output.Duration -= resist;

		if ( output.Duration < 20 ) output.Duration=20;

		// ����Ʈ ������Ʈ�� �����ؼ� ���δ�.
		EffectParalyze* pEffectParalyze = new EffectParalyze(pEnemy);
		pEffectParalyze->setLevel(pSkillInfo->getLevel()/2);
		//pEffectParalyze->setDefensePenalty(output.Damage);
		pEffectParalyze->setDeadline(output.Duration);
		pEnemy->addEffect(pEffectParalyze);
		pEnemy->setFlag(Effect::EFFECT_CLASS_PARALYZE);

		// ���ֿ� �ɸ��� ���潺�� ��������.
		if (pEnemy->isSlayer()) 
		{
			Slayer* pTargetSlayer = dynamic_cast<Slayer*>(pEnemy);
			SLAYER_RECORD prev;
			pTargetSlayer->getSlayerRecord(prev);
			pTargetSlayer->initAllStat();
			pTargetSlayer->addModifyInfo(prev, _GCSkillToObjectOK2);
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

		// ����Ʈ�� �پ��ٴ� ���� ��ε�ĳ�������ش�.
		GCAddEffect gcAddEffect;
		gcAddEffect.setObjectID(pEnemy->getObjectID());
		gcAddEffect.setEffectID(Effect::EFFECT_CLASS_PARALYZE);
		gcAddEffect.setDuration(output.Duration);
		pZone->broadcastPacket(targetX, targetY, &gcAddEffect);
		
		_GCSkillToObjectOK2.setObjectID(pMonster->getObjectID());
		_GCSkillToObjectOK2.setSkillType(SkillType);
		_GCSkillToObjectOK2.setDuration(output.Duration);
										
		_GCSkillToObjectOK3.setObjectID(pMonster->getObjectID());
		_GCSkillToObjectOK3.setSkillType(SkillType);
		_GCSkillToObjectOK3.setTargetXY(targetX, targetY);
														
		_GCSkillToObjectOK4.setSkillType(SkillType);
		_GCSkillToObjectOK4.setTargetObjectID(pEnemy->getObjectID());

		_GCSkillToObjectOK5.setObjectID(pMonster->getObjectID());
		_GCSkillToObjectOK5.setTargetObjectID(pEnemy->getObjectID());
		_GCSkillToObjectOK5.setSkillType(SkillType);
		_GCSkillToObjectOK5.setDuration(output.Duration);

		_GCSkillToObjectOK6.setXY(vampX, vampY);
		_GCSkillToObjectOK6.setSkillType(SkillType);
		_GCSkillToObjectOK6.setDuration(output.Duration);

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
		else
		{
			Monster* pTargetMonster = dynamic_cast<Monster*>(pEnemy);
			pTargetMonster->addEnemy(pMonster);
		}

		list<Creature*> cList;
		cList.push_back(pMonster);
		cList.push_back(pEnemy);

		cList = pZone->broadcastSkillPacket(vampX, vampY, targetX, targetY, &_GCSkillToObjectOK5, cList);

		pZone->broadcastPacket(vampX, vampY,  &_GCSkillToObjectOK3 , cList);
		pZone->broadcastPacket(targetX, targetY,  &_GCSkillToObjectOK4 , cList);
	} 
	else
	{
		executeSkillFailNormal(pMonster, getSkillType(), pEnemy);
	}

	__END_CATCH
}

Paralyze g_Paralyze;
