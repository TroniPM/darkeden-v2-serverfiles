//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectPlasmaRocketLauncher.h
// Written by  : excel96
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_PLASMA_ROCKET_LAUNCHER__
#define __EFFECT_PLASMA_ROCKET_LAUNCHER__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectPlasmaRocketLauncher
//////////////////////////////////////////////////////////////////////////////

class EffectPlasmaRocketLauncher : public Effect 
{
public:
	EffectPlasmaRocketLauncher(Creature* pCreature);

public:
    EffectClass getEffectClass()  { return EFFECT_CLASS_PLASMA_ROCKET_LAUNCHER; }

	void affect();
	void affect(Creature* pCreature);

	void unaffect();
	string toString() ;

public:
	HP_t getPoint()  { return m_Point; }
	void setPoint(HP_t Point)  { m_Point = Point; }

	void setUserObjectID(ObjectID_t oid)  { m_UserObjectID = oid; }
	ObjectID_t getUserObjectID()  { return m_UserObjectID; }

private:
	HP_t    m_Point;
	ObjectID_t m_UserObjectID;
};

#endif // __EFFECT_PLASMA_ROCKET_LAUNCHER__
