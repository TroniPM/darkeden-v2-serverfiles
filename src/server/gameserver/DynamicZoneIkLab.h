/////////////////////////////////////////////////////////////////////////////
// DynamicZoneOustersMirrorOfAbyss.h
/////////////////////////////////////////////////////////////////////////////

#ifndef __DYNAMIC_ZONE_IK_LAB_H__
#define __DYNAMIC_ZONE_IK_LAB_H__

#include "DynamicZone.h"


///////////////////////////////////////////////////////////
// class DynamicZoneBossRoom
///////////////////////////////////////////////////////////
class DynamicZoneIkLab : public DynamicZone
{
public:
	DynamicZoneIkLab();
	virtual ~DynamicZoneIkLab();

public:
	void init();		// 다이나믹 존 초기화
	void heartbeat();	// 다이나믹 존 하트비트

public:
	bool checkPC();
	bool addMono();
	bool clearMono();
	bool openGateToOut();
	bool checkComplete();
	bool checkMono();
	void timecheck();
	void processEntering();
	void killPC();

	int getInstantID() { return m_Indun; }
	void setInstantID( int Indun) { m_Indun = Indun; }

	void setZoneID( int ZoneID) { m_ZoneID = ZoneID; }
	void setZoneX( int ZoneX) { m_ZoneX = ZoneX; }
	void setZoneY( int ZoneY) { m_ZoneY = ZoneY; }

private:
	int m_OMOAStatus;
	ObjectID_t m_MonoObjectID;
	ObjectID_t m_MonoObjectID2;
	ObjectID_t m_MonoObjectID3;
	Timeval m_EndTime;
	int m_ZoneID;
	int m_ZoneX;
	int m_ZoneY;

	// 인스턴트 던전 정보
	int	m_Indun;
};


DECLARE_DYNAMIC_ZONE_FACTORY( DynamicZoneIkLab )

#endif

