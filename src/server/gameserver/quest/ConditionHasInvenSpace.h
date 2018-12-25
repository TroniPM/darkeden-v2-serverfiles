////////////////////////////////////////////////////////////////////////////////
// Filename    : ConditionHasInvenSpace.h
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#ifndef __HAS_INVEN_SPACE_H__
#define __HAS_INVEN_SPACE_H__

#include "Condition.h"
#include "ConditionFactory.h"
#include "Creature.h"

//////////////////////////////////////////////////////////////////////////////
// class ConditionHasInvenSpace;
//////////////////////////////////////////////////////////////////////////////

class ConditionHasInvenSpace : public Condition 
{
public:
	virtual ConditionType_t getConditionType()  { return CONDITION_HAS_INVEN_SPACE; }
	virtual bool isPassive()  { return true; }
	virtual bool isSatisfied(Creature* pNPC, Creature* pPC = NULL, void* pParam = NULL) ;
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual string toString() ;
private:
	uint	m_Height, m_Width;
};

//////////////////////////////////////////////////////////////////////////////
// class ConditionHasInvenSpaceFactory;
//////////////////////////////////////////////////////////////////////////////

class ConditionHasInvenSpaceFactory : public ConditionFactory 
{
public:
    virtual ConditionType_t getConditionType()  { return Condition::CONDITION_HAS_INVEN_SPACE; }
    virtual Condition* createCondition()  { return new ConditionHasInvenSpace(); }
    virtual string getConditionName()  { return "HasInvenSpace"; }
};

#endif
