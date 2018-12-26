//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectVigorDropToCreature.h
// Written by  : excel96
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_VIGOR_DROP_TO_CREATURE__
#define __EFFECT_VIGOR_DROP_TO_CREATURE__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectVigorDropToCreature
//////////////////////////////////////////////////////////////////////////////

class EffectVigorDropToCreature : public Effect 
{
public:
	EffectVigorDropToCreature(Creature* pCreature);

public:
    EffectClass getEffectClass()  { return EFFECT_CLASS_VIGOR_DROP_TO_CREATURE; }

	void affect();
	void affect(Creature* pCreature);
	void affect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject);

	void unaffect();
	void unaffect(Creature* pCreature);
	void unaffect(Item* pItem)  {}
	void unaffect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject);

	string toString() ;

public:
//	string getCasterName(void) const { return m_CasterName; }
//	void setCasterName(const string & CasterName ) { m_CasterName = CasterName; }

//	int getPartyID(void) const { return m_PartyID; }
//	void setPartyID(int PartyID) { m_PartyID = PartyID; }

	ObjectID_t getUserObjectID() const { return m_UserObjectID; }
	void setUserObjectID( ObjectID_t UserObjectID ) { m_UserObjectID = UserObjectID; }

	Level_t getLevel()  { return m_Level; }
	void setLevel(Level_t Level) throw() { m_Level = Level; }

	HP_t getPoint()  { return m_Point; }
	void setPoint(HP_t Point) throw() { m_Point = Point; }

	void setTick(Turn_t Tick) throw() { m_Tick = Tick; }
	Turn_t getTick()  { return m_Tick; }

private:
//	string  m_CasterName;
//	int     m_PartyID;
	ObjectID_t	m_UserObjectID;
	Level_t m_Level;
	HP_t    m_Point;
	Turn_t  m_Tick;
};

#endif // __EFFECT_STORM__
