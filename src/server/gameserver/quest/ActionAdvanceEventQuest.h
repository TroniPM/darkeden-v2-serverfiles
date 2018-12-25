//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionAdvanceEventQuest.h
// Written By  : excel96
// Description : 
// Creature�� PC���� ������ ������. �� ���� NPC ��ȭâ�� ��µȴ�.
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_ADVANCE_EVENT_QUEST_H__
#define __ACTION_ADVANCE_EVENT_QUEST_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionAdvanceEventQuest
//////////////////////////////////////////////////////////////////////////////

class ActionAdvanceEventQuest : public Action 
{
public:
	virtual ActionType_t getActionType()  { return ACTION_ADVANCE_EVENT_QUEST; }
	virtual void read(PropertyBuffer & propertyBuffer);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL);
	virtual string toString() ;

public:
private:
	int		m_QuestLevel;
};


//////////////////////////////////////////////////////////////////////////////
// class ActionAdvanceEventQuestFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionAdvanceEventQuestFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType()  { return Action::ACTION_ADVANCE_EVENT_QUEST; }
	virtual string getActionName()  { return "AdvanceEventQuest"; }
	virtual Action* createAction()  { return new ActionAdvanceEventQuest(); }
};
#endif
