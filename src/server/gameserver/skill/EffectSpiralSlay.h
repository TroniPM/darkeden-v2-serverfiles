//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectPotentialExplosion.h
// Written by  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_SPIRAL_SLAY__
#define __EFFECT_SPIRAL_SLAY__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectPotentialExplosion
//////////////////////////////////////////////////////////////////////////////

class EffectSpiralSlay : public Effect 
{
public:
	EffectSpiralSlay(Creature* pCreature);

public:
    EffectClass getEffectClass()  { return EFFECT_CLASS_SPIRAL_SLAY; }

	void affect()  {}
	void affect(Creature* pCreature);
	void affect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject);

	void unaffect(Creature* pCreature);
	void unaffect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject);
	void unaffect(); 
	void unaffect(Item* pItem)  {}

	string toString() ;
};

#endif // __EFFECT_POTENTIAL_EXPLOSION__
