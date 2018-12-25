//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionAskDynamic.h
// Written By  : excel96
// Description : 
// Creature�� PC���� ������ ������. �� ���� NPC ��ȭâ�� ��µȴ�.
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_ASK_DYNAMIC_H__
#define __ACTION_ASK_DYNAMIC_H__

#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionAskDynamic
//////////////////////////////////////////////////////////////////////////////

class ActionAskDynamic : public Action 
{
public:
	virtual ActionType_t getActionType()  { return ACTION_ASK_DYNAMIC; }
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) throw(Error);
	virtual string toString() ;

public:
	ScriptID_t getScriptID()  { return m_ScriptID; }
	void setScriptID(ScriptID_t scriptID) throw() { m_ScriptID = scriptID; }

private:
	ScriptID_t m_ScriptID;   // ���� ��� ���̵�
};


//////////////////////////////////////////////////////////////////////////////
// class ActionAskDynamicFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionAskDynamicFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType()  { return Action::ACTION_ASK_DYNAMIC; }
	virtual string getActionName()  { return "AskDynamic"; }
	virtual Action* createAction()  { return new ActionAskDynamic(); }
};

#endif
