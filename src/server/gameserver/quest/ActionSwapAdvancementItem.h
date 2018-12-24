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
	virtual ActionType_t getActionType() const throw() { return ACTION_SWAP_ADVANCEMENT_ITEM; }
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) throw(Error);
	virtual string toString() const throw();
};


//////////////////////////////////////////////////////////////////////////////
// class ActionSwapAdvancementItemFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionSwapAdvancementItemFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType() const throw() { return Action::ACTION_SWAP_ADVANCEMENT_ITEM; }
	virtual string getActionName() const throw() { return "SwapAdvancementItem"; }
	virtual Action* createAction() const throw() { return new ActionSwapAdvancementItem(); }
};
#endif
