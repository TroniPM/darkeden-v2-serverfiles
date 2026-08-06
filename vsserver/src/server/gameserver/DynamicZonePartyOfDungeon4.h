/////////////////////////////////////////////////////////////////////////////
// DynamicZonePartyOfDungeon.h
/////////////////////////////////////////////////////////////////////////////

#ifndef __DYNAMIC_ZONE_PARTY_OF_DUNGEON4_H__
#define __DYNAMIC_ZONE_PARTY_OF_DUNGEON4_H__

#include "DynamicZone.h"
#include <list>


///////////////////////////////////////////////////////////
// class DynamicZonePartyOfDungeon
///////////////////////////////////////////////////////////
class DynamicZonePartyOfDungeon4 : public DynamicZone
{
public:
	DynamicZonePartyOfDungeon4();
	virtual ~DynamicZonePartyOfDungeon4();

public:
	void init();		// 다이나믹 존 초기화
	void heartbeat();	// 다이나믹 존 하트비트

public:
	bool checkPC();
	bool addMono();
	bool clearMono();
	bool openGateToOut();
	bool checkComplete();
	//bool checkMono();
	bool CountMonster();
	void addItem();
	void timecheck();
	void processEntering();
	void killPC();

	void setGroupID( int setGroupID) { m_GroupID = setGroupID; }
	void setZoneID( int ZoneID) { m_ZoneID = ZoneID; }
	void setZoneX( int ZoneX) { m_ZoneX = ZoneX; }
	void setZoneY( int ZoneY) { m_ZoneY = ZoneY; }

	int getZoneID() { return m_ZoneID; }
	ZoneCoord_t getZoneX() { return m_ZoneX; }
	ZoneCoord_t getZoneY() { return m_ZoneY; }
private:
	int m_TowerEnd;
	int m_OMOAStatus;
	int m_GroupID;
	int m_CountMonster;
	int m_NextStage;
	int m_PrevStage;
	int m_ZoneID;
	int m_ZoneX;
	int m_ZoneY;
	Timeval m_EndTime;
	int m_SaveTime;
};


DECLARE_DYNAMIC_ZONE_FACTORY( DynamicZonePartyOfDungeon4 )

#endif

