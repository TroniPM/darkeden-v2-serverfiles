//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectReflection.h
// Written by  : crazydog
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_REFLECTION__
#define __EFFECT_REFLECTION__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectReflection
//////////////////////////////////////////////////////////////////////////////

class EffectReflection : public Effect 
{
public:
	EffectReflection(Creature* pCreature);

public:
    EffectClass getEffectClass()  { return EFFECT_CLASS_REFLECTION; }

	void affect() throw(Error){}
	void affect(Creature* pCreature);
	void affect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject);

	void unaffect(Creature* pCreature);
	void unaffect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject);
	void unaffect(Item* pItem) throw(Error) {}
	void unaffect();

	string toString() ;

public:
	Level_t getLevel()  { return m_Level; }
	void setLevel(Level_t Level) throw() { m_Level = Level; }

private:
	Level_t m_Level;
};

//////////////////////////////////////////////////////////////////////////////
// class EffectReflectionLoader
//////////////////////////////////////////////////////////////////////////////

class EffectReflectionLoader : public EffectLoader 
{
public:
	virtual Effect::EffectClass getEffectClass()  { return Effect::EFFECT_CLASS_REFLECTION; }
	virtual string getEffectClassName()  { return "EffectReflection"; }

public:
	virtual void load(Creature* pCreature) throw(Error) {}
};


#endif // __EFFECT_REFLECTION__
