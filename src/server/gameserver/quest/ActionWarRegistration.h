//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionWarRegistration.h
// Written By  : excel96
// Description : 
// Creature�� PC���� ������ ������. �� ���� NPC ��ȭâ�� ��µȴ�.
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_WAR_REGISTRATION_H__
#define __ACTION_WAR_REGISTRATION_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionWarRegistration
//////////////////////////////////////////////////////////////////////////////

class ActionWarRegistration : public Action 
{
public:
	virtual ActionType_t getActionType() const throw() { return ACTION_WAR_REGISTRATION; }
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
// class ActionWarRegistrationFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionWarRegistrationFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType() const throw() { return Action::ACTION_WAR_REGISTRATION; }
	virtual string getActionName() const throw() { return "WarRegistration"; }
	virtual Action* createAction() const throw() { return new ActionWarRegistration(); }
};
#endif
