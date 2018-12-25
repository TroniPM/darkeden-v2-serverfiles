////////////////////////////////////////////////////////////////////////////////
// Filename    : ConditionPayPlay.h
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#ifndef __PAY_PLAY_H__
#define __PAY_PLAY_H__

#include "Condition.h"
#include "ConditionFactory.h"
#include "Creature.h"

//////////////////////////////////////////////////////////////////////////////
// class ConditionPayPlay;
//////////////////////////////////////////////////////////////////////////////

class ConditionPayPlay : public Condition 
{
public:
	virtual ConditionType_t getConditionType()  { return CONDITION_PAY_PLAY; }
	virtual bool isPassive()  { return true; }
	virtual bool isSatisfied(Creature* pNPC, Creature* pPC = NULL, void* pParam = NULL) ;
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual string toString() ;

public:

};

//////////////////////////////////////////////////////////////////////////////
// class ConditionPayPlayFactory;
//////////////////////////////////////////////////////////////////////////////

class ConditionPayPlayFactory : public ConditionFactory 
{
public:
    virtual ConditionType_t getConditionType()  { return Condition::CONDITION_PAY_PLAY; }
    virtual Condition* createCondition()  { return new ConditionPayPlay(); }
    virtual string getConditionName()  { return "PayPlay"; }
};

#endif
