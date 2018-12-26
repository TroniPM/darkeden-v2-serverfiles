//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectBless.h
// Written by  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_THE_ROAR_OF_AWAKEN_WARRIOR__
#define __EFFECT_THE_ROAR_OF_AWAKEN_WARRIOR__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectBless
//////////////////////////////////////////////////////////////////////////////

class EffectTheRoarOfAwakenWarrior : public Effect 
{
public:
	EffectTheRoarOfAwakenWarrior(Creature* pCreature);

public:
    EffectClass getEffectClass()  { return EFFECT_CLASS_THE_ROAR_OF_AWAKEN_WARRIOR; }

	void affect()  {}
	void affect(Creature* pCreature);
	void affect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject);

	void unaffect(Creature* pCreature);
	void unaffect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject);
	void unaffect(); 
	void unaffect(Item* pItem)  {}

	string toString() ;
};

#endif // __EFFECT_BLESS__
