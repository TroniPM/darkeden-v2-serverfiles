//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionAcceptApartCouple.h
// Written By  : excel96
// Description : 
// Creature�� PC���� ������ ������. �� ���� NPC ��ȭâ�� ��µȴ�.
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_ACCEPT_APART_COUPLE_H__
#define __ACTION_ACCEPT_APART_COUPLE_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionAcceptApartCouple
//////////////////////////////////////////////////////////////////////////////

class ActionAcceptApartCouple : public Action 
{
public:
	virtual ActionType_t getActionType() const throw() { return ACTION_ACCEPT_APART_COUPLE; }
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) throw(Error);
	virtual string toString() const throw();

public:

private:
};


//////////////////////////////////////////////////////////////////////////////
// class ActionAcceptApartCoupleFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionAcceptApartCoupleFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType() const throw() { return Action::ACTION_ACCEPT_APART_COUPLE; }
	virtual string getActionName() const throw() { return "AcceptApartCouple"; }
	virtual Action* createAction() const throw() { return new ActionAcceptApartCouple(); }
};
#endif
