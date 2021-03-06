//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectSatelliteBombAim.h
// Written by  : bezz
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_SKILL_SATELLITE_BOMB_AIM2__
#define __EFFECT_SKILL_SATELLITE_BOMB_AIM2__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectSatelliteBombAim
//////////////////////////////////////////////////////////////////////////////

class EffectSatelliteBombAim2 : public Effect 
{
public:
	EffectSatelliteBombAim2(Creature* pCreature, Zone* pZone, ZoneCoord_t x, ZoneCoord_t y);

public:
    EffectClass getEffectClass()  { return EFFECT_CLASS_SKILL_SATELLITE_BOMB_AIM2; }

	void affect() {}
	void affect(Creature* pCreature);

	void unaffect();
	void unaffect(Creature* pCreature);

	string toString() ;

public:
	Damage_t getDamage() const { return m_Damage; }
	void setDamage( Damage_t damage ) { m_Damage = damage; }
	
private:

	Damage_t	m_Damage;
};

#endif
