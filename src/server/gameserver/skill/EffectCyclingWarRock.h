//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectRingOfFlare.h
// Written by  : crazydog
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_CYCLING_WAR_ROCK__
#define __EFFECT_CYCLING_WAR_ROCK__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectRingOfFlare
//////////////////////////////////////////////////////////////////////////////

class EffectCyclingWarRock : public Effect 
{
public:
	EffectCyclingWarRock(Creature* pCreature);

public:
    EffectClass getEffectClass()  { return EFFECT_CLASS_CYCLING_WAR_ROCK; }
	EffectClass getSendEffectClass()  { return m_SendEffectClass; }

	void affect();

	void unaffect(Creature* pCreature);
	void unaffect();

	string toString() ;

public:
	void setSendEffectClass(EffectClass eClass) throw() { m_SendEffectClass = eClass; }

	void setDamage( uint bonus ) { m_Damage = bonus; }
	uint getDamage() const { return m_Damage; }

private:
	EffectClass m_SendEffectClass;
	uint	m_Damage;
};

#endif // __EFFECT_RING_OF_FLARE__
