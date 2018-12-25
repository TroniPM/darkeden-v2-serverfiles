////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionCreateGuild.h
// Written By  : excel96
// Description :
// NPC�� ���� Ŭ���̾�Ʈ�� �Ͽ��� ��� ����â�� ���� �Ѵ�.
////////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_CREATE_GUILD_H__
#define __ACTION_CREATE_GUILD_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionCreateGuild;
//////////////////////////////////////////////////////////////////////////////

class ActionCreateGuild : public Action 
{
public:
	virtual ActionType_t getActionType()  { return ACTION_CREATE_GUILD; }
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) throw(Error);
	virtual string toString() ;
};

//////////////////////////////////////////////////////////////////////////////
// class ActionCreateGuildFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionCreateGuildFactory : public ActionFactory 
{
public:
    virtual ActionType_t getActionType()  { return Action::ACTION_CREATE_GUILD; }
	virtual string getActionName()  { return "CreateGuild"; }
    virtual Action* createAction()  { return new ActionCreateGuild(); }
};

#endif
