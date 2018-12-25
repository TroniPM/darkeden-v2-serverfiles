////////////////////////////////////////////////////////////////////////////////
// Filename    : ConditionHasInvenSpace.h
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#ifndef __ZONE_HAS_MONSTER_H__
#define __ZONE_HAS_MONSTER_H__

#include "Condition.h"
#include "ConditionFactory.h"
#include "Creature.h"

//////////////////////////////////////////////////////////////////////////////
// class ConditionHasInvenSpace;
//////////////////////////////////////////////////////////////////////////////

class ConditionZoneHasMonster : public Condition 
{
public:
	virtual ConditionType_t getConditionType()  { return CONDITION_ZONE_HAS_MONSTER; }
	virtual bool isPassive()  { return true; }
	virtual bool isSatisfied(Creature* pNPC, Creature* pPC = NULL, void* pParam = NULL) ;
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual string toString() ;
private:
	//uint	m_ZoneID, 
	MonsterType_t m_MonsterType;
};

//////////////////////////////////////////////////////////////////////////////
// class ConditionHasInvenSpaceFactory;
//////////////////////////////////////////////////////////////////////////////

class ConditionZoneHasMonsterFactory : public ConditionFactory 
{
public:
    virtual ConditionType_t getConditionType()  { return Condition::CONDITION_ZONE_HAS_MONSTER; }
    virtual Condition* createCondition()  { return new ConditionZoneHasMonster(); }
    virtual string getConditionName()  { return "ZoneHasMonster"; }
};

#endif
