//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionSayDynamic.h
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_SAY_DYNAMIC_H__
#define __ACTION_SAY_DYNAMIC_H__

#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionSayDynamic
//////////////////////////////////////////////////////////////////////////////

class ActionSayDynamic : public Action 
{
public:
	virtual ActionType_t getActionType()  { return ACTION_SAY_DYNAMIC; }
	virtual void read(PropertyBuffer & propertyBuffer);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL);
	virtual string toString() ;

public:
	ScriptID_t getScriptID()  { return m_ScriptID; }
	void setScriptID(ScriptID_t scriptID) throw() { m_ScriptID = scriptID; }

private:
	ScriptID_t m_ScriptID;   // 말할 대사 아이디
};


//////////////////////////////////////////////////////////////////////////////
// class ActionSayDynamicFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionSayDynamicFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType()  { return Action::ACTION_SAY_DYNAMIC; }
	virtual string getActionName()  { return "SayDynamic"; }
	virtual Action* createAction()  { return new ActionSayDynamic(); }
};

#endif
