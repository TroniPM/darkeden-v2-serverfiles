//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionEnterGDRLair.h
// Written By  : excel96
// Description : 
// Creature�� PC���� ������ ������. �� ���� NPC ��ȭâ�� ��µȴ�.
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_ENTER_GDR_LAIR_H__
#define __ACTION_ENTER_GDR_LAIR_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionEnterGDRLair
//////////////////////////////////////////////////////////////////////////////

class ActionEnterGDRLair : public Action 
{
public:
	virtual ActionType_t getActionType() const throw() { return ACTION_ENTER_GDR_LAIR; }
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) throw(Error);
	virtual string toString() const throw();

private:
	BYTE    m_PortalID;
};


//////////////////////////////////////////////////////////////////////////////
// class ActionEnterGDRLairFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionEnterGDRLairFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType() const throw() { return Action::ACTION_ENTER_GDR_LAIR; }
	virtual string getActionName() const throw() { return "EnterGDRLair"; }
	virtual Action* createAction() const throw() { return new ActionEnterGDRLair(); }
};
#endif
