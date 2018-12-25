//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionCheckPartnerName.h
// Written By  : excel96
// Description : 
// Creature�� PC���� ������ ������. �� ���� NPC ��ȭâ�� ��µȴ�.
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_CHECK_PARTNER_NAME_H__
#define __ACTION_CHECK_PARTNER_NAME_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionCheckPartnerName
//////////////////////////////////////////////////////////////////////////////

class ActionCheckPartnerName : public Action 
{
public:
	virtual ActionType_t getActionType()  { return ACTION_CHECK_PARTNER_NAME; }
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) throw(Error);
	virtual string toString() ;
};


//////////////////////////////////////////////////////////////////////////////
// class ActionCheckPartnerNameFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionCheckPartnerNameFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType()  { return Action::ACTION_CHECK_PARTNER_NAME; }
	virtual string getActionName()  { return "CheckPartnerName"; }
	virtual Action* createAction()  { return new ActionCheckPartnerName(); }
};
#endif
