//////////////////////////////////////////////////////////////////////////////
// Filename    : Paralyze.cpp
// Written by  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "MistOfSoul2.h"
#include "EffectMistOfSoul1.h"
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

//////////////////////////////////////////////////////////////////////////////
// 슬레이어 셀프 핸들러
//////////////////////////////////////////////////////////////////////////////
void MistOfSoul2::execute(Ousters* pOusters, OustersSkillSlot* pSkillSlot, CEffectID_t CEffectID)
	
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin(slayer)" << endl;

	Assert(pOusters != NULL);
	Assert(pSkillSlot != NULL);

	try 
	{
		Player* pPlayer = pOusters->getPlayer();
		Zone* pZone = pOusters->getZone();

		Assert(pPlayer != NULL);
		Assert(pZone != NULL);

		GCSkillToSelfOK1 _GCSkillToSelfOK1;
		GCSkillToSelfOK2 _GCSkillToSelfOK2;

		SkillType_t       SkillType  = pSkillSlot->getSkillType();
		SkillInfo*        pSkillInfo = g_pSkillInfoManager->getSkillInfo(SkillType);
		SkillDomainType_t DomainType = pSkillInfo->getDomainType();

		int  RequiredMP  = (int)pSkillInfo->getConsumeMP();
		bool bManaCheck  = hasEnoughMana(pOusters, RequiredMP);
		bool bTimeCheck  = verifyRunTime(pSkillSlot);
		bool bRangeCheck = checkZoneLevelToUseSkill(pOusters);
		bool bEffectd = false;
		ZoneCoord_t X = pOusters->getX();
		ZoneCoord_t Y = pOusters->getY();

		VSRect rect(0, 0, pZone->getWidth()-1, pZone->getHeight()-1);

		if (bManaCheck && bTimeCheck && bRangeCheck)
		{
			decreaseMana(pOusters, RequiredMP, _GCSkillToSelfOK1);

			// 지속 시간을 계산한다.
			SkillInput input(pOusters, pSkillSlot);
			SkillOutput output;
			computeOutput(input, output);

			bool bHit = false;

			Level_t maxEnemyLevel = 0;
			uint EnemyNum = 0;

			for( int ox = -4 ; ox <= 4 ; ox++ )
			for( int oy = -4 ; oy <= 4 ; oy++ )
			{
				int tileX = X+ox;
				int tileY = Y+oy;

				if( !rect.ptInRect(tileX,tileY) ) continue;

				Tile& tile = pZone->getTile( tileX, tileY );
				if ( tile.getEffect( Effect::EFFECT_CLASS_TRYING_POSITION ) ) continue;

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
				for ( ; itr != targetList.end() ; itr++ )
				{
					Creature* pTargetCreature = (*itr);
					Assert( pTargetCreature != NULL );

					// 안전지대 체크
					// 2003.1.10 by bezz, Sequoia
					// NPC도 체크
					// 2003.3.14 by Sequoia
					if ( 
						pTargetCreature->isNPC()
						|| !checkZoneLevelToHitTarget(pTargetCreature)
				  		|| !canAttack( pOusters, pTargetCreature )
						|| pTargetCreature->isFlag( Effect::EFFECT_CLASS_COMA )
					)
						continue;

					if( HitRoll::isSuccessMistOfSoul( pOusters, pSkillSlot, pTargetCreature ) && pTargetCreature->isMonster())
					{
						HP_t RemainHP = 0;
						// 맞는 넘한테 데미지를 주고 남은 HP 를 구한다.
						if ( pTargetCreature->isVampire() )
						{
							GCModifyInformation gcMI;
							setDamage( pTargetCreature, output.Damage, pOusters, SkillType, &gcMI );

							pTargetCreature->getPlayer()->sendPacket( &gcMI );

							Vampire* pVampire = dynamic_cast<Vampire*>(pTargetCreature);
							RemainHP = pVampire->getHP(ATTR_CURRENT);
						}
						else if ( pTargetCreature->isMonster() )
						{
							setDamage( pTargetCreature, output.Damage, pOusters, SkillType );
							Monster* pMonster = dynamic_cast<Monster*>(pTargetCreature);
							RemainHP = pMonster->getHP(ATTR_CURRENT);
						}
						if ( pTargetCreature->isMonster() ){
							Monster* pMonster = dynamic_cast<Monster*>(pTargetCreature);
							if(pMonster->isMaster())bEffectd = true;
						}
					if(!bEffectd){

						// 이미 SLEEP 이펙트가 걸려있으면 먼저 걸려있던 이펙트를 삭제한다.
						if ( pTargetCreature->isFlag( Effect::EFFECT_CLASS_MIST_OF_SOUL1 ) )
						{
							pTargetCreature->deleteEffect( Effect::EFFECT_CLASS_MIST_OF_SOUL1 );
						}

						EffectMistOfSoul1* pEffect = new EffectMistOfSoul1( pTargetCreature );

						// 맞는 넘한테 SLEEP 이펙트를 걸어준다.
						pEffect->setDeadline( output.Duration );
						pTargetCreature->addEffect( pEffect );
						pTargetCreature->setFlag( Effect::EFFECT_CLASS_MIST_OF_SOUL1 );

						GCAddEffect gcAddEffect;
						gcAddEffect.setObjectID( pTargetCreature->getObjectID() );
						gcAddEffect.setEffectID( Effect::EFFECT_CLASS_MIST_OF_SOUL1 );
						gcAddEffect.setDuration( output.Duration );
						pZone->broadcastPacket( tileX, tileY, &gcAddEffect );
					}
						bHit = true;

						// 성향을 올린다.
						// 타겟이 슬레이어이면 먼가 문제가 있다.
						if ( !pTargetCreature->isSlayer() )
						{
						//	increaseAlignment( pOusters, pTargetCreature, &_GCSkillToSelfOK1 );
							if ( maxEnemyLevel < pTargetCreature->getLevel() ) maxEnemyLevel = pTargetCreature->getLevel();
							EnemyNum++;
						}
					}
				}
			}

			_GCSkillToSelfOK1.setSkillType(SkillType);
			_GCSkillToSelfOK1.setCEffectID(CEffectID);
			_GCSkillToSelfOK1.setDuration(0);
		
			_GCSkillToSelfOK2.setObjectID(pOusters->getObjectID());
			_GCSkillToSelfOK2.setSkillType(SkillType);
			_GCSkillToSelfOK2.setDuration(0);
		
			pPlayer->sendPacket(&_GCSkillToSelfOK1);
			pZone->broadcastPacket(pOusters->getX(), pOusters->getY(),  &_GCSkillToSelfOK2, pOusters);

			pSkillSlot->setRunTime(output.Delay);
		} 
		else 
		{
			executeSkillFailNormal(pOusters, getSkillType(), NULL);
		}
	} 
	catch (Throwable & t) 
	{
		executeSkillFailException(pOusters, getSkillType());
	}

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End(slayer)" << endl;

	__END_CATCH
}

MistOfSoul2 g_MistOfSoul2;
