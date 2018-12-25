//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectAcidSwamp.h
// Written by  : elca@ewestsoft.com
// Description : �������� AcidSwamp�� Effect�� ó�����ֱ� ���� Ŭ�����̴�.
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_ACID_SWAMP__
#define __EFFECT_ACID_SWAMP__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectAcidSwamp
//////////////////////////////////////////////////////////////////////////////

class EffectAcidSwamp : public Effect 
{
public:
	EffectAcidSwamp(Zone* pZone, ZoneCoord_t zoneX, ZoneCoord_t zoneY);

public:
    EffectClass getEffectClass()  { return EFFECT_CLASS_ACID_SWAMP; }

	void affect();
	void affect(Creature* pCreature);
	void affect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject);

	void unaffect();
	void unaffect(Creature* pCreature);
	void unaffect(Item* pItem) throw(Error) {}
	void unaffect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject);

	string toString() ;

public:
	int getDamage(void) const { return m_Damage; }
	void setDamage(int damage) { m_Damage = damage; }

	Turn_t getTick() const { return m_Tick; }
	void setTick(Turn_t Tick) { m_Tick = Tick; }

	int getLevel(void) const { return m_Level; }
	void setLevel(int level) { m_Level = level; }

	ObjectID_t getUserObjectID() const { return m_UserObjectID; }
	void setUserObjectID( ObjectID_t UserObjectID ) { m_UserObjectID = UserObjectID; }

	void setVampire( bool bVampire = true ) { m_bVampire = bVampire; }
	bool isVampire() const { return m_bVampire; }

	void setForce( bool force ) { m_bForce = force; }
	bool isForce() const { return m_bForce; };

	ObjectID_t getBurrowingTargetObjectID() const { return m_TargetObjectID[0]; }
	void setBurrowingTargetObjectID( ObjectID_t oid ) { m_TargetObjectID[0] = oid; }

	ObjectID_t getWalkingTargetObjectID() const { return m_TargetObjectID[1]; }
	void setWalkingTargetObjectID( ObjectID_t oid ) { m_TargetObjectID[1] = oid; }

private:
	int     m_Damage;
	Turn_t  m_Tick;
	int     m_Level;
	bool	m_bVampire;
	bool	m_bForce;

	ObjectID_t	m_UserObjectID;
	ObjectID_t	m_TargetObjectID[2];	// 0 - Burrowing, 1 - Walking
};

//////////////////////////////////////////////////////////////////////////////
// class EffectAcidSwampLoader
//////////////////////////////////////////////////////////////////////////////

class EffectAcidSwampLoader : public EffectLoader 
{
public:
	virtual Effect::EffectClass getEffectClass()  { return Effect::EFFECT_CLASS_ACID_SWAMP; }
	virtual string getEffectClassName()  { return "EffectAcidSwamp"; }

public:
	virtual void load(Creature* pCreature) throw(Error) {}
	virtual void load(Zone* pZone);
};

extern EffectAcidSwampLoader* g_pEffectAcidSwampLoader;

#endif // __EFFECT_ACID_SWAMP__
