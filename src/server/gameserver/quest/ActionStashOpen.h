//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionStashOpen.h
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_STASH_OPEN_H__
#define __ACTION_STASH_OPEN_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionStashOpen;
//////////////////////////////////////////////////////////////////////////////

class ActionStashOpen : public Action 
{
public:
	virtual ActionType_t getActionType()  { return ACTION_STASH_OPEN; }
	virtual void read(PropertyBuffer & propertyBuffer);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL);
	virtual string toString() ;
};


//////////////////////////////////////////////////////////////////////////////
// class ActionStashOpenFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionStashOpenFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType()  { return Action::ACTION_STASH_OPEN; }
	virtual string getActionName()  { return "StashOpen"; }
	virtual Action* createAction()  { return new ActionStashOpen(); }
};

#endif
