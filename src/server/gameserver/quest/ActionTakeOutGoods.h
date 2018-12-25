//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionTakeOutGoods.h
// Written By  : excel96
// Description : 
// Creature�� PC���� ������ ������. �� ���� NPC ��ȭâ�� ��µȴ�.
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_TAKE_OUT_GOODS_H__
#define __ACTION_TAKE_OUT_GOODS_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionTakeOutGoods
//////////////////////////////////////////////////////////////////////////////

class ActionTakeOutGoods : public Action 
{
public:
	virtual ActionType_t getActionType()  { return ACTION_TAKE_OUT_GOODS; }
	virtual void read(PropertyBuffer & propertyBuffer);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL);
	virtual string toString() ;

public:

private:
};


//////////////////////////////////////////////////////////////////////////////
// class ActionTakeOutGoodsFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionTakeOutGoodsFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType()  { return Action::ACTION_TAKE_OUT_GOODS; }
	virtual string getActionName()  { return "TakeOutGoods"; }
	virtual Action* createAction()  { return new ActionTakeOutGoods(); }
};
#endif
