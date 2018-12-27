//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectShrineGuard.h
// Written by  : 
// Description : Doom에 의한 방어력 하강 effect
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_SHRINE_GUARD__
#define __EFFECT_SHRINE_GUARD__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectShrineGuard
//////////////////////////////////////////////////////////////////////////////
// 성물 보관대에 붙는 이펙트이다.

class EffectShrineGuard : public Effect 
{
public:
	EffectShrineGuard(Creature* pCreature);
	EffectShrineGuard(Item* pItem);

public:
    EffectClass getEffectClass()  { return EFFECT_CLASS_SHRINE_GUARD; }
    EffectClass getSendEffectClass()  { return (EffectClass)((int)EFFECT_CLASS_SHRINE_GUARD + m_ShrineID); }

	void affect()  {}
	void affect(Creature* pCreature);
	void affect(Item* pItem);

	void unaffect(Creature* pCreature);
	void unaffect(Item* pItem);
	void unaffect(); 

	string toString() ;

public:
	int getTick(void) const { return m_Tick; }
	void   setTick(Turn_t Tick)  { m_Tick = Tick; }

	int getShrineID() const { return m_ShrineID; }
	void setShrineID(int id) { m_ShrineID = id; }

private:
	int		m_ShrineID;
	Turn_t 	m_Tick;
};

#endif // __EFFECT_DOOM__
