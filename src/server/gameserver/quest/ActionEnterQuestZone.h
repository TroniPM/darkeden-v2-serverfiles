//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionEnterQuestZone.h
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_ENTER_QUEST_ZONE_H__
#define __ACTION_ENTER_QUEST_ZONE_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionEnterQuestZone
//////////////////////////////////////////////////////////////////////////////

class ActionEnterQuestZone : public Action 
{
public:
	virtual ActionType_t getActionType()  { return ACTION_ENTER_QUEST_ZONE; }
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
};


//////////////////////////////////////////////////////////////////////////////
// class ActionEnterQuestZoneFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionEnterQuestZoneFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType()  { return Action::ACTION_ENTER_QUEST_ZONE; }
	virtual string getActionName()  { return "EnterQuestZone"; }
	virtual Action* createAction()  { return new ActionEnterQuestZone(); }
};
#endif
