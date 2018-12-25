////////////////////////////////////////////////////////////////////////////////
// Filename    : ConditionEffectFlag.h
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_FLAG_H__
#define __EFFECT_FLAG_H__

#include "Condition.h"
#include "ConditionFactory.h"
#include "Effect.h"

class Creature;

//////////////////////////////////////////////////////////////////////////////
// class ConditionEffectFlag;
//////////////////////////////////////////////////////////////////////////////

class ConditionEffectFlag : public Condition 
{
public:
	virtual ConditionType_t getConditionType()  { return CONDITION_EFFECT_FLAG; }
	virtual bool isPassive()  { return true; }
	virtual bool isSatisfied(Creature* pNPC, Creature* pPC = NULL, void* pParam = NULL) ;
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual string toString() ;

public:
	Effect::EffectClass getIndex(void)  { return m_Index; }
	void setIndex(Effect::EffectClass index) throw() { m_Index = index; }

private:
	Effect::EffectClass m_Index; // 플래그의 값

};

//////////////////////////////////////////////////////////////////////////////
// class ConditionEffectFlagFactory;
//////////////////////////////////////////////////////////////////////////////

class ConditionEffectFlagFactory : public ConditionFactory 
{
public:
    virtual ConditionType_t getConditionType()  { return Condition::CONDITION_EFFECT_FLAG; }
    virtual Condition* createCondition()  { return new ConditionEffectFlag(); }
    virtual string getConditionName()  { return "EffectFlag"; }
};

#endif
