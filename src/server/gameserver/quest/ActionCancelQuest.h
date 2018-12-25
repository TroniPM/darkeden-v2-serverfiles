//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionCancelQuest.h
// Written By  : excel96
// Description : 
// Creature�� PC���� ������ ������. �� ���� NPC ��ȭâ�� ��µȴ�.
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_CANCEL_QUEST_H__
#define __ACTION_CANCEL_QUEST_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionCancelQuest
//////////////////////////////////////////////////////////////////////////////

class ActionCancelQuest : public Action 
{
public:
	virtual ActionType_t getActionType()  { return ACTION_CANCEL_QUEST; }
	virtual void read(PropertyBuffer & propertyBuffer);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL);
	virtual string toString() ;

public:
private:
	ScriptID_t	m_ScriptID;
	ScriptID_t	m_CounterScriptID;
};


//////////////////////////////////////////////////////////////////////////////
// class ActionCancelQuestFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionCancelQuestFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType()  { return Action::ACTION_CANCEL_QUEST; }
	virtual string getActionName()  { return "CancelQuest"; }
	virtual Action* createAction()  { return new ActionCancelQuest(); }
};
#endif
