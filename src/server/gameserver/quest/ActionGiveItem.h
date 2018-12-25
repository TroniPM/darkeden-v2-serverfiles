//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionGiveItem.h
// Written By  : excel96
// Description : 
// Creature가 PC에게 질문을 던진다. 이 대사는 NPC 대화창에 출력된다.
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_GIVE_ITEM_H__
#define __ACTION_GIVE_ITEM_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"
#include "Item.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionGiveItem
//////////////////////////////////////////////////////////////////////////////

class ActionGiveItem : public Action 
{
public:
	virtual ActionType_t getActionType()  { return ACTION_GIVE_ITEM; }
	virtual void read(PropertyBuffer & propertyBuffer);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL);
	virtual string toString() ;

public:
private:
	Item::ItemClass m_ItemClass;
	ItemType_t		m_ItemType;
};


//////////////////////////////////////////////////////////////////////////////
// class ActionGiveItemFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionGiveItemFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType()  { return Action::ACTION_GIVE_ITEM; }
	virtual string getActionName()  { return "GiveItem"; }
	virtual Action* createAction()  { return new ActionGiveItem(); }
};
#endif
