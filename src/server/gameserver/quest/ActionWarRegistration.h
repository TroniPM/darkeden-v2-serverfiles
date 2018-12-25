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
	virtual ActionType_t getActionType()  { return ACTION_WAR_REGISTRATION; }
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
// class ActionWarRegistrationFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionWarRegistrationFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType()  { return Action::ACTION_WAR_REGISTRATION; }
	virtual string getActionName()  { return "WarRegistration"; }
	virtual Action* createAction()  { return new ActionWarRegistration(); }
};
#endif
