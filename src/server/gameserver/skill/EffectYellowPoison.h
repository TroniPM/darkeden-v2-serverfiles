//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectYellowPoison.h
// Written by  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_YELLOW_POISON__
#define __EFFECT_YELLOW_POISON__

#include "Tile.h"
#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectYellowPoison
//////////////////////////////////////////////////////////////////////////////

class EffectYellowPoison : public Effect 
{
public:
	EffectYellowPoison(Zone*, ZoneCoord_t, ZoneCoord_t);

public:
    EffectClass getEffectClass()  { return EFFECT_CLASS_YELLOW_POISON; }

	void affect() {}
	void affect(Creature* pCreature); 
	void affect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject);

	void unaffect();
	void unaffect(Creature* pCreature);
	void unaffect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject);
	void unaffect(Item*  pItem)  {}

	string toString() ;

public:
	Duration_t getDuration()  { return m_Duration; }
	void setDuration(Duration_t d) throw() { m_Duration = d; }
	
	Attr_t getLevel()  { return m_Level; }
	void setLevel(Attr_t l) throw() { m_Level = l; }

	void setVampire( bool bVampire = true ) { m_bVampire = bVampire; }
	bool isVampire() { return m_bVampire; }

	void setForce( bool force ) { m_bForce = force; }
	bool isForce() { return m_bForce; }
	
	bool affectCreature(Creature* pCreature, bool bAffectByMove); 

private:
	Duration_t m_Duration;
	Attr_t     m_Level;

	bool       m_bVampire;
	bool	   m_bForce;
};

class EffectYellowPoisonLoader : public EffectLoader
{
public:
	virtual Effect::EffectClass getEffectClass()  { return Effect::EFFECT_CLASS_YELLOW_POISON; }
	virtual string getEffectClassName()  { return "EffectYellowPoison"; }

public:
	virtual void load(Creature* pCreature)  {}
	virtual void load(Zone* pZone);
};

extern EffectYellowPoisonLoader* g_pEffectYellowPoisonLoader;

#endif // __EFFECT_YELLOW_POISON__
