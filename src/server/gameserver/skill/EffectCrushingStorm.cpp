//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectShadowOfStorm.cpp
// Written by  :
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "Effect.h"
#include "EffectCrushingStorm.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Ousters.h"
#include "Monster.h"
#include "GamePlayer.h"
#include "SkillUtil.h"
#include "ZoneUtil.h"

#include "Gpackets/GCModifyInformation.h"
#include "Gpackets/GCStatusCurrentHP.h"
#include "Gpackets/GCAddEffect.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectCrushingStorm::EffectCrushingStorm(Zone* pZone, ZoneCoord_t zoneX, ZoneCoord_t zoneY) 
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

void EffectCrushingStorm::checkPosition()
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
void EffectCrushingStorm::affect()
	throw(Error)
{
	__BEGIN_TRY

	//cout << "EffectCrushingStorm" << "affect BEGIN" << endl;
	
	Assert(m_pZone != NULL);

	// 이펙트 사용자를 가져온다.
	// 존에 없을 수 있으므로 NULL 이 될 수 있다.
	Creature * pCastCreature = m_pZone->getCreature( m_UserObjectID );
	
	setNextTime(10);

	//cout << "EffectCrushingStorm" << "affect END" << endl;

	__END_CATCH 
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectCrushingStorm::unaffect()
	throw(Error)
{
	__BEGIN_TRY

	//cout << "EffectCrushingStorm" << "unaffect BEGIN" << endl;

    Tile& tile = m_pZone->getTile(m_X, m_Y);
	tile.deleteEffect(m_ObjectID);

	//cout << "EffectCrushingStorm" << "unaffect END" << endl;

	__END_CATCH
}
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectCrushingStorm::toString()
	
{
	__BEGIN_TRY

	StringStream msg;

	msg << "EffectCrushingStorm("
		<< "ObjectID:" << getObjectID()
		<< ")";

	return msg.toString();

	__END_CATCH

}

