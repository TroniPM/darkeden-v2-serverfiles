//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectParalyze.h
// Written by  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_MIST_OF_SOUL1__
#define __EFFECT_MIST_OF_SOUL1__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectParalyze
//////////////////////////////////////////////////////////////////////////////

class EffectMistOfSoul1: public Effect 
{
public:
	EffectMistOfSoul1(Creature* pCreature) throw(Error);

public:
    EffectClass getEffectClass()  { return EFFECT_CLASS_MIST_OF_SOUL1; }

	void affect() throw(Error);
	void affect(Creature* pCreature) throw(Error);

	void unaffect() throw(Error);
	void unaffect(Creature* pCreature) throw(Error);

	string toString() ;

public:
	Level_t getLevel()  { return m_Level; }
	void setLevel(Level_t level) throw() { m_Level = level; }

//	int getDefensePenalty(void)  { return m_DefensePenalty; }
//	void setDefensePenalty(int penalty) { m_DefensePenalty = penalty; }
	
private:
	Level_t  m_Level;
//	int     m_DefensePenalty;
};

#endif // __EFFECT_PARALYZE__
