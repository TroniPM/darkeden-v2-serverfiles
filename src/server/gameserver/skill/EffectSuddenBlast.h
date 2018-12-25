//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectSetAfire.h
// Written by  : 
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_SUDDEN_BLAST__
#define __EFFECT_SUDDEN_BLAST__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectSetAfire
//////////////////////////////////////////////////////////////////////////////

class EffectSuddenBlast : public Effect 
{
public:
	EffectSuddenBlast(Creature* pCreature);

public:
    EffectClass getEffectClass()  { return EFFECT_CLASS_SUDEEN_BLAST; }

	void affect();
	void affect(Creature* pCreature);

	void unaffect(Creature* pCreature);
	void unaffect(); 

	string toString() ;

public:
	Damage_t	getDamage() const { return m_Damage; }
	void		setDamage( Damage_t Damage ) { m_Damage = Damage; }
	
	int			getTimes() const { return m_Times; }
	void		setTimes( int Times ) { m_TotalTimes = m_Times = Times; }

	Turn_t		getTick() const { return m_Tick; }
	void		setTick( Turn_t Tick ) { m_Tick = Tick; }

	ObjectID_t	getCasterOID() const { return m_CasterOID; }
	void		setCasterOID( ObjectID_t CasterOID ) { m_CasterOID = CasterOID; }
	
private:
	Damage_t	m_Damage;
	int			m_Times;
	int			m_TotalTimes;
	Turn_t		m_Tick;
	ObjectID_t	m_CasterOID;

};

#endif // __EFFECT_SET_AFIRE__
