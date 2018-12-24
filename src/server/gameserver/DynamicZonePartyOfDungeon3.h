/////////////////////////////////////////////////////////////////////////////
// DynamicZonePartyOfDungeon.h
/////////////////////////////////////////////////////////////////////////////

#ifndef __DYNAMIC_ZONE_PARTY_OF_DUNGEON3_H__
#define __DYNAMIC_ZONE_PARTY_OF_DUNGEON3_H__

#include "DynamicZone.h"


///////////////////////////////////////////////////////////
// class DynamicZonePartyOfDungeon
///////////////////////////////////////////////////////////
class DynamicZonePartyOfDungeon3 : public DynamicZone
{
public:
	DynamicZonePartyOfDungeon3();
	virtual ~DynamicZonePartyOfDungeon3();

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
	void addItem2();
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
	int m_OMOAStatus;
	int m_GroupID;
	int m_CountMonster;
	int m_MonsterSize;
	int m_ItemCreate;
	int m_ZoneID;
	int m_ZoneX;
	int m_ZoneY;
	Timeval m_EndTime;
};


DECLARE_DYNAMIC_ZONE_FACTORY( DynamicZonePartyOfDungeon3 )

#endif

