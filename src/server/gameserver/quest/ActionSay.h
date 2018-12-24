//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionSay.h
// Written By  : 
// Description :
// Creature�� �־��� ��縦 ���Ѵ�. �� ���� ũ��ó�� �Ӹ� ���� ��ǳ������
// ��µȴ�.
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_SAY_H__
#define __ACTION_SAY_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionSay;
//////////////////////////////////////////////////////////////////////////////

class ActionSay : public Action 
{
public:
	virtual ActionType_t getActionType() const throw() { return ACTION_SAY; }
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) throw(Error);
	virtual string toString() const throw();

public:
	ScriptID_t getScriptID() const throw() { return m_ScriptID; }
	void setScriptID(ScriptID_t scriptID) throw() { m_ScriptID = scriptID; }

private:
	ScriptID_t m_ScriptID; // ���� ��� ���̵�
};

//////////////////////////////////////////////////////////////////////////////
// class ActionSayFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionSayFactory : public ActionFactory 
{
public:
    virtual ActionType_t getActionType() const throw() { return Action::ACTION_SAY; }
	virtual string getActionName() const throw() { return "Say"; }
    virtual Action* createAction() const throw() { return new ActionSay(); }
};

#endif
