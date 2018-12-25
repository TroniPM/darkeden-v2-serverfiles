//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectHasVampireRelic.h
// Written by  : 
// Description : Doom�� ���� ���� �ϰ� effect
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_HAS_VAMPIRE_RELIC__
#define __EFFECT_HAS_VAMPIRE_RELIC__

#include "EffectHasRelic.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectHasVampireRelic
//////////////////////////////////////////////////////////////////////////////

class EffectHasVampireRelic : public EffectHasRelic
{
public:
	EffectHasVampireRelic(Creature* pCreature);
	EffectHasVampireRelic(Item* pItem);

public:
    EffectClass getEffectClass()  { return EFFECT_CLASS_HAS_VAMPIRE_RELIC; }

	void affect(Creature* pCreature);
	void affect(Item* pItem);

	string toString() ;

};

#endif // __EFFECT_DOOM__
