//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionRecallSiege.h
// Written By  : excel96
// Description : 
// Creature�� PC���� ������ ������. �� ���� NPC ��ȭâ�� ��µȴ�.
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_RECALL_SIEGE_H__
#define __ACTION_RECALL_SIEGE_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionRecallSiege
//////////////////////////////////////////////////////////////////////////////

class ActionRecallSiege : public Action 
{
public:
	virtual ActionType_t getActionType()  { return ACTION_RECALL_SIEGE; }
	virtual void read(PropertyBuffer & propertyBuffer);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL);
	virtual string toString() ;

private:
	ZoneID_t    m_ZoneID;
};


//////////////////////////////////////////////////////////////////////////////
// class ActionRecallSiegeFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionRecallSiegeFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType()  { return Action::ACTION_RECALL_SIEGE; }
	virtual string getActionName()  { return "RecallSiege"; }
	virtual Action* createAction()  { return new ActionRecallSiege(); }
};
#endif
