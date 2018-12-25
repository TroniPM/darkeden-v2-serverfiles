//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectGroundElemental.h
// Written by  : excel96
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_GROUND_ELEMENTAL__
#define __EFFECT_GROUND_ELEMENTAL__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectGroundElemental
//////////////////////////////////////////////////////////////////////////////

class EffectGroundElemental : public Effect 
{
public:
	EffectGroundElemental(Creature* pCreature);

public:
    EffectClass getEffectClass()  { return EFFECT_CLASS_GROUND_ELEMENTAL_CENTER; }

	void unaffect();
	void unaffect(Creature* pCreature);
	string toString() ;

public:
};

#endif // __EFFECT_GROUND_ELEMENTAL__
