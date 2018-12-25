////////////////////////////////////////////////////////////////////////////////
// Filename    : ConditionExistReinforce.h
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#ifndef __EXIST_REINFORCE_H__
#define __EXIST_REINFORCE_H__

#include "Condition.h"
#include "ConditionFactory.h"
#include "Creature.h"

//////////////////////////////////////////////////////////////////////////////
// class ConditionExistReinforce;
//////////////////////////////////////////////////////////////////////////////

class ConditionExistReinforce : public Condition 
{
public:
	virtual ConditionType_t getConditionType()  { return CONDITION_EXIST_REINFORCE; }
	virtual bool isPassive()  { return true; }
	virtual bool isSatisfied(Creature* pNPC, Creature* pPC = NULL, void* pParam = NULL) ;
	virtual void read(PropertyBuffer & propertyBuffer);
	virtual string toString() ;

public:

private:
	ZoneID_t	m_ZoneID;
};

//////////////////////////////////////////////////////////////////////////////
// class ConditionExistReinforceFactory;
//////////////////////////////////////////////////////////////////////////////

class ConditionExistReinforceFactory : public ConditionFactory 
{
public:
    virtual ConditionType_t getConditionType()  { return Condition::CONDITION_EXIST_REINFORCE; }
    virtual Condition* createCondition()  { return new ConditionExistReinforce(); }
    virtual string getConditionName()  { return "ExistReinforce"; }
};

#endif
