//////////////////////////////////////////////////////////////////////////////
// Filename    : Paralyze.cpp
// Written by  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "FreezeRing1.h"
#include "EffectFreezeRing1.h"
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
// �����̾� ���� �ڵ鷯
//////////////////////////////////////////////////////////////////////////////
void FreezeRing1::execute(Slayer* pSlayer, SkillSlot* pSkillSlot, CEffectID_t CEffectID)
	
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
		SkillDomainType_t DomainType = pSkillInfo->getDomainType();

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

			// ���� �ð��� ����Ѵ�.
			SkillInput input(pSlayer, pSkillSlot);
			SkillOutput output;
			computeOutput(input, output);

			bool bHit = false;

			Level_t maxEnemyLevel = 0;
			uint EnemyNum = 0;

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

					// �������� üũ
					// 2003.1.10 by bezz, Sequoia
					// NPC�� üũ
					// 2003.3.14 by Sequoia
					if ( 
						pTargetCreature->isNPC()
						|| !checkZoneLevelToHitTarget(pTargetCreature)
				  		|| !canAttack( pSlayer, pTargetCreature )
						|| pTargetCreature->isFlag( Effect::EFFECT_CLASS_COMA )
					)
						continue;

					if( HitRoll::isSuccessRebuke( pSlayer, pSkillSlot, pTargetCreature ) )
					{
						HP_t RemainHP = 0;
						// �´� ������ �������� �ְ� ���� HP �� ���Ѵ�.
						// �̹� SLEEP ����Ʈ�� �ɷ�����??���� �ɷ��ִ� ����Ʈ�� �����Ѵ�.
						if ( pTargetCreature->isMonster() ){
							Monster* pMonster = dynamic_cast<Monster*>(pTargetCreature);
							if(pMonster->isMaster())bEffectd = true;
						}
					if(!bEffectd){
						if ( pTargetCreature->isFlag( Effect::EFFECT_CLASS_FREEZE_RING1 ) )
						{
							pTargetCreature->deleteEffect( Effect::EFFECT_CLASS_FREEZE_RING1 );
						}

						EffectFreezeRing1* pEffect = new EffectFreezeRing1( pTargetCreature );

						// �´� ������ SLEEP ����Ʈ�� �ɾ��ش�.
						pEffect->setDeadline( output.Duration );
						pTargetCreature->addEffect( pEffect );
						pTargetCreature->setFlag( Effect::EFFECT_CLASS_FREEZE_RING1 );

						GCAddEffect gcAddEffect;
						gcAddEffect.setObjectID( pTargetCreature->getObjectID() );
						gcAddEffect.setEffectID( Effect::EFFECT_CLASS_FREEZE_RING1 );
						gcAddEffect.setDuration( output.Duration );
						pZone->broadcastPacket( tileX, tileY, &gcAddEffect );
					}
						bHit = true;

						// ������ �ø���.
						// Ÿ���� �����̾��̸� �հ� ������ �ִ�.
						if ( !pTargetCreature->isSlayer() )
						{
						//	increaseAlignment( pSlayer, pTargetCreature, &_GCSkillToSelfOK1 );
							if ( maxEnemyLevel < pTargetCreature->getLevel() ) maxEnemyLevel = pTargetCreature->getLevel();
							EnemyNum++;
						}
					}
				}
			}

			// ����ġ�� �ø���.
			if( bHit )
			{
				SkillGrade Grade = g_pSkillInfoManager->getGradeByDomainLevel(pSlayer->getSkillDomainLevel(DomainType));
				Exp_t ExpUp = 10* (Grade + 1);
				shareAttrExp(pSlayer, ExpUp, 1, 1, 8, _GCSkillToSelfOK1);
				increaseDomainExp(pSlayer, DomainType, pSkillInfo->getPoint(), _GCSkillToSelfOK1, maxEnemyLevel, EnemyNum);
				increaseSkillExp(pSlayer, DomainType, pSkillSlot, pSkillInfo, _GCSkillToSelfOK1);
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

FreezeRing1 g_FreezeRing1;
