//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectConcealment.h
// Written by  : crazydog
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_TRUE_COLOR_OF_VAMP_LOAD__
#define __EFFECT_TRUE_COLOR_OF_VAMP_LOAD__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectConcealment
//////////////////////////////////////////////////////////////////////////////

class EffectTrueColorofVampLoad : public Effect 
{
public:
	EffectTrueColorofVampLoad(Creature* pCreature) throw(Error);

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_TRUE_COLOR_OF_VAMP_LOAD; }

	void affect() throw(Error){}

	void unaffect(Creature* pCreature) throw(Error);
	void unaffect() throw(Error);

	string toString() const throw();
};

#endif // __EFFECT_CONCEALMENT__
