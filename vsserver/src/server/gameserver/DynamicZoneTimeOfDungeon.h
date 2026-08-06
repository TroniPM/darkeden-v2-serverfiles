/////////////////////////////////////////////////////////////////////////////
// DynamicZoneOustersMirrorOfAbyss.h
/////////////////////////////////////////////////////////////////////////////

#ifndef __DYNAMIC_ZONE_TIME_OF_DUNGEON_H__
#define __DYNAMIC_ZONE_TIME_OF_DUNGEON_H__

#include "DynamicZone.h"


///////////////////////////////////////////////////////////
// class DynamicZoneTimeOfDungeon
///////////////////////////////////////////////////////////
class DynamicZoneTimeOfDungeon : public DynamicZone
{
public:
	DynamicZoneTimeOfDungeon();
	virtual ~DynamicZoneTimeOfDungeon();

public:
	void init();		// 다이나믹 존 초기화
	void heartbeat();	// 다이나믹 존 하트비트

public:
	bool checkPC();
	bool addMono();
	bool clearMono();
	bool openGateToOut();
	bool openGateToMiniGame();
	bool checkComplete();
	bool checkMono();
	bool checkMonster();
	void timecheck();
	void TreasureCheck();

	void processEntering();
	void killPC();

	void setZoneID( int ZoneID) { m_ZoneID = ZoneID; }
	void setZoneX( int ZoneX) { m_ZoneX = ZoneX; }
	void setZoneY( int ZoneY) { m_ZoneY = ZoneY; }

	int getZoneID() { return m_ZoneID; }
	ZoneCoord_t getZoneX() { return m_ZoneX; }
	ZoneCoord_t getZoneY() { return m_ZoneY; }

	int getInstantID() { return m_Indun; }
	void setInstantID( int Indun) { m_Indun = Indun; }

	int getStates() { return m_States; }
	void setStates( int States) { m_States = States; }

private:
	int m_OMOAStatus;
	int m_addTimesec;
	int m_States;
	int m_States_trasure;
	// 들어온 곳의 위치를 저장한다.
	int m_ZoneID;
	int m_ZoneX;
	int m_ZoneY;
	
	// 인스턴트 던전 정보
	int	m_Indun;
};


DECLARE_DYNAMIC_ZONE_FACTORY( DynamicZoneTimeOfDungeon )

#endif

