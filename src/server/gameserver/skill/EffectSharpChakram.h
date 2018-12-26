//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectSharpChakram.h
// Written by  : crazydog
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_SHARP_CHAKRAM__
#define __EFFECT_SHARP_CHAKRAM__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectSharpChakram
//////////////////////////////////////////////////////////////////////////////

class EffectSharpChakram : public Effect 
{
public:
	EffectSharpChakram(Creature* pCreature);

public:
    EffectClass getEffectClass()  { return EFFECT_CLASS_SHARP_CHAKRAM; }

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

#endif // __EFFECT_SHARP_CHAKRAM__
