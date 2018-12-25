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
	EffectTrapTriggered(Creature* pCreature) throw(Error);

public:
    EffectClass getEffectClass()  { return EFFECT_CLASS_TRAP_TRIGGERED; }
	EffectClass getSendEffectClass()  { return EFFECT_CLASS_TRAPPED; }

	void affect() throw(Error) {}
	void affect(Creature* pCreature) throw(Error);

	void unaffect(Creature* pCreature) throw(Error);
	void unaffect() throw(Error); 

	string toString() ;

public:
private :
};

#endif // __EFFECT_TRAP_TRIGGERED__
