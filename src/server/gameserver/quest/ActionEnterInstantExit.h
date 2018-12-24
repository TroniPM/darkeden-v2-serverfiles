//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionEnterQuestZone.h
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_ENTER_INSTANT_EXIT_H__
#define __ACTION_ENTER_INSTANT_EXIT_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionEnterQuestZone
//////////////////////////////////////////////////////////////////////////////

class ActionEnterInstantExit : public Action 
{
public:
	virtual ActionType_t getActionType() const throw() { return ACTION_ENTER_INSTANT_EXIT; }
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) throw(Error);
	virtual string toString() const throw();

public:
	ZoneID_t    getZoneID(void) const throw() { return m_ZoneID; }
	ZoneCoord_t getX(void) const throw() { return m_X; }
	ZoneCoord_t getY(void) const throw() { return m_Y; }

private:
	ZoneID_t    m_ZoneID;
	ZoneCoord_t m_X;
	ZoneCoord_t m_Y;
};


//////////////////////////////////////////////////////////////////////////////
// class ActionEnterInstantExitFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionEnterInstantExitFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType() const throw() { return Action::ACTION_ENTER_INSTANT_EXIT; }
	virtual string getActionName() const throw() { return "EnterInstantExit"; }
	virtual Action* createAction() const throw() { return new ActionEnterInstantExit(); }
};
#endif
