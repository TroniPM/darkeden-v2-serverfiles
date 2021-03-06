//////////////////////////////////////////////////////////////////////////////
// Filename    : ConditionFactory.h 
// Written By  : 
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __CONDITION_FACTORY_H__
#define __CONDITION_FACTORY_H__

#include "Condition.h"

//////////////////////////////////////////////////////////////////////////////
// class ConditionFactory
//////////////////////////////////////////////////////////////////////////////

class ConditionFactory 
{
public:
	virtual ~ConditionFactory()  {}
	virtual ConditionType_t getConditionType()  = 0;
	virtual string getConditionName()  = 0;
	virtual Condition* createCondition()  = 0;
};

#endif
