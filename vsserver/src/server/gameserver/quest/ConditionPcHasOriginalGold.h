////////////////////////////////////////////////////////////////////////////////
// Filename    : ConditionHasInvenSpace.h
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#ifndef __PC_HAS_ORIGINAL_GOLD_H__
#define __PC_HAS_ORIGINAL_GOLD_H__

#include "Condition.h"
#include "ConditionFactory.h"
#include "Creature.h"

//////////////////////////////////////////////////////////////////////////////
// class ConditionHasInvenSpace;
//////////////////////////////////////////////////////////////////////////////

class ConditionPcHasOriginalGold : public Condition 
{
public:
	virtual ConditionType_t getConditionType() const throw() { return CONDITION_PC_HAS_ORIGINAL_GOLD; }
	virtual bool isPassive() const throw() { return true; }
	virtual bool isSatisfied(Creature* pNPC, Creature* pPC = NULL, void* pParam = NULL) const throw();
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual string toString() const throw();
private:
	Gold_t m_Gold;
};

//////////////////////////////////////////////////////////////////////////////
// class ConditionHasInvenSpaceFactory;
//////////////////////////////////////////////////////////////////////////////

class ConditionPcHasOriginalGoldFactory : public ConditionFactory 
{
public:
    virtual ConditionType_t getConditionType() const throw() { return Condition::CONDITION_PC_HAS_ORIGINAL_GOLD; }
    virtual Condition* createCondition() const throw() { return new ConditionPcHasOriginalGold(); }
    virtual string getConditionName() const throw() { return "PcHasOriginalGold"; }
};

#endif
