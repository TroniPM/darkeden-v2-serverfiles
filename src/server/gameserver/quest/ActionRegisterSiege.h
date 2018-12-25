//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionRegisterSiege.h
// Written By  : excel96
// Description : 
// Creature�� PC���� ������ ������. �� ���� NPC ��ȭâ�� ��µȴ�.
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_REGISTER_SIEGE_H__
#define __ACTION_REGISTER_SIEGE_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionRegisterSiege
//////////////////////////////////////////////////////////////////////////////

class ActionRegisterSiege : public Action 
{
public:
	virtual ActionType_t getActionType()  { return ACTION_REGISTER_SIEGE; }
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
// class ActionRegisterSiegeFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionRegisterSiegeFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType()  { return Action::ACTION_REGISTER_SIEGE; }
	virtual string getActionName()  { return "RegisterSiege"; }
	virtual Action* createAction()  { return new ActionRegisterSiege(); }
};
#endif
