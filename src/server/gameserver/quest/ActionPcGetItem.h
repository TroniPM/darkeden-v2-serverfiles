//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionPcGetItem.h
// Written By  : excel96
// Description : 
// Creature�� PC���� ������ ������. �� ���� NPC ��ȭâ�� ��µȴ�.
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
	// ��ᰡ ����� �Ǵ� �������� ���� ����.
	Item::ItemClass m_ItemClass;
	ItemType_t		m_ItemType;
	ItemNum_t		m_ItemNum;

	// ���� ������ ����.
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
