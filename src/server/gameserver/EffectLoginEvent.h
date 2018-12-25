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
	int m_Delay;      // �� �ʸ��� TICK�� �ߵ� �Ǵ°�.
};

#endif
