//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectHalo.h
// Written by  : elca@ewestsoft.com
// Description : �������� Halo�� Effect�� ó�����ֱ� ���� Ŭ�����̴�.
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_HALO__
#define __EFFECT_HALO__

#include "Effect.h"
#include "EffectLoader.h"
#include "Creature.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectHalo
//////////////////////////////////////////////////////////////////////////////

class EffectHalo : public Effect 
{
public:
	EffectHalo(Zone* pZone, ZoneCoord_t zoneX, ZoneCoord_t zoneY);

public:
    EffectClass getEffectClass()  { return EFFECT_CLASS_HALO; }

	void affect();
	void affect(Creature* pCreature);

	void unaffect();
	void unaffect(Creature* pCreature);

	string toString() ;

public:
	ObjectID_t getUserOID(void) const { return m_UserOID; }
	void setUserOID(ObjectID_t UserOID ) { m_UserOID = UserOID; }

	ObjectID_t getTargetOID(void) const { return m_TargetOID; }
	void setTargetOID(ObjectID_t TargetOID ) { m_TargetOID = TargetOID; }

	Damage_t getDamage(void) const { return m_Damage; }
	void setDamage(Damage_t Damage ) { m_Damage = Damage; }

private:
	ObjectID_t  m_UserOID;
	ObjectID_t  m_TargetOID;
	Damage_t	m_Damage;

};

#endif // __EFFECT_HALO__
