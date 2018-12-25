//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionShowWarSchedule.h
// Written By  : excel96
// Description : 
// Creature가 PC에게 질문을 던진다. 이 대사는 NPC 대화창에 출력된다.
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
	virtual ActionType_t getActionType()  { return ACTION_SHOW_WAR_SCHEDULE; }
	virtual void read(PropertyBuffer & propertyBuffer);
	virtual void execute(Creature* pCreature1, Creature* pCreature2);
	virtual string toString() ;

public:
	ZoneID_t	getZoneID() const { return m_ZoneID; }
	void		setZoneID( ZoneID_t ZoneID ) { m_ZoneID = ZoneID; }

private:
	ZoneID_t	m_ZoneID;	// 전쟁을 신청한 성의 ZoneID
};


//////////////////////////////////////////////////////////////////////////////
// class ActionShowWarScheduleFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionShowWarScheduleFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType()  { return Action::ACTION_SHOW_WAR_SCHEDULE; }
	virtual string getActionName()  { return "ShowWarSchedule"; }
	virtual Action* createAction()  { return new ActionShowWarSchedule(); }
};
#endif
