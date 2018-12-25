//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectGhostBlade.h
// Written by  : 
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_GHOST_BLADE__
#define __EFFECT_GHOST_BLADE__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectGhostBlade
//////////////////////////////////////////////////////////////////////////////

class EffectGhostBlade : public Effect 
{
public:
	EffectGhostBlade(Creature* pCreature);

public:
	void affect() throw(Error) {}
	void affect(Creature* pCreature);

	void unaffect(Creature* pCreature);
	void unaffect(); 

    EffectClass getEffectClass()  { return EFFECT_CLASS_GHOST_BLADE; }

	string toString() ;

public:
	int getToHitBonus() throw() { return m_ToHitBonus;}
	void setToHitBonus(ToHit_t ToHitBonus) throw(Error) { m_ToHitBonus = ToHitBonus;}

private :
	ToHit_t m_ToHitBonus;
};

#endif // __EFFECT_GHOST_BLADE__
