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
	EffectHasVampireRelic(Creature* pCreature) throw(Error);
	EffectHasVampireRelic(Item* pItem) throw(Error);

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_HAS_VAMPIRE_RELIC; }

	void affect(Creature* pCreature) throw(Error);
	void affect(Item* pItem) throw(Error);

	string toString() const throw();

};

#endif // __EFFECT_DOOM__
