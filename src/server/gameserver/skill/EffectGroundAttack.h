//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectGroundAttack.h
// Written by  : elca@ewestsoft.com
// Description : �������� GroundAttack�� Effect�� ó�����ֱ� ���� Ŭ�����̴�.
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_GROUND_ATTACK__
#define __EFFECT_GROUND_ATTACK__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectGroundAttack
//////////////////////////////////////////////////////////////////////////////

class EffectGroundAttack : public Effect 
{
public:
	EffectGroundAttack(Zone* pZone, ZoneCoord_t zoneX, ZoneCoord_t zoneY);

public:
    EffectClass getEffectClass()  { return EFFECT_CLASS_GROUND_ATTACK; }

	void affect();
	void affect(Creature* pCreature);

	void unaffect();
	void unaffect(Creature* pCreature);

	string toString() ;

public:
	int getDamagePercent(void) const { return m_DamagePercent; }
	void setDamagePercent(int damagePercent) { m_DamagePercent = damagePercent; }

	Turn_t getDelay() const { return m_Delay; }
	void setDelay(Turn_t Delay) { m_Delay = Delay; }

//	string getCasterName(void) const { return m_CasterName; }
//	void setCasterName(const string & CasterName ) { m_CasterName = CasterName; }

	ObjectID_t getUserObjectID() const { return m_UserObjectID; }
	void setUserObjectID( ObjectID_t UserObjectID ) { m_UserObjectID = UserObjectID; }


private:
	int     m_DamagePercent;
	Turn_t  m_Delay;
//	string  m_CasterName;
	ObjectID_t	m_UserObjectID;
};

//////////////////////////////////////////////////////////////////////////////
// class EffectGroundAttackLoader
//////////////////////////////////////////////////////////////////////////////

class EffectGroundAttackLoader : public EffectLoader 
{
public:
	virtual Effect::EffectClass getEffectClass()  { return Effect::EFFECT_CLASS_GROUND_ATTACK; }
	virtual string getEffectClassName()  { return "EffectGroundAttack"; }

public:
	virtual void load(Creature* pCreature)  {}
};

extern EffectGroundAttackLoader* g_pEffectGroundAttackLoader;

#endif // __EFFECT_GROUND_ATTACK__
