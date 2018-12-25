//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionGiveEventQuestScript.h
// Written By  : excel96
// Description : 
// Creature�� PC���� ������ ������. �� ���� NPC ��ȭâ�� ��µȴ�.
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_GIVE_EVENT_QUEST_SCRIPT_H__
#define __ACTION_GIVE_EVENT_QUEST_SCRIPT_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionGiveEventQuestScript
//////////////////////////////////////////////////////////////////////////////

class ActionGiveEventQuestScript : public Action 
{
public:
	virtual ActionType_t getActionType()  { return ACTION_GIVE_EVENT_QUEST_SCRIPT; }
	virtual void read(PropertyBuffer & propertyBuffer);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL);
	virtual string toString() ;

public:
	ScriptID_t getScriptID( int index )  { return m_ScriptID[index]; }
	void setScriptID( int index, ScriptID_t scriptID ) throw() { m_ScriptID[index] = scriptID; }

private:
	ScriptID_t m_ScriptID[5];   // ���� ��� ���̵�
	ScriptID_t m_NotComplete;
	ScriptID_t m_Success;
};


//////////////////////////////////////////////////////////////////////////////
// class ActionGiveEventQuestScriptFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionGiveEventQuestScriptFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType()  { return Action::ACTION_GIVE_EVENT_QUEST_SCRIPT; }
	virtual string getActionName()  { return "GiveEventQuestScript"; }
	virtual Action* createAction()  { return new ActionGiveEventQuestScript(); }
};
#endif
