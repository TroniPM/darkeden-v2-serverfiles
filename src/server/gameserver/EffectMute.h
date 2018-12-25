//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectMute.h
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_MUTE__
#define __EFFECT_MUTE__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectMute
//////////////////////////////////////////////////////////////////////////////

class EffectMute : public Effect 
{
public:
	EffectMute(Creature* pCreature);

public:
    EffectClass getEffectClass()  { return EFFECT_CLASS_MUTE; }

	void affect() throw(Error) { }
	void affect(Creature* pCreature);
	void affect(Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pObject);

	void unaffect();
	void unaffect(Creature* pCreature);
	void unaffect(Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pObject);

	virtual void create(const string & ownerID);
	virtual void destroy(const string & ownerID);
	virtual void save(const string & ownerID);

	string toString() ;

};

//////////////////////////////////////////////////////////////////////////////
// class EffectMuteLoader
//////////////////////////////////////////////////////////////////////////////

class EffectMuteLoader : public EffectLoader 
{
public:
	virtual Effect::EffectClass getEffectClass()  { return Effect::EFFECT_CLASS_MUTE; }
	virtual string getEffectClassName()  { return "EffectMute"; }

public:
	virtual void load(Creature* pCreature);

};

extern EffectMuteLoader* g_pEffectMuteLoader;

#endif // __EFFECT_MUTE__
