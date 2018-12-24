/////////////////////////////////////////////////////////////////////////////
// DynamicZoneAlterOfBlood.h
/////////////////////////////////////////////////////////////////////////////

#ifndef __DYNAMIC_ZONE_ASYLION_H__
#define __DYNAMIC_ZONE_ASYLION_H__

#include "DynamicZone.h"


///////////////////////////////////////////////////////////
// class DynamicZoneAlterOfBlood
///////////////////////////////////////////////////////////
class DynamicZoneAsylion : public DynamicZone
{
public:
	DynamicZoneAsylion();
	virtual ~DynamicZoneAsylion();

public:
	void init();		// 다이나믹 존 초기화
	void heartbeat();	// 다이나믹 존 하트비트

public:
	bool checkPC();
	bool addOffering();
	bool checkNoOffering();
	bool clearOffering();
	bool openGateToOut();
	
	// 시간을 체크해 주어야 한다.
	bool checkComplete();
	void timecheck();

	// 보스 몬스터가 나온다
	bool addMono();
	bool clearMono();
	bool checkMono();

	// 지역 함수
	void setZoneID( int ZoneID) { m_ZoneID = ZoneID; }
	void setZoneX( int ZoneX) { m_ZoneX = ZoneX; }
	void setZoneY( int ZoneY) { m_ZoneY = ZoneY; }

	int getZoneID() { return m_ZoneID; }
	ZoneCoord_t getZoneX() { return m_ZoneX; }
	ZoneCoord_t getZoneY() { return m_ZoneY; }

	int getInstantID() { return m_Indun; }
	void setInstantID( int Indun) { m_Indun = Indun; }

public:
	void setRace( Race_t race ) { m_Race = race; }

private:
	int m_AOBStatus;
	Race_t m_Race;
	ObjectID_t m_OfferingObjectID[5];
	ObjectID_t m_MonoObjectID;

	// 시간 타이머 관련 함수
	Timeval m_EndTime;

	// 들어온 곳의 위치를 저장한다.
	int m_ZoneID;
	int m_ZoneX;
	int m_ZoneY;
	
	// 인스턴트 던전 정보
	int	m_Indun;
};


DECLARE_DYNAMIC_ZONE_FACTORY( DynamicZoneAsylion )

#endif

