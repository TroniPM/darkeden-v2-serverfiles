//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectAutoTurret.h
// Written by  : bezz
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_TIFFAUGES_REALWORLD_LEFT_UP__
#define __EFFECT_TIFFAUGES_REALWORLD_LEFT_UP__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectAutoTurret
//////////////////////////////////////////////////////////////////////////////

class EffectTiffaugesRealWorldLeftUP : public Effect 
{
public:
	EffectTiffaugesRealWorldLeftUP(Zone* pZone, ZoneCoord_t X, ZoneCoord_t Y);

public:
    EffectClass getEffectClass()  { return EFFECT_CLASS_TIFFAUGES_REALWORLD_LEFT_UP; }

	void affect();
	void affect(Zone* pZone, ZoneCoord_t X, ZoneCoord_t Y);

	void unaffect();

	string toString() ;
};

#endif
