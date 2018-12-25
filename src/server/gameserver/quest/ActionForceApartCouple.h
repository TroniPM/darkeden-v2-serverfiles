//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionForceApartCouple.h
// Written By  : excel96
// Description : 
// Creature�� PC���� ������ ������. �� ���� NPC ��ȭâ�� ��µȴ�.
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_FORCE_APART_COUPLE_H__
#define __ACTION_FORCE_APART_COUPLE_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionForceApartCouple
//////////////////////////////////////////////////////////////////////////////

class ActionForceApartCouple : public Action 
{
public:
	virtual ActionType_t getActionType()  { return ACTION_FORCE_APART_COUPLE; }
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) throw(Error);
	virtual string toString() ;

public:

private:
};

//////////////////////////////////////////////////////////////////////////////
// class ActionForceApartCoupleFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionForceApartCoupleFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType()  { return Action::ACTION_FORCE_APART_COUPLE; }
	virtual string getActionName()  { return "ForceApartCouple"; }
	virtual Action* createAction()  { return new ActionForceApartCouple(); }
};
#endif
