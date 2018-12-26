///////////////////////////////////////////////////////////////////////////////
// Filename    : ConditionAtFirst.h
// Written By  : 
// Description :
// NPC 가 로딩된 직후에 최초로 한번만 실행되어야 하는 액션들을
// 이 컨디션과 연관시켜주면 자동으로 실행된다.
//////////////////////////////////////////////////////////////////////////////

#ifndef __AT_FIRST_H__
#define __AT_FIRST_H__

#include "Condition.h"
#include "ConditionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ConditionAtFirst;
//////////////////////////////////////////////////////////////////////////////

class ConditionAtFirst : public Condition 
{
public:
	virtual ConditionType_t getConditionType()  { return CONDITION_AT_FIRST; }
	virtual bool isActive()  { return true; }
	virtual bool isSatisfied(Creature* pCreature1, Creature* pCreature2 = NULL, void* pParam = NULL)  { return true; }
	virtual void read(PropertyBuffer & propertyBuffer)  {}
	virtual string toString()  { return "AtFirst"; }

};

//////////////////////////////////////////////////////////////////////////////
// class ConditionAtFirstFactory;
//////////////////////////////////////////////////////////////////////////////

class ConditionAtFirstFactory : public ConditionFactory 
{
public:
	virtual ConditionType_t getConditionType()  { return Condition::CONDITION_AT_FIRST; }
	virtual Condition* createCondition()  { return new ConditionAtFirst(); }
	virtual string getConditionName()  { return "AtFirst"; }
};

#endif
