//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionCancelEventQuestScript.h
// Written By  : excel96
// Description : 
// Creature�� PC���� ������ ������. �� ���� NPC ��ȭâ�� ��µȴ�.
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_CANCEL_EVENT_QUEST_SCRIPT_H__
#define __ACTION_CANCEL_EVENT_QUEST_SCRIPT_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionCancelEventQuestScript
//////////////////////////////////////////////////////////////////////////////

class ActionCancelEventQuestScript : public Action 
{
public:
	virtual ActionType_t getActionType()  { return ACTION_CANCEL_EVENT_QUEST_SCRIPT; }
	virtual void read(PropertyBuffer & propertyBuffer);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL);
	virtual string toString() ;

public:
	ScriptID_t getScriptID( int index )  { return m_ScriptID[index]; }
	void setScriptID( int index, ScriptID_t scriptID ) throw() { m_ScriptID[index] = scriptID; }

private:
	ScriptID_t m_ScriptID[5];   // ���� ��� ���̵�
	ScriptID_t m_CounterScriptID;
	ScriptID_t m_SuccessScriptID;
};


//////////////////////////////////////////////////////////////////////////////
// class ActionCancelEventQuestScriptFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionCancelEventQuestScriptFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType()  { return Action::ACTION_CANCEL_EVENT_QUEST_SCRIPT; }
	virtual string getActionName()  { return "CancelEventQuestScript"; }
	virtual Action* createAction()  { return new ActionCancelEventQuestScript(); }
};
#endif
