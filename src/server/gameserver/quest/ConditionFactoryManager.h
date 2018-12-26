//////////////////////////////////////////////////////////////////////////////
// Filename    : ConditionFactoryManager.h 
// Written By  : 
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __CONDITION_FACTORY_MANAGER_H__
#define __CONDITION_FACTORY_MANAGER_H__

#include "Types.h"
#include "Exception.h"
#include "Condition.h"
#include "ConditionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ConditionFactoryManager
//////////////////////////////////////////////////////////////////////////////

class ConditionFactoryManager 
{
public:
	ConditionFactoryManager() ;
	~ConditionFactoryManager() ;

public:
	void init();
	void addFactory(ConditionFactory* pFactory);
	Condition* createCondition(ConditionType_t conditionType) ;
	string getConditionName(ConditionType_t conditionType) ;
	ConditionType_t getConditionType(const string & contionname) ;
	string toString() ;

private:
	ConditionFactory** m_Factories;
	ushort             m_Size;

};

extern ConditionFactoryManager* g_pConditionFactoryManager;

#endif
