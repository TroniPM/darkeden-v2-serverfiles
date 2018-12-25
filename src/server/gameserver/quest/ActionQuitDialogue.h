//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionQuitDialogue.h
// Written By  : 
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_ActionQuitDialogue_H__
#define __ACTION_ActionQuitDialogue_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionQuitDialogue;
//////////////////////////////////////////////////////////////////////////////

class ActionQuitDialogue : public Action 
{
public:
	virtual ActionType_t getActionType()  { return ACTION_QUIT_DIALOGUE; }
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) throw(Error);
	virtual string toString() ;

};


//////////////////////////////////////////////////////////////////////////////
// class ActionQuitDialogueFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionQuitDialogueFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType()  { return Action::ACTION_QUIT_DIALOGUE; }
	virtual string getActionName()  { return "QuitDialogue"; }
	virtual Action* createAction()  { return new ActionQuitDialogue(); }

};


#endif
