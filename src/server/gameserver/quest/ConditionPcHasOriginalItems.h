////////////////////////////////////////////////////////////////////////////////
// Filename    : ConditionHasInvenSpace.h
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#ifndef __PC_HAS_ORIGINAL_ITEMS_H__
#define __PC_HAS_ORIGINAL_ITEMS_H__

#include "Condition.h"
#include "ConditionFactory.h"
#include "Creature.h"

//////////////////////////////////////////////////////////////////////////////
// class ConditionHasInvenSpace;
//////////////////////////////////////////////////////////////////////////////

class ConditionPcHasOriginalItems : public Condition 
{
public:
	virtual ConditionType_t getConditionType()  { return CONDITION_PC_HAS_ORIGINAL_ITEMS; }
	virtual bool isPassive()  { return true; }
	virtual bool isSatisfied(Creature* pNPC, Creature* pPC = NULL, void* pParam = NULL) ;
	virtual void read(PropertyBuffer & propertyBuffer);
	virtual string toString() ;
private:
	uint	m_ItemClass, m_ItemType, m_ItemNumber;
};

//////////////////////////////////////////////////////////////////////////////
// class ConditionHasInvenSpaceFactory;
//////////////////////////////////////////////////////////////////////////////

class ConditionPcHasOriginalItemsFactory : public ConditionFactory 
{
public:
    virtual ConditionType_t getConditionType()  { return Condition::CONDITION_PC_HAS_ORIGINAL_ITEMS; }
    virtual Condition* createCondition()  { return new ConditionPcHasOriginalItems(); }
    virtual string getConditionName()  { return "PcHasOriginalItems"; }
};

#endif
