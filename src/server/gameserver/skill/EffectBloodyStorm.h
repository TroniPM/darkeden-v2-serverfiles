#ifndef __EFFECT_BLOODY_STORM__
#define __EFFECT_BLOODY_STORM__

#include "Effect.h"
#include "EffectLoader.h"

class EffectBloodyStorm : public Effect
{
public:
	EffectBloodyStorm(Zone* pZone, ZoneCoord_t zoneX, ZoneCoord_t zoneY);

	EffectClass getEffectClass()  { return EFFECT_CLASS_BLOODY_STORM; }

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

	void setVampire( bool bVampire = true ) { m_bVampire = bVampire; }
	bool isVampire() const { return m_bVampire; }

	void setUserObjectID(ObjectID_t oid)  { m_UserObjectID = oid; }
	ObjectID_t getUserObjectID()  { return m_UserObjectID; }

	bool affectCreature(Creature* pCreature, bool bAffectByMove); 
private:
	int 	 	m_Damage;  	    // EffectBloodyStorm Damage;
	Turn_t 		m_Tick;			// EffectBloodyStorm turn;	
	int 		m_Level;		// EffectBloodyStorm level;
	bool		m_bVampire;
	Duration_t 	m_Duration;		// EffectBloodyStorm Duration;
	Duration_t  m_StormDuration; // BloodyStorm Effect ���� �ð� 
	ObjectID_t	m_UserObjectID;
};

class EffectBloodyStormLoader : public EffectLoader
{
public:
	virtual Effect::EffectClass getEffectClass()  { return Effect::EFFECT_CLASS_BLOODY_STORM; }
	virtual string getEffectClassName()  { return "EffectBloodyStorm"; }

public:
	virtual void load(Creature* pCreature)  {}
};

extern EffectBloodyStormLoader* g_pEffectBloodyStormLoader;

#endif
