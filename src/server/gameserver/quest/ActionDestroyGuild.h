//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionDestroyGuild.h
// Written By  : 
// Description :
// NPC�� ���� Ŭ���̾�Ʈ�� �Ͽ��� ��� ����â�� ���� �Ѵ�.
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_DESTROY_GUILD_H__
#define __ACTION_DESTROY_GUILD_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionDestroyGuild;
//////////////////////////////////////////////////////////////////////////////

class ActionDestroyGuild : public Action 
{
public:
	virtual ActionType_t getActionType() const throw() { return ACTION_DESTROY_GUILD; }
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) throw(Error);
	virtual string toString() const throw();
};

//////////////////////////////////////////////////////////////////////////////
// class ActionDestroyGuildFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionDestroyGuildFactory : public ActionFactory 
{
public:
    virtual ActionType_t getActionType() const throw() { return Action::ACTION_DESTROY_GUILD; }
	virtual string getActionName() const throw() { return "DestroyGuild"; }
    virtual Action* createAction() const throw() { return new ActionDestroyGuild(); }

};

#endif
