//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectMephisto.h
// Written by  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_MEPHISTO__
#define __EFFECT_MEPHISTO__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectMephisto
//////////////////////////////////////////////////////////////////////////////

class EffectMephisto : public Effect 
{
public:
	EffectMephisto(Creature* pCreature);

public:
    EffectClass getEffectClass()  { return EFFECT_CLASS_MEPHISTO; }

	void affect()  {}
	void affect(Creature* pCreature);

	void unaffect(Creature* pCreature);
	void unaffect(); 

	string toString() ;

public:
	int getBonus() throw() { return m_Bonus;}
	void setBonus(int Bonus)  { m_Bonus = Bonus;}

private:
	int m_Bonus;
};

#endif // __EFFECT_MEPHISTO__
