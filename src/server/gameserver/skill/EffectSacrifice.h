//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectSacrifice.h
// Written by  : excel96
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_SACRIFICE__
#define __EFFECT_SACRIFICE__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectSacrifice
//////////////////////////////////////////////////////////////////////////////

class EffectSacrifice : public Effect 
{
public:
	EffectSacrifice(Creature* pCreature);

public:
	void affect()  {}
	void affect(Creature* pCreature);

	void unaffect(Creature* pCreature);
	void unaffect(); 

    EffectClass getEffectClass()  { return EFFECT_CLASS_SACRIFICE; }

	string toString() ;

public:
	int getToHitBonus() throw() { return m_ToHitBonus;}
	void setToHitBonus(ToHit_t ToHitBonus)  { m_ToHitBonus = ToHitBonus;}

private :
	ToHit_t m_ToHitBonus;
};

#endif // __EFFECT_SACRIFICE__
