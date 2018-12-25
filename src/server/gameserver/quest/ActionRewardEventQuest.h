//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionRewardEventQuest.h
// Written By  : excel96
// Description : 
// Creature�� PC���� ������ ������. �� ���� NPC ��ȭâ�� ��µȴ�.
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_REWARD_EVENT_QUEST_H__
#define __ACTION_REWARD_EVENT_QUEST_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionRewardEventQuest
//////////////////////////////////////////////////////////////////////////////

class ActionRewardEventQuest : public Action 
{
public:
	virtual ActionType_t getActionType()  { return ACTION_REWARD_EVENT_QUEST; }
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) throw(Error);
	virtual string toString() ;

public:
	ScriptID_t getScriptID( int index )  { return m_ScriptID[index]; }
	void setScriptID( int index, ScriptID_t scriptID ) throw() { m_ScriptID[index] = scriptID; }

private:
	ScriptID_t m_ScriptID[5];   // ���� ��� ���̵�
	ScriptID_t m_CounterScriptID;	// ����Ʈ�� �Ϸ���� �ʾ��� ��
	ScriptID_t m_CancelScriptID;	// ���� �ܰ� ����Ʈ�� ������ ���� ��
};


//////////////////////////////////////////////////////////////////////////////
// class ActionRewardEventQuestFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionRewardEventQuestFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType()  { return Action::ACTION_REWARD_EVENT_QUEST; }
	virtual string getActionName()  { return "RewardEventQuest"; }
	virtual Action* createAction()  { return new ActionRewardEventQuest(); }
};
#endif
