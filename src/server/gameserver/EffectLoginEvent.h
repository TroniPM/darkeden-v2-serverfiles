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
	EffectLoginEvent(Creature* pCreature);

public:
    EffectClass getEffectClass()  { return EFFECT_CLASS_LOGIN_EVENT; }

	void affect();
	void affect(Creature* pCreature);

	void unaffect(Creature* pCreature);
	void unaffect(); 

	string toString() ;

private:
	int m_Delay;      // 몇 초마다 TICK이 발동 되는가.
};

#endif
