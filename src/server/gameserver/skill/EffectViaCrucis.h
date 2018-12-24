//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectShadowOfStorm.h
// Written by  : elca@ewestsoft.com
// Description : 성직마법 ShadowOfStorm의 Effect를 처리해주기 위한 클래스이다.
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_VIA_CRUCIS__
#define __EFFECT_VIA_CRUCIS__

#include "Effect.h"
#include <hash_map>

//////////////////////////////////////////////////////////////////////////////
// class EffectShadowOfStorm
//////////////////////////////////////////////////////////////////////////////

class EffectViaCrucis : public Effect 
{
public:
	EffectViaCrucis(Zone* pZone, ZoneCoord_t zoneX, ZoneCoord_t zoneY) throw(Error);

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_VIA_CRUCIS; }

	void affect() throw(Error);
	void unaffect() throw(Error);
	string toString() const throw();

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
