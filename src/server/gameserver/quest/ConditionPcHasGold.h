////////////////////////////////////////////////////////////////////////////////
// Filename    : ConditionHasInvenSpace.h
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#ifndef __PC_HAS_GOLD_H__
#define __PC_HAS_GOLD_H__

#include "Condition.h"
#include "ConditionFactory.h"
#include "Creature.h"

//////////////////////////////////////////////////////////////////////////////
// class ConditionHasInvenSpace;
//////////////////////////////////////////////////////////////////////////////

class ConditionPcHasGold : public Condition 
{
public:
	virtual ConditionType_t getConditionType()  { return CONDITION_PC_HAS_GOLD; }
	virtual bool isPassive()  { return true; }
	virtual bool isSatisfied(Creature* pNPC, Creature* pPC = NULL, void* pParam = NULL) ;
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual string toString() ;
private:
	Gold_t m_Gold;
};

//////////////////////////////////////////////////////////////////////////////
// class ConditionHasInvenSpaceFactory;
//////////////////////////////////////////////////////////////////////////////

class ConditionPcHasGoldFactory : public ConditionFactory 
{
public:
    virtual ConditionType_t getConditionType()  { return Condition::CONDITION_PC_HAS_GOLD; }
    virtual Condition* createCondition()  { return new ConditionPcHasGold(); }
    virtual string getConditionName()  { return "PcHasGold"; }
};

#endif
