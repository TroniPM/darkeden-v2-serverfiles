
//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectRequital.h
// Written by  : crazydog
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_REQUITAL__
#define __EFFECT_REQUITAL__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectRequital
//////////////////////////////////////////////////////////////////////////////

class EffectRequital : public Effect 
{
public:
	EffectRequital(Creature* pCreature);

public:
    EffectClass getEffectClass()  { return EFFECT_CLASS_REQUITAL; }

	void affect() {}

	void unaffect();
	void unaffect(Creature* pCreature);

	string toString() ;

public:
	void setReflection( int ref ) { m_Reflection = ref; }
	int getReflection() const { return m_Reflection; }

private:
	int m_Reflection;
};

//////////////////////////////////////////////////////////////////////////////
// class EffectRequitalLoader
//////////////////////////////////////////////////////////////////////////////

class EffectRequitalLoader : public EffectLoader 
{
public:
	virtual Effect::EffectClass getEffectClass()  { return Effect::EFFECT_CLASS_REQUITAL; }
	virtual string getEffectClassName()  { return "EffectRequital"; }

public:
	virtual void load(Creature* pCreature)  {}
};


#endif // __EFFECT_REQUITAL__
