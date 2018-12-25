//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectStoneSkin.h
// Written by  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_STONE_SKIN__
#define __EFFECT_STONE_SKIN__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectStoneSkin
//////////////////////////////////////////////////////////////////////////////

class EffectStoneSkin : public Effect 
{
public:
	EffectStoneSkin(Creature* pCreature);

public:
    EffectClass getEffectClass()  { return EFFECT_CLASS_STONE_SKIN; }

	void affect() throw(Error) {}
	void affect(Creature* pCreature);

	void unaffect(Creature* pCreature);
	void unaffect(); 

	string toString() ;

public:
	int getBonus() throw() { return m_Bonus;}
	void setBonus(int Bonus) throw(Error) { m_Bonus = Bonus;}

private:
	int m_Bonus;
};

#endif // __EFFECT_STONE_SKIN__
