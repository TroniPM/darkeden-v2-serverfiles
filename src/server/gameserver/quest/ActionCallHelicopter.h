//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionCallHelicopter.h
// Written By  : 
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_CALL_HELICOPTER_H__
#define __ACTION_CALL_HELICOPTER_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionCallHelicopter;
//////////////////////////////////////////////////////////////////////////////

class ActionCallHelicopter : public Action 
{
public:
	virtual ActionType_t getActionType()  { return ACTION_CALL_HELICOPTER; }
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) throw(Error);
	virtual string toString() ;
};

//////////////////////////////////////////////////////////////////////////////
// class ActionCallHelicopterFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionCallHelicopterFactory : public ActionFactory 
{
public:
    virtual ActionType_t getActionType()  { return Action::ACTION_CALL_HELICOPTER; }
	virtual string getActionName()  { return "CallHelicopter"; }
    virtual Action* createAction()  { return new ActionCallHelicopter(); }
};

#endif
