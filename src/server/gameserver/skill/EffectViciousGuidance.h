//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectDivineGuidance.h
// Written by  : excel96
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_VICIOUS_GUIDANCE__
#define __EFFECT_VICIOUS_GUIDANCE__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectDivineGuidance
//////////////////////////////////////////////////////////////////////////////

class EffectViciousGuidance : public Effect 
{
public:
	EffectViciousGuidance(Creature* pCreature);

public:
    EffectClass getEffectClass()  { return EFFECT_CLASS_VICIOUS_GUIDANCE; }

	void affect();
	void affect(Creature* pCreature);

	void unaffect();
	void unaffect(Creature* pCreature);
	string toString() ;

public:
	HP_t getPoint()  { return m_Point; }
	void setPoint(HP_t Point)  { m_Point = Point; }

	Turn_t getTick()  { return m_Tick; }
	void setTick(Turn_t Tick)  { m_Tick = Tick; }

	void setUserObjectID(ObjectID_t oid)  { m_UserObjectID = oid; }
	ObjectID_t getUserObjectID()  { return m_UserObjectID; }

private:
	HP_t    m_Point;
	Turn_t	m_Tick;
	ObjectID_t m_UserObjectID;
};

#endif // __EFFECT_Vicious_GUIDANCE__
