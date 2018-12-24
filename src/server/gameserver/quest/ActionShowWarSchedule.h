//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionShowWarSchedule.h
// Written By  : excel96
// Description : 
// Creature�� PC���� ������ ������. �� ���� NPC ��ȭâ�� ��µȴ�.
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_SHOW_WAR_SCHEDULE_H__
#define __ACTION_SHOW_WAR_SCHEDULE_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionShowWarSchedule
//////////////////////////////////////////////////////////////////////////////

class ActionShowWarSchedule : public Action 
{
public:
	virtual ActionType_t getActionType() const throw() { return ACTION_SHOW_WAR_SCHEDULE; }
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
// class ActionShowWarScheduleFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionShowWarScheduleFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType() const throw() { return Action::ACTION_SHOW_WAR_SCHEDULE; }
	virtual string getActionName() const throw() { return "ShowWarSchedule"; }
	virtual Action* createAction() const throw() { return new ActionShowWarSchedule(); }
};
#endif
