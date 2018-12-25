//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectPotentialExplosion.h
// Written by  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_HURRICANECOMBO__
#define __EFFECT_HURRICANECOMBO__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectPotentialExplosion
//////////////////////////////////////////////////////////////////////////////

class EffectHurricaneCombo : public Effect 
{
public:
	EffectHurricaneCombo(Creature* pCreature) throw(Error);

public:
    EffectClass getEffectClass()  { return EFFECT_CLASS_HURRICANECOMBO; }

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
