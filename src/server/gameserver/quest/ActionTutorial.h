//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionTutorial.h
// Written By  : excel96
// Description : 
// Creature�� PC���� ������ ������. �� ���� NPC ��ȭâ�� ��µȴ�.
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_TUTORIAL_H__
#define __ACTION_TUTORIAL_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionTutorial
//////////////////////////////////////////////////////////////////////////////

class ActionTutorial : public Action 
{
public:
	virtual ActionType_t getActionType()  { return ACTION_TUTORIAL; }
	virtual void read(PropertyBuffer & propertyBuffer);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL);
	virtual string toString() ;

public:
	string getInterface(void)  { return m_Interface; }
	void setInterface(string interface)  { m_Interface = interface; }

private:
	string m_Interface;

};


//////////////////////////////////////////////////////////////////////////////
// class ActionTutorialFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionTutorialFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType()  { return Action::ACTION_TUTORIAL; }
	virtual string getActionName()  { return "Tutorial"; }
	virtual Action* createAction()  { return new ActionTutorial(); }
};
#endif
