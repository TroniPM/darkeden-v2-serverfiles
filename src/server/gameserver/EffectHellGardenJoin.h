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
	int m_Delay;      // �� �ʸ��� TICK�� �ߵ� �Ǵ°�.
};

#endif
