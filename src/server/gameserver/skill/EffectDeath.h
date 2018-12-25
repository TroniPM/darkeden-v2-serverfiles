//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectDeath.h
// Written by  : 
// Description : Death�� ���� ���� �ϰ� effect
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_DEATH__
#define __EFFECT_DEATH__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectDeath
//////////////////////////////////////////////////////////////////////////////

class EffectDeath : public Effect 
{
public:
	EffectDeath(Creature* pCreature);

public:
    EffectClass getEffectClass()  { return EFFECT_CLASS_DEATH; }

	void affect() throw(Error) {}
	void affect(Creature* pCreature);

	void unaffect(Creature* pCreature);
	void unaffect(); 

	string toString() ;

public:
	int  getLevel() const { return m_Level; }
	void setLevel(int level) throw() { m_Level = level; }

	int getResistPenalty(void) const { return m_ResistPenalty; }
	void setResistPenalty(int penalty) { m_ResistPenalty = penalty; }

private:
	int m_Level;
	int m_ResistPenalty;
};

#endif // __EFFECT_DEATH__
