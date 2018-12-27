//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectDecreaseHP.h
// Written by  : excel96
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_DECREASE_HP__
#define __EFFECT_DECREASE_HP__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectDecreaseHP
//////////////////////////////////////////////////////////////////////////////

class EffectDecreaseHP : public Effect 
{
public:
	EffectDecreaseHP(Creature* pCreature);

public:
    EffectClass getEffectClass()  { return EFFECT_CLASS_DECREASE_HP; }

	void affect();
	void affect(Creature* pCreature);
	void affect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject);

	void unaffect();
	void unaffect(Creature* pCreature);
	void unaffect(Item* pItem)  {}
	void unaffect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject);

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

#endif // __EFFECT_DECREASE_HP__
