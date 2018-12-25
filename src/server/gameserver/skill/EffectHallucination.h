//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectHallucination.h
// Written by  : 
// Description : Hallucination에 의한 방어력 하강 effect
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_HALLUCINATION__
#define __EFFECT_HALLUCINATION__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectHallucination
//////////////////////////////////////////////////////////////////////////////

class EffectHallucination : public Effect 
{
public:
	EffectHallucination(Creature* pCreature);

public:
    EffectClass getEffectClass()  { return EFFECT_CLASS_HALLUCINATION; }

	void affect() throw(Error) {}
	void affect(Creature* pCreature);

	void unaffect(Creature* pCreature);
	void unaffect(); 

	string toString() ;

public:
	int  getLevel() const { return m_Level; }
	void setLevel(int level) throw() { m_Level = level; }

private:
	int m_Level;
};

#endif // __EFFECT_HALLUCINATION__
