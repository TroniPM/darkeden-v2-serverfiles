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
	EffectHellGardenJoin(Creature* pCreature);

public:
    EffectClass getEffectClass()  { return EFFECT_CLASS_HELL_GARDEN_JOIN; }

	void affect();
	void affect(Creature* pCreature);

	void unaffect(Creature* pCreature);
	void unaffect(); 

	string toString() ;

private:
	int m_Delay;      // 몇 초마다 TICK이 발동 되는가.
};

#endif
