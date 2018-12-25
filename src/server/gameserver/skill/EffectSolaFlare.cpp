//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectShadowOfStorm.cpp
// Written by  :
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "Effect.h"
#include "EffectSolaFlare.h"
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
EffectSolaFlare::EffectSolaFlare(Zone* pZone, ZoneCoord_t zoneX, ZoneCoord_t zoneY) 
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

void EffectSolaFlare::checkPosition()
{
	__BEGIN_TRY

	for ( int i=-2; i<=2; ++i )
	for ( int j=-2; j<=2; ++j )
	{
		int tx = m_X + i;
		int ty = m_Y + j;

		if ( !isValidZoneCoord( m_pZone, tx, ty ) ) continue;
		Tile& tile = m_pZone->getTile(tx, ty);
		// 타일 안에 존재하는 오브젝트들을 검색한다.
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
void EffectSolaFlare::affect()
	throw(Error)
{
	__BEGIN_TRY

	//cout << "EffectSolaFlare" << "affect BEGIN" << endl;
	
	Assert(m_pZone != NULL);

	// 이펙트 사용자를 가져온다.
	// 존에 없을 수 있으므로 NULL 이 될 수 있다.
	Creature * pCastCreature = m_pZone->getCreature( m_UserObjectID );

	for ( int i=-2; i<=2; ++i )
	for ( int j=-2; j<=2; ++j )
	{
		int tx = m_X + i;
		int ty = m_Y + j;

		if ( !isValidZoneCoord( m_pZone, tx, ty ) ) continue;

		// 현재 이펙트가 붙어있는 타일을 받아온다.
		Tile& tile = m_pZone->getTile(tx, ty);

		// 타일 안에 존재하는 오브젝트들을 검색한다.
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

				// 무적상태 체크. by sigi. 2002.9.5
				// 산 면역. by sigi. 2002.9.13
				if ( pCastCreature != NULL &&
					( !canAttack( pCastCreature, pCreature )
					|| pCreature->isFlag(Effect::EFFECT_CLASS_COMA) 
					|| !canHit( pCastCreature, pCreature, SKILL_SOLA_FLARE ) )
				)
				{
					continue;
				}

				// 2003.1.10 by Sequoia
				// 안전지대 체크
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

						::setDamage( pVampire, damage, pCastCreature, SKILL_SOLA_FLARE, &gcDefenderMI, &gcAttackerMI, true, false );

						Player* pPlayer = pVampire->getPlayer();
						Assert(pPlayer != NULL);
						pPlayer->sendPacket(&gcDefenderMI);
					}
					else if (pCreature->isOusters()) 
					{
						Ousters* pOusters = dynamic_cast<Ousters*>(pCreature);

						::setDamage( pOusters, damage, pCastCreature, SKILL_SOLA_FLARE, &gcDefenderMI, &gcAttackerMI, true, false );

						Player* pPlayer = pOusters->getPlayer();
						Assert(pPlayer != NULL);
						pPlayer->sendPacket(&gcDefenderMI);
					} 
					else if (pCreature->isMonster())
					{
						Monster* pMonster = dynamic_cast<Monster*>(pCreature);
					
						::setDamage( pMonster, damage, pCastCreature, SKILL_SOLA_FLARE, NULL, &gcAttackerMI, true, false );
					}
					else continue; // 아우스터즈나 NPC 상대로... -_-

					if ( gcAttackerMI.getShortCount() != 0 || gcAttackerMI.getLongCount() != 0 ) pCastCreature->getPlayer()->sendPacket(&gcAttackerMI);
				}
			}
		}
	}
	
	setNextTime(3);

	//cout << "EffectSolaFlare" << "affect END" << endl;

	__END_CATCH 
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectSolaFlare::unaffect()
	throw(Error)
{
	__BEGIN_TRY

	//cout << "EffectSolaFlare" << "unaffect BEGIN" << endl;

    Tile& tile = m_pZone->getTile(m_X, m_Y);
	tile.deleteEffect(m_ObjectID);

	//cout << "EffectSolaFlare" << "unaffect END" << endl;

	__END_CATCH
}
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectSolaFlare::toString()
	
{
	__BEGIN_TRY

	StringStream msg;

	msg << "EffectSolaFlare("
		<< "ObjectID:" << getObjectID()
		<< ")";

	return msg.toString();

	__END_CATCH

}

