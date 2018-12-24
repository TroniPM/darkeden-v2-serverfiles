//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionStartEventQuest.h
// Written By  : excel96
// Description : 
// Creature�� PC���� ������ ������. �� ���� NPC ��ȭâ�� ��µȴ�.
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_START_EVENT_QUEST_H__
#define __ACTION_START_EVENT_QUEST_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionStartEventQuest
//////////////////////////////////////////////////////////////////////////////

class ActionStartEventQuest : public Action 
{
public:
	virtual ActionType_t getActionType() const throw() { return ACTION_START_EVENT_QUEST; }
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) throw(Error);
	virtual string toString() const throw();

public:
private:
	int		m_QuestLevel;
};


//////////////////////////////////////////////////////////////////////////////
// class ActionStartEventQuestFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionStartEventQuestFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType() const throw() { return Action::ACTION_START_EVENT_QUEST; }
	virtual string getActionName() const throw() { return "StartEventQuest"; }
	virtual Action* createAction() const throw() { return new ActionStartEventQuest(); }
};
#endif
