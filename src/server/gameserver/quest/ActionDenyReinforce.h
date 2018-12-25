//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionDenyReinforce.h
// Written By  : excel96
// Description : 
// Creature�� PC���� ������ ������. �� ���� NPC ��ȭâ�� ��µȴ�.
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_DENY_REINFORCE_H__
#define __ACTION_DENY_REINFORCE_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionDenyReinforce
//////////////////////////////////////////////////////////////////////////////

class ActionDenyReinforce : public Action 
{
public:
	virtual ActionType_t getActionType()  { return ACTION_DENY_REINFORCE; }
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual void execute(Creature* pCreature1, Creature* pCreature2) throw(Error);
	virtual string toString() ;

public:
	ZoneID_t	getZoneID() const { return m_ZoneID; }
	void		setZoneID( ZoneID_t ZoneID ) { m_ZoneID = ZoneID; }

private:
	ZoneID_t	m_ZoneID;	// ������ ��û�� ���� ZoneID
};


//////////////////////////////////////////////////////////////////////////////
// class ActionDenyReinforceFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionDenyReinforceFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType()  { return Action::ACTION_DENY_REINFORCE; }
	virtual string getActionName()  { return "DenyReinforce"; }
	virtual Action* createAction()  { return new ActionDenyReinforce(); }
};
#endif
