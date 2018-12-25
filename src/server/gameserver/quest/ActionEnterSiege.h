//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionEnterSiege.h
// Written By  : excel96
// Description : 
// Creature가 PC에게 질문을 던진다. 이 대사는 NPC 대화창에 출력된다.
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_ENTER_SIEGE_H__
#define __ACTION_ENTER_SIEGE_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionEnterSiege
//////////////////////////////////////////////////////////////////////////////

class ActionEnterSiege : public Action 
{
public:
	virtual ActionType_t getActionType()  { return ACTION_ENTER_SIEGE; }
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) throw(Error);
	virtual string toString() ;

private:
	ZoneID_t    m_ZoneID;
};


//////////////////////////////////////////////////////////////////////////////
// class ActionEnterSiegeFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionEnterSiegeFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType()  { return Action::ACTION_ENTER_SIEGE; }
	virtual string getActionName()  { return "EnterSiege"; }
	virtual Action* createAction()  { return new ActionEnterSiege(); }
};
#endif
