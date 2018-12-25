//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionSimpleQuestComplete.h
// Written By  : excel96
// Description : 
// Creature가 PC에게 질문을 던진다. 이 대사는 NPC 대화창에 출력된다.
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
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) throw(Error);
	virtual string toString() ;

public:
	ScriptID_t getScriptID()  { return m_ScriptID; }
	void setScriptID(ScriptID_t scriptID) throw() { m_ScriptID = scriptID; }

private:
	ScriptID_t m_ScriptID;   // 말할 대사 아이디
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
