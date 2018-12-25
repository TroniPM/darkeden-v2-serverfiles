//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionInitEventQuest.h
// Written By  : excel96
// Description : 
// Creature가 PC에게 질문을 던진다. 이 대사는 NPC 대화창에 출력된다.
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_INIT_EVENT_QUEST_H__
#define __ACTION_INIT_EVENT_QUEST_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionInitEventQuest
//////////////////////////////////////////////////////////////////////////////

class ActionInitEventQuest : public Action 
{
public:
	virtual ActionType_t getActionType()  { return ACTION_INIT_EVENT_QUEST; }
	virtual void read(PropertyBuffer & propertyBuffer);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL);
	virtual string toString() ;

public:
private:
};


//////////////////////////////////////////////////////////////////////////////
// class ActionInitEventQuestFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionInitEventQuestFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType()  { return Action::ACTION_INIT_EVENT_QUEST; }
	virtual string getActionName()  { return "InitEventQuest"; }
	virtual Action* createAction()  { return new ActionInitEventQuest(); }
};
#endif
