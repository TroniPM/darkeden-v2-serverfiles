////////////////////////////////////////////////////////////////////////////////
// Filename    : ConditionCanEnterDynamicZone.h
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#ifndef __CAN_ENTER_DYNAMIC_ZONE_H__
#define __CAN_ENTER_DYNAMIC_ZONE_H__

#include "Condition.h"
#include "ConditionFactory.h"
#include "Creature.h"

//////////////////////////////////////////////////////////////////////////////
// class ConditionCanEnterDynamicZone;
//////////////////////////////////////////////////////////////////////////////

class ConditionCanEnterDynamicZone : public Condition 
{
public:
	virtual ConditionType_t getConditionType()  { return CONDITION_CAN_ENTER_DYNAMIC_ZONE; }
	virtual bool isPassive()  { return true; }
	virtual bool isSatisfied(Creature* pNPC, Creature* pPC = NULL, void* pParam = NULL) ;
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual string toString() ;

public:
	ZoneID_t	m_DynamicZoneID;
};

//////////////////////////////////////////////////////////////////////////////
// class ConditionCanEnterDynamicZoneFactory;
//////////////////////////////////////////////////////////////////////////////

class ConditionCanEnterDynamicZoneFactory : public ConditionFactory 
{
public:
    virtual ConditionType_t getConditionType()  { return Condition::CONDITION_CAN_ENTER_DYNAMIC_ZONE; }
    virtual Condition* createCondition()  { return new ConditionCanEnterDynamicZone(); }
    virtual string getConditionName()  { return "CanEnterDynamicZone"; }
};

#endif
