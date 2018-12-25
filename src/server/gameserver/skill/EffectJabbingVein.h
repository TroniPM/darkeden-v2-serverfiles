//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectJabbingVein.h
// Written by  : crazydog
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_JABBING_VEIN__
#define __EFFECT_JABBING_VEIN__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectJabbingVein
//////////////////////////////////////////////////////////////////////////////

class EffectJabbingVein : public Effect 
{
public:
	EffectJabbingVein(Creature* pCreature);

public:
    EffectClass getEffectClass()  { return EFFECT_CLASS_JABBING_VEIN; }

	void affect() throw(Error){}

	void unaffect(Creature* pCreature);
	void unaffect();

	string toString() ;

};

#endif // __EFFECT_JABBING_VEIN__
