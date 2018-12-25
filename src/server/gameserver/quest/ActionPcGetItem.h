//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionPcGetItem.h
// Written By  : excel96
// Description : 
// Creature가 PC에게 질문을 던진다. 이 대사는 NPC 대화창에 출력된다.
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_PC_GETITEM_H__
#define __ACTION_PC_GETITEM_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"
#include "Item.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionPcGetItem
//////////////////////////////////////////////////////////////////////////////

class ActionPcGetItem : public Action 
{
public:
	virtual ActionType_t getActionType()  { return ACTION_PC_GETITEM; }
	virtual void read(PropertyBuffer & propertyBuffer);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL);
	virtual string toString() ;

public:
private:
	// 재료가 기반이 되는 아이템을 위한 선언.
	Item::ItemClass m_ItemClass;
	ItemType_t		m_ItemType;
	ItemNum_t		m_ItemNum;

	// 지급 아이템 선언.
	Item::ItemClass m_GItemClass;
	ItemType_t		m_GItemType;
	ItemNum_t		m_GItemNum;
};


//////////////////////////////////////////////////////////////////////////////
// class ActionPcGetItemFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionPcGetItemFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType()  { return Action::ACTION_PC_GETITEM; }
	virtual string getActionName()  { return "PcGetItem"; }
	virtual Action* createAction()  { return new ActionPcGetItem(); }
};
#endif
