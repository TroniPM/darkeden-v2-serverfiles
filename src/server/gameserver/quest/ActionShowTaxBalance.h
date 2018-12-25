//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionShowTaxBalance.h
// Written By  : excel96
// Description : 
// Creature�� PC���� ������ ������. �� ���� NPC ��ȭâ�� ��µȴ�.
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_SHOW_TAX_BALANCE_H__
#define __ACTION_SHOW_TAX_BALANCE_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionShowTaxBalance
//////////////////////////////////////////////////////////////////////////////

class ActionShowTaxBalance : public Action 
{
public:
	virtual ActionType_t getActionType()  { return ACTION_SHOW_TAX_BALANCE; }
	virtual void read(PropertyBuffer & propertyBuffer);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL);
	virtual string toString() ;
};


//////////////////////////////////////////////////////////////////////////////
// class ActionShowTaxBalanceFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionShowTaxBalanceFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType()  { return Action::ACTION_SHOW_TAX_BALANCE; }
	virtual string getActionName()  { return "ShowTaxBalance"; }
	virtual Action* createAction()  { return new ActionShowTaxBalance(); }
};
#endif
