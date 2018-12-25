//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionSystemMessagePerRace.h
// Written By  : 
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_SYSTEM_MESSAGE_PER_RACE_H__
#define __ACTION_SYSTEM_MESSAGE_PER_RACE_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionSystemMessagePerRace;
//////////////////////////////////////////////////////////////////////////////

class ActionSystemMessagePerRace : public Action 
{
public:
	virtual ActionType_t getActionType()  { return ACTION_SYSTEM_MESSAGE_PER_RACE; }
	virtual void read(PropertyBuffer & propertyBuffer);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL);
	virtual string toString() ;

};

//////////////////////////////////////////////////////////////////////////////
// class ActionSystemMessagePerRaceFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionSystemMessagePerRaceFactory : public ActionFactory 
{
public:
    virtual ActionType_t getActionType()  { return Action::ACTION_SYSTEM_MESSAGE_PER_RACE; }
	virtual string getActionName()  { return "SystemMessagePerRace"; }
    virtual Action* createAction()  { return new ActionSystemMessagePerRace(); }
};

#endif
