//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectHandsOfFire.h
// Written by  : crazydog
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_THE_RAGE_OF_GUARDIAN_SPIRIT__
#define __EFFECT_THE_RAGE_OF_GUARDIAN_SPIRIT__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectHandsOfFire
//////////////////////////////////////////////////////////////////////////////

class EffectTheRageofGuardianSpirit : public Effect 
{
public:
	EffectTheRageofGuardianSpirit(Creature* pCreature) throw(Error);

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_THE_RAGE_OF_GUARDIAN_SPIRIT; }

	void affect() throw(Error){}

	void unaffect(Creature* pCreature) throw(Error);
	void unaffect() throw(Error);

	string toString() const throw();
};

#endif // __EFFECT_HANDS_OF_FIRE__
