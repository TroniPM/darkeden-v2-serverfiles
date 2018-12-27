//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectRegeneration.h
// Written by  : bezz
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_GLORYGROUND__
#define __EFFECT_GLORYGROUND__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectRegeneration
//////////////////////////////////////////////////////////////////////////////

class EffectGloryGround : public Effect 
{
public:
	EffectGloryGround(Zone* pZone, ZoneCoord_t X, ZoneCoord_t Y);

public:
    EffectClass getEffectClass()  { return EFFECT_CLASS_GLORYGROUND; }

	void affect();
	void affect(Zone* pZone, ZoneCoord_t X, ZoneCoord_t Y);

	void unaffect();

	string toString() ;

public:
	void setUserObjectID(ObjectID_t oid)  { m_UserObjectID = oid; }
	ObjectID_t getUserObjectID()  { return m_UserObjectID; }

	void setSlayer( bool bVampire = true ) { m_bSlayer = bVampire; }
	bool isSlayer() const { return m_bSlayer; }

	Damage_t getDamage() const { return m_Damage; }
	void setDamage( Damage_t damage ) { m_Damage = damage; }
	
	void setDelay(Turn_t delay) { m_Delay = delay; }
	Turn_t getDelay() const { return m_Delay; }

private:
	ObjectID_t	m_UserObjectID;
	bool		m_bSlayer;
	Turn_t m_Delay;
	Damage_t m_Damage;
};

#endif
