//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectHeavenGround.h
// Written by  : bezz
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_CURSE_OF_BLOOD1__
#define __EFFECT_CURSE_OF_BLOOD1__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectHeavenGround
//////////////////////////////////////////////////////////////////////////////

class EffectCurseOfBlood1 : public Effect 
{
public:
	EffectCurseOfBlood1(Creature* pCreature) throw(Error);

public:
    EffectClass getEffectClass()  { return EFFECT_CLASS_CURSE_OF_BLOOD1; }

	void affect() throw(Error);
	void affect(Creature* pCreature) throw(Error);

	void unaffect() throw(Error);
	void unaffect(Creature* pCreature) throw(Error);

	string toString() ;

public:
	Level_t getLevel()  { return m_Level; }
	void setLevel(Level_t level) throw() { m_Level = level; }
	
private:
	Level_t  m_Level;
};
#endif
