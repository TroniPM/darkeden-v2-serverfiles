//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionQuestReward.h
// Written By  : excel96
// Description : 
// Creature�� PC���� ������ ������. �� ���� NPC ��ȭâ�� ��µȴ�.
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_QUEST_REWARD_H__
#define __ACTION_QUEST_REWARD_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionQuestReward
//////////////////////////////////////////////////////////////////////////////

class ActionQuestReward : public Action 
{
public:
	virtual ActionType_t getActionType()  { return ACTION_QUEST_REWARD; }
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) throw(Error);
	virtual string toString() ;

public:
private:
};


//////////////////////////////////////////////////////////////////////////////
// class ActionQuestRewardFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionQuestRewardFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType()  { return Action::ACTION_QUEST_REWARD; }
	virtual string getActionName()  { return "QuestReward"; }
	virtual Action* createAction()  { return new ActionQuestReward(); }
};
#endif
