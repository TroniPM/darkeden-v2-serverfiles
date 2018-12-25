//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionWaitForApartCouple.h
// Written By  : excel96
// Description : 
// Creature�� PC���� ������ ������. �� ���� NPC ��ȭâ�� ��µȴ�.
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_WAIT_FOR_APART_COUPLE_H__
#define __ACTION_WAIT_FOR_APART_COUPLE_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionWaitForApartCouple
//////////////////////////////////////////////////////////////////////////////

class ActionWaitForApartCouple : public Action 
{
public:
	virtual ActionType_t getActionType()  { return ACTION_WAIT_FOR_APART_COUPLE; }
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) throw(Error);
	virtual string toString() ;

public:

private:
};


//////////////////////////////////////////////////////////////////////////////
// class ActionWaitForApartCoupleFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionWaitForApartCoupleFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType()  { return Action::ACTION_WAIT_FOR_APART_COUPLE; }
	virtual string getActionName()  { return "WaitForApartCouple"; }
	virtual Action* createAction()  { return new ActionWaitForApartCouple(); }
};
#endif
