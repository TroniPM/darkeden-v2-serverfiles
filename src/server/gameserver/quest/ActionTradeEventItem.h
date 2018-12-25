//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionTradeEventItem.h
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_TRADE_EVENT_ITEM_H__
#define __ACTION_TRADE_EVENT_ITEM_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionTradeEventItem
//////////////////////////////////////////////////////////////////////////////

class ActionTradeEventItem : public Action 
{
public:
	virtual ActionType_t getActionType()  { return ACTION_TRADE_EVENT_ITEM; }
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) throw(Error);
	virtual string toString() ;
public:
	int getAmount(void) const { return m_GoalAmount; }
	void setAmount(int amount) { m_GoalAmount = amount; }

private:
	int m_GoalAmount; // ���� �౸���� ��
}
;


//////////////////////////////////////////////////////////////////////////////
// class ActionTradeEventItemFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionTradeEventItemFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType()  { return Action::ACTION_TRADE_EVENT_ITEM; }
	virtual string getActionName()  { return "TradeEventItem"; }
	virtual Action* createAction()  { return new ActionTradeEventItem(); }
};

#endif
