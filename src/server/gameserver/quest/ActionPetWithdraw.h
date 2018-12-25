//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionPetWithdraw.h
// Written By  : excel96
// Description : 
// Creature가 PC에게 질문을 던진다. 이 대사는 NPC 대화창에 출력된다.
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_PET_WITHDRAW_H__
#define __ACTION_PET_WITHDRAW_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionPetWithdraw
//////////////////////////////////////////////////////////////////////////////

class ActionPetWithdraw : public Action 
{
public:
	virtual ActionType_t getActionType()  { return ACTION_PET_WITHDRAW; }
	virtual void read(PropertyBuffer & propertyBuffer);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL);
	virtual string toString() ;
};


//////////////////////////////////////////////////////////////////////////////
// class ActionPetWithdrawFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionPetWithdrawFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType()  { return Action::ACTION_PET_WITHDRAW; }
	virtual string getActionName()  { return "PetWithdraw"; }
	virtual Action* createAction()  { return new ActionPetWithdraw(); }
};
#endif
