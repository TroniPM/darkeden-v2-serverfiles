//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectDenialMagic.h
// Written by  : crazydog
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_DENIAL_MAGIC__
#define __EFFECT_DENIAL_MAGIC__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectDenialMagic
//////////////////////////////////////////////////////////////////////////////

class EffectDenialMagic : public Effect 
{
public:
	EffectDenialMagic(Creature* pCreature) throw(Error);

public:
    EffectClass getEffectClass()  { return EFFECT_CLASS_DENIAL_MAGIC; }

	void affect() throw(Error){}
	void affect(Creature* pCreature) throw(Error);
	void affect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject) throw(Error);

	void unaffect(Creature* pCreature) throw(Error);
	void unaffect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject) throw(Error);
	void unaffect(Item* pItem) throw(Error) {}
	void unaffect() throw(Error);

	string toString() ;

public:

private:
};

//////////////////////////////////////////////////////////////////////////////
// class EffectDenialMagicLoader
//////////////////////////////////////////////////////////////////////////////

class EffectDenialMagicLoader : public EffectLoader 
{
public:
	virtual Effect::EffectClass getEffectClass()  { return Effect::EFFECT_CLASS_DENIAL_MAGIC; }
	virtual string getEffectClassName()  { return "EffectDenialMagic"; }

public:
	virtual void load(Creature* pCreature) throw(Error) {}
};


#endif // __EFFECT_DENIAL_MAGIC__
