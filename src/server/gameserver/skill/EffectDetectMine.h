//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectDetectMine.h
// Written by  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_DETECT_MINE__
#define __EFFECT_DETECT_MINE__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectDetectMine
//////////////////////////////////////////////////////////////////////////////

class EffectDetectMine : public Effect 
{
public:
	EffectDetectMine(Creature* pCreature);

public:
    EffectClass getEffectClass()  { return EFFECT_CLASS_REVEALER; }

	void affect() {}
	void affect(Creature* pCreature);
	void affect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject);

	void unaffect();
	void unaffect(Creature* pCreature);
	void unaffect(Item* pItem)  {}
	void unaffect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject);

	string toString() ;

private:
};

#endif // __EFFECT_DETECT_MINE__
