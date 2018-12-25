//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectWaterBarrier.h
// Written by  : crazydog
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_WATER_BARRIER__
#define __EFFECT_WATER_BARRIER__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectWaterBarrier
//////////////////////////////////////////////////////////////////////////////

class EffectWaterBarrier : public Effect 
{
public:
	EffectWaterBarrier(Creature* pCreature);

public:
    EffectClass getEffectClass()  { return EFFECT_CLASS_WATER_BARRIER; }

	void affect() throw(Error){}

	void unaffect(Creature* pCreature);
	void unaffect();

	string toString() ;

public:
	void setBonus( uint bonus ) { m_Bonus = bonus; }
	uint getBonus() const { return m_Bonus; }

private:
	uint	m_Bonus;
};

#endif // __EFFECT_WATER_BARRIER__
