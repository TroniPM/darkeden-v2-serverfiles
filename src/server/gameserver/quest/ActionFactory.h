//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionFactory.h 
// Written By  : excel96
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_FACTORY_H__
#define __ACTION_FACTORY_H__

#include "Action.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionFactory
//////////////////////////////////////////////////////////////////////////////

class ActionFactory 
{
public:
	virtual ~ActionFactory() throw() {}
	virtual ActionType_t getActionType()  = 0;
	virtual string getActionName()  = 0;
	virtual Action* createAction()  = 0;

};

#endif
