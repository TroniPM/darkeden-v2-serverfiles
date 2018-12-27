////////////////////////////////////////////////////////////////////////////////
// Filename    : ConditionFlagOff.h
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#ifndef __FLAG_OFF_H__
#define __FLAG_OFF_H__

#include "Condition.h"
#include "ConditionFactory.h"
#include "Creature.h"

//////////////////////////////////////////////////////////////////////////////
// class ConditionFlagOff;
//////////////////////////////////////////////////////////////////////////////

class ConditionFlagOff : public Condition 
{
public:
	virtual ConditionType_t getConditionType()  { return CONDITION_FLAG_OFF; }
	virtual bool isPassive()  { return true; }
	virtual bool isSatisfied(Creature* pNPC, Creature* pPC = NULL, void* pParam = NULL) ;
	virtual void read(PropertyBuffer & propertyBuffer);
	virtual string toString() ;

public:
	int getIndex(void)  { return m_Index; }
	void setIndex(int index)  { m_Index = index; }

private:
	int m_Index; // 플래그의 값

};

//////////////////////////////////////////////////////////////////////////////
// class ConditionFlagOffFactory;
//////////////////////////////////////////////////////////////////////////////

class ConditionFlagOffFactory : public ConditionFactory 
{
public:
    virtual ConditionType_t getConditionType()  { return Condition::CONDITION_FLAG_OFF; }
    virtual Condition* createCondition()  { return new ConditionFlagOff(); }
    virtual string getConditionName()  { return "FlagOff"; }
};

#endif
