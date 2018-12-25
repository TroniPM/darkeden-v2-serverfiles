//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionRepair.h
// Written By  : 
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_REPAIR_H__
#define __ACTION_REPAIR_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionRepair;
//////////////////////////////////////////////////////////////////////////////

class ActionRepair : public Action 
{
public:
	virtual ActionType_t getActionType()  { return ACTION_REPAIR; }
	virtual void read(PropertyBuffer & propertyBuffer);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL);
	virtual string toString() ;
};


//////////////////////////////////////////////////////////////////////////////
// class ActionRepairFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionRepairFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType()  { return Action::ACTION_REPAIR; }
	virtual string getActionName()  { return "Repair"; }
	virtual Action* createAction()  { return new ActionRepair(); }
};

#endif
