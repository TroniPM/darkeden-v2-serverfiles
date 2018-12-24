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
	virtual ActionType_t getActionType() const throw() { return ACTION_RESTORE; }
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) throw(Error);
	virtual string toString() const throw();

private :

};

//////////////////////////////////////////////////////////////////////////////
// class ActionRestoreFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionRestoreFactory : public ActionFactory 
{
public:
    virtual ActionType_t getActionType() const throw() { return Action::ACTION_RESTORE; }
    virtual Action* createAction() const throw() { return new ActionRestore(); }
    virtual string getActionName() const throw() { return "Restore"; }

};

#endif
