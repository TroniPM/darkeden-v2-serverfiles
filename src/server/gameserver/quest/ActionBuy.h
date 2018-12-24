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
	virtual ActionType_t getActionType() const throw() { return ACTION_BUY; }
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) throw(Error);
	virtual string toString() const throw();
};


//////////////////////////////////////////////////////////////////////////////
// class AskFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionBuyFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType() const throw() { return Action::ACTION_BUY; }
	virtual string getActionName() const throw() { return "Buy"; }
	virtual Action* createAction() const throw() { return new ActionBuy(); }
};


#endif
