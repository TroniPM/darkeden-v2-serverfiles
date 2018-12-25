//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectRelic.h
// Written by  : 
// Description : Doom에 의한 방어력 하강 effect
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_RELIC__
#define __EFFECT_RELIC__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectRelic
//////////////////////////////////////////////////////////////////////////////

class EffectRelic : public Effect 
{
public:
	EffectRelic(Creature* pCreature);

public:
    EffectClass getEffectClass()  { return EFFECT_CLASS_RELIC; }

	void affect() throw(Error) {}
	void affect(Creature* pCreature);

	void unaffect(Creature* pCreature);
	void unaffect(); 

	string toString() ;

public:
	HP_t getPoint()  { return m_Point; }
	void setPoint(HP_t Point) throw() { m_Point = Point; }

	Turn_t getTick()  { return m_Tick; }
	void   setTick(Turn_t Tick) throw() { m_Tick = Tick; }

private:
	HP_t   m_Point;  // 회복 에너지량
	Turn_t m_Tick;
};

#endif // __EFFECT_DOOM__
