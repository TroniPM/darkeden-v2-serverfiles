//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectSummonSylph.h
// Written by  : crazydog
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_SUMMON_SYLPH__
#define __EFFECT_SUMMON_SYLPH__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectSummonSylph
//////////////////////////////////////////////////////////////////////////////

class EffectSummonSylph : public Effect 
{
public:
	EffectSummonSylph(Creature* pCreature);

public:
    EffectClass getEffectClass()  { return EFFECT_CLASS_SUMMON_SYLPH; }
    EffectClass getSendEffectClass()  { return m_EClass; }

	void affect() {}

	void unaffect(Creature* pCreature);
	void unaffect();

	string toString() ;

public:
	void setBonus( uint bonus ) { m_Bonus = bonus; }
	uint getBonus() const { return m_Bonus; }

	void setEClass( EffectClass eclass ) { m_EClass = eclass; }
	EffectClass getEClass() const { return m_EClass; }

private:
	uint	m_Bonus;
	EffectClass m_EClass;
};

#endif // __EFFECT_SUMMON_SYLPH__
