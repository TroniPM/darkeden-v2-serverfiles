//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionPcGetItem.h
// Written By  : excel96
// Description : 
// Creature가 PC에게 질문을 던진다. 이 대사는 NPC 대화창에 출력된다.
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_CREATE_GETITEM_H__
#define __ACTION_CREATE_GETITEM_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"
#include "Item.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionPcGetItem
//////////////////////////////////////////////////////////////////////////////

class ActionCreateGetItem : public Action 
{
public:
	virtual ActionType_t getActionType()  { return ACTION_CREATE_GETITEM; }
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) throw(Error);
	virtual string toString() ;

public:
private:
	// 몬스터 셋업
	int	m_ItemClass;
};


//////////////////////////////////////////////////////////////////////////////
// class ActionPcGetItemFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionCreateGetItemFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType()  { return Action::ACTION_CREATE_GETITEM; }
	virtual string getActionName()  { return "CreateGetItem"; }
	virtual Action* createAction()  { return new ActionCreateGetItem(); }
};
#endif
