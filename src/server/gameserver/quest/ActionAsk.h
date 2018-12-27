//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionAsk.h
// Written By  : excel96
// Description : 
// Creature�� PC���� ������ ������. �� ���� NPC ��ȭâ�� ��µȴ�.
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_ASK_H__
#define __ACTION_ASK_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionAsk
//////////////////////////////////////////////////////////////////////////////

class ActionAsk : public Action 
{
public:
	virtual ActionType_t getActionType()  { return ACTION_ASK; }
	virtual void read(PropertyBuffer & propertyBuffer);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL);
	virtual string toString() ;

public:
	ScriptID_t getScriptID()  { return m_ScriptID; }
	void setScriptID(ScriptID_t scriptID)  { m_ScriptID = scriptID; }

private:
	ScriptID_t m_ScriptID;   // ���� ��� ���̵�
};


//////////////////////////////////////////////////////////////////////////////
// class ActionAskFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionAskFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType()  { return Action::ACTION_ASK; }
	virtual string getActionName()  { return "Ask"; }
	virtual Action* createAction()  { return new ActionAsk(); }
};
#endif
