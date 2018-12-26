//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectHymn.h
// Written by  : 
// Description : Doom�� ���� ���� �ϰ� effect
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_HYMN__
#define __EFFECT_HYMN__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectHymn
//////////////////////////////////////////////////////////////////////////////

class EffectHymn : public Effect 
{
public:
	EffectHymn(Creature* pCreature);

public:
    EffectClass getEffectClass()  { return EFFECT_CLASS_HYMN; }

	void affect()  {}
	void affect(Creature* pCreature);

	void unaffect(Creature* pCreature);
	void unaffect(); 

	string toString() ;

public:
	int  getLevel() const { return m_Level; }
	void setLevel(int level) throw() { m_Level = level; }

	int getDamagePenalty(void) const { return m_DamagePenalty; }
	void setDamagePenalty(int penalty) { m_DamagePenalty = penalty; }

	int getToHitPenalty(void) const { return m_ToHitPenalty; }
	void setToHitPenalty(int penalty) { m_ToHitPenalty = penalty; }

private:
	int m_Level;
	int m_DamagePenalty;
	int m_ToHitPenalty;
};

#endif // __EFFECT_DOOM__
