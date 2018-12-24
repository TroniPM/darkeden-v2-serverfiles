//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectShadowOfStorm.cpp
// Written by  :
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "Effect.h"
#include "EffectBlizzard.h"
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
EffectBlizzard::EffectBlizzard(Zone* pZone, ZoneCoord_t zoneX, ZoneCoord_t zoneY) 
	throw(Error)
{
	__BEGIN_TRY

	m_pZone = pZone;
	m_X = zoneX;
	m_Y = zoneY;
	m_UserObjectID = 0;
	m_Damage = 0;

	__END_CATCH
}

void EffectBlizzard::checkPosition()
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
void EffectBlizzard::affect()
	throw(Error)
{
	__BEGIN_TRY

	//cout << "EffectBlizzard" << "affect BEGIN" << endl;
	
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
					|| !canHit( pCastCreature, pCreature, SKILL_BLIZZARD ) )
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
							damage /= 2;
						}
					}

					if (pCreature->isSlayer()) 
					{
						Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);

						::setDamage( pSlayer, damage, pCastCreature, SKILL_BLIZZARD, &gcDefenderMI, &gcAttackerMI, true, false );

						Player* pPlayer = pSlayer->getPlayer();
						Assert(pPlayer != NULL);
						pPlayer->sendPacket(&gcDefenderMI);
					} 
					else if (pCreature->isVampire())
					{
						Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);

						::setDamage( pVampire, damage, pCastCreature, SKILL_BLIZZARD, &gcDefenderMI, &gcAttackerMI, true, false );

						Player* pPlayer = pVampire->getPlayer();
						Assert(pPlayer != NULL);
						pPlayer->sendPacket(&gcDefenderMI);
					}
					else if (pCreature->isMonster())
					{
						Monster* pMonster = dynamic_cast<Monster*>(pCreature);
					
						::setDamage( pMonster, damage, pCastCreature, SKILL_BLIZZARD, NULL, &gcAttackerMI, true, false );
					}
					else continue; // �ƿ콺��� NPC ����... -_-

					// �׾����� ����ġ�ش�. ��.....
					if ( pCastCreature != NULL )
					{
						if (pCreature->isDead() && pCastCreature->isOusters())
						{
							Ousters* pCastOusters = dynamic_cast<Ousters*>( pCastCreature );
							Assert( pCastOusters != NULL );

	//						int exp = computeCreatureExp(pCreature, 100, pCastOusters);
							int exp = computeCreatureExp(pCreature, 70, pCastOusters);
							shareOustersExp(pCastOusters, exp, gcAttackerMI);
						}
					}

					// ���� ����ϱ�
	/*				if ( pCastCreature != NULL
						&& pCastCreature->isPC()
						&& pCreature->isPC()
					)
					{
						computeAlignmentChange( pCreature, m_Damage, pCastCreature, &gcDefenderMI, &gcAttackerMI );
						modifiedAttacker = true;
					}*/

					if ( gcAttackerMI.getShortCount() != 0 || gcAttackerMI.getLongCount() != 0 ) pCastCreature->getPlayer()->sendPacket(&gcAttackerMI);
				}
			}
		}
	}
	
	setNextTime(3);

	//cout << "EffectBlizzard" << "affect END" << endl;

	__END_CATCH 
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectBlizzard::unaffect()
	throw(Error)
{
	__BEGIN_TRY

	//cout << "EffectBlizzard" << "unaffect BEGIN" << endl;

    Tile& tile = m_pZone->getTile(m_X, m_Y);
	tile.deleteEffect(m_ObjectID);

	//cout << "EffectBlizzard" << "unaffect END" << endl;

	__END_CATCH
}
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectBlizzard::toString()
	const throw()
{
	__BEGIN_TRY

	StringStream msg;

	msg << "EffectBlizzard("
		<< "ObjectID:" << getObjectID()
		<< ")";

	return msg.toString();

	__END_CATCH

}

