//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionStashSell.h
// Written By  : 
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_STASH_SELL_H__
#define __ACTION_STASH_SELL_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionStashSell;
//////////////////////////////////////////////////////////////////////////////

class ActionStashSell : public Action 
{
public:
	virtual ActionType_t getActionType()  { return ACTION_STASH_SELL; }
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) throw(Error);
	virtual string toString() ;

};

//////////////////////////////////////////////////////////////////////////////
// class ActionStashSellFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionStashSellFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType()  { return Action::ACTION_STASH_SELL; }
	virtual string getActionName()  { return "StashSell"; }
	virtual Action* createAction()  { return new ActionStashSell(); }

};

#endif
