//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionPetDeposit.h
// Written By  : excel96
// Description : 
// Creature가 PC에게 질문을 던진다. 이 대사는 NPC 대화창에 출력된다.
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_PET_DEPOSIT_H__
#define __ACTION_PET_DEPOSIT_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionPetDeposit
//////////////////////////////////////////////////////////////////////////////

class ActionPetDeposit : public Action 
{
public:
	virtual ActionType_t getActionType()  { return ACTION_PET_DEPOSIT; }
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) throw(Error);
	virtual string toString() ;
};


//////////////////////////////////////////////////////////////////////////////
// class ActionPetDepositFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionPetDepositFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType()  { return Action::ACTION_PET_DEPOSIT; }
	virtual string getActionName()  { return "PetDeposit"; }
	virtual Action* createAction()  { return new ActionPetDeposit(); }
};
#endif
