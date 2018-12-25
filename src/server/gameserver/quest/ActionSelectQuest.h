//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionSelectQuest.h
// Written By  : excel96
// Description : 
// Creature�� PC���� ������ ������. �� ���� NPC ��ȭâ�� ��µȴ�.
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_SELECT_QUEST_H__
#define __ACTION_SELECT_QUEST_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionSelectQuest
//////////////////////////////////////////////////////////////////////////////

class ActionSelectQuest : public Action 
{
public:
	virtual ActionType_t getActionType()  { return ACTION_SELECT_QUEST; }
	virtual void read(PropertyBuffer & propertyBuffer);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL);
	virtual string toString() ;

public:
private:
};


//////////////////////////////////////////////////////////////////////////////
// class ActionSelectQuestFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionSelectQuestFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType()  { return Action::ACTION_SELECT_QUEST; }
	virtual string getActionName()  { return "SelectQuest"; }
	virtual Action* createAction()  { return new ActionSelectQuest(); }
};
#endif
