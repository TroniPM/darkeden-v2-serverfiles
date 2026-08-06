//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectShadowOfStorm.cpp
// Written by  :
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "Effect.h"
#include "EffectLightingShock.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Ousters.h"
#include "Monster.h"
#include "GamePlayer.h"
#include "SkillUtil.h"
#include "ZoneUtil.h"
#include "HitRoll.h"

#include "Gpackets/GCModifyInformation.h"
#include "Gpackets/GCStatusCurrentHP.h"
#include "Gpackets/GCSkillToObjectOK2.h"
#include "Gpackets/GCSkillToObjectOK4.h"
#include "Gpackets/GCAddEffect.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectLightingShock::EffectLightingShock(Zone* pZone, ZoneCoord_t zoneX, ZoneCoord_t zoneY) 
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

void EffectLightingShock::checkPosition()
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
void EffectLightingShock::affect()
	throw(Error)
{
	__BEGIN_TRY

	//cout << "EffectLightingShock" << "affect BEGIN" << endl;
	
	Assert(m_pZone != NULL);

	// 이펙트 사용자를 가져온다.
	// 존에 없을 수 있으므로 NULL 이 될 수 있다.
	Creature * pCastCreature = m_pZone->getCreature( m_UserObjectID );

	if(pCastCreature != NULL)
	{

	GCSkillToObjectOK2 gcSkillToObjectOK2;
	GCSkillToObjectOK4 gcSkillToObjectOK4;

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

				bool bHitRoll = HitRoll::isSuccess(pCastCreature, pCreature, 100/2);

				// 무적상태 체크. by sigi. 2002.9.5
				// 산 면역. by sigi. 2002.9.13
				if ( pCastCreature != NULL &&
					( !canAttack( pCastCreature, pCreature )
					|| pCreature->isFlag(Effect::EFFECT_CLASS_COMA) 
					|| !canHit( pCastCreature, pCreature, SKILL_LIGHTING_SHOCK ) || !bHitRoll)
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

						::setDamage( pVampire, damage, pCastCreature, SKILL_LIGHTING_SHOCK, &gcDefenderMI, &gcAttackerMI, true, false );

						Player* pPlayer = pVampire->getPlayer();
						Assert(pPlayer != NULL);
						pPlayer->sendPacket(&gcDefenderMI);

							// 맞는 동작을 보여준다.
							gcSkillToObjectOK2.setObjectID( 1 );    // 의미 없다.
							gcSkillToObjectOK2.setSkillType( SKILL_ATTACK_MELEE );
							gcSkillToObjectOK2.setDuration(0);
							pCreature->getPlayer()->sendPacket(&gcSkillToObjectOK2);

						GCAddEffect gcAddEffect;
						gcAddEffect.setObjectID(pCreature->getObjectID());
						gcAddEffect.setEffectID(Effect::EFFECT_CLASS_LIGHTING_SHOCK_USER);
						gcAddEffect.setDuration(20);
						m_pZone->broadcastPacket(pCreature->getX(), pCreature->getY(), &gcAddEffect);
					}
					else if (pCreature->isOusters()) 
					{
						Ousters* pOusters = dynamic_cast<Ousters*>(pCreature);

						::setDamage( pOusters, damage, pCastCreature, SKILL_LIGHTING_SHOCK, &gcDefenderMI, &gcAttackerMI, true, false );

						Player* pPlayer = pOusters->getPlayer();
						Assert(pPlayer != NULL);
						pPlayer->sendPacket(&gcDefenderMI);

							// 맞는 동작을 보여준다.
							gcSkillToObjectOK2.setObjectID( 1 );    // 의미 없다.
							gcSkillToObjectOK2.setSkillType( SKILL_ATTACK_MELEE );
							gcSkillToObjectOK2.setDuration(0);
							pCreature->getPlayer()->sendPacket(&gcSkillToObjectOK2);

						GCAddEffect gcAddEffect;
						gcAddEffect.setObjectID(pCreature->getObjectID());
						gcAddEffect.setEffectID(Effect::EFFECT_CLASS_LIGHTING_SHOCK_USER);
						gcAddEffect.setDuration(20);
						m_pZone->broadcastPacket(pCreature->getX(), pCreature->getY(), &gcAddEffect);
					} 
					else if (pCreature->isMonster())
					{
						Monster* pMonster = dynamic_cast<Monster*>(pCreature);
					
						::setDamage( pMonster, damage, pCastCreature, SKILL_LIGHTING_SHOCK, NULL, &gcAttackerMI, true, false );

						GCAddEffect gcAddEffect;
						gcAddEffect.setObjectID(pCreature->getObjectID());
						gcAddEffect.setEffectID(Effect::EFFECT_CLASS_LIGHTING_SHOCK_USER);
						gcAddEffect.setDuration(20);
						m_pZone->broadcastPacket(pCreature->getX(), pCreature->getY(), &gcAddEffect);
					}
					else continue; // 아우스터즈나 NPC 상대로... -_-

						gcSkillToObjectOK4.setTargetObjectID( pCreature->getObjectID() );
						gcSkillToObjectOK4.setSkillType( SKILL_ATTACK_MELEE );
						gcSkillToObjectOK4.setDuration( 0 );
						m_pZone->broadcastPacket( tx, ty, &gcSkillToObjectOK4, pCreature );


					if ( gcAttackerMI.getShortCount() != 0 || gcAttackerMI.getLongCount() != 0 ) pCastCreature->getPlayer()->sendPacket(&gcAttackerMI);
				}
			}
		}
	}
	}
	
	setNextTime(5);

	//cout << "EffectLightingShock" << "affect END" << endl;

	__END_CATCH 
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectLightingShock::unaffect()
	throw(Error)
{
	__BEGIN_TRY

	//cout << "EffectLightingShock" << "unaffect BEGIN" << endl;

    Tile& tile = m_pZone->getTile(m_X, m_Y);
	tile.deleteEffect(m_ObjectID);

	//cout << "EffectLightingShock" << "unaffect END" << endl;

	__END_CATCH
}
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectLightingShock::toString()
	const throw()
{
	__BEGIN_TRY

	StringStream msg;

	msg << "EffectLightingShock("
		<< "ObjectID:" << getObjectID()
		<< ")";

	return msg.toString();

	__END_CATCH

}

