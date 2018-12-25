//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionContractGnomesHorn.h
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_CONTRACT_GNOMES_HORN_H__
#define __ACTION_CONTRACT_GNOMES_HORN_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionContractGnomesHorn
//////////////////////////////////////////////////////////////////////////////

class ActionContractGnomesHorn : public Action 
{
public:
	virtual ActionType_t getActionType()  { return ACTION_CONTRACT_GNOMES_HORN; }
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) throw(Error);
	virtual string toString() ;
};

//////////////////////////////////////////////////////////////////////////////
// class AskFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionContractGnomesHornFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType()  { return Action::ACTION_CONTRACT_GNOMES_HORN; }
	virtual string getActionName()  { return "ContractGnomesHorn"; }
	virtual Action* createAction()  { return new ActionContractGnomesHorn(); }
};

#endif
