//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectEvade.h
// Written by  : crazydog
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_EVADE__
#define __EFFECT_EVADE__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectEvade
//////////////////////////////////////////////////////////////////////////////

class EffectEvade : public Effect 
{
public:
	EffectEvade(Creature* pCreature);

public:
    EffectClass getEffectClass()  { return EFFECT_CLASS_EVADE; }

	void affect() {}

	void unaffect(Creature* pCreature);
	void unaffect();

	string toString() ;

public:
	void setBonus( uint bonus ) { m_Bonus = bonus; }
	uint getBonus() const { return m_Bonus; }

private:
	uint	m_Bonus;
};

#endif // __EFFECT_EVADE__
