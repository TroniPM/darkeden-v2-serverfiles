//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionRestore.h
// Written By  : 
// Description : 
// �����̾ �� �÷��̾ �����̾�� �����ִ� �׼��̴�.
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_RESTORE_H__
#define __ACTION_RESTORE_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionRestore;
//////////////////////////////////////////////////////////////////////////////

class ActionRestore : public Action 
{
public:
	virtual ActionType_t getActionType()  { return ACTION_RESTORE; }
	virtual void read(PropertyBuffer & propertyBuffer);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL);
	virtual string toString() ;

private :

};

//////////////////////////////////////////////////////////////////////////////
// class ActionRestoreFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionRestoreFactory : public ActionFactory 
{
public:
    virtual ActionType_t getActionType()  { return Action::ACTION_RESTORE; }
    virtual Action* createAction()  { return new ActionRestore(); }
    virtual string getActionName()  { return "Restore"; }

};

#endif
