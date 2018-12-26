//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectCannonade.cpp
// Written by  : bezz
//////////////////////////////////////////////////////////////////////////////

#include "EffectCannonade.h"
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
#include "Gpackets/GCSkillToObjectOK2.h"
#include "Gpackets/GCSkillToObjectOK4.h"
#include "Gpackets/GCStatusCurrentHP.h"


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectCannonade::EffectCannonade(Creature* pCreature, Zone* pZone, ZoneCoord_t x, ZoneCoord_t y)
	
{
	__BEGIN_TRY

	setTarget(pCreature);
	m_pZone = pZone;
	m_X = x;
	m_Y = y;
	setBroadcastingEffect(false);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectCannonade::affect(Creature* pCreature)
	
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectCannonade::unaffect(Creature* pCastCreature)
	
{
	__BEGIN_TRY
	
	Assert(pCastCreature != NULL);

	VSRect rect( 0, 0, m_pZone->getWidth()-1, m_pZone->getHeight()-1 );	// -1 �߰� by sigi. 2003.1.10

	bool bHit = false;

	GCSkillToObjectOK2 gcSkillToObjectOK2;
	GCSkillToObjectOK4 gcSkillToObjectOK4;

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

			Damage_t Damage = m_Damage;

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
					
					if ( pCastCreature->isMonster() )
					{
						Monster* pMonster = dynamic_cast<Monster*>(pCastCreature);
						Assert( pMonster != NULL );
						bPK = pMonster->isEnemyToAttack(pCreature);
					}

					bool bHitRoll           = HitRoll::isSuccess( pCastCreature, pCreature );

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
							::setDamage( pCreature, FinalDamage, pCastCreature, SKILL_CANNONADE, &gcMI ); // ::�߰� by Sequoia

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

							::setDamage( pMonster, FinalDamage, pCastCreature, SKILL_CANNONADE );	// ::�߰� by Sequoia

							pMonster->addEnemy( pCastCreature );
							bHit = true;
						}
						else continue;

						gcSkillToObjectOK4.setTargetObjectID( pCreature->getObjectID() );
						gcSkillToObjectOK4.setSkillType( SKILL_ATTACK_MELEE );
						gcSkillToObjectOK4.setDuration( 0 );
						m_pZone->broadcastPacket( X, Y, &gcSkillToObjectOK4, pCreature );
					}
				}
			}
		}
	}

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectCannonade::unaffect()
	
{
	__BEGIN_TRY

	Creature* pCreature = dynamic_cast<Creature*>(m_pTarget);	// by Sequoia

	Assert( pCreature != NULL );

	if ( m_pZone != NULL && m_pZone == pCreature->getZone() )
	{
		unaffect(pCreature);
	}

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectCannonade::toString() const 
	throw()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectCannonade("
		<< "Zone:" << g_pZoneInfoManager->getZoneInfo( m_pZone->getZoneID() )->getFullName()
		<< ",X:" << (int)m_X
		<< ",Y:" << (int)m_Y
		<< ",Damage:" << (int)m_Damage
		<< ")";
	return msg.toString();

	__END_CATCH
}

