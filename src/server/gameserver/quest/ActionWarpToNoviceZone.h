//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionWarpToNoviceZone.h
// Written By  : excel96
// Description : 
// Creature가 PC에게 질문을 던진다. 이 대사는 NPC 대화창에 출력된다.
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_WARP_TO_NOVICE_ZONE_H__
#define __ACTION_WARP_TO_NOVICE_ZONE_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionWarpToNoviceZone
//////////////////////////////////////////////////////////////////////////////

class ActionWarpToNoviceZone : public Action 
{
public:
	virtual ActionType_t getActionType()  { return ACTION_WARP_TO_NOVICE_ZONE; }
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) throw(Error);
	virtual string toString() ;

public:
	ZoneID_t    getNoviceZoneID(void)  { return m_NoviceZoneID; }
	ZoneCoord_t getNoviceX(void)  { return m_NoviceX; }
	ZoneCoord_t getNoviceY(void)  { return m_NoviceY; }

	ZoneID_t    getBeginnerZoneID(void)  { return m_BeginnerZoneID; }
	ZoneCoord_t getBeginnerX(void)  { return m_BeginnerX; }
	ZoneCoord_t getBeginnerY(void)  { return m_BeginnerY; }

private:
	ZoneID_t    m_NoviceZoneID;
	ZoneCoord_t m_NoviceX;
	ZoneCoord_t m_NoviceY;

	ZoneID_t    m_BeginnerZoneID;
	ZoneCoord_t m_BeginnerX;
	ZoneCoord_t m_BeginnerY;
};


//////////////////////////////////////////////////////////////////////////////
// class ActionWarpToNoviceZoneFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionWarpToNoviceZoneFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType()  { return Action::ACTION_WARP_TO_NOVICE_ZONE; }
	virtual string getActionName()  { return "WarpToNoviceZone"; }
	virtual Action* createAction()  { return new ActionWarpToNoviceZone(); }
};
#endif
