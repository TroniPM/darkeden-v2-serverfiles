//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionActivateMazeReturn.h
// Written By  : excel96
// Description : 
// Creature가 PC에게 질문을 던진다. 이 대사는 NPC 대화창에 출력된다.
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_ACTIVATE_MAZE_RETURN_H__
#define __ACTION_ACTIVATE_MAZE_RETURN_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionActivateMazeReturn
//////////////////////////////////////////////////////////////////////////////

class ActionActivateMazeReturn : public Action 
{
public:
	virtual ActionType_t getActionType()  { return ACTION_ACTIVATE_MAZE_RETURN; }
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) throw(Error);
	virtual string toString() ;

public:
	ZoneID_t    getZoneID(void)  { return m_ZoneID; }
	ZoneCoord_t getX(void)  { return m_X; }
	ZoneCoord_t getY(void)  { return m_Y; }

private:
	ZoneID_t    m_ZoneID;
	ZoneCoord_t m_X;
	ZoneCoord_t m_Y;
};


//////////////////////////////////////////////////////////////////////////////
// class ActionActivateMazeReturnFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionActivateMazeReturnFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType()  { return Action::ACTION_ACTIVATE_MAZE_RETURN; }
	virtual string getActionName()  { return "ActivateMazeReturn"; }
	virtual Action* createAction()  { return new ActionActivateMazeReturn(); }
};
#endif
