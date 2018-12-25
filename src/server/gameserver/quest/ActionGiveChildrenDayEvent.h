/////////////////////////////////////////////////////////////////////////////
//
//
//
//
//
//
/////////////////////////////////////////////////////////////////////////////
#ifndef __ACTION_GIVE_CHILDREN_EVENT_ITEM_H__
#define __ACTION_GIVE_CHILDREN_EVENT_ITEM_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionGiveChildrenEvent
//////////////////////////////////////////////////////////////////////////////

class ActionGiveChildrenEvent : public Action 
{
public:
	virtual ActionType_t getActionType()  { return ACTION_GIVE_CHILDREN_EVENT_ITEM; }
	virtual void read(PropertyBuffer & propertyBuffer);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL);
	virtual string toString() ;
};


//////////////////////////////////////////////////////////////////////////////
// class ActionGiveChildrenEventFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionGiveChildrenEventFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType()  { return Action::ACTION_GIVE_CHILDREN_EVENT_ITEM; }
	virtual string getActionName()  { return "GiveChildrenEventItem"; }
	virtual Action* createAction()  { return new ActionGiveChildrenEvent(); }
};

#endif
