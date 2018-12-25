//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionBuy.h
// Written By  : excel96
// Description : 
// NPC�� �÷��̾�κ��� �������� ����̴� �׼��̴�. Sell �׼ǰ� ���������� 
// Ư���� �ϴ� ���� ����, ���� �÷��̾�� ���� ������ ������ ��Ŷ���� 
// �����ִ� ������ �Ѵ�.
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_BUY_H__
#define __ACTION_BUY_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionBuy
//////////////////////////////////////////////////////////////////////////////

class ActionBuy : public Action 
{
public:
	virtual ActionType_t getActionType()  { return ACTION_BUY; }
	virtual void read(PropertyBuffer & propertyBuffer);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL);
	virtual string toString() ;
};


//////////////////////////////////////////////////////////////////////////////
// class AskFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionBuyFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType()  { return Action::ACTION_BUY; }
	virtual string getActionName()  { return "Buy"; }
	virtual Action* createAction()  { return new ActionBuy(); }
};


#endif
