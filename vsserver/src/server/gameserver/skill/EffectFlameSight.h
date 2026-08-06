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
	EffectFlameSight(Creature* pCreature) throw(Error);

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_FLAME_SIGHT; }

	void affect() throw(Error){}
	void affect(Creature* pCreature) throw(Error);
	void affect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject) throw(Error);

	void unaffect() throw(Error);
	void unaffect(Creature* pCreature) throw(Error);
	void unaffect(Item*  pItem) throw(Error) {}
	void unaffect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject) throw(Error);

	virtual void create(const string & ownerID) throw(Error);
	virtual void destroy(const string & ownerID) throw(Error);
	virtual void save(const string & ownerID) throw(Error);

	string toString() const throw();

public:
	Sight_t getOldSight() const throw() { return m_OldSight; }
	void setOldSight(Sight_t OldSight) throw() { m_OldSight = OldSight; }

private:
	Sight_t m_OldSight;

};

//////////////////////////////////////////////////////////////////////////////
// class EffectFlameSightLoader
//////////////////////////////////////////////////////////////////////////////

class EffectFlameSightLoader : public EffectLoader 
{
public:
	virtual Effect::EffectClass getEffectClass() const throw() { return Effect::EFFECT_CLASS_FLAME_SIGHT; }
	virtual string getEffectClassName() const throw() { return "EffectFlameSight"; }

public:
	virtual void load(Creature* pCreature) throw(Error);

};

extern EffectFlameSightLoader* g_pEffectFlameSightLoader;

#endif // __EFFECT_FLAME_SIGHT__
