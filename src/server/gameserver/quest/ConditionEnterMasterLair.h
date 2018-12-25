////////////////////////////////////////////////////////////////////////////////
// Filename    : ConditionEnterMasterLair.h
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#ifndef __ENTER_MASTER_LAIR_H__
#define __ENTER_MASTER_LAIR_H__

#include "Condition.h"
#include "ConditionFactory.h"
#include "Creature.h"

//////////////////////////////////////////////////////////////////////////////
// class ConditionEnterMasterLair;
//////////////////////////////////////////////////////////////////////////////

class ConditionEnterMasterLair : public Condition 
{
public:
	virtual ConditionType_t getConditionType()  { return CONDITION_ENTER_MASTER_LAIR; }
	virtual bool isPassive()  { return true; }
	virtual bool isSatisfied(Creature* pNPC, Creature* pPC = NULL, void* pParam = NULL) ;
	virtual void read(PropertyBuffer & propertyBuffer);

	ZoneID_t getTargetZoneID() const	{ return m_TargetZoneID; }

	virtual string toString() ;

public:
	ZoneID_t 	m_TargetZoneID;
};

//////////////////////////////////////////////////////////////////////////////
// class ConditionEnterMasterLairFactory;
//////////////////////////////////////////////////////////////////////////////

class ConditionEnterMasterLairFactory : public ConditionFactory 
{
public:
    virtual ConditionType_t getConditionType()  { return Condition::CONDITION_ENTER_MASTER_LAIR; }
    virtual Condition* createCondition()  { return new ConditionEnterMasterLair(); }
    virtual string getConditionName()  { return "EnterMasterLair"; }
};

#endif
