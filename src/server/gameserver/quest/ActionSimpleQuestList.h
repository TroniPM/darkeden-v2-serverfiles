//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionSimpleQuestList.h
// Written By  : excel96
// Description : 
// Creature�� PC���� ������ ������. �� ���� NPC ��ȭâ�� ��µȴ�.
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_SIMPLE_QUEST_LIST_H__
#define __ACTION_SIMPLE_QUEST_LIST_H__

#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionSimpleQuestList
//////////////////////////////////////////////////////////////////////////////

class ActionSimpleQuestList : public Action 
{
public:
	virtual ActionType_t getActionType() const throw() { return ACTION_SIMPLE_QUEST_LIST; }
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) throw(Error);
	virtual string toString() const throw();

public:
	ScriptID_t getScriptID() const throw() { return m_ScriptID; }
	void setScriptID(ScriptID_t scriptID) throw() { m_ScriptID = scriptID; }

private:
	ScriptID_t m_ScriptID;   // ���� ��� ���̵�
};


//////////////////////////////////////////////////////////////////////////////
// class ActionSimpleQuestListFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionSimpleQuestListFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType() const throw() { return Action::ACTION_SIMPLE_QUEST_LIST; }
	virtual string getActionName() const throw() { return "SimpleQuestList"; }
	virtual Action* createAction() const throw() { return new ActionSimpleQuestList(); }
};

#endif
