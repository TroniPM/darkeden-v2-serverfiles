//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectRingOfFlare.h
// Written by  : crazydog
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_RING_OF_FLARE__
#define __EFFECT_RING_OF_FLARE__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectRingOfFlare
//////////////////////////////////////////////////////////////////////////////

class EffectRingOfFlare : public Effect 
{
public:
	EffectRingOfFlare(Creature* pCreature);

public:
    EffectClass getEffectClass()  { return EFFECT_CLASS_RING_OF_FLARE; }
	EffectClass getSendEffectClass()  { return m_SendEffectClass; }

	void affect();

	void unaffect(Creature* pCreature);
	void unaffect();

	string toString() ;

public:
	void setSendEffectClass(EffectClass eClass)  { m_SendEffectClass = eClass; }

	void setDamage( uint bonus ) { m_Damage = bonus; }
	uint getDamage() const { return m_Damage; }

private:
	EffectClass m_SendEffectClass;
	uint	m_Damage;
};

#endif // __EFFECT_RING_OF_FLARE__
