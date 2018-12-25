//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionTurnOnFlag.h
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_TURN_ON_FLAG_H__
#define __ACTION_TURN_ON_FLAG_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionTurnOnFlag
//////////////////////////////////////////////////////////////////////////////

class ActionTurnOnFlag : public Action 
{
public:
	virtual ActionType_t getActionType()  { return ACTION_TURN_ON_FLAG; }
	virtual void read(PropertyBuffer & propertyBuffer);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL);
	virtual string toString() ;

private:
	uint m_Index;
};


//////////////////////////////////////////////////////////////////////////////
// class ActionTurnOnFlagFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionTurnOnFlagFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType()  { return Action::ACTION_TURN_ON_FLAG; }
	virtual string getActionName()  { return "TurnOnFlag"; }
	virtual Action* createAction()  { return new ActionTurnOnFlag(); }
};

#endif
