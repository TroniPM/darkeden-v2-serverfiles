//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectHasPet.h
// Written by  : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_HAS_PET__
#define __EFFECT_HAS_PET__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectHasPet
//////////////////////////////////////////////////////////////////////////////

class EffectHasPet : public Effect 
{
public:
	EffectHasPet(Creature* pCreature) throw(Error);

public:
    EffectClass getEffectClass()  { return EFFECT_CLASS_HAS_PET; }

	void affect() throw(Error);
	void affect(Creature* pCreature) throw(Error);

	void unaffect(Creature* pCreature) throw(Error);
	void unaffect() throw(Error); 

	string toString() ;

private:
};

#endif
