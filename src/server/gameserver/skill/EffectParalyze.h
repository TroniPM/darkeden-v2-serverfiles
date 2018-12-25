//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectParalyze.h
// Written by  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_PARALYZE__
#define __EFFECT_PARALYZE__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectParalyze
//////////////////////////////////////////////////////////////////////////////

class EffectParalyze : public Effect 
{
public:
	EffectParalyze(Creature* pCreature);

public:
    EffectClass getEffectClass()  { return EFFECT_CLASS_PARALYZE; }

	void affect();
	void affect(Creature* pCreature);

	void unaffect();
	void unaffect(Creature* pCreature);

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
