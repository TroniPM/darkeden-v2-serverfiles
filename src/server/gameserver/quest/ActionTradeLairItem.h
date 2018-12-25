//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionTradeLairItem.h
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_TRADE_LAIR_ITEM_H__
#define __ACTION_TRADE_LAIR_ITEM_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionTradeLairItem
//////////////////////////////////////////////////////////////////////////////

const int BATORI_TYPE = 44;
const int TEPEZ_TYPE  = 45;
const int GDR_TYPE  = 46;

class ActionTradeLairItem : public Action 
{
public:
	virtual ActionType_t getActionType()  { return ACTION_TRADE_LAIR_ITEM; }
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) throw(Error);
	virtual string toString() ;
public:
	int getType(void) const { return m_Type; }
	void setType(int type) { m_Type = type; }

private:
	ItemType_t m_Type; // 받을 축구공의 수
}
;


//////////////////////////////////////////////////////////////////////////////
// class ActionTradeLairItemFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionTradeLairItemFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType()  { return Action::ACTION_TRADE_LAIR_ITEM; }
	virtual string getActionName()  { return "TradeLairItem"; }
	virtual Action* createAction()  { return new ActionTradeLairItem(); }
};

#endif
