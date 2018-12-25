//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectBombCrashWalkToEnemy.h
// Written by  : excel96
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_BOMB_CRASH_WALK_TO_ENEMY__
#define __EFFECT_BOMB_CRASH_WALK_TO_ENEMY__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectBombCrashWalkToEnemy
//////////////////////////////////////////////////////////////////////////////

class EffectBombCrashWalkToEnemy : public Effect 
{
public:
	EffectBombCrashWalkToEnemy(Creature* pCreature);

public:
    EffectClass getEffectClass()  { return EFFECT_CLASS_SKILL_BOMB_CRASH_WALK_TO_ENEMY; }

	void affect();
	void affect(Creature* pCreature);

	void unaffect();
	void unaffect(Creature* pCreature);
	string toString() ;

public:
	HP_t getPoint()  { return m_Point; }
	void setPoint(HP_t Point) throw() { m_Point = Point; }

	Turn_t getTick()  { return m_Tick; }
	void setTick(Turn_t Tick) throw() { m_Tick = Tick; }

	void setUserObjectID(ObjectID_t oid) throw() { m_UserObjectID = oid; }
	ObjectID_t getUserObjectID()  { return m_UserObjectID; }

private:
	HP_t    m_Point;
	Turn_t	m_Tick;
	ObjectID_t m_UserObjectID;
};

#endif // __EFFECT_BOMB_CRASH_WALK_TO_ENEMY__
