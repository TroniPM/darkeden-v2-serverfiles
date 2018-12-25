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
	EffectSpiralSlay(Creature* pCreature) throw(Error);

public:
    EffectClass getEffectClass()  { return EFFECT_CLASS_SPIRAL_SLAY; }

	void affect() throw(Error) {}
	void affect(Creature* pCreature) throw(Error);
	void affect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject) throw(Error);

	void unaffect(Creature* pCreature) throw(Error);
	void unaffect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject) throw(Error);
	void unaffect() throw(Error); 
	void unaffect(Item* pItem) throw(Error) {}

	string toString() ;
};

#endif // __EFFECT_POTENTIAL_EXPLOSION__
