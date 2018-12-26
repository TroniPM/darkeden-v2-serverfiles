///////////////////////////////////////////////////////////////////////////////
// Filename    : ConditionAtFirst.h
// Written By  : 
// Description :
// NPC �� �ε��� ���Ŀ� ���ʷ� �ѹ��� ����Ǿ�� �ϴ� �׼ǵ���
// �� ����ǰ� ���������ָ� �ڵ����� ����ȴ�.
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
