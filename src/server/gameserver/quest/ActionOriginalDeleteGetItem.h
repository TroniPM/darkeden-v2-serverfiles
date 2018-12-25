//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionPcGetItem.h
// Written By  : excel96
// Description : 
// Creature�� PC���� ������ ������. �� ���� NPC ��ȭâ�� ��µȴ�.
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_ORIGINAL_DELETE_GETITEM_H__
#define __ACTION_ORIGINAL_DELETE_GETITEM_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"
#include "Item.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionPcGetItem
//////////////////////////////////////////////////////////////////////////////

class ActionOriginalDeleteGetItem : public Action 
{
public:
	virtual ActionType_t getActionType()  { return ACTION_ORIGINAL_DELETE_GETITEM; }
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) throw(Error);
	virtual string toString() ;

public:
private:
	// ��ᰡ ����� �Ǵ� �������� ���� ����.
	Item::ItemClass m_ItemClass;
	ItemType_t		m_ItemType;
	ItemNum_t		m_ItemNum;
};


//////////////////////////////////////////////////////////////////////////////
// class ActionPcGetItemFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionOriginalDeleteGetItemFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType()  { return Action::ACTION_ORIGINAL_DELETE_GETITEM; }
	virtual string getActionName()  { return "OriginalDeleteGetItem"; }
	virtual Action* createAction()  { return new ActionOriginalDeleteGetItem(); }
};
#endif
