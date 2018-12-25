//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectHolyArmor.h
// Written by  : 
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_HOLY_ARMOR2__
#define __EFFECT_HOLY_ARMOR2__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectHolyArmor
//////////////////////////////////////////////////////////////////////////////

class EffectHolyArmor2 : public Effect 
{
public:
	EffectHolyArmor2(Creature* pCreature);

public:
    EffectClass getEffectClass()  { return EFFECT_CLASS_HOLY_ARMOR2; }

	void affect() throw(Error) {}
	void affect(Creature* pCreature);

	void unaffect(Creature* pCreature);
	void unaffect(); 

	string toString() ;

public:
	int getDefBonus() throw() { return m_DefBonus;}
	void setDefBonus(Attr_t DefBonus) throw(Error) { m_DefBonus = DefBonus;}

private :
	Defense_t m_DefBonus;
};

#endif // __EFFECT_HOLY_ARMOR__
