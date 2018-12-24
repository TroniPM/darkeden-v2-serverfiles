//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionEnterEventZone.h
// Written By  : excel96
// Description : 
// Creature�� PC���� ������ ������. �� ���� NPC ��ȭâ�� ��µȴ�.
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_ENTER_EVENT_ZONE_H__
#define __ACTION_ENTER_EVENT_ZONE_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionEnterEventZone
//////////////////////////////////////////////////////////////////////////////

class ActionEnterEventZone : public Action 
{
public:
	virtual ActionType_t getActionType() const throw() { return ACTION_ENTER_EVENT_ZONE; }
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) throw(Error);
	virtual string toString() const throw();

private:
	WORD    m_EventID;
};


//////////////////////////////////////////////////////////////////////////////
// class ActionEnterEventZoneFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionEnterEventZoneFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType() const throw() { return Action::ACTION_ENTER_EVENT_ZONE; }
	virtual string getActionName() const throw() { return "EnterEventZone"; }
	virtual Action* createAction() const throw() { return new ActionEnterEventZone(); }
};
#endif
