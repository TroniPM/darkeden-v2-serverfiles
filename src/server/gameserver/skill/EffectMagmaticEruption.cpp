//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectShadowOfStorm.cpp
// Written by  :
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "Effect.h"
#include "EffectMagmaticEruption.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Ousters.h"
#include "Monster.h"
#include "GamePlayer.h"
#include "SkillUtil.h"
#include "ZoneUtil.h"

#include "Gpackets/GCModifyInformation.h"
#include "Gpackets/GCStatusCurrentHP.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectMagmaticEruption::EffectMagmaticEruption(Zone* pZone, ZoneCoord_t zoneX, ZoneCoord_t zoneY) 
	
{
	__BEGIN_TRY

	m_pZone = pZone;
	m_X = zoneX;
	m_Y = zoneY;
	m_UserObjectID = 0;
	m_Damage = 0;

	__END_CATCH
}

void EffectMagmaticEruption::checkPosition()
{
	__BEGIN_TRY

	for ( int i=-2; i<=2; ++i )
	for ( int j=-2; j<=2; ++j )
	{
		int tx = m_X + i;
		int ty = m_Y + j;

		if ( !isValidZoneCoord( m_pZone, tx, ty ) ) continue;
		Tile& tile = m_pZone->getTile(tx, ty);
		// Ÿ�� �ȿ� �����ϴ� ������Ʈ���� �˻��Ѵ�.
		const slist<Object*>& oList = tile.getObjectList();
		slist<Object*>::const_iterator itr = oList.begin();
		for (; itr != oList.end(); itr++) 
		{
			Assert(*itr != NULL);

			Object* pObject = *itr;
			Assert(pObject != NULL);

			if (pObject->getObjectClass() == Object::OBJECT_CLASS_CREATURE)
			{
				Creature* pCreature = dynamic_cast<Creature*>(pObject);
				Assert(pCreature != NULL);

				m_TargetPositions[pCreature->getObjectID()].x = tx;
				m_TargetPositions[pCreature->getObjectID()].y = ty;
			}
		}
	}


	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectMagmaticEruption::affect()
	
{
	__BEGIN_TRY

	//cout << "EffectMagmaticEruption" << "affect BEGIN" << endl;
	
	Assert(m_pZone != NULL);

	// ����Ʈ ����ڸ� �����´�.
	// ���� ���� �� �����Ƿ� NULL �� �� �� �ִ�.
	Creature * pCastCreature = m_pZone->getCreature( m_UserObjectID );

	for ( int i=-2; i<=2; ++i )
	for ( int j=-2; j<=2; ++j )
	{
		int tx = m_X + i;
		int ty = m_Y + j;

		if ( !isValidZoneCoord( m_pZone, tx, ty ) ) continue;

		// ���� ����Ʈ�� �پ��ִ� Ÿ���� �޾ƿ´�.
		Tile& tile = m_pZone->getTile(tx, ty);

		// Ÿ�� �ȿ� �����ϴ� ������Ʈ���� �˻��Ѵ�.
		const slist<Object*>& oList = tile.getObjectList();
		slist<Object*>::const_iterator itr = oList.begin();
		for (; itr != oList.end(); itr++) 
		{
			Assert(*itr != NULL);

			Object* pObject = *itr;
			Assert(pObject != NULL);

			if (pObject->getObjectClass() == Object::OBJECT_CLASS_CREATURE)
			{
				Creature* pCreature = dynamic_cast<Creature*>(pObject);
				Assert(pCreature != NULL);

				// �������� üũ. by sigi. 2002.9.5
				// �� �鿪. by sigi. 2002.9.13
				if ( pCastCreature != NULL &&
					( !canAttack( pCastCreature, pCreature )
					|| pCreature->isFlag(Effect::EFFECT_CLASS_COMA) 
					|| !canHit( pCastCreature, pCreature, SKILL_MAGMATIC_ERUPTION ) )
				)
				{
					continue;
				}

				// 2003.1.10 by Sequoia
				// �������� üũ
				if( !checkZoneLevelToHitTarget( pCreature ) ) continue;

				if (pCreature->getMoveMode() != Creature::MOVE_MODE_FLYING)
				{
					GCModifyInformation gcAttackerMI;
					GCModifyInformation gcDefenderMI;

					Damage_t damage = m_Damage;
					hash_map<ObjectID_t, TPOINT>::iterator itr = m_TargetPositions.find( pCreature->getObjectID() );

					if ( itr == m_TargetPositions.end() )
					{
//						damage = m_Damage;
						m_TargetPositions[pCreature->getObjectID()].x = pCreature->getX();
						m_TargetPositions[pCreature->getObjectID()].y = pCreature->getY();
					}
					else
					{
						if ( itr->second.x == pCreature->getX() && itr->second.y == pCreature->getY() )
						{
//							damage = m_Damage;
						}
						else
						{
							m_TargetPositions[pCreature->getObjectID()].x = pCreature->getX();
							m_TargetPositions[pCreature->getObjectID()].y = pCreature->getY();
							damage = 2;
						}
					}

					if (pCreature->isVampire())
					{
						Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);

						::setDamage( pVampire, damage, pCastCreature, SKILL_MAGMATIC_ERUPTION, &gcDefenderMI, &gcAttackerMI, true, false );

						Player* pPlayer = pVampire->getPlayer();
						Assert(pPlayer != NULL);
						pPlayer->sendPacket(&gcDefenderMI);
					}
					else if (pCreature->isOusters()) 
					{
						Ousters* pOusters = dynamic_cast<Ousters*>(pCreature);

						::setDamage( pOusters, damage, pCastCreature, SKILL_MAGMATIC_ERUPTION, &gcDefenderMI, &gcAttackerMI, true, false );

						Player* pPlayer = pOusters->getPlayer();
						Assert(pPlayer != NULL);
						pPlayer->sendPacket(&gcDefenderMI);
					} 
					else if (pCreature->isMonster())
					{
						Monster* pMonster = dynamic_cast<Monster*>(pCreature);
					
						::setDamage( pMonster, damage, pCastCreature, SKILL_MAGMATIC_ERUPTION, NULL, &gcAttackerMI, true, false );
					}
					else continue; // �ƿ콺��� NPC ����... -_-

					if ( gcAttackerMI.getShortCount() != 0 || gcAttackerMI.getLongCount() != 0 ) pCastCreature->getPlayer()->sendPacket(&gcAttackerMI);
				}
			}
		}
	}
	
	setNextTime(10);

	//cout << "EffectMagmaticEruption" << "affect END" << endl;

	__END_CATCH 
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectMagmaticEruption::unaffect()
	
{
	__BEGIN_TRY

	//cout << "EffectMagmaticEruption" << "unaffect BEGIN" << endl;

    Tile& tile = m_pZone->getTile(m_X, m_Y);
	tile.deleteEffect(m_ObjectID);

	//cout << "EffectMagmaticEruption" << "unaffect END" << endl;

	__END_CATCH
}
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectMagmaticEruption::toString()
	
{
	__BEGIN_TRY

	StringStream msg;

	msg << "EffectMagmaticEruption("
		<< "ObjectID:" << getObjectID()
		<< ")";

	return msg.toString();

	__END_CATCH

}

