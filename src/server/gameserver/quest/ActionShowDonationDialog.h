//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionShowDonationDialog.h
// Written By  : 
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_SHOW_DONATION_DIALOG_H__
#define __ACTION_SHOW_DONATION_DIALOG_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"


//////////////////////////////////////////////////////////////////////////////
// class ActionShowDonationDialog;
//////////////////////////////////////////////////////////////////////////////

class ActionShowDonationDialog : public Action 
{
public:
	virtual ActionType_t getActionType()  { return ACTION_SHOW_DONATION_DIALOG; }
	virtual void read(PropertyBuffer & propertyBuffer);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL);
	virtual string toString() ;

private:
	string m_Type;
};

//////////////////////////////////////////////////////////////////////////////
// class ActionShowDonationDialogFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionShowDonationDialogFactory : public ActionFactory 
{
public:
    virtual ActionType_t getActionType()  { return Action::ACTION_SHOW_DONATION_DIALOG; }
	virtual string getActionName()  { return "ShowDonationDialog"; }
    virtual Action* createAction()  { return new ActionShowDonationDialog(); }
};

#endif

