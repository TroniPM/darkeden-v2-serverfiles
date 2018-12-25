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
	EffectTiffaugesJoin(Creature* pCreature);

public:
    EffectClass getEffectClass()  { return EFFECT_CLASS_TIFFAUGES_OLD_JOIN; }

	void affect();
	void affect(Creature* pCreature);

	void unaffect();
	void unaffect(Creature* pCreature);

	string toString() ;
};

#endif
