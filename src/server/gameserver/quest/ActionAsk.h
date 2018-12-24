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
	virtual ActionType_t getActionType() const throw() { return ACTION_ASK; }
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) throw(Error);
	virtual string toString() const throw();

public:
	ScriptID_t getScriptID() const throw() { return m_ScriptID; }
	void setScriptID(ScriptID_t scriptID) throw() { m_ScriptID = scriptID; }

private:
	ScriptID_t m_ScriptID;   // ���� ��� ���̵�
};


//////////////////////////////////////////////////////////////////////////////
// class ActionAskFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionAskFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType() const throw() { return Action::ACTION_ASK; }
	virtual string getActionName() const throw() { return "Ask"; }
	virtual Action* createAction() const throw() { return new ActionAsk(); }
};
#endif
