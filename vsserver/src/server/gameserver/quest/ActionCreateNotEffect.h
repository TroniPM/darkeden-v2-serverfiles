//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionPcGetItem.h
// Written By  : excel96
// Description : 
// Creature가 PC에게 질문을 던진다. 이 대사는 NPC 대화창에 출력된다.
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_CREATE_EFFECT_NOTLOGOUT_H__
#define __ACTION_CREATE_EFFECT_NOTLOGOUT_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"
#include "Item.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionPcGetItem
//////////////////////////////////////////////////////////////////////////////

class ActionCreateNotEffect : public Action 
{
public:
	virtual ActionType_t getActionType() const throw() { return ACTION_CREATE_EFFECT_NOTLOGOUT; }
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) throw(Error);
	virtual string toString() const throw();

public:
private:
	int	m_EffectClass;
	int	m_EffectTime;
};


//////////////////////////////////////////////////////////////////////////////
// class ActionPcGetItemFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionCreateNotEffectFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType() const throw() { return Action::ACTION_CREATE_EFFECT_NOTLOGOUT; }
	virtual string getActionName() const throw() { return "CreateNotEffect"; }
	virtual Action* createAction() const throw() { return new ActionCreateNotEffect(); }
};
#endif
