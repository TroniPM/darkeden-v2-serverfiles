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
	virtual ConditionType_t getConditionType() const throw() { return CONDITION_AT_FIRST; }
	virtual bool isActive() const throw() { return true; }
	virtual bool isSatisfied(Creature* pCreature1, Creature* pCreature2 = NULL, void* pParam = NULL) const throw() { return true; }
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error) {}
	virtual string toString() const throw() { return "AtFirst"; }

};

//////////////////////////////////////////////////////////////////////////////
// class ConditionAtFirstFactory;
//////////////////////////////////////////////////////////////////////////////

class ConditionAtFirstFactory : public ConditionFactory 
{
public:
	virtual ConditionType_t getConditionType() const throw() { return Condition::CONDITION_AT_FIRST; }
	virtual Condition* createCondition() const throw() { return new ConditionAtFirst(); }
	virtual string getConditionName() const throw() { return "AtFirst"; }
};

#endif
