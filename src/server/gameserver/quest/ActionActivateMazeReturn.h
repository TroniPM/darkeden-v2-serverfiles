//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionActivateMazeReturn.h
// Written By  : excel96
// Description : 
// Creature�� PC���� ������ ������. �� ���� NPC ��ȭâ�� ��µȴ�.
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
	virtual ActionType_t getActionType() const throw() { return ACTION_ACTIVATE_MAZE_RETURN; }
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) throw(Error);
	virtual string toString() const throw();

public:
	ZoneID_t    getZoneID(void) const throw() { return m_ZoneID; }
	ZoneCoord_t getX(void) const throw() { return m_X; }
	ZoneCoord_t getY(void) const throw() { return m_Y; }

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
	virtual ActionType_t getActionType() const throw() { return Action::ACTION_ACTIVATE_MAZE_RETURN; }
	virtual string getActionName() const throw() { return "ActivateMazeReturn"; }
	virtual Action* createAction() const throw() { return new ActionActivateMazeReturn(); }
};
#endif
