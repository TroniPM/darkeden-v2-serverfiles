/////////////////////////////////////////////////////////////////////////////
// DynamicZoneOustersMirrorOfAbyss.h
/////////////////////////////////////////////////////////////////////////////

#ifndef __DYNAMIC_ZONE_MENEGROTH2_H__
#define __DYNAMIC_ZONE_MENEGROTH2_H__

#include "DynamicZone.h"


///////////////////////////////////////////////////////////
// class DynamicZoneBossRoom
///////////////////////////////////////////////////////////
class DynamicZoneMenegroth2 : public DynamicZone
{
public:
	DynamicZoneMenegroth2();
	virtual ~DynamicZoneMenegroth2();

public:
	void init();		// 다이나믹 존 초기화
	void heartbeat();	// 다이나믹 존 하트비트

public:
	bool checkPC();
	bool addMono();
	bool clearMonster();
	bool addMonster();
	bool clearMono();
	bool openGateToOut();
	bool openGateToOutNextStage();
	bool checkComplete();
	bool addMonster_boss_regen();
	bool checkMonster();
	bool checkbossmonster();
	bool checkMono();
	bool checkMonoHPcount();
	bool checkMonoEffect();
	void timecheck();
	void processEntering();
	void killPC();
	void TreasureCheck();

	int getInstantID() { return m_Indun; }
	void setInstantID( int Indun) { m_Indun = Indun; }

	void setZoneID( int ZoneID) { m_ZoneID = ZoneID; }
	void setZoneX( int ZoneX) { m_ZoneX = ZoneX; }
	void setZoneY( int ZoneY) { m_ZoneY = ZoneY; }

private:
	int m_OMOAStatus;
	ObjectID_t m_MonoObjectID;
	Timeval m_EndTime;
	int m_ZoneID;
	int m_ZoneX;
	int m_ZoneY;
	int	m_CabracamHP;
	// 인스턴트 던전 정보
	int	m_Indun;
};


DECLARE_DYNAMIC_ZONE_FACTORY( DynamicZoneMenegroth2 )

#endif

