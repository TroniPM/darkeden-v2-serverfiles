//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectDestinies.h
// Written by  : elca@ewestsoft.com
// Description : �������� Destinies�� Effect�� ó�����ֱ� ���� Ŭ�����̴�.
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_DESTINIES__
#define __EFFECT_DESTINIES__

#include "Effect.h"
#include "Creature.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectDestinies
//////////////////////////////////////////////////////////////////////////////

class EffectDestinies : public Effect 
{
public:
	EffectDestinies(Creature* pCreature);

public:
    EffectClass getEffectClass()  { return EFFECT_CLASS_MAX; }

	void affect();
	void affect(Creature* pCreature);

	void unaffect();
	void unaffect(Creature* pCreature);

	string toString() ;

public:
	ObjectID_t getUserOID(void) const { return m_UserOID; }
	void setUserOID(ObjectID_t UserOID ) { m_UserOID = UserOID; }

	Damage_t getDamage(void) const { return m_Damage; }
	void setDamage(Damage_t Damage ) { m_Damage = Damage; }

	void setTargetType( Creature* pCreature );

private:
	Creature::CreatureClass	m_TargetClass;
	SpriteType_t			m_TargetSpriteType;
	ObjectID_t  			m_UserOID;
	Damage_t				m_Damage;
};

#endif // __EFFECT_DESTINIES__
