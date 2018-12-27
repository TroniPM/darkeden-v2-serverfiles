//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectExtreme.h
// Written by  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_EXTREME__
#define __EFFECT_EXTREME__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectExtreme
//////////////////////////////////////////////////////////////////////////////

class EffectExtreme : public Effect 
{
public:
	EffectExtreme(Creature* pCreature);

public:
    EffectClass getEffectClass()  { return EFFECT_CLASS_EXTREME; }

	void affect()  {}
	void affect(Creature* pCreature);

	void unaffect(Creature* pCreature);
	void unaffect(); 

	string toString() ;

public:
	int getDamageBonus()  { return m_DamageBonus;}
	void setDamageBonus(ToHit_t DamageBonus)  { m_DamageBonus = DamageBonus;}

private:
	Damage_t m_DamageBonus;
};

#endif // __EFFECT_EXTREME__
