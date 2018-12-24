//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionAskVariable.h
// Written By  : excel96
// Description : 
// Creature�� PC���� ������ ������. �� ���� NPC ��ȭâ�� ��µȴ�.
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_ASK_VARIABLE_H__
#define __ACTION_ASK_VARIABLE_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionAskVariable
//////////////////////////////////////////////////////////////////////////////

class VariableBuffer;

class ActionAskVariable : public Action 
{
public:
	ActionAskVariable() : m_pVariableBuffer(NULL) {}

public:
	virtual ActionType_t getActionType() const throw() { return ACTION_ASK_VARIABLE; }
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) throw(Error);
	virtual string toString() const throw();

public:
	ScriptID_t getScriptID() const throw() { return m_ScriptID; }
	void setScriptID(ScriptID_t scriptID) throw() { m_ScriptID = scriptID; }

private:
	ScriptID_t m_ScriptID;   // ���� ��� ���̵�
	VariableBuffer* m_pVariableBuffer;
};


//////////////////////////////////////////////////////////////////////////////
// class ActionAskVariableFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionAskVariableFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType() const throw() { return Action::ACTION_ASK_VARIABLE; }
	virtual string getActionName() const throw() { return "AskVariable"; }
	virtual Action* createAction() const throw() { return new ActionAskVariable(); }
};
#endif
