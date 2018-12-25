//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectKillAftermath.h
// Written by  : elca@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_KILL_AFTERMATH__
#define __EFFECT_KILL_AFTERMATH__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectKillAftermath
//////////////////////////////////////////////////////////////////////////////

class EffectKillAftermath : public Effect 
{
public:
	EffectKillAftermath(Creature* pCreature);
	~EffectKillAftermath();

public:
    EffectClass getEffectClass()  { return EFFECT_CLASS_KILL_AFTERMATH; }

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
// class EffectKillAftermathLoader
//////////////////////////////////////////////////////////////////////////////

class EffectKillAftermathLoader : public EffectLoader 
{
public:
	virtual Effect::EffectClass getEffectClass()  { return Effect::EFFECT_CLASS_KILL_AFTERMATH; }
	virtual string getEffectClassName()  { return "EffectKillAftermath"; }

public:
	virtual void load(Creature* pCreature);
};

extern EffectKillAftermathLoader* g_pEffectKillAftermathLoader;

#endif // __EFFECT_KILL_AFTERMATH__
