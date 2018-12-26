#ifndef __EFFECT_BAT_STORM__
#define __EFFECT_BAT_STORM__

#include "Effect.h"
#include "EffectLoader.h"

class EffectBatStorm : public Effect
{
public:
	EffectBatStorm(Zone* pZone, ZoneCoord_t zoneX, ZoneCoord_t zoneY);

	EffectClass getEffectClass()  { return EFFECT_CLASS_BAT_STORM; }

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

	void setUserObjectID(ObjectID_t oid) throw() { m_UserObjectID = oid; }
	ObjectID_t getUserObjectID()  { return m_UserObjectID; }

	void setVampire( bool bVampire = true ) { m_bVampire = bVampire; }
	bool isVampire() const { return m_bVampire; }

	bool affectCreature(Creature* pCreature, bool bAffectByMove); 
private:
	int 	 	m_Damage;  	    // EffectBatStorm Damage;
	Turn_t 		m_Tick;			// EffectBatStorm turn;	
	int 		m_Level;		// EffectBatStorm level;
	Duration_t 	m_Duration;		// EffectBatStorm Duration;
	Duration_t  m_StormDuration; // BatStorm Effect 지속 시간 
	ObjectID_t	m_UserObjectID;
	bool		m_bVampire;
};

class EffectBatStormLoader : public EffectLoader
{
public:
	virtual Effect::EffectClass getEffectClass()  { return Effect::EFFECT_CLASS_BAT_STORM; }
	virtual string getEffectClassName()  { return "EffectBatStorm"; }

public:
	virtual void load(Creature* pCreature)  {}
	virtual void load(Zone* pZone)  {}
};

extern EffectBatStormLoader* g_pEffectBatStormLoader;

#endif
