//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectAftermath.h
// Written by  : elca@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_AFTERMATH__
#define __EFFECT_AFTERMATH__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectAftermath
//////////////////////////////////////////////////////////////////////////////

class EffectAftermath : public Effect 
{
public:
	EffectAftermath(Creature* pCreature);
	~EffectAftermath();

public:
    EffectClass getEffectClass()  { return EFFECT_CLASS_AFTERMATH; }

	void affect() throw(Error) {}
	void affect(Creature* pCreature);
	void affect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject);

	void unaffect();
	void unaffect(Item* pItem) throw(Error) {}
	void unaffect(Creature* pCreature);
	void unaffect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject);

	virtual void create(const string & ownerID);
	virtual void destroy(const string & ownerID);
	virtual void save(const string & ownerID);

	string toString() ;
};


//////////////////////////////////////////////////////////////////////////////
// class EffectAftermathLoader
//////////////////////////////////////////////////////////////////////////////

class EffectAftermathLoader : public EffectLoader 
{
public:
	virtual Effect::EffectClass getEffectClass()  { return Effect::EFFECT_CLASS_AFTERMATH; }
	virtual string getEffectClassName()  { return "EffectAftermath"; }

public:
	virtual void load(Creature* pCreature);
};

extern EffectAftermathLoader* g_pEffectAftermathLoader;

#endif // __EFFECT_AFTERMATH__
