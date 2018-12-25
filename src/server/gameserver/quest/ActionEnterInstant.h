//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionEnterQuestZone.h
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_ENTER_INSTANT_H__
#define __ACTION_ENTER_INSTANT_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionEnterQuestZone
//////////////////////////////////////////////////////////////////////////////

class ActionEnterInstant : public Action 
{
public:
	virtual ActionType_t getActionType()  { return ACTION_ENTER_INSTANT; }
	virtual void read(PropertyBuffer & propertyBuffer);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL);
	virtual string toString() ;

public:
	ZoneID_t    getZoneID(void)  { return m_ZoneID; }
	ZoneCoord_t getX(void)  { return m_X; }
	ZoneCoord_t getY(void)  { return m_Y; }

private:
	ZoneID_t    m_ZoneID;
	ZoneCoord_t m_X;
	ZoneCoord_t m_Y;
	ZoneCoord_t m_InstantID;
};


//////////////////////////////////////////////////////////////////////////////
// class ActionEnterInstantFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionEnterInstantFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType()  { return Action::ACTION_ENTER_INSTANT; }
	virtual string getActionName()  { return "EnterInstant"; }
	virtual Action* createAction()  { return new ActionEnterInstant(); }
};
#endif
