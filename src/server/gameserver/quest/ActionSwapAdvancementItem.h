//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionSwapAdvancementItem.h
// Written By  : excel96
// Description : 
// Creature�� PC���� ������ ������. �� ���� NPC ��ȭâ�� ��µȴ�.
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_SWAP_ADVANCEMENT_ITEM_H__
#define __ACTION_SWAP_ADVANCEMENT_ITEM_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionSwapAdvancementItem
//////////////////////////////////////////////////////////////////////////////

class ActionSwapAdvancementItem : public Action 
{
public:
	virtual ActionType_t getActionType()  { return ACTION_SWAP_ADVANCEMENT_ITEM; }
	virtual void read(PropertyBuffer & propertyBuffer);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL);
	virtual string toString() ;
};


//////////////////////////////////////////////////////////////////////////////
// class ActionSwapAdvancementItemFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionSwapAdvancementItemFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType()  { return Action::ACTION_SWAP_ADVANCEMENT_ITEM; }
	virtual string getActionName()  { return "SwapAdvancementItem"; }
	virtual Action* createAction()  { return new ActionSwapAdvancementItem(); }
};
#endif
