//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectSharpHail.h
// Written by  : elca@ewestsoft.com
// Description : �������� SharpHail�� Effect�� ó�����ֱ� ���� Ŭ�����̴�.
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_NUCK__
#define __EFFECT_NUCK__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectSharpHail
//////////////////////////////////////////////////////////////////////////////

class EffectNuck : public Effect 
{
public:
	EffectNuck(Zone* pZone, ZoneCoord_t zoneX, ZoneCoord_t zoneY) throw(Error);

public:
    EffectClass getEffectClass()  { return EFFECT_CLASS_PROMINENCE; }

	void affect() throw(Error);
	void unaffect() throw(Error);
	string toString() ;

public:
	int getDamage(void) const { return m_Damage; }
	void setDamage(int damage) { m_Damage = damage; }

	Turn_t getTick() const { return m_Tick; }
	void setTick(Turn_t Tick) { m_Tick = Tick; }

	int getLevel(void) const { return m_Level; }
	void setLevel(int level) { m_Level = level; }

	void setForce( bool force ) { m_bForce = force; }
	bool isForce() const { return m_bForce; }

	ObjectID_t getUserObjectID() const { return m_UserObjectID; }
	void setUserObjectID( ObjectID_t UserObjectID ) { m_UserObjectID = UserObjectID; }

private:
	int     m_Damage;
	Turn_t  m_Tick;
	int     m_Level;
	bool	m_bForce;

	ObjectID_t	m_UserObjectID;
};

#endif // __EFFECT_SHARP_HAIL__
