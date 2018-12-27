#ifndef __EFFECT_BLOODY_SKULL__
#define __EFFECT_BLOODY_SKULL__

#include "Effect.h"
#include "EffectLoader.h"

class EffectBloodySkull : public Effect
{
public:
	EffectBloodySkull(Zone* pZone, ZoneCoord_t zoneX, ZoneCoord_t zoneY);

	EffectClass getEffectClass()  { return EFFECT_CLASS_BLOODY_SKULL; }

	void affect();
	void affect(Creature* pCreature);
	void affect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject);

	void unaffect();
	void unaffect(Creature* pCreature);
	void unaffect(Item* pItem)  {}
	void unaffect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject);

	string toString() ;

public:
	int getDamage(void) const { return m_Damage; }
	void setDamage(int damage) { m_Damage = damage; }

	Turn_t getTick() const { return m_Tick; }
	void setTick(Turn_t Tick) { m_Tick = Tick; }

	int getLevel(void) const { return m_Level; }
	void setLevel(int level) { m_Level = level; }

	void setUserObjectID(ObjectID_t oid)  { m_UserObjectID = oid; }
	ObjectID_t getUserObjectID()  { return m_UserObjectID; }

	void setVampire( bool bVampire = true ) { m_bVampire = bVampire; }
	bool isVampire() const { return m_bVampire; }

	bool affectCreature(Creature* pCreature, bool bAffectByMove); 
private:
	int 	 	m_Damage;  	    // EffectAcidStorm Damage;
	Turn_t 		m_Tick;			// EffectAcidStorm turn;	
	int 		m_Level;		// EffectAcidStorm level;
	Duration_t 	m_Duration;		// EffectAcidStorm Duration;
	Duration_t  m_StormDuration; // AcidStorm Effect 지속 시간 
	ObjectID_t	m_UserObjectID;
	bool		m_bVampire;
};

class EffectBloodySkullLoader : public EffectLoader
{
public:
	virtual Effect::EffectClass getEffectClass()  { return Effect::EFFECT_CLASS_BLOODY_SKULL; }
	virtual string getEffectClassName()  { return "EffectAcidStorm"; }

public:
	virtual void load(Creature* pCreature)  {}
	virtual void load(Zone* pZone)  {}
};

extern EffectBloodySkullLoader* g_pEffectBloodySkullLoader;

#endif
