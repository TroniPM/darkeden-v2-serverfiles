//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectXRLMissile.h
// Written by  : rallser
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_XRL_Missile__
#define __EFFECT_XRL_Missile__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class XRLMissile
//////////////////////////////////////////////////////////////////////////////

class EffectXRLMissile : public Effect 
{
public:
	EffectXRLMissile(Creature* pCreature);

public:
    EffectClass getEffectClass()  { return EFFECT_CLASS_XRL_Missile; }

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

#endif // __EFFECT_XRLMissile
