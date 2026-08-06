/////////////////////////////////////////////////////////////////////////////
// DynamicZonePartyOfDungeon.h
/////////////////////////////////////////////////////////////////////////////

#ifndef __DYNAMIC_ZONE_PARTY_OF_DUNGEON2_H__
#define __DYNAMIC_ZONE_PARTY_OF_DUNGEON2_H__

#include "DynamicZone.h"


///////////////////////////////////////////////////////////
// class DynamicZonePartyOfDungeon
///////////////////////////////////////////////////////////
class DynamicZonePartyOfDungeon2 : public DynamicZone
{
public:
	DynamicZonePartyOfDungeon2();
	virtual ~DynamicZonePartyOfDungeon2();

public:
	void init();		// 다이나믹 존 초기화
	void heartbeat();	// 다이나믹 존 하트비트

public:
	bool checkPC();
	bool addMono();
	bool addMono2();
	bool clearMono();
	bool openGateToOut();
	bool checkComplete();
	bool checkMono();
	bool checkMono2();
	void CountMonster();
	void addItem();
	void processEntering();
	void killPC();

	void setGroupID( int setGroupID) { m_GroupID = setGroupID; }
	void setZoneID( int ZoneID) { m_ZoneID = ZoneID; }
	void setZoneX( int ZoneX) { m_ZoneX = ZoneX; }
	void setZoneY( int ZoneY) { m_ZoneY = ZoneY; }

	int getZoneID() { return m_ZoneID; }
	ZoneCoord_t getZoneX() { return m_ZoneX; }
	ZoneCoord_t getZoneY() { return m_ZoneY; }

	int getBossID() const { return m_BossID; }
	void setBossID( int GroupID ) { m_BossID = GroupID; }
private:
	int m_OMOAStatus;
	int m_GroupID;
	int m_CountMonster;
	int m_PersentMonster;
	int m_SkullPrice;
	int m_ZoneID;
	int m_ZoneX;
	int m_ZoneY;
	int m_BossID;
	ObjectID_t m_MonoObjectID;
	ObjectID_t m_MonoObjectID1;
	ObjectID_t m_MonoObjectID2;
	ObjectID_t m_MonoObjectID3;
	Timeval m_EndTime;
};


DECLARE_DYNAMIC_ZONE_FACTORY( DynamicZonePartyOfDungeon2 )

#endif

