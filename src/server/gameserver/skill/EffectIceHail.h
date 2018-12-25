//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectIceHail.h
// Written by  : elca@ewestsoft.com
// Description : �������� IceHail�� Effect�� ó�����ֱ� ���� Ŭ�����̴�.
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_ICE_HAIL__
#define __EFFECT_ICE_HAIL__

#include "Effect.h"
#include "EffectLoader.h"
#include "Creature.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectIceHail
//////////////////////////////////////////////////////////////////////////////

class EffectIceHail : public Effect 
{
public:
	EffectIceHail(Zone* pZone, ZoneCoord_t zoneX, ZoneCoord_t zoneY);

public:
    EffectClass getEffectClass()  { return EFFECT_CLASS_ICE_HAIL; }

	void affect();
	void affect(Creature* pCreature);

	void unaffect();
	void unaffect(Creature* pCreature);

	string toString() ;

public:
	ObjectID_t getCasterID(void) const { return m_CasterID; }
	void setCasterID(ObjectID_t CasterID ) { m_CasterID = CasterID; }

	Turn_t getTick() const { return m_Tick; }
	void setTick(Turn_t Tick) { m_Tick = Tick; }

	int isRange() const { return m_Range; }
	void setRange(int range) { m_Range = range; }

	Damage_t getDamage() const { return m_Damage; }
	void setDamage( Damage_t damage ) { m_Damage = damage; }

private:
	ObjectID_t  m_CasterID;
	Turn_t  m_Tick;
	int		m_Range;
	Damage_t	m_Damage;
};

#endif // __EFFECT_ICE_HAIL__
