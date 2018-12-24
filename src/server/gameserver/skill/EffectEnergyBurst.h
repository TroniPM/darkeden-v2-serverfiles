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
	EffectEnergyBurst(Creature* pCreature) throw(Error);

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_ENERGY_BURST; }

	void affect() throw(Error){}

	void unaffect(Creature* pCreature) throw(Error);
	void unaffect() throw(Error);

	string toString() const throw();
};

//////////////////////////////////////////////////////////////////////////////
// class EffectEnergyBurstLoader
//////////////////////////////////////////////////////////////////////////////

class EffectEnergyBurstLoader : public EffectLoader 
{
public:
	virtual Effect::EffectClass getEffectClass() const throw() { return Effect::EFFECT_CLASS_ENERGY_BURST; }
	virtual string getEffectClassName() const throw() { return "EffectEnergyBurst"; }

public:
	virtual void load(Creature* pCreature) throw(Error) {}
};


#endif // __EFFECT_CONCEALMENT__
