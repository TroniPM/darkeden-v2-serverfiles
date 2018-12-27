//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectPeace.h
// Written by  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_PEACE__
#define __EFFECT_PEACE__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectPeace
//////////////////////////////////////////////////////////////////////////////

class EffectPeace : public Effect 
{
public:
	// pCreature(��)�� pPeaceCreature���� peace���¸� �����Ѵ�.
	EffectPeace(Creature* pCreature, ObjectID_t PeaceCreatureID);

public:
    EffectClass getEffectClass()  { return EFFECT_CLASS_PEACE; }

	void affect() {}
	void affect(Creature* pCreature);
	void affect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject);

	void unaffect();
	void unaffect(Creature* pCreature);
	void unaffect(Item*  pItem)  {}
	void unaffect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject);

	string toString() ;
	
public:
	ObjectID_t getPeaceCreatureID()  { return m_PeaceCreatureID; }
	void setPeaceCreatureID(ObjectID_t PeaceCreatureID)  { m_PeaceCreatureID = PeaceCreatureID; }

private:
	ObjectID_t m_PeaceCreatureID;

};

#endif // __EFFECT_YELLOW_POISON_TO_CREATURE__
