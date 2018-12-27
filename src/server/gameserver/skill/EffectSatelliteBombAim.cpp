//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectSatelliteBombAim.cpp
// Written by  : bezz
//////////////////////////////////////////////////////////////////////////////

#include "EffectSatelliteBombAim.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Monster.h"
#include "GamePlayer.h"
#include "PCFinder.h"
#include "ZoneUtil.h"
#include "ZoneInfoManager.h"
#include "SkillInfo.h"
#include "SkillUtil.h"
#include "HitRoll.h"
#include "Gpackets/GCRemoveEffect.h"
#include "Gpackets/GCAddEffectToTile.h"
#include "Gpackets/GCSkillToObjectOK2.h"
#include "Gpackets/GCSkillToObjectOK4.h"
#include "Gpackets/GCStatusCurrentHP.h"


int SBADamageModify[5][5] =
{
    { 50, 50,  50, 50, 50 },
    { 50, 75,  75, 75, 50 },
    { 50, 75, 100, 75, 50 },
    { 50, 75,  75, 75, 50 },
    { 50, 50,  50, 50, 50 }
};

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectSatelliteBombAim::EffectSatelliteBombAim(Creature* pCreature, Zone* pZone, ZoneCoord_t x, ZoneCoord_t y)
	
{
	__BEGIN_TRY

	setTarget(pCreature);
	m_pZone = pZone;
	m_X = x;
	m_Y = y;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectSatelliteBombAim::affect(Creature* pCreature)
	
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectSatelliteBombAim::unaffect(Creature* pCastCreature)
	
{
	__BEGIN_TRY
	
	Assert(pCastCreature != NULL);

	// ����Ʈ �÷��װ� ���ٸ� �׾��ٰų� �ϴ� ������ transport ���� �ʰڴٴ°� �ǹ��Ѵ�.
	if ( !pCastCreature->isFlag( Effect::EFFECT_CLASS_SKILL_SATELLITE_BOMB_AIM ) )
		return;

	// Effect�� ���ְ� �˸���.
	pCastCreature->removeFlag( Effect::EFFECT_CLASS_SKILL_SATELLITE_BOMB_AIM );

	GCRemoveEffect gcRemoveEffect;
	gcRemoveEffect.setObjectID( pCastCreature->getObjectID() );
	gcRemoveEffect.addEffectList( Effect::EFFECT_CLASS_SKILL_SATELLITE_BOMB_AIM );

	m_pZone->broadcastPacket( pCastCreature->getX(), pCastCreature->getY(), &gcRemoveEffect );

	VSRect rect( 0, 0, m_pZone->getWidth()-1, m_pZone->getHeight()-1 );	// -1 �߰� by sigi. 2003.1.10

	bool bHit = false;
	Damage_t maxDamage=0;

	GCSkillToObjectOK2 gcSkillToObjectOK2;
	GCSkillToObjectOK4 gcSkillToObjectOK4;

	Level_t maxEnemyLevel = 0;
	uint EnemyNum = 0;

	for ( int x=-2; x<=2; x++ )
	{
		for ( int y=-2; y<=2; y++ )
		{
			int X = m_X + x;
			int Y = m_Y + y;

			if ( !rect.ptInRect( X, Y ) ) continue;

			// Ÿ�Ͼȿ� �����ϴ� ������Ʈ�� �����´�.
			Tile& tile = m_pZone->getTile( X, Y );
			const slist<Object*>& oList = tile.getObjectList();
			slist<Object*>::const_iterator itr = oList.begin();

			int DamageModifier = SBADamageModify[x+2][y+2];
			Damage_t Damage = getPercentValue( m_Damage, DamageModifier );

			for ( ; itr != oList.end(); itr++ )
			{
				Object* pObject = *itr;
				Assert( pObject != NULL );

				if ( pObject->getObjectClass() == Object::OBJECT_CLASS_CREATURE )
				{
					Creature* pCreature = dynamic_cast<Creature*>(pObject);
					Assert( pCreature != NULL );

					// �ڽ��� ���� �ʴ´�. ������ �� �´´�. �����̾�� ���� �ʴ´�.
					if ( pCreature == m_pTarget
					  || !canAttack( pCastCreature, pCreature )
					  || pCreature->isFlag( Effect::EFFECT_CLASS_COMA ) )
					{
						continue;
					}

					bool bPK                = verifyPK( pCastCreature, pCreature );
					bool bZoneLevelCheck    = checkZoneLevelToHitTarget( pCreature );
					
					int bonus = 100;
					if ( pCastCreature->isSlayer() )
					{
						Slayer* pSlayer = dynamic_cast<Slayer*>(pCastCreature);
						Assert( pSlayer != NULL );

						SkillSlot* pSkillSlot   = pSlayer->hasSkill( SKILL_SATELLITE_BOMB );
						if ( pSkillSlot != NULL )
							bonus = pSkillSlot->getExpLevel();
					}

					if ( pCastCreature->isMonster() )
					{
						Monster* pMonster = dynamic_cast<Monster*>(pCastCreature);
						Assert( pMonster != NULL );
						bPK = pMonster->isEnemyToAttack(pCreature);
					}

					bool bHitRoll           = HitRoll::isSuccess( pCastCreature, pCreature, bonus );

					if ( bPK && bZoneLevelCheck && bHitRoll )
					{
						// ���� �������� ��ų ������ ���ʽ��� ���� ���� �������� ���Ѵ�.
						Damage_t FinalDamage = 0;
						FinalDamage = computeDamage( pCastCreature, pCreature );
						FinalDamage += Damage;

						if ( pCreature->isPC() && pCreature->getCreatureClass() != pCastCreature->getCreatureClass() )
						{
//							Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);

							GCModifyInformation gcMI;
							::setDamage( pCreature, FinalDamage, pCastCreature, SKILL_SATELLITE_BOMB, &gcMI ); // ::�߰� by Sequoia

							pCreature->getPlayer()->sendPacket( &gcMI );

							// �´� ������ �����ش�.
							gcSkillToObjectOK2.setObjectID( 1 );    // �ǹ� ����.
							gcSkillToObjectOK2.setSkillType( SKILL_ATTACK_MELEE );
							gcSkillToObjectOK2.setDuration(0);
							pCreature->getPlayer()->sendPacket(&gcSkillToObjectOK2);

							bHit = true;
						}
						else if ( pCreature->isMonster() )
						{
							Monster* pMonster = dynamic_cast<Monster*>(pCreature);

							::setDamage( pMonster, FinalDamage, pCastCreature, SKILL_SATELLITE_BOMB );	// ::�߰� by Sequoia

							pMonster->addEnemy( pCastCreature );
							bHit = true;
						}
						else continue;

						gcSkillToObjectOK4.setTargetObjectID( pCreature->getObjectID() );
						gcSkillToObjectOK4.setSkillType( SKILL_ATTACK_MELEE );
						gcSkillToObjectOK4.setDuration( 0 );
						m_pZone->broadcastPacket( X, Y, &gcSkillToObjectOK4, pCreature );

						if ( maxEnemyLevel < pCreature->getLevel() ) maxEnemyLevel = pCreature->getLevel();
						EnemyNum++;

						if ( FinalDamage > maxDamage ) maxDamage = FinalDamage;
					}
				}
			}
		}
	}

	if ( bHit && pCastCreature->isSlayer() )
	{
		Slayer* pSlayer = dynamic_cast<Slayer*>(pCastCreature);
		Assert( pSlayer != NULL );

		bool bIncreaseExp = pSlayer->isRealWearingEx( Slayer::WEAR_RIGHTHAND );
		if ( bIncreaseExp )
		{
			SkillSlot* pSkillSlot   = pSlayer->hasSkill( SKILL_SATELLITE_BOMB );
			SkillInfo* pSkillInfo   = g_pSkillInfoManager->getSkillInfo( SKILL_SATELLITE_BOMB );
			SkillDomainType_t DomainType = pSkillInfo->getDomainType();
			SkillLevel_t SkillLevel = pSkillSlot->getExpLevel();

			GCModifyInformation gcMI;
			shareAttrExp( pSlayer, maxDamage, 1, 8, 1, gcMI );
			increaseDomainExp( pSlayer, DomainType, pSkillInfo->getPoint(), gcMI, maxEnemyLevel, EnemyNum );
			increaseSkillExp( pSlayer, DomainType, pSkillSlot, pSkillInfo, gcMI );

			pSlayer->getPlayer()->sendPacket( &gcMI );
		}
	}

	// ���� ����Ʈ�� �����ֵ��� �Ѵ�.
	GCAddEffectToTile gcAddEffectToTile;
	gcAddEffectToTile.setObjectID( pCastCreature->getObjectID() );
	gcAddEffectToTile.setEffectID( Effect::EFFECT_CLASS_SKILL_SATELLITE_BOMB_FIRE );
	gcAddEffectToTile.setXY( m_X, m_Y );
	gcAddEffectToTile.setDuration( 10 ); // �� �ǹ̾���. �� 1��

	m_pZone->broadcastPacket( m_X, m_Y, &gcAddEffectToTile );

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectSatelliteBombAim::unaffect()
	
{
	__BEGIN_TRY

	Creature* pCreature = dynamic_cast<Creature*>(m_pTarget);	// by Sequoia

	Assert( pCreature != NULL );

	if ( m_pZone != NULL && m_pZone == pCreature->getZone() )
	{
		unaffect(pCreature);
	}
	else
	{
		// ���� ���� �׾��ų� �̵��ߴٴ� �ǹ��̹Ƿ� ����Ʈ�� ���ְ� ��ε�ĳ�����Ѵ�.
		// Effect�� ���ְ� �˸���.
		Zone* pZone = pCreature->getZone();
		Assert( pZone != NULL );

		pCreature->removeFlag( Effect::EFFECT_CLASS_SKILL_SATELLITE_BOMB_AIM );

		GCRemoveEffect gcRemoveEffect;
		gcRemoveEffect.setObjectID( pCreature->getObjectID() );
		gcRemoveEffect.addEffectList( Effect::EFFECT_CLASS_SKILL_SATELLITE_BOMB_AIM );

		pZone->broadcastPacket( pCreature->getX(), pCreature->getY(), &gcRemoveEffect );
	}
	
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectSatelliteBombAim::toString() const 
	
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectSatelliteBombAim("
		<< "Zone:" << g_pZoneInfoManager->getZoneInfo( m_pZone->getZoneID() )->getFullName()
		<< ",X:" << (int)m_X
		<< ",Y:" << (int)m_Y
		<< ",Damage:" << (int)m_Damage
		<< ")";
	return msg.toString();

	__END_CATCH
}

