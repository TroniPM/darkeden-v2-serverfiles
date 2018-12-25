//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionPcGetItem.h
// Written By  : excel96
// Description : 
// Creature가 PC에게 질문을 던진다. 이 대사는 NPC 대화창에 출력된다.
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_DELETE_GETITEM_H__
#define __ACTION_DELETE_GETITEM_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"
#include "Item.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionPcGetItem
//////////////////////////////////////////////////////////////////////////////

class ActionDeleteGetItem : public Action 
{
public:
	virtual ActionType_t getActionType()  { return ACTION_DELETE_GETITEM; }
	virtual void read(PropertyBuffer & propertyBuffer);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL);
	virtual string toString() ;

public:
private:
	// 재료가 기반이 되는 아이템을 위한 선언.
	Item::ItemClass m_ItemClass;
	ItemType_t		m_ItemType;
	ItemNum_t		m_ItemNum;
};


//////////////////////////////////////////////////////////////////////////////
// class ActionPcGetItemFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionDeleteGetItemFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType()  { return Action::ACTION_DELETE_GETITEM; }
	virtual string getActionName()  { return "DeleteGetItem"; }
	virtual Action* createAction()  { return new ActionDeleteGetItem(); }
};
#endif
