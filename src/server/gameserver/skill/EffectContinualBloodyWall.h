//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectContinualBloodyWall.h
// Written by  : Reiot
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_CONTINUAL_BLOODY_WALL_H__
#define __EFFECT_CONTINUAL_BLOODY_WALL_H__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectContinualBloodyWall;
//////////////////////////////////////////////////////////////////////////////

class Corpse;

class EffectContinualBloodyWall : public Effect 
{
public:
	EffectContinualBloodyWall(Zone* pZone);
	virtual ~EffectContinualBloodyWall();

public:


	EffectClass getEffectClass()  { return EFFECT_CLASS_CONTINUAL_BLOODY_WALL; }

	// OBJECT_PRIORITY_NONE 라는 뜻은, 타일에 들어가서는 안된다는 뜻이다.
//	virtual ObjectPriority getObjectPriority()  { return OBJECT_PRIORITY_NONE; }

	virtual void affect();
	
	virtual void unaffect();

	void create(const string & ownerID) throw(Error) {}
	void save(const string & ownerID) throw(Error) {}
	void destroy(const string & ownerID) throw(Error) {}

	virtual string toString() ;


public:
	
	void setDamage(Damage_t damage) throw(Error) { m_Damage = damage; }
	Damage_t getDamage()  { return m_Damage; }
  
	void setTick( Turn_t tick ) throw(Error) { m_Tick = tick; }
	Turn_t getTick()  { return m_Tick; }

	void setDuration( Turn_t duration ) throw(Error) { m_Duration = duration; }
	Turn_t getDuration()  { return m_Duration; }

	void setRect(ZoneCoord_t left, ZoneCoord_t right, ZoneCoord_t top, ZoneCoord_t bottom) throw(Error) { m_Left = left; m_Right = right; m_Top = top; m_Bottom = bottom; }

private:
	Damage_t 	m_Damage;
	Turn_t 		m_Tick;
	Turn_t		m_Duration;

	ZoneCoord_t m_Left;
	ZoneCoord_t m_Right;
	ZoneCoord_t m_Top;
	ZoneCoord_t m_Bottom;

};

//////////////////////////////////////////////////////////////////////////////
// class EffectContinualBloodyWallLoader
//////////////////////////////////////////////////////////////////////////////

class EffectContinualBloodyWallLoader : public EffectLoader
{
public:
    virtual Effect::EffectClass getEffectClass()  { return Effect::EFFECT_CLASS_CONTINUAL_BLOODY_WALL; }
    virtual string getEffectClassName()  { return "EffectContinualBloodyWall"; }

public:
    virtual void load(Creature* pCreature) throw(Error) {}
    virtual void load(Zone* pZone);
};

extern EffectContinualBloodyWallLoader* g_pEffectContinualBloodyWallLoader;

#endif
