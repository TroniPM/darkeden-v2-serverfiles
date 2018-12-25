//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectRestore.h
// Written by  : excel96
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_RESTORE__
#define __EFFECT_RESTORE__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectRestore
//////////////////////////////////////////////////////////////////////////////

class EffectRestore : public Effect 
{
public:
	EffectRestore(Creature* pCreature) throw(Error);

public:
    EffectClass getEffectClass()  { return EFFECT_CLASS_RESTORE; }

	void affect() throw(Error) {}
	void affect(Creature* pCreature) throw(Error);
	void affect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject) throw(Error);

	void unaffect() throw(Error);
	void unaffect(Item* pItem) throw(Error) {}
	void unaffect(Creature* pCreature) throw(Error);
	void unaffect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject) throw(Error);

	virtual void create(const string & ownerID) throw(Error);
	virtual void destroy(const string & ownerID) throw(Error);
	virtual void save(const string & ownerID) throw(Error);

	string toString() ;
};

//////////////////////////////////////////////////////////////////////////////
// class EffectRestoreLoader
//////////////////////////////////////////////////////////////////////////////

class EffectRestoreLoader : public EffectLoader 
{
public:
	virtual Effect::EffectClass getEffectClass()  { return Effect::EFFECT_CLASS_RESTORE; }
	virtual string getEffectClassName()  { return "EffectRestore"; }

public:
	virtual void load(Creature* pCreature) throw(Error);

};

extern EffectRestoreLoader* g_pEffectRestoreLoader;

#endif // __EFFECT_RESTORE__
