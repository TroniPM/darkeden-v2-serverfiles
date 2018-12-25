//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectDestinies.h
// Written by  : elca@ewestsoft.com
// Description : 성직마법 Destinies의 Effect를 처리해주기 위한 클래스이다.
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_DEMOLISHER__
#define __EFFECT_DEMOLISHER__

#include "Effect.h"
#include "Creature.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectDEMOLISHER
//////////////////////////////////////////////////////////////////////////////

class EffectDemolisher : public Effect 
{
public:
	EffectDemolisher(Creature* pCreature);

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
