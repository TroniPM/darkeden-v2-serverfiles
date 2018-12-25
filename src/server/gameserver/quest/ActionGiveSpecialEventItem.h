//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionGiveSpecialEventItem.h
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_GIVE_SPECIAL_EVENT_ITEM_H__
#define __ACTION_GIVE_SPECIAL_EVENT_ITEM_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionGiveSpecialEventItem
//////////////////////////////////////////////////////////////////////////////

class ActionGiveSpecialEventItem : public Action 
{
public:
	virtual ActionType_t getActionType()  { return ACTION_GIVE_SPECIAL_EVENT_ITEM; }
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) throw(Error);
	virtual string toString() ;
};


//////////////////////////////////////////////////////////////////////////////
// class ActionGiveSpecialEventItemFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionGiveSpecialEventItemFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType()  { return Action::ACTION_GIVE_SPECIAL_EVENT_ITEM; }
	virtual string getActionName()  { return "GiveSpecialEventItem"; }
	virtual Action* createAction()  { return new ActionGiveSpecialEventItem(); }
};

#endif
