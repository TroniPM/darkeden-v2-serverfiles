//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionEnterPKZone.h
// Written By  : excel96
// Description : 
// Creature가 PC에게 질문을 던진다. 이 대사는 NPC 대화창에 출력된다.
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_ENTER_PK_ZONE_H__
#define __ACTION_ENTER_PK_ZONE_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionEnterPKZone
//////////////////////////////////////////////////////////////////////////////

class ActionEnterPKZone : public Action 
{
public:
	virtual ActionType_t getActionType()  { return ACTION_ENTER_PK_ZONE; }
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) throw(Error);
	virtual string toString() ;

public:
	ZoneID_t    getZoneID(void)  { return m_ZoneID; }

private:
	ZoneID_t    m_ZoneID;
};


//////////////////////////////////////////////////////////////////////////////
// class ActionEnterPKZoneFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionEnterPKZoneFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType()  { return Action::ACTION_ENTER_PK_ZONE; }
	virtual string getActionName()  { return "EnterPKZone"; }
	virtual Action* createAction()  { return new ActionEnterPKZone(); }
};
#endif
