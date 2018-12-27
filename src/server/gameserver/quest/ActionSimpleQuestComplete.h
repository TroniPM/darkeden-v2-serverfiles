//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionSimpleQuestComplete.h
// Written By  : excel96
// Description : 
// Creature�� PC���� ������ ������. �� ���� NPC ��ȭâ�� ��µȴ�.
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_SIMPLE_QUEST_COMPLETE_H__
#define __ACTION_SIMPLE_QUEST_COMPLETE_H__

#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionSimpleQuestComplete
//////////////////////////////////////////////////////////////////////////////

class ActionSimpleQuestComplete : public Action 
{
public:
	virtual ActionType_t getActionType()  { return ACTION_SIMPLE_QUEST_COMPLETE; }
	virtual void read(PropertyBuffer & propertyBuffer);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL);
	virtual string toString() ;

public:
	ScriptID_t getScriptID()  { return m_ScriptID; }
	void setScriptID(ScriptID_t scriptID)  { m_ScriptID = scriptID; }

private:
	ScriptID_t m_ScriptID;   // ���� ��� ���̵�
};


//////////////////////////////////////////////////////////////////////////////
// class ActionSimpleQuestCompleteFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionSimpleQuestCompleteFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType()  { return Action::ACTION_SIMPLE_QUEST_COMPLETE; }
	virtual string getActionName()  { return "SimpleQuestComplete"; }
	virtual Action* createAction()  { return new ActionSimpleQuestComplete(); }
};

#endif
