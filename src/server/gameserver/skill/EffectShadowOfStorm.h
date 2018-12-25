//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectShadowOfStorm.h
// Written by  : elca@ewestsoft.com
// Description : �������� ShadowOfStorm�� Effect�� ó�����ֱ� ���� Ŭ�����̴�.
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_SHADOW_OF_STORM__
#define __EFFECT_SHADOW_OF_STORM__

#include "Effect.h"
#include <hash_map>

//////////////////////////////////////////////////////////////////////////////
// class EffectShadowOfStorm
//////////////////////////////////////////////////////////////////////////////

class EffectShadowOfStorm : public Effect 
{
public:
	EffectShadowOfStorm(Zone* pZone, ZoneCoord_t zoneX, ZoneCoord_t zoneY) throw(Error);

public:
    EffectClass getEffectClass()  { return EFFECT_CLASS_SHADOW_OF_STORM; }

	void affect() throw(Error);
	void unaffect() throw(Error);
	string toString() ;

public:
	int getDamage(void) const { return m_Damage; }
	void setDamage(int damage) { m_Damage = damage; }

	ObjectID_t getUserObjectID() const { return m_UserObjectID; }
	void setUserObjectID( ObjectID_t UserObjectID ) { m_UserObjectID = UserObjectID; }

	void checkPosition();

private:
	int     						m_Damage;
	ObjectID_t						m_UserObjectID;
	hash_map<ObjectID_t, TPOINT>	m_TargetPositions;
};

#endif // __EFFECT_SHADOW_OF_STORM__
