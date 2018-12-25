//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectSlayerRelic.h
// Written by  : 
// Description : Doom�� ���� ���� �ϰ� effect
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_SLAYER_RELIC__
#define __EFFECT_SLAYER_RELIC__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectSlayerRelic
//////////////////////////////////////////////////////////////////////////////
// ���� �����뿡 �ٴ� ����Ʈ�̴�.

class EffectSlayerRelic : public Effect 
{
public:
	EffectSlayerRelic(Creature* pCreature);
	EffectSlayerRelic(Item* pItem);

public:
    EffectClass getEffectClass()  { return EFFECT_CLASS_SLAYER_RELIC; }

	void affect() throw(Error) {}
	void affect(Creature* pCreature);
	void affect(Item* pItem);

	void unaffect(Creature* pCreature);
	void unaffect(Item* pItem);
	void unaffect(); 

	string toString() ;

public:
	int  getHPRecovery(void) const { return m_HPRecovery; }
	void setHPRecovery(int hp) { m_HPRecovery = hp; }

	int getTick(void) const { return m_Tick; }
	void   setTick(Turn_t Tick) throw() { m_Tick = Tick; }
private:
	int m_HPRecovery; 
	Turn_t m_Tick;
};

#endif // __EFFECT_DOOM__
