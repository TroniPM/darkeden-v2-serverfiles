//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionPcGetItem.h
// Written By  : excel96
// Description : 
// Creature가 PC에게 질문을 던진다. 이 대사는 NPC 대화창에 출력된다.
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_ORIGINAL_DELETE_GETGOLD_H__
#define __ACTION_ORIGINAL_DELETE_GETGOLD_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"
#include "Item.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionPcGetItem
//////////////////////////////////////////////////////////////////////////////

class ActionOriginalDeleteGetGold : public Action 
{
public:
	virtual ActionType_t getActionType()  { return ACTION_ORIGINAL_DELETE_GETGOLD; }
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) throw(Error);
	virtual string toString() ;

public:
private:
	Gold_t	m_GoldNum;
};


//////////////////////////////////////////////////////////////////////////////
// class ActionPcGetItemFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionOriginalDeleteGetGoldFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType()  { return Action::ACTION_ORIGINAL_DELETE_GETGOLD; }
	virtual string getActionName()  { return "OriginalDeleteGetGold"; }
	virtual Action* createAction()  { return new ActionOriginalDeleteGetGold(); }
};
#endif
