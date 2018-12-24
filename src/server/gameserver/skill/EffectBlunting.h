//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectBlunting.h
// Written by  : 
// Description : Blunting�� ���� ���� �ϰ� effect
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_BLUNTING__
#define __EFFECT_BLUNTING__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectBlunting
//////////////////////////////////////////////////////////////////////////////

class EffectBlunting : public Effect 
{
public:
	EffectBlunting(Creature* pCreature) throw(Error);

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_BLUNTING; }

	void affect() throw(Error) {}
	void affect(Creature* pCreature) throw(Error);

	void unaffect(Creature* pCreature) throw(Error);
	void unaffect() throw(Error); 

	string toString() const throw();

public:
	int  getLevel() const { return m_Level; }
	void setLevel(int level) throw() { m_Level = level; }

	int getDefensePenalty(void) const { return m_DefensePenalty; }
	void setDefensePenalty(int penalty) { m_DefensePenalty = penalty; }

private:
	int m_Level;
	int m_DefensePenalty;
};

#endif // __EFFECT_BLUNTING__
