
//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionAcceptCoupleRequest.h
// Written By  : excel96
// Description : 
// Creature�� PC���� ������ ������. �� ���� NPC ��ȭâ�� ��µȴ�.
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_ACCEPT_COUPLE_REQUEST_H__
#define __ACTION_ACCEPT_COUPLE_REQUEST_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionAcceptCoupleRequest
//////////////////////////////////////////////////////////////////////////////

class ActionAcceptCoupleRequest : public Action 
{
public:
	virtual ActionType_t getActionType()  { return ACTION_ACCEPT_COUPLE_REQUEST; }
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) throw(Error);
	virtual string toString() ;

public:

private:
};


//////////////////////////////////////////////////////////////////////////////
// class ActionAcceptCoupleRequestFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionAcceptCoupleRequestFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType()  { return Action::ACTION_ACCEPT_COUPLE_REQUEST; }
	virtual string getActionName()  { return "AcceptCoupleRequest"; }
	virtual Action* createAction()  { return new ActionAcceptCoupleRequest(); }
};
#endif
