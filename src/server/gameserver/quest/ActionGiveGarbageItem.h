//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionGiveGarbageEventItem.h
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_GIVE_GARBAGE_EVENT_ITEM_H__
#define __ACTION_GIVE_GARBAGE_EVENT_ITEM_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionGiveGarbageEventItem
//////////////////////////////////////////////////////////////////////////////

class ActionGiveGarbageEventItem : public Action 
{
public:
	virtual ActionType_t getActionType()  { return ACTION_GIVE_GARBAGE_EVENT_ITEM; }
	virtual void read(PropertyBuffer & propertyBuffer);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL);
	virtual string toString() ;
};


//////////////////////////////////////////////////////////////////////////////
// class ActionGiveGarbageEventItemFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionGiveGarbageEventItemFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType()  { return Action::ACTION_GIVE_GARBAGE_EVENT_ITEM; }
	virtual string getActionName()  { return "GiveGarbageEventItem"; }
	virtual Action* createAction()  { return new ActionGiveGarbageEventItem(); }
};

#endif
