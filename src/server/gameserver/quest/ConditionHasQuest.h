////////////////////////////////////////////////////////////////////////////////
// Filename    : ConditionHasQuest.h
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#ifndef __HAS_QUEST_H__
#define __HAS_QUEST_H__

#include "Condition.h"
#include "ConditionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ConditionHasQuest;
//////////////////////////////////////////////////////////////////////////////

class ConditionHasQuest : public Condition 
{
public:
	ConditionHasQuest() throw();
	virtual ~ConditionHasQuest() throw();

public:
	virtual ConditionType_t getConditionType()  { return CONDITION_HAS_QUEST; }
	virtual bool isPassive()  { return true; }
	virtual bool isSatisfied(Creature* pNPC, Creature* pPC = NULL, void* pParam = NULL) ;
	virtual void read(PropertyBuffer & propertyBuffer);
	virtual string toString() ;

private:
	QuestID_t m_QuestID;
};

//////////////////////////////////////////////////////////////////////////////
// class ConditionHasQuestFactory;
//////////////////////////////////////////////////////////////////////////////

class ConditionHasQuestFactory : public ConditionFactory 
{
public:
    virtual ConditionType_t getConditionType()  { return Condition::CONDITION_HAS_QUEST; }
    virtual Condition* createCondition()  { return new ConditionHasQuest(); }
    virtual string getConditionName()  { return "HasQuest"; }
};

#endif
