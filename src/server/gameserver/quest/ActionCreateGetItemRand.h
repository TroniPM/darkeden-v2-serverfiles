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
	virtual ActionType_t getActionType() const throw() { return ACTION_CREATE_GETITEM_RAND; }
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) throw(Error);
	virtual string toString() const throw();

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
	virtual ActionType_t getActionType() const throw() { return Action::ACTION_CREATE_GETITEM_RAND; }
	virtual string getActionName() const throw() { return "CreateGetItemRand"; }
	virtual Action* createAction() const throw() { return new ActionCreateGetItemRand(); }
};
#endif
