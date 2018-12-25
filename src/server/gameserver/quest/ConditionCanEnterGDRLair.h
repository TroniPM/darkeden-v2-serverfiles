////////////////////////////////////////////////////////////////////////////////
// Filename    : ConditionCanEnterGDRLair.h
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#ifndef __CAN_ENTER_GDR_LAIR_H__
#define __CAN_ENTER_GDR_LAIR_H__

#include "Condition.h"
#include "ConditionFactory.h"
#include "Creature.h"

//////////////////////////////////////////////////////////////////////////////
// class ConditionCanEnterGDRLair;
//////////////////////////////////////////////////////////////////////////////

class ConditionCanEnterGDRLair : public Condition 
{
public:
	virtual ConditionType_t getConditionType()  { return CONDITION_CAN_ENTER_GDR_LAIR; }
	virtual bool isPassive()  { return true; }
	virtual bool isSatisfied(Creature* pNPC, Creature* pPC = NULL, void* pParam = NULL) ;
	virtual void read(PropertyBuffer & propertyBuffer);
	virtual string toString() ;

public:

};

//////////////////////////////////////////////////////////////////////////////
// class ConditionCanEnterGDRLairFactory;
//////////////////////////////////////////////////////////////////////////////

class ConditionCanEnterGDRLairFactory : public ConditionFactory 
{
public:
    virtual ConditionType_t getConditionType()  { return Condition::CONDITION_CAN_ENTER_GDR_LAIR; }
    virtual Condition* createCondition()  { return new ConditionCanEnterGDRLair(); }
    virtual string getConditionName()  { return "CanEnterGDRLair"; }
};

#endif
