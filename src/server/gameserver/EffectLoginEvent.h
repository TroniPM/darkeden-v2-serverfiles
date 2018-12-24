//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectHasPet.h
// Written by  : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_LOGIN_EVENT__
#define __EFFECT_LOGIN_EVENT__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectHasPet
//////////////////////////////////////////////////////////////////////////////

class EffectLoginEvent : public Effect 
{
public:
	EffectLoginEvent(Creature* pCreature) throw(Error);

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_LOGIN_EVENT; }

	void affect() throw(Error);
	void affect(Creature* pCreature) throw(Error);

	void unaffect(Creature* pCreature) throw(Error);
	void unaffect() throw(Error); 

	string toString() const throw();

private:
	int m_Delay;      // �� �ʸ��� TICK�� �ߵ� �Ǵ°�.
};

#endif
