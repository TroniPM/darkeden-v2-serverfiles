//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectConcealment.h
// Written by  : crazydog
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_ENERGY_BURST__
#define __EFFECT_ENERGY_BURST__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectConcealment
//////////////////////////////////////////////////////////////////////////////

class EffectEnergyBurst : public Effect 
{
public:
	EffectEnergyBurst(Creature* pCreature);

public:
    EffectClass getEffectClass()  { return EFFECT_CLASS_ENERGY_BURST; }

	void affect() {}

	void unaffect(Creature* pCreature);
	void unaffect();

	string toString() ;
};

//////////////////////////////////////////////////////////////////////////////
// class EffectEnergyBurstLoader
//////////////////////////////////////////////////////////////////////////////

class EffectEnergyBurstLoader : public EffectLoader 
{
public:
	virtual Effect::EffectClass getEffectClass()  { return Effect::EFFECT_CLASS_ENERGY_BURST; }
	virtual string getEffectClassName()  { return "EffectEnergyBurst"; }

public:
	virtual void load(Creature* pCreature)  {}
};


#endif // __EFFECT_CONCEALMENT__
