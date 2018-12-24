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
	EffectTheRoarOfAwakenWarrior(Creature* pCreature) throw(Error);

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_THE_ROAR_OF_AWAKEN_WARRIOR; }

	void affect() throw(Error) {}
	void affect(Creature* pCreature) throw(Error);
	void affect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject) throw(Error);

	void unaffect(Creature* pCreature) throw(Error);
	void unaffect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject) throw(Error);
	void unaffect() throw(Error); 
	void unaffect(Item* pItem) throw(Error) {}

	string toString() const throw();
};

#endif // __EFFECT_BLESS__
