//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectHellFireToEnemy.h
// Written by  : crazydog
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_HELLFIRE_TO_ENEMY__
#define __EFFECT_HELLFIRE_TO_ENEMY__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectHellFireToEnemy
//////////////////////////////////////////////////////////////////////////////

class EffectHellFireToEnemy : public Effect 
{
public:
	EffectHellFireToEnemy(Creature* pCreature);

public:
	EffectClass getEffectClass()  { return EFFECT_CLASS_HELLFIRE_TO_ENEMY; }
	EffectClass getSendEffectClass()  { return EFFECT_CLASS_HELLFIRE_TO_ENEMY; }

	void affect();
	void affect(Creature* pCreature);

	void unaffect(Creature* pCreature);
	void unaffect();

	string toString() ;

	Damage_t    getDamage() const { return m_Damage; }
	void        setDamage( Damage_t Damage ) { m_Damage = Damage; }

	ObjectID_t  getCasterOID() const { return m_CasterOID; }
	void        setCasterOID( ObjectID_t CasterOID ) { m_CasterOID = CasterOID; }


private:
	Damage_t		m_Damage;
	ObjectID_t		m_CasterOID;

};

#endif // __EFFECT_HELLFIRE_TO_ENEMY__
