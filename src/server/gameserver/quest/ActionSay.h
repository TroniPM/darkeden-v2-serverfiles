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
	virtual ActionType_t getActionType()  { return ACTION_SAY; }
	virtual void read(PropertyBuffer & propertyBuffer);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL);
	virtual string toString() ;

public:
	ScriptID_t getScriptID()  { return m_ScriptID; }
	void setScriptID(ScriptID_t scriptID)  { m_ScriptID = scriptID; }

private:
	ScriptID_t m_ScriptID; // ���� ��� ���̵�
};

//////////////////////////////////////////////////////////////////////////////
// class ActionSayFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionSayFactory : public ActionFactory 
{
public:
    virtual ActionType_t getActionType()  { return Action::ACTION_SAY; }
	virtual string getActionName()  { return "Say"; }
    virtual Action* createAction()  { return new ActionSay(); }
};

#endif
