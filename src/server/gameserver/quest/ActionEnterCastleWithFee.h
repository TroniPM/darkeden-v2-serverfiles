//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionEnterCastleWithFee.h
// Written By  : excel96
// Description : 
// Creature�� PC���� ������ ������. �� ���� NPC ��ȭâ�� ��µȴ�.
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_ENTER_CASTLE_WITH_FEE_H__
#define __ACTION_ENTER_CASTLE_WITH_FEE_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionEnterCastleWithFee
//////////////////////////////////////////////////////////////////////////////

class ActionEnterCastleWithFee : public Action 
{
public:
	virtual ActionType_t getActionType()  { return ACTION_ENTER_CASTLE_WITH_FEE; }
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
// class ActionEnterCastleWithFeeFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionEnterCastleWithFeeFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType()  { return Action::ACTION_ENTER_CASTLE_WITH_FEE; }
	virtual string getActionName()  { return "EnterCastleWithFee"; }
	virtual Action* createAction()  { return new ActionEnterCastleWithFee(); }
};
#endif
