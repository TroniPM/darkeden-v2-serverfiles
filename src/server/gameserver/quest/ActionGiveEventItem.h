//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionGiveEventItem.h
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_GIVE_EVENT_ITEM_H__
#define __ACTION_GIVE_EVENT_ITEM_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"
#include "LuaTradeEventSlayerItem.h"
#include "LuaTradeEventVampireItem.h"
#include "FlagSet.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionGiveEventItem
//////////////////////////////////////////////////////////////////////////////

class ActionGiveEventItem : public Action 
{
public:
	ActionGiveEventItem();
	~ActionGiveEventItem();

	virtual ActionType_t getActionType()  { return ACTION_GIVE_EVENT_ITEM; }
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) throw(Error);
	virtual string toString() ;

	void						load() throw (Error);

private :
	FlagSetType					m_FlagSetType;

	LuaState*					m_pLuaState;
	LuaTradeEventSlayerItem*	m_pLuaSlayerItem;
	LuaTradeEventVampireItem*	m_pLuaVampireItem;

	string						m_CommonFilename;
	string						m_SlayerFilename;
	string						m_VampireFilename;
};


//////////////////////////////////////////////////////////////////////////////
// class ActionGiveEventItemFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionGiveEventItemFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType()  { return Action::ACTION_GIVE_EVENT_ITEM; }
	virtual string getActionName()  { return "GiveEventItem"; }
	virtual Action* createAction()  { return new ActionGiveEventItem(); }
};

#endif
