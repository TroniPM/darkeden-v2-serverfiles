//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectSatelliteBombPoint.h
// Written by  : bezz
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_SKILL_SATELLITE_BOMB_POINT2__
#define __EFFECT_SKILL_SATELLITE_BOMB_POINT2__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectSatelliteBombPoint
//////////////////////////////////////////////////////////////////////////////

class EffectSatelliteBombPoint2 : public Effect 
{
public:
	EffectSatelliteBombPoint2(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y) throw(Error);

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_SKILL_SATELLITE_BOMB_POINT2; }

	void affect() throw(Error){}

	void unaffect() throw(Error);

	string toString() const throw();

private:
};

#endif
