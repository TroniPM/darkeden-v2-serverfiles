//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectDetectInvisibility.h
// Written by  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_DETECT_INVISIBILITY__
#define __EFFECT_DETECT_INVISIBILITY__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectDetectInvisibility
//////////////////////////////////////////////////////////////////////////////

class EffectDetectInvisibility : public Effect 
{
public:
	EffectDetectInvisibility(Creature* pCreature);

public:
    EffectClass getEffectClass()  { return EFFECT_CLASS_DETECT_INVISIBILITY; }

	void affect() throw(Error){}
	void affect(Creature* pCreature);
	void affect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject);

	void unaffect();
	void unaffect(Creature* pCreature);
	void unaffect(Item* pItem) throw(Error) {}
	void unaffect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject);

	string toString() ;

private:

};

#endif // __EFFECT_DETECT_INVISIBILITY__
