//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectPenetrateWheel.h
// Written by  : rallser
// Description : ��������PenetrateWheel�� Effect�� ó�����ֱ� ���� Ŭ�����̴�.
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_Penetrate_Wheel__
#define __EFFECT_Penetrate_Wheel__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectPenetrateWheel
//////////////////////////////////////////////////////////////////////////////

class EffectPenetrateWheel : public Effect 
{
public:
	EffectPenetrateWheel(Creature* pCreature);

public:
    EffectClass getEffectClass()  { return EFFECT_CLASS_Penetrate_Wheel; }

	void affect();
	void affect(Creature* pCreature);

	void unaffect();
	void unaffect(Creature* pCreature);

	string toString() ;

public:
	void		setCasterID( ObjectID_t objectID ) { m_CasterID = objectID; }
	ObjectID_t	getCasterID() const { return m_CasterID; }

	void		setDamage( Damage_t damage ) { m_Damage = damage; }
	Damage_t	getDamage() const { return m_Damage; }

	bool		canSteal() const { return m_CanSteal; }
	void		setSteal(bool steal) { m_CanSteal = steal; }

private:
	ObjectID_t	m_CasterID;
	Damage_t	m_Damage;
	bool		m_CanSteal;
};

#endif // __EFFECT_Penetrate_Wheel__
