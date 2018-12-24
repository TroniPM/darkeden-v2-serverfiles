//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectShrineShield.h
// Written by  : 
// Description : Doom�� ���� ���� �ϰ� effect
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_SHRINE_SHIELD__
#define __EFFECT_SHRINE_SHIELD__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectShrineShield
//////////////////////////////////////////////////////////////////////////////
// ���� �����뿡 �ٴ� ����Ʈ�̴�.

class EffectShrineShield : public Effect 
{
public:
	EffectShrineShield(Creature* pCreature) throw(Error);
	EffectShrineShield(Item* pItem) throw(Error);

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_SHRINE_SHIELD; }

	void affect() throw(Error) {}
	void affect(Creature* pCreature) throw(Error);
	void affect(Item* pItem) throw(Error);

	void unaffect(Creature* pCreature) throw(Error);
	void unaffect(Item* pItem) throw(Error);
	void unaffect() throw(Error); 

	string toString() const throw();

public:
	int getTick(void) const { return m_Tick; }
	void   setTick(Turn_t Tick) throw() { m_Tick = Tick; }

	int getShrineID() const { return m_ShrineID; }
	void setShrineID(int id) { m_ShrineID = id; }

private:
	int		m_ShrineID;
	Turn_t 	m_Tick;
};

#endif // __EFFECT_DOOM__
