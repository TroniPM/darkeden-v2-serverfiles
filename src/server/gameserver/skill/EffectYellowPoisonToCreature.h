//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectYellowPoisonToCreature.h
// Written by  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_YELLOW_POISON_TO_CREATURE__
#define __EFFECT_YELLOW_POISON_TO_CREATURE__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectYellowPoisonToCreature
//////////////////////////////////////////////////////////////////////////////

class EffectYellowPoisonToCreature : public Effect 
{
public:
	EffectYellowPoisonToCreature(Creature* pCreature);

public:
    EffectClass getEffectClass()  { return EFFECT_CLASS_YELLOW_POISON_TO_CREATURE; }

	void affect() throw(Error){}
	void affect(Creature* pCreature);
	void affect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject);

	void unaffect();
	void unaffect(Creature* pCreature);
	void unaffect(Item*  pItem) throw(Error) {}
	void unaffect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject);

	virtual void create(const string & ownerID);
	virtual void destroy(const string & ownerID);
	virtual void save(const string & ownerID);

	string toString() ;

public:
	Sight_t getOldSight()  { return m_OldSight; }
	void setOldSight(Sight_t OldSight) throw() { m_OldSight = OldSight; }

	Level_t getLevel()  { return m_Level; }
	void setLevel(Level_t Level) throw() { m_Level = Level; }

private:
	Level_t m_Level;
	Sight_t m_OldSight;
};

//////////////////////////////////////////////////////////////////////////////
// class EffectYellowPoisonToCreatureLoader
//////////////////////////////////////////////////////////////////////////////

class EffectYellowPoisonToCreatureLoader : public EffectLoader 
{
public:
	virtual Effect::EffectClass getEffectClass()  { return Effect::EFFECT_CLASS_YELLOW_POISON_TO_CREATURE; }
	virtual string getEffectClassName()  { return "EffectYellowPoisonToCreature"; }

public:
	virtual void load(Creature* pCreature);

};

extern EffectYellowPoisonToCreatureLoader* g_pEffectYellowPoisonToCreatureLoader;

#endif // __EFFECT_YELLOW_POISON_TO_CREATURE__
