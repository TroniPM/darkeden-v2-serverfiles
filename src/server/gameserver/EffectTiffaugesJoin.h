//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectBrambleHalo.h
// Written by  : bezz
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_TIFFAUGES_JOIN__
#define __EFFECT_TIFFAUGES_JOIN__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectBrambleHalo
//////////////////////////////////////////////////////////////////////////////

class EffectTiffaugesJoin : public Effect 
{
public:
	EffectTiffaugesJoin(Creature* pCreature) throw(Error);

public:
    EffectClass getEffectClass()  { return EFFECT_CLASS_TIFFAUGES_OLD_JOIN; }

	void affect() throw(Error);
	void affect(Creature* pCreature) throw(Error);

	void unaffect() throw(Error);
	void unaffect(Creature* pCreature) throw(Error);

	string toString() ;
};

#endif
