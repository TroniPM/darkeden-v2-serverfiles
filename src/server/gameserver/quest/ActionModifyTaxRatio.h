//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionModifyTaxRatio.h
// Written By  : excel96
// Description : 
// Creature가 PC에게 질문을 던진다. 이 대사는 NPC 대화창에 출력된다.
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_MODIFY_TAX_RATIO_H__
#define __ACTION_MODIFY_TAX_RATIO_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionModifyTaxRatio
//////////////////////////////////////////////////////////////////////////////

class ActionModifyTaxRatio : public Action 
{
public:
	virtual ActionType_t getActionType()  { return ACTION_MODIFY_TAX_RATIO; }
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) throw(Error);
	virtual string toString() ;
};


//////////////////////////////////////////////////////////////////////////////
// class ActionModifyTaxRatioFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionModifyTaxRatioFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType()  { return Action::ACTION_MODIFY_TAX_RATIO; }
	virtual string getActionName()  { return "ModifyTaxRatio"; }
	virtual Action* createAction()  { return new ActionModifyTaxRatio(); }
};
#endif
