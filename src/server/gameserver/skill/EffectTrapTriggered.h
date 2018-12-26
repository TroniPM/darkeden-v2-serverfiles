//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectTrapTriggered.h
// Written by  : 
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_TRAP_TRIGGERED__
#define __EFFECT_TRAP_TRIGGERED__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectTrapTriggered
//////////////////////////////////////////////////////////////////////////////

class EffectTrapTriggered : public Effect 
{
public:
	EffectTrapTriggered(Creature* pCreature);

public:
    EffectClass getEffectClass()  { return EFFECT_CLASS_TRAP_TRIGGERED; }
	EffectClass getSendEffectClass()  { return EFFECT_CLASS_TRAPPED; }

	void affect()  {}
	void affect(Creature* pCreature);

	void unaffect(Creature* pCreature);
	void unaffect(); 

	string toString() ;

public:
private :
};

#endif // __EFFECT_TRAP_TRIGGERED__
