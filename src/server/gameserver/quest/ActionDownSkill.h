////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionDownSkill.h
// Written By  : excel96
// Description :
// NPC�� ���� Ŭ���̾�Ʈ�� �Ͽ��� ��� ����â�� ���� �Ѵ�.
////////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_DOWN_SKILL_H__
#define __ACTION_DOWN_SKILL_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionDownSkill;
//////////////////////////////////////////////////////////////////////////////

class ActionDownSkill : public Action 
{
public:
	virtual ActionType_t getActionType() const throw() { return ACTION_DOWN_SKILL; }
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) throw(Error);
	virtual string toString() const throw();
};

//////////////////////////////////////////////////////////////////////////////
// class ActionDownSkillFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionDownSkillFactory : public ActionFactory 
{
public:
    virtual ActionType_t getActionType() const throw() { return Action::ACTION_DOWN_SKILL; }
	virtual string getActionName() const throw() { return "DownSkill"; }
    virtual Action* createAction() const throw() { return new ActionDownSkill(); }
};

#endif
