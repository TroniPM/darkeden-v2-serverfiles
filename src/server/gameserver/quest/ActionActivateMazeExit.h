//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionActivateMazeExit.h
// Written By  : excel96
// Description : 
// Creature가 PC에게 질문을 던진다. 이 대사는 NPC 대화창에 출력된다.
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_ACTIVATE_MAZE_EXIT_H__
#define __ACTION_ACTIVATE_MAZE_EXIT_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionActivateMazeExit
//////////////////////////////////////////////////////////////////////////////

class ActionActivateMazeExit : public Action 
{
public:
	virtual ActionType_t getActionType()  { return ACTION_ACTIVATE_MAZE_EXIT; }
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) throw(Error);
	virtual string toString() ;

public:
	ZoneID_t    getGoodZoneID(void)  { return m_GoodZoneID; }
	ZoneCoord_t getGoodX(void)  { return m_GoodX; }
	ZoneCoord_t getGoodY(void)  { return m_GoodY; }
	ZoneID_t    getBadZoneID(void)  { return m_BadZoneID; }
	ZoneCoord_t getBadX(void)  { return m_BadX; }
	ZoneCoord_t getBadY(void)  { return m_BadY; }
	int			getExitID()  { return m_ExitID; }

private:
	ZoneID_t    m_GoodZoneID;
	ZoneCoord_t m_GoodX;
	ZoneCoord_t m_GoodY;
	ZoneID_t    m_BadZoneID;
	ZoneCoord_t m_BadX;
	ZoneCoord_t m_BadY;
	int			m_ExitID;
};


//////////////////////////////////////////////////////////////////////////////
// class ActionActivateMazeExitFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionActivateMazeExitFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType()  { return Action::ACTION_ACTIVATE_MAZE_EXIT; }
	virtual string getActionName()  { return "ActivateMazeExit"; }
	virtual Action* createAction()  { return new ActionActivateMazeExit(); }
};
#endif
