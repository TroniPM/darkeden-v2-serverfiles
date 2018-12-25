////////////////////////////////////////////////////////////////////////////////
// Filename    : ConditionEnterCastleDungeon.h
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#ifndef __ENTER_CASTLE_DUNGEON_H__
#define __ENTER_CASTLE_DUNGEON_H__

#include "Condition.h"
#include "ConditionFactory.h"
#include "Creature.h"

//////////////////////////////////////////////////////////////////////////////
// class ConditionEnterCastleDungeon;
//////////////////////////////////////////////////////////////////////////////

class ConditionEnterCastleDungeon : public Condition 
{
public:
	virtual ConditionType_t getConditionType()  { return CONDITION_ENTER_CASTLE_DUNGEON; }
	virtual bool isPassive()  { return true; }
	virtual bool isSatisfied(Creature* pNPC, Creature* pPC = NULL, void* pParam = NULL) ;
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);

	ZoneID_t getCastleZoneID() const	{ return m_CastleZoneID; }

	virtual string toString() ;

public:
	ZoneID_t 	m_CastleZoneID;
};

//////////////////////////////////////////////////////////////////////////////
// class ConditionEnterCastleDungeonFactory;
//////////////////////////////////////////////////////////////////////////////

class ConditionEnterCastleDungeonFactory : public ConditionFactory 
{
public:
    virtual ConditionType_t getConditionType()  { return Condition::CONDITION_ENTER_CASTLE_DUNGEON; }
    virtual Condition* createCondition()  { return new ConditionEnterCastleDungeon(); }
    virtual string getConditionName()  { return "EnterCastleDungeon"; }
};

#endif
