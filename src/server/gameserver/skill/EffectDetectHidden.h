//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectDetectHidden.h
// Written by  : elca@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_DETECT_HIDDEN__
#define __EFFECT_DETECT_HIDDEN__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectDetectHidden
//////////////////////////////////////////////////////////////////////////////

class EffectDetectHidden : public Effect 
{
public:
	EffectDetectHidden(Creature* pCreature);

public:
    EffectClass getEffectClass()  { return EFFECT_CLASS_DETECT_HIDDEN; }

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

#endif // __EFFECT_DETECT_HIDDEN__
