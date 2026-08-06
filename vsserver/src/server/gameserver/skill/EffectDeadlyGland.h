//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectRingOfFlare.h
// Written by  : crazydog
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_DEADLY_GLAND__
#define __EFFECT_DEADLY_GLAND__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectRingOfFlare
//////////////////////////////////////////////////////////////////////////////

class EffectDeadlyGland : public Effect 
{
public:
	EffectDeadlyGland(Creature* pCreature) throw(Error);

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_DEADLY_GLAND; }
	EffectClass getSendEffectClass() const throw() { return m_SendEffectClass; }

	void affect() throw(Error);

	void unaffect(Creature* pCreature) throw(Error);
	void unaffect() throw(Error);

	string toString() const throw();

public:
	void setSendEffectClass(EffectClass eClass) throw() { m_SendEffectClass = eClass; }

	void setDamage( uint bonus ) { m_Damage = bonus; }
	uint getDamage() const { return m_Damage; }

	void setUserObjectID(ObjectID_t oid) throw() { m_UserObjectID = oid; }
	ObjectID_t getUserObjectID() const throw() { return m_UserObjectID; }

private:
	EffectClass m_SendEffectClass;
	ObjectID_t	m_UserObjectID;
	uint	m_Damage;
};

#endif // __EFFECT_RING_OF_FLARE__
