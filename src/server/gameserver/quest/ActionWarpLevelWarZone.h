//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionWarpLevelWarZone.h
// Written By  : 
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_WARP_LEVEL_WAR_ZONE_H__
#define __ACTION_WARP_LEVEL_WAR_ZONE_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionWarpLevelWarZone;
//////////////////////////////////////////////////////////////////////////////

class ActionWarpLevelWarZone : public Action 
{
public:
	virtual ActionType_t getActionType()  { return ACTION_WARP_LEVEL_WAR_ZONE; }
	virtual void read(PropertyBuffer & propertyBuffer);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL);
	virtual string toString() ;

public :

private :
	
};


//////////////////////////////////////////////////////////////////////////////
// class ActionWarpLevelWarZoneFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionWarpLevelWarZoneFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType()  { return Action::ACTION_WARP_LEVEL_WAR_ZONE; }
	virtual string getActionName()  { return "WarpLevelWarZone"; }
	virtual Action* createAction()  { return new ActionWarpLevelWarZone(); }

};

#endif
