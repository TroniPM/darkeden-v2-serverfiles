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
	virtual ActionType_t getActionType() const throw() { return ACTION_ACCEPT_REINFORCE; }
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual void execute(Creature* pCreature1, Creature* pCreature2) throw(Error);
	virtual string toString() const throw();

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
	virtual ActionType_t getActionType() const throw() { return Action::ACTION_ACCEPT_REINFORCE; }
	virtual string getActionName() const throw() { return "AcceptReinforce"; }
	virtual Action* createAction() const throw() { return new ActionAcceptReinforce(); }
};
#endif
