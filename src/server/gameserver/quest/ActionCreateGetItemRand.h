//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionPcGetItem.h
// Written By  : excel96
// Description : 
// Creature�� PC���� ������ ������. �� ���� NPC ��ȭâ�� ��µȴ�.
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_CREATE_GETITEM_RAND_H__
#define __ACTION_CREATE_GETITEM_RAND_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"
#include "Item.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionPcGetItem
//////////////////////////////////////////////////////////////////////////////

class ActionCreateGetItemRand : public Action 
{
public:
	virtual ActionType_t getActionType()  { return ACTION_CREATE_GETITEM_RAND; }
	virtual void read(PropertyBuffer & propertyBuffer);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL);
	virtual string toString() ;

public:
private:
	int m_ItemGroupID,m_ItemGroupID2;
	// �ɼ��� �����ֱ� ���� �κ�.
};


//////////////////////////////////////////////////////////////////////////////
// class ActionPcGetItemFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionCreateGetItemRandFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType()  { return Action::ACTION_CREATE_GETITEM_RAND; }
	virtual string getActionName()  { return "CreateGetItemRand"; }
	virtual Action* createAction()  { return new ActionCreateGetItemRand(); }
};
#endif
