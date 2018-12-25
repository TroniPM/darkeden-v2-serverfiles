////////////////////////////////////////////////////////////////////////////////
// Filename    : ConditionCanPetQuest.h
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#ifndef __CAN_PET_QUEST_H__
#define __CAN_PET_QUEST_H__

#include "Condition.h"
#include "ConditionFactory.h"
#include "Creature.h"

//////////////////////////////////////////////////////////////////////////////
// class ConditionCanPetQuest;
//////////////////////////////////////////////////////////////////////////////

class ConditionCanPetQuest : public Condition 
{
public:
	virtual ConditionType_t getConditionType()  { return CONDITION_CAN_PET_QUEST; }
	virtual bool isPassive()  { return true; }
	virtual bool isSatisfied(Creature* pNPC, Creature* pPC = NULL, void* pParam = NULL) ;
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual string toString() ;

public:

};

//////////////////////////////////////////////////////////////////////////////
// class ConditionCanPetQuestFactory;
//////////////////////////////////////////////////////////////////////////////

class ConditionCanPetQuestFactory : public ConditionFactory 
{
public:
    virtual ConditionType_t getConditionType()  { return Condition::CONDITION_CAN_PET_QUEST; }
    virtual Condition* createCondition()  { return new ConditionCanPetQuest(); }
    virtual string getConditionName()  { return "CanPetQuest"; }
};

#endif
