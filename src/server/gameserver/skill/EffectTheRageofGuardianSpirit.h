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
	EffectTheRageofGuardianSpirit(Creature* pCreature);

public:
    EffectClass getEffectClass()  { return EFFECT_CLASS_THE_RAGE_OF_GUARDIAN_SPIRIT; }

	void affect() {}

	void unaffect(Creature* pCreature);
	void unaffect();

	string toString() ;
};

#endif // __EFFECT_HANDS_OF_FIRE__
