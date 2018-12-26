//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectGateWayMonster.h
// Written by  : 
// Description : Doom�� ���� ���� �ϰ� effect
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_GATEWAY_MONSTER__
#define __EFFECT_GATEWAY_MONSTER__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectGateWayMonster
//////////////////////////////////////////////////////////////////////////////

class EffectGateWayMonster : public Effect 
{
public:
	EffectGateWayMonster(Creature* pCreature);

public:
    EffectClass getEffectClass()  { return EFFECT_CLASS_GATEWAY_MONSTER; }

	void affect()  {}
	void affect(Creature* pCreature);

	void unaffect(Creature* pCreature);
	void unaffect(); 

	string toString() ;

public:
	int  getHPRecovery(void) const { return m_HPRecovery; }
	void setHPRecovery(int hp) { m_HPRecovery = hp; }

private:
	int m_HPRecovery = 1;
};

#endif // __EFFECT_DOOM__
