//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectAuraShield.h
// Written by  : crazydog
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_AURA_SHIELD__
#define __EFFECT_AURA_SHIELD__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectAuraShield
//////////////////////////////////////////////////////////////////////////////

class EffectAuraShield : public Effect 
{
public:
	EffectAuraShield(Creature* pCreature);

public:
    EffectClass getEffectClass()  { return EFFECT_CLASS_AURA_SHIELD; }

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
// class EffectAuraShieldLoader
//////////////////////////////////////////////////////////////////////////////

class EffectAuraShieldLoader : public EffectLoader 
{
public:
	virtual Effect::EffectClass getEffectClass()  { return Effect::EFFECT_CLASS_AURA_SHIELD; }
	virtual string getEffectClassName()  { return "EffectAuraShield"; }

public:
	virtual void load(Creature* pCreature) throw(Error) {}
};


#endif // __EFFECT_AURA_SHIELD__
