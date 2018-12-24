//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectHeavenGround.h
// Written by  : bezz
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_MAGMA_DETONATION1__
#define __EFFECT_MAGMA_DETONATION1__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectHeavenGround
//////////////////////////////////////////////////////////////////////////////

class EffectMagmaDetonation1 : public Effect 
{
public:
	EffectMagmaDetonation1(Zone* pZone, ZoneCoord_t X, ZoneCoord_t Y) throw(Error);

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_MAGMA_DETONATION1; }

	void affect() throw(Error);
	void affect(Zone* pZone, ZoneCoord_t X, ZoneCoord_t Y) throw(Error);

	void unaffect() throw(Error);

	string toString() const throw();

public:
	int getDamage(void) const { return m_Damage; }
	void setDamage(int damage) { m_Damage = damage; }

	Turn_t getTick() const { return m_Tick; }
	void setTick(Turn_t Tick) { m_Tick = Tick; }

	int getLevel(void) const { return m_Level; }
	void setLevel(int level) { m_Level = level; }

	void setUserObjectID(ObjectID_t oid) throw() { m_UserObjectID = oid; }
	ObjectID_t getUserObjectID() const throw() { return m_UserObjectID; }

	void setSlayer( bool bSlayer = true ) { m_bSlayer = bSlayer; }
	bool isSlayer() const { return m_bSlayer; }
private:
	int 	 	m_Damage;  	    // EffectAcidStorm Damage;
	Turn_t 		m_Tick;			// EffectAcidStorm turn;	
	int 		m_Level;		// EffectAcidStorm level;
	Duration_t 	m_Duration;		// EffectAcidStorm Duration;
	Duration_t  m_StormDuration; // AcidStorm Effect ���� �ð� 
	ObjectID_t	m_UserObjectID;
	bool		m_bSlayer;
};

#endif
