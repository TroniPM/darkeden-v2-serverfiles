////////////////////////////////////////////////////////////////////////////////
// Filename    : ConditionHasInvenSpace.h
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#ifndef __PC_HAS_EFFECT_H__
#define __PC_HAS_EFFECT_H__

#include "Condition.h"
#include "ConditionFactory.h"
#include "Creature.h"

//////////////////////////////////////////////////////////////////////////////
// class ConditionHasInvenSpace;
//////////////////////////////////////////////////////////////////////////////

class ConditionPcHasEffect : public Condition 
{
public:
	virtual ConditionType_t getConditionType() const throw() { return CONDITION_PC_HAS_EFFECT; }
	virtual bool isPassive() const throw() { return true; }
	virtual bool isSatisfied(Creature* pNPC, Creature* pPC = NULL, void* pParam = NULL) const throw();
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual string toString() const throw();
private:
	int m_EffectClass;
};

//////////////////////////////////////////////////////////////////////////////
// class ConditionHasInvenSpaceFactory;
//////////////////////////////////////////////////////////////////////////////

class ConditionPcHasEffectFactory : public ConditionFactory 
{
public:
    virtual ConditionType_t getConditionType() const throw() { return Condition::CONDITION_PC_HAS_EFFECT; }
    virtual Condition* createCondition() const throw() { return new ConditionPcHasEffect(); }
    virtual string getConditionName() const throw() { return "PcHasEffect"; }
};

#endif
