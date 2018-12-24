/////////////////////////////////////////////////////////////////////////////
// DynamicZoneOustersMirrorOfAbyss.h
/////////////////////////////////////////////////////////////////////////////

#ifndef __DYNAMIC_ZONE_MINI_GAME_H__
#define __DYNAMIC_ZONE_MINI_GAME_H__

#include "DynamicZone.h"


///////////////////////////////////////////////////////////
// class DynamicZoneTimeOfDungeon
///////////////////////////////////////////////////////////
class DynamicZoneMiniGame : public DynamicZone
{
public:
	DynamicZoneMiniGame();
	virtual ~DynamicZoneMiniGame();

public:
	void init();		// 다이나믹 존 초기화
	void heartbeat();	// 다이나믹 존 하트비트

public:
	bool checkPC();
	bool addMono();
	bool openGateToOut();
	bool checkComplete();
	bool checkComplete2();
	void timecheck();
	void TreasureCheck();
	void addEffect();

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


private:
	int m_OMOAStatus;
	Timeval m_RegenEffectTime;
	int m_States;
	int m_States_trasure;
	// 들어온 곳의 위치를 저장한다.
	int m_ZoneID;
	int m_ZoneX;
	int m_ZoneY;
	
	// 인스턴트 던전 정보
	int	m_Indun;
};


DECLARE_DYNAMIC_ZONE_FACTORY( DynamicZoneMiniGame )

#endif

