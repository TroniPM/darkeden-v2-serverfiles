//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectMeteorStrike.h
// Written by  : elca@ewestsoft.com
// Description : �������� MeteorStrike�� Effect�� ó�����ֱ� ���� Ŭ�����̴�.
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_METEOR_STRIKE__
#define __EFFECT_METEOR_STRIKE__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectMeteorStrike
//////////////////////////////////////////////////////////////////////////////

class EffectMeteorStrike : public Effect 
{
public:
	EffectMeteorStrike(Zone* pZone, ZoneCoord_t zoneX, ZoneCoord_t zoneY, bool bPlayer = false) throw(Error);

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_METEOR_STRIKE; }

	void affect() throw(Error);
	void affect(Creature* pCreature) throw(Error);

	void unaffect() throw(Error);
	void unaffect(Creature* pCreature) throw(Error);

	string toString() const throw();

public:
	int getDamage(void) const { return m_Damage; }
	void setDamage(int damage) { m_Damage = damage; }

	Turn_t getDelay() const { return m_Delay; }
	void setDelay(Turn_t Delay) { m_Delay = Delay; }

//	string getCasterName(void) const { return m_CasterName; }
//	void setCasterName(const string & CasterName ) { m_CasterName = CasterName; }

	ObjectID_t getUserObjectID(void) const { return m_UserObjectID; }
	void setUserObjectID(ObjectID_t UserObjectID ) { m_UserObjectID = UserObjectID; }

	void setSplashRatio(int index, uint ratio) { m_SplashRatio[index] = ratio; }

private:
	int     m_Damage;
	Turn_t  m_Delay;
//	string  m_CasterName;
	ObjectID_t   m_UserObjectID;
	bool	m_bPlayer;			// ������ ����� ����ΰ�?
	uint	m_SplashRatio[3];
};

//////////////////////////////////////////////////////////////////////////////
// class EffectMeteorStrikeLoader
//////////////////////////////////////////////////////////////////////////////

class EffectMeteorStrikeLoader : public EffectLoader 
{
public:
	virtual Effect::EffectClass getEffectClass() const throw() { return Effect::EFFECT_CLASS_METEOR_STRIKE; }
	virtual string getEffectClassName() const throw() { return "EffectMeteorStrike"; }

public:
	virtual void load(Creature* pCreature) throw(Error) {}
};

extern EffectMeteorStrikeLoader* g_pEffectMeteorStrikeLoader;

#endif // __EFFECT_METEOR_STRIKE__
