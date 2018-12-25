//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionTurnOffFlag.h
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_TURN_OFF_FLAG_H__
#define __ACTION_TURN_OFF_FLAG_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionTurnOffFlag
//////////////////////////////////////////////////////////////////////////////

class ActionTurnOffFlag : public Action 
{
public:
	virtual ActionType_t getActionType()  { return ACTION_TURN_OFF_FLAG; }
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) throw(Error);
	virtual string toString() ;

private:
	uint m_Index;
};


//////////////////////////////////////////////////////////////////////////////
// class ActionTurnOffFlagFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionTurnOffFlagFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType()  { return Action::ACTION_TURN_OFF_FLAG; }
	virtual string getActionName()  { return "TurnOffFlag"; }
	virtual Action* createAction()  { return new ActionTurnOffFlag(); }
};

#endif
