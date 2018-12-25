//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectHasRelic.h
// Written by  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_HAS_RELIC__
#define __EFFECT_HAS_RELIC__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectHasRelic
//////////////////////////////////////////////////////////////////////////////

class EffectHasRelic : public Effect 
{
public:
	EffectHasRelic(Creature* pCreature);
	EffectHasRelic(Item* pItem);

public:
    virtual EffectClass getEffectClass()  = 0;
    virtual EffectClass getSendEffectClass()  { return (EffectClass)((int)getEffectClass() + m_Part); }

	virtual void affect();
	virtual void affect(Creature* pCreature) throw(Error) = 0;
	virtual void affect(Item* pItem) throw(Error) =0;

	virtual void unaffect(Creature* pCreature);
	virtual void unaffect(Item* pItem);
	virtual void unaffect();

	virtual string toString()  = 0;

public:
	int 	getPart(void) const { return m_Part; }
	virtual void   	setPart(int part) throw() { m_Part = part; }

	int 	getTick(void) const { return m_Tick; }
	void   	setTick(Turn_t Tick) throw() { m_Tick = Tick; }

protected:
	int		m_Part;		// 피의 성서 조각 번호
	Turn_t 	m_Tick;
};

#endif 
