//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionSelectBloodBible.h
// Written By  : excel96
// Description : 
// Creature�� PC���� ������ ������. �� ���� NPC ��ȭâ�� ��µȴ�.
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_SELECT_BLOOD_BIBLE_H__
#define __ACTION_SELECT_BLOOD_BIBLE_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionSelectBloodBible
//////////////////////////////////////////////////////////////////////////////

class ActionSelectBloodBible : public Action 
{
public:
	virtual ActionType_t getActionType()  { return ACTION_SELECT_BLOOD_BIBLE; }
	virtual void read(PropertyBuffer & propertyBuffer);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL);
	virtual string toString() ;

public:
private:
};


//////////////////////////////////////////////////////////////////////////////
// class ActionSelectBloodBibleFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionSelectBloodBibleFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType()  { return Action::ACTION_SELECT_BLOOD_BIBLE; }
	virtual string getActionName()  { return "SelectBloodBible"; }
	virtual Action* createAction()  { return new ActionSelectBloodBible(); }
};
#endif
