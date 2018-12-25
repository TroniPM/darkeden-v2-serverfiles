//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionGiveQuestItem.h
// Written By  : excel96
// Description : 
// Creature�� PC���� ������ ������. �� ���� NPC ��ȭâ�� ��µȴ�.
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_GIVE_QUEST_ITEM_H__
#define __ACTION_GIVE_QUEST_ITEM_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionGiveQuestItem
//////////////////////////////////////////////////////////////////////////////

class ActionGiveQuestItem : public Action 
{
public:
	virtual ActionType_t getActionType()  { return ACTION_GIVE_QUEST_ITEM; }
	virtual void read(PropertyBuffer & propertyBuffer);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL);
	virtual string toString() ;

public:

private:
	ScriptID_t	m_CounterScriptID;
};


//////////////////////////////////////////////////////////////////////////////
// class ActionGiveQuestItemFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionGiveQuestItemFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType()  { return Action::ACTION_GIVE_QUEST_ITEM; }
	virtual string getActionName()  { return "GiveQuestItem"; }
	virtual Action* createAction()  { return new ActionGiveQuestItem(); }
};
#endif
