//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectLight.h
// Written by  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_FLAME_SIGHT__
#define __EFFECT_FLAME_SIGHT__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectFlameSight
//////////////////////////////////////////////////////////////////////////////

class EffectFlameSight : public Effect 
{
public:
	EffectFlameSight(Creature* pCreature);

public:
    EffectClass getEffectClass()  { return EFFECT_CLASS_FLAME_SIGHT; }

	void affect() {}
	void affect(Creature* pCreature);
	void affect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject);

	void unaffect();
	void unaffect(Creature* pCreature);
	void unaffect(Item*  pItem)  {}
	void unaffect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject);

	virtual void create(const string & ownerID);
	virtual void destroy(const string & ownerID);
	virtual void save(const string & ownerID);

	string toString() ;

public:
	Sight_t getOldSight()  { return m_OldSight; }
	void setOldSight(Sight_t OldSight)  { m_OldSight = OldSight; }

private:
	Sight_t m_OldSight;

};

//////////////////////////////////////////////////////////////////////////////
// class EffectFlameSightLoader
//////////////////////////////////////////////////////////////////////////////

class EffectFlameSightLoader : public EffectLoader 
{
public:
	virtual Effect::EffectClass getEffectClass()  { return Effect::EFFECT_CLASS_FLAME_SIGHT; }
	virtual string getEffectClassName()  { return "EffectFlameSight"; }

public:
	virtual void load(Creature* pCreature);

};

extern EffectFlameSightLoader* g_pEffectFlameSightLoader;

#endif // __EFFECT_FLAME_SIGHT__
