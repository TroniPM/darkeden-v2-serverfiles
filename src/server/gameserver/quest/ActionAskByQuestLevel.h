//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionAskByQuestLevel.h
// Written By  : excel96
// Description : 
// Creature�� PC���� ������ ������. �� ���� NPC ��ȭâ�� ��µȴ�.
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_ASK_BY_QUEST_LEVEL_H__
#define __ACTION_ASK_BY_QUEST_LEVEL_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionAskByQuestLevel
//////////////////////////////////////////////////////////////////////////////

class ActionAskByQuestLevel : public Action 
{
public:
	virtual ActionType_t getActionType()  { return ACTION_ASK_BY_QUEST_LEVEL; }
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) throw(Error);
	virtual string toString() ;

public:
	ScriptID_t getScriptID( int index )  { return m_ScriptID[index]; }
	void setScriptID( int index, ScriptID_t scriptID ) throw() { m_ScriptID[index] = scriptID; }

private:
	ScriptID_t m_ScriptID[5];   // ���� ��� ���̵�
};


//////////////////////////////////////////////////////////////////////////////
// class ActionAskByQuestLevelFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionAskByQuestLevelFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType()  { return Action::ACTION_ASK_BY_QUEST_LEVEL; }
	virtual string getActionName()  { return "AskByQuestLevel"; }
	virtual Action* createAction()  { return new ActionAskByQuestLevel(); }
};
#endif
