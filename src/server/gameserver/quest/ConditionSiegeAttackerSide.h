////////////////////////////////////////////////////////////////////////////////
// Filename    : ConditionSiegeAttackerSide.h
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#ifndef __SIEGE_ATTACKER_SIDE_H__
#define __SIEGE_ATTACKER_SIDE_H__

#include "Condition.h"
#include "ConditionFactory.h"
#include "Creature.h"

//////////////////////////////////////////////////////////////////////////////
// class ConditionSiegeAttackerSide;
//////////////////////////////////////////////////////////////////////////////

class ConditionSiegeAttackerSide : public Condition 
{
public:
	virtual ConditionType_t getConditionType()  { return CONDITION_SIEGE_ATTACKER_SIDE; }
	virtual bool isPassive()  { return true; }
	virtual bool isSatisfied(Creature* pNPC, Creature* pPC = NULL, void* pParam = NULL) ;
	virtual void read(PropertyBuffer & propertyBuffer);
	virtual string toString() ;

public:

};

//////////////////////////////////////////////////////////////////////////////
// class ConditionSiegeAttackerSideFactory;
//////////////////////////////////////////////////////////////////////////////

class ConditionSiegeAttackerSideFactory : public ConditionFactory 
{
public:
    virtual ConditionType_t getConditionType()  { return Condition::CONDITION_SIEGE_ATTACKER_SIDE; }
    virtual Condition* createCondition()  { return new ConditionSiegeAttackerSide(); }
    virtual string getConditionName()  { return "SiegeAttackerSide"; }
};

#endif
