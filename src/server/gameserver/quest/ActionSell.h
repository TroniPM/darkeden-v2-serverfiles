//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionSell.h
// Written By  : 
// Description : 
// NPC�� �������� �÷��̾�� �Ĵ� �׼��̴�. �����δ� �ŷ���
// �����ϰ� ����� �׼��̸�, �ϴ� ���� �÷��̾�� ���� NPC��
// ���� ������ ��Ŷ���� �����ִ� �� ���̴�.
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_SELL_H__
#define __ACTION_SELL_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionSell
//////////////////////////////////////////////////////////////////////////////

class ActionSell : public Action 
{
public:
	virtual ActionType_t getActionType() const throw() { return ACTION_SELL; }
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) throw(Error);
	virtual string toString() const throw();
};

//////////////////////////////////////////////////////////////////////////////
// class AskFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionSellFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType() const throw() { return Action::ACTION_SELL; }
	virtual string getActionName() const throw() { return "Sell"; }
	virtual Action* createAction() const throw() { return new ActionSell(); }
};

#endif
