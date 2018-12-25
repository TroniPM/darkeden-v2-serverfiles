//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionSilverCoating.h
// Written By  : 
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_SILVER_COATING_H__
#define __ACTION_SILVER_COATING_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionSilverCoating;
//////////////////////////////////////////////////////////////////////////////

class ActionSilverCoating : public Action 
{
public:
	virtual ActionType_t getActionType()  { return ACTION_SILVER_COATING; }
	virtual void read(PropertyBuffer & propertyBuffer);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL);
	virtual string toString() ;
};

//////////////////////////////////////////////////////////////////////////////
// class ActionSilverCoatingFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionSilverCoatingFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType()  { return Action::ACTION_SILVER_COATING; }
	virtual string getActionName()  { return "SilverCoating"; }
	virtual Action* createAction()  { return new ActionSilverCoating(); }
};

#endif
