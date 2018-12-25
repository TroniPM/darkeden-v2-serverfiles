//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionSearchMotorcycle.h
// Written By  : 
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_SEARCH_MOTORCYCLE_H__
#define __ACTION_SEARCH_MOTORCYCLE_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"
#include "Item.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionSearchMotorcycle;
//////////////////////////////////////////////////////////////////////////////

class ActionSearchMotorcycle : public Action 
{
public:
	virtual ActionType_t getActionType()  { return ACTION_SEARCH_MOTORCYCLE; }
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual void execute(Creature* pCreature1, Creature* pCreature2=NULL) throw(Error);
	virtual string toString() ;

protected:
	bool search(Item* pItem, uint& zoneid, uint& x, uint& y) ;
};


////////////////////////////////////////////////////////////////////////////////
// class ActionSearchMotorcycleFactory;
////////////////////////////////////////////////////////////////////////////////

class ActionSearchMotorcycleFactory : public ActionFactory 
{
public :
	virtual ActionType_t getActionType()  { return Action::ACTION_SEARCH_MOTORCYCLE; }
	virtual string getActionName()  { return "SearchMotorcycle"; }
	virtual Action* createAction()  { return new ActionSearchMotorcycle(); }
};



#endif
