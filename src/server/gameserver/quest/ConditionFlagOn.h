////////////////////////////////////////////////////////////////////////////////
// Filename    : ConditionFlagOn.h
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#ifndef __FLAG_ON_H__
#define __FLAG_ON_H__

#include "Condition.h"
#include "ConditionFactory.h"
#include "Creature.h"

//////////////////////////////////////////////////////////////////////////////
// class ConditionFlagOn;
//////////////////////////////////////////////////////////////////////////////

class ConditionFlagOn : public Condition 
{
public:
	virtual ConditionType_t getConditionType()  { return CONDITION_FLAG_ON; }
	virtual bool isPassive()  { return true; }
	virtual bool isSatisfied(Creature* pNPC, Creature* pPC = NULL, void* pParam = NULL) ;
	virtual void read(PropertyBuffer & propertyBuffer);
	virtual string toString() ;

public:
	int getIndex(void)  { return m_Index; }
	void setIndex(int index) throw() { m_Index = index; }

private:
	int m_Index; // �÷����� ��

};

//////////////////////////////////////////////////////////////////////////////
// class ConditionFlagOnFactory;
//////////////////////////////////////////////////////////////////////////////

class ConditionFlagOnFactory : public ConditionFactory 
{
public:
    virtual ConditionType_t getConditionType()  { return Condition::CONDITION_FLAG_ON; }
    virtual Condition* createCondition()  { return new ConditionFlagOn(); }
    virtual string getConditionName()  { return "FlagOn"; }
};

#endif
