//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectHandsOfFire.h
// Written by  : crazydog
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_HANDS_OF_FIRE__
#define __EFFECT_HANDS_OF_FIRE__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectHandsOfFire
//////////////////////////////////////////////////////////////////////////////

class EffectHandsOfFire : public Effect 
{
public:
	EffectHandsOfFire(Creature* pCreature);

public:
    EffectClass getEffectClass()  { return EFFECT_CLASS_HANDS_OF_FIRE; }

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

#endif // __EFFECT_HANDS_OF_FIRE__
