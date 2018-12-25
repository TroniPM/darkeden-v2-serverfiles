////////////////////////////////////////////////////////////////////////////////
// Filename    : ConditionCanEnterPayZone.h
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#ifndef __CAN_ENTER_PAY_ZONE_H__
#define __CAN_ENTER_PAY_ZONE_H__

#include "Condition.h"
#include "ConditionFactory.h"
#include "Creature.h"

//////////////////////////////////////////////////////////////////////////////
// class ConditionCanEnterPayZone;
//////////////////////////////////////////////////////////////////////////////

class ConditionCanEnterPayZone : public Condition 
{
public:
	virtual ConditionType_t getConditionType()  { return CONDITION_CAN_ENTER_PAY_ZONE; }
	virtual bool isPassive()  { return true; }
	virtual bool isSatisfied(Creature* pNPC, Creature* pPC = NULL, void* pParam = NULL) ;
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual string toString() ;

public:

};

//////////////////////////////////////////////////////////////////////////////
// class ConditionCanEnterPayZoneFactory;
//////////////////////////////////////////////////////////////////////////////

class ConditionCanEnterPayZoneFactory : public ConditionFactory 
{
public:
    virtual ConditionType_t getConditionType()  { return Condition::CONDITION_CAN_ENTER_PAY_ZONE; }
    virtual Condition* createCondition()  { return new ConditionCanEnterPayZone(); }
    virtual string getConditionName()  { return "CanEnterPayZone"; }
};

#endif
