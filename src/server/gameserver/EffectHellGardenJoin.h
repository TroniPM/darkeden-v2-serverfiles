//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectHasPet.h
// Written by  : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_CLASS_HELL_GARDEN_JOIN__
#define __EFFECT_CLASS_HELL_GARDEN_JOIN__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectHasPet
//////////////////////////////////////////////////////////////////////////////

class EffectHellGardenJoin : public Effect 
{
public:
	EffectHellGardenJoin(Creature* pCreature) throw(Error);

public:
    EffectClass getEffectClass()  { return EFFECT_CLASS_HELL_GARDEN_JOIN; }

	void affect() throw(Error);
	void affect(Creature* pCreature) throw(Error);

	void unaffect(Creature* pCreature) throw(Error);
	void unaffect() throw(Error); 

	string toString() ;

private:
	int m_Delay;      // 몇 초마다 TICK이 발동 되는가.
};

#endif
