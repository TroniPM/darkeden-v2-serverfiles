////////////////////////////////////////////////////////////////////////////////
// Filename    : ConditionCanEnterBeginnerZone.h
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#ifndef __CAN_ENTER_BEGINNER_ZONE_H__
#define __CAN_ENTER_BEGINNER_ZONE_H__

#include "Condition.h"
#include "ConditionFactory.h"
#include "Creature.h"

//////////////////////////////////////////////////////////////////////////////
// class ConditionCanEnterBeginnerZone;
//////////////////////////////////////////////////////////////////////////////

class ConditionCanEnterBeginnerZone : public Condition 
{
public:
	virtual ConditionType_t getConditionType()  { return CONDITION_CAN_ENTER_BEGINNER_ZONE; }
	virtual bool isPassive()  { return true; }
	virtual bool isSatisfied(Creature* pNPC, Creature* pPC = NULL, void* pParam = NULL) ;
	virtual void read(PropertyBuffer & propertyBuffer);
	virtual string toString() ;

public:

};

//////////////////////////////////////////////////////////////////////////////
// class ConditionCanEnterBeginnerZoneFactory;
//////////////////////////////////////////////////////////////////////////////

class ConditionCanEnterBeginnerZoneFactory : public ConditionFactory 
{
public:
    virtual ConditionType_t getConditionType()  { return Condition::CONDITION_CAN_ENTER_BEGINNER_ZONE; }
    virtual Condition* createCondition()  { return new ConditionCanEnterBeginnerZone(); }
    virtual string getConditionName()  { return "CanEnterBeginnerZone"; }
};

#endif
