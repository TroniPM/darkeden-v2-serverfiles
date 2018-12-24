//////////////////////////////////////////////////////////////////////////////
// Filename    : Paralyze.cpp
// Written by  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CurseOfBlood1.h"
#include "EffectCurseOfBlood1.h"
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
#include "Slayer.h"
#include "Ousters.h"
#include "Reflection.h"
#include "Tile.h"
#include "RankBonus.h"

//////////////////////////////////////////////////////////////////////////////
// 슬레이어 셀프 핸들러
//////////////////////////////////////////////////////////////////////////////
void CurseOfBlood1::execute(Vampire* pSlayer, VampireSkillSlot* pSkillSlot, CEffectID_t CEffectID)
	throw(Error)
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin(slayer)" << endl;

	Assert(pSlayer != NULL);
	Assert(pSkillSlot != NULL);

	try 
	{
		Player* pPlayer = pSlayer->getPlayer();
		Zone* pZone = pSlayer->getZone();

		Assert(pPlayer != NULL);
		Assert(pZone != NULL);

		GCSkillToSelfOK1 _GCSkillToSelfOK1;
		GCSkillToSelfOK2 _GCSkillToSelfOK2;

		SkillType_t       SkillType  = pSkillSlot->getSkillType();
		SkillInfo*        pSkillInfo = g_pSkillInfoManager->getSkillInfo(SkillType);
//		SkillDomainType_t DomainType = pSkillInfo->getDomainType();

		int  RequiredMP  = (int)pSkillInfo->getConsumeMP();
		bool bManaCheck  = hasEnoughMana(pSlayer, RequiredMP);
		bool bTimeCheck  = verifyRunTime(pSkillSlot);
		bool bRangeCheck = checkZoneLevelToUseSkill(pSlayer);
		bool bEffectd = false;

		ZoneCoord_t X = pSlayer->getX();
		ZoneCoord_t Y = pSlayer->getY();

		VSRect rect(0, 0, pZone->getWidth()-1, pZone->getHeight()-1);

		if (bManaCheck && bTimeCheck && bRangeCheck)
		{
			decreaseMana(pSlayer, RequiredMP, _GCSkillToSelfOK1);

			// 지속 시간을 계산한다.
			SkillInput input(pSlayer);
			SkillOutput output;
			computeOutput(input, output);

			for( int ox = -1 ; ox <= 1 ; ox++ )
			for( int oy = -1 ; oy <= 1 ; oy++ )
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
				  		|| !canAttack( pSlayer, pTargetCreature )
						|| pTargetCreature->isFlag( Effect::EFFECT_CLASS_COMA )
					)
						continue;

					if( HitRoll::isSuccessVenom( pSlayer, pSkillSlot, pTargetCreature ) &&  pTargetCreature->isMonster())
					{
						/*HP_t RemainHP = 0;
						// 맞는 넘한테 데미지를 주고 남은 HP 를 구한다.
						if ( pTargetCreature->isSlayer() )
						{
							GCModifyInformation gcMI;
							setDamage( pTargetCreature, output.Damage, pSlayer, SkillType, &gcMI );

							pTargetCreature->getPlayer()->sendPacket( &gcMI );

							Slayer* pVampire = dynamic_cast<Slayer*>(pTargetCreature);
							RemainHP = pVampire->getHP(ATTR_CURRENT);
						}
						else if ( pTargetCreature->isOusters() )
						{
							GCModifyInformation gcMI;
							setDamage( pTargetCreature, output.Damage, pSlayer, SkillType, &gcMI );

							pTargetCreature->getPlayer()->sendPacket( &gcMI );

							Ousters* pVampire = dynamic_cast<Ousters*>(pTargetCreature);
							RemainHP = pVampire->getHP(ATTR_CURRENT);
						}
						else if ( pTargetCreature->isMonster() )
						{
							setDamage( pTargetCreature, output.Damage, pSlayer, SkillType );
							Monster* pMonster = dynamic_cast<Monster*>(pTargetCreature);
							RemainHP = pMonster->getHP(ATTR_CURRENT);
						}*/
						if ( pTargetCreature->isMonster() ){
							Monster* pMonster = dynamic_cast<Monster*>(pTargetCreature);
							if(pMonster->isMaster())bEffectd = true;
						}
					if(!bEffectd){
						// 이미 SLEEP 이펙트가 걸려있으면 먼저 걸려있던 이펙트를 삭제한다.
						if ( pTargetCreature->isFlag( Effect::EFFECT_CLASS_CURSE_OF_BLOOD1) )
						{
							pTargetCreature->deleteEffect( Effect::EFFECT_CLASS_CURSE_OF_BLOOD1 );
						}

						EffectCurseOfBlood1* pEffect = new EffectCurseOfBlood1( pTargetCreature );

						// 맞는 넘한테 SLEEP 이펙트를 걸어준다.
						pEffect->setDeadline( output.Duration );
						pTargetCreature->addEffect( pEffect );
						pTargetCreature->setFlag( Effect::EFFECT_CLASS_CURSE_OF_BLOOD1 );

						GCAddEffect gcAddEffect;
						gcAddEffect.setObjectID( pTargetCreature->getObjectID() );
						gcAddEffect.setEffectID( Effect::EFFECT_CLASS_CURSE_OF_BLOOD1);
						gcAddEffect.setDuration( output.Duration );
						pZone->broadcastPacket( tileX, tileY, &gcAddEffect );
						}
					}
				}
			}

			_GCSkillToSelfOK1.setSkillType(SkillType);
			_GCSkillToSelfOK1.setCEffectID(CEffectID);
			_GCSkillToSelfOK1.setDuration(0);
		
			_GCSkillToSelfOK2.setObjectID(pSlayer->getObjectID());
			_GCSkillToSelfOK2.setSkillType(SkillType);
			_GCSkillToSelfOK2.setDuration(0);
		
			pPlayer->sendPacket(&_GCSkillToSelfOK1);
			pZone->broadcastPacket(pSlayer->getX(), pSlayer->getY(),  &_GCSkillToSelfOK2, pSlayer);

			pSkillSlot->setRunTime(output.Delay);
		} 
		else 
		{
			executeSkillFailNormal(pSlayer, getSkillType(), NULL);
		}
	} 
	catch (Throwable & t) 
	{
		executeSkillFailException(pSlayer, getSkillType());
	}

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End(slayer)" << endl;

	__END_CATCH
}

CurseOfBlood1 g_CurseOfBlood1;
