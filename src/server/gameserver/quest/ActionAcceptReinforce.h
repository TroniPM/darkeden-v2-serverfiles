//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionAcceptReinforce.h
// Written By  : excel96
// Description : 
// Creature�� PC���� ������ ������. �� ���� NPC ��ȭâ�� ��µȴ�.
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_ACCEPT_REINFORCE_H__
#define __ACTION_ACCEPT_REINFORCE_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionAcceptReinforce
//////////////////////////////////////////////////////////////////////////////

class ActionAcceptReinforce : public Action 
{
public:
	virtual ActionType_t getActionType()  { return ACTION_ACCEPT_REINFORCE; }
	virtual void read(PropertyBuffer & propertyBuffer);
	virtual void execute(Creature* pCreature1, Creature* pCreature2);
	virtual string toString() ;

public:
	ZoneID_t	getZoneID() const { return m_ZoneID; }
	void		setZoneID( ZoneID_t ZoneID ) { m_ZoneID = ZoneID; }

private:
	ZoneID_t	m_ZoneID;	// ������ ��û�� ���� ZoneID
};


//////////////////////////////////////////////////////////////////////////////
// class ActionAcceptReinforceFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionAcceptReinforceFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType()  { return Action::ACTION_ACCEPT_REINFORCE; }
	virtual string getActionName()  { return "AcceptReinforce"; }
	virtual Action* createAction()  { return new ActionAcceptReinforce(); }
};
#endif
