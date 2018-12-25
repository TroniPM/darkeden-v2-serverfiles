//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectHideSight.h
// Written by  : crazydog
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_HIDE_SIGHT__
#define __EFFECT_HIDE_SIGHT__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectHideSight
//////////////////////////////////////////////////////////////////////////////

class EffectHideSight : public Effect 
{
public:
	EffectHideSight(Creature* pCreature) throw(Error);

public:
    EffectClass getEffectClass()  { return EFFECT_CLASS_HIDE_SIGHT; }

	void affect() throw(Error){}

	void unaffect(Creature* pCreature) throw(Error);
	void unaffect() throw(Error);

	string toString() ;

public:
	void setBonus( uint bonus ) { m_Bonus = bonus; }
	uint getBonus() const { return m_Bonus; }

private:
	uint	m_Bonus;
};

//////////////////////////////////////////////////////////////////////////////
// class EffectHideSightLoader
//////////////////////////////////////////////////////////////////////////////

class EffectHideSightLoader : public EffectLoader 
{
public:
	virtual Effect::EffectClass getEffectClass()  { return Effect::EFFECT_CLASS_HIDE_SIGHT; }
	virtual string getEffectClassName()  { return "EffectHideSight"; }

public:
	virtual void load(Creature* pCreature) throw(Error) {}
};


#endif // __EFFECT_HIDE_SIGHT__
