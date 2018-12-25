//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionFactoryManager.h 
// Written By  : excel96
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_FACTORY_MANAGER_H__
#define __ACTION_FACTORY_MANAGER_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionFactoryManager
//////////////////////////////////////////////////////////////////////////////

class ActionFactoryManager 
{
public:
	ActionFactoryManager() throw();
	~ActionFactoryManager() throw();

public:
	void init();
	void addFactory(ActionFactory* pFactory);
	Action* createAction(ActionType_t conditionType) ;
	string getActionName(ActionType_t conditionType) ;
	ActionType_t getActionType(const string & actionname) ;
	string toString() ;

private:
	ActionFactory** m_Factories;
	ushort          m_Size;
};

extern ActionFactoryManager* g_pActionFactoryManager;

#endif
