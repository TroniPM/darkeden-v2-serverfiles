//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectBrambleHalo.cpp
// Written by  : bezz
//////////////////////////////////////////////////////////////////////////////

#include "EffectBrambleHalo.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Monster.h"
#include "GamePlayer.h"
#include "PCFinder.h"
#include "ZoneUtil.h"
#include "ZoneInfoManager.h"
#include "SkillUtil.h"
#include "Gpackets/GCRemoveEffect.h"
#include "Gpackets/GCAddEffectToTile.h"
#include "Gpackets/GCSkillToObjectOK2.h"
#include "Gpackets/GCSkillToObjectOK4.h"
#include "Gpackets/GCStatusCurrentHP.h"

#include "SkillInfo.h"
#include "SkillSlot.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectBrambleHalo::EffectBrambleHalo(Creature* pCreature)
	
{
	__BEGIN_TRY

	setTarget(pCreature);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectBrambleHalo::affect()
	
{
	__BEGIN_TRY

	Creature* pCreature = dynamic_cast<Creature*>(m_pTarget);	// by Sequoia

	if ( pCreature != NULL )
	{
		affect(pCreature);
	}
	
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectBrambleHalo::affect(Creature* pCastCreature)
	
{
	__BEGIN_TRY

	Assert(pCastCreature != NULL);

	if ( !pCastCreature->isSlayer() )
		return;

	Player* pPlayer = dynamic_cast<Player*>(pCastCreature->getPlayer());
	Assert( pPlayer != NULL );

	Slayer* pSlayer = dynamic_cast<Slayer*>(pCastCreature);
	Assert( pSlayer != NULL );

	SkillInfo* pSkillInfo = g_pSkillInfoManager->getSkillInfo( SKILL_Bramble_Halo );
	if ( pSkillInfo == NULL )
	{
		return;
	}

	GCModifyInformation gcAttackerMI;

	Zone* pZone = pCastCreature->getZone();
	Assert( pZone != NULL );

	VSRect rect( 0, 0, pZone->getWidth()-1, pZone->getHeight()-1 );

	ZoneCoord_t Cx = pCastCreature->getX();
	ZoneCoord_t Cy = pCastCreature->getY();

	bool isHit = false;

	Level_t maxEnemyLevel = 0;
	uint EnemyNum = 0;

	for ( int x=-1; x<=1; x++ )
	{
		for ( int y=-1; y<=1; y++ )
		{
			if ( x == 0 && y == 0 ) continue;

			int X = Cx + x;
			int Y = Cy + y;

			if ( !rect.ptInRect( X, Y ) ) continue;

			// Ÿ�Ͼȿ� �����ϴ� ������Ʈ�� �����´�.
			Tile& tile = pZone->getTile( X, Y );

			if( tile.hasCreature(Creature::MOVE_MODE_WALKING) )
			{
				Creature* pCreature = tile.getCreature(Creature::MOVE_MODE_WALKING);
				Assert( pCreature != NULL );

				// �ڽ��� ���� �ʴ´�. ������ �� �´´�. �����̾ �� �´���.
				// �������� üũ
				// 2003.1.10 by bezz, Sequoia
				if ( pCreature == m_pTarget
				  || !canAttack( pCastCreature, pCreature )
				  || pCreature->isFlag( Effect::EFFECT_CLASS_COMA )
				  || pCreature->isSlayer() 
				  || pCreature->isNPC()
				)
				{
					continue;
				}

			if( !checkZoneLevelToHitTarget( pCreature ) ) continue;
				isHit = true;

				if ( maxEnemyLevel < pCreature->getLevel() ) maxEnemyLevel = pCreature->getLevel();
				EnemyNum++;

				if ( pCreature->isVampire() || pCreature->isOusters() )
				{
//					Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);

					GCModifyInformation gcMI;
					::setDamage( pCreature, m_Damage, pCastCreature, SKILL_Bramble_Halo, &gcMI, &gcAttackerMI, 0, true );

					pCreature->getPlayer()->sendPacket( &gcMI );

					// �´� ������ �����ش�.
					GCSkillToObjectOK2 gcSkillToObjectOK2;
					gcSkillToObjectOK2.setObjectID( 1 );    // �ǹ� ����.
					gcSkillToObjectOK2.setSkillType( SKILL_ATTACK_MELEE );
					gcSkillToObjectOK2.setDuration(0);
					pCreature->getPlayer()->sendPacket(&gcSkillToObjectOK2);

				}
				else if ( pCreature->isMonster() )
				{
					Monster* pMonster = dynamic_cast<Monster*>(pCreature);

					::setDamage( pMonster, m_Damage, pCastCreature, SKILL_Bramble_Halo, NULL, &gcAttackerMI, 0, true );

					pMonster->addEnemy( pCastCreature );
				}
				else Assert(false);

				GCSkillToObjectOK4 gcSkillToObjectOK4;
				gcSkillToObjectOK4.setSkillType( SKILL_ATTACK_MELEE );
				gcSkillToObjectOK4.setTargetObjectID( pCreature->getObjectID() );
				gcSkillToObjectOK4.setDuration(0);

				pZone->broadcastPacket( X, Y, &gcSkillToObjectOK4, pCreature );
			}
		}
	}

	if ( isHit )
	{
		SkillDomainType_t DomainType = pSkillInfo->getDomainType();
		SkillSlot* pSkillSlot = pSlayer->getSkill( SKILL_Bramble_Halo );

		if ( pSkillSlot != NULL )
		{
			increaseDomainExp(pSlayer, DomainType, pSkillInfo->getPoint(), gcAttackerMI, maxEnemyLevel, EnemyNum);
			increaseSkillExp(pSlayer, DomainType, pSkillSlot, pSkillInfo, gcAttackerMI);
		}
	}

	setNextTime( m_Delay );

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectBrambleHalo::unaffect(Creature* pCreature)
	
{
	__BEGIN_TRY
	
	// cout << "EffectBrambleHalo " << "unaffect BEGIN" << endl;
	Assert(pCreature != NULL);

	if ( !pCreature->isSlayer() )
		return;

	Player* pPlayer = dynamic_cast<Player*>(pCreature->getPlayer());
	Assert( pPlayer != NULL );

	Zone* pZone = pCreature->getZone();
	Assert( pZone != NULL );

	// Effect�� ���ְ� �˸���.
	pCreature->removeFlag( Effect::EFFECT_CLASS_Bramble_Halo );

	GCRemoveEffect gcRemoveEffect;
	gcRemoveEffect.setObjectID( pCreature->getObjectID() );
	gcRemoveEffect.addEffectList( Effect::EFFECT_CLASS_Bramble_Halo );

	pPlayer->sendPacket( &gcRemoveEffect );
	pZone->broadcastPacket( pCreature->getX(), pCreature->getY(), &gcRemoveEffect, pCreature );

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectBrambleHalo::unaffect()
	
{
	__BEGIN_TRY

	Creature* pCreature = dynamic_cast<Creature*>(m_pTarget);	// by Sequoia

	if ( pCreature != NULL )
	{
		unaffect(pCreature);
	}
	
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectBrambleHalo::setLevel(SkillLevel_t Level)
{
	if( Level <= GRADE_ADEPT_LIMIT_LEVEL ) m_EffectClass = EFFECT_CLASS_Bramble_Halo;
	else if( Level <= GRADE_EXPERT_LIMIT_LEVEL ) m_EffectClass = EFFECT_CLASS_Bramble_Halo;
	else if( Level <= GRADE_MASTER_LIMIT_LEVEL ) m_EffectClass = EFFECT_CLASS_Bramble_Halo;
	else m_EffectClass = EFFECT_CLASS_Bramble_Halo;
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectBrambleHalo::toString() const 
	
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectBrambleHalo("
		<< "Damage:" << (int)m_Damage
		<< ", EffectClass:" << (int)m_EffectClass
		<< ")";
	return msg.toString();

	__END_CATCH
}

