//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionStartPetQuest.h
// Written By  : excel96
// Description : 
// Creature�� PC���� ������ ������. �� ���� NPC ��ȭâ�� ��µȴ�.
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_START_PET_QUEST_H__
#define __ACTION_START_PET_QUEST_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionStartPetQuest
//////////////////////////////////////////////////////////////////////////////

class ActionStartPetQuest : public Action 
{
public:
	virtual ActionType_t getActionType()  { return ACTION_START_PET_QUEST; }
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) throw(Error);
	virtual string toString() ;
};


//////////////////////////////////////////////////////////////////////////////
// class ActionStartPetQuestFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionStartPetQuestFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType()  { return Action::ACTION_START_PET_QUEST; }
	virtual string getActionName()  { return "StartPetQuest"; }
	virtual Action* createAction()  { return new ActionStartPetQuest(); }
};
#endif
