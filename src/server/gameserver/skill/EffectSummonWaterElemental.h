//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectSummonWaterElemental.h
// Written by  : crazydog
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_SUMMON_WATER_ELEMENTAL__
#define __EFFECT_SUMMON_WATER_ELEMENTAL__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectSummonWaterElemental
//////////////////////////////////////////////////////////////////////////////

class EffectSummonWaterElemental : public Effect 
{
public:
	EffectSummonWaterElemental(Creature* pCreature);

public:
    EffectClass getEffectClass()  { return EFFECT_CLASS_WATER_ELEMENTAL; }

	void affect();

	void unaffect(Creature* pCreature);
	void unaffect();

	string toString() ;

public:
	void setDamage( uint bonus ) { m_Damage = bonus; }
	uint getDamage() const { return m_Damage; }

private:
	uint	m_Damage;
};

#endif // __EFFECT_SUMMON_WATER_ELEMENTAL__
