/////////////////////////////////////////////////////////////////////////////
// DynamicZoneSlayerMirrorOfAbyss.h
/////////////////////////////////////////////////////////////////////////////

#ifndef __DYNAMIC_ZONE_CASTLE_OF_DEFENSE_H__
#define __DYNAMIC_ZONE_CASTLE_OF_DEFENSE_H__

#include "DynamicZone.h"


///////////////////////////////////////////////////////////
// class DynamicZoneCastleOfDefense
///////////////////////////////////////////////////////////
class DynamicZoneCastleOfDefense : public DynamicZone
{
public:
	DynamicZoneCastleOfDefense();
	virtual ~DynamicZoneCastleOfDefense();

public:
	void init();		// 다이나믹 존 초기화
	void heartbeat();	// 다이나믹 존 하트비트

public:
	bool checkPC();
	bool addMono();
	bool clearMono();
	bool openGateToOut();
	bool checkComplete();
	bool checkRegenComplete();
	bool checkMono();
	bool checkMonster();
	bool addMonster();

	void processEntering();
	void killPC();

	void TreasureCheck();
	void TreasureCheck2();

	void setZoneID( int ZoneID) { m_ZoneID = ZoneID; }
	void setZoneX( int ZoneX) { m_ZoneX = ZoneX; }
	void setZoneY( int ZoneY) { m_ZoneY = ZoneY; }

	int getInstantID() { return m_Indun; }
	void setInstantID( int Indun) { m_Indun = Indun; }

	int getStatus() { return m_States; }
	void setStatus( int States) { m_States = States; }

private:
	int m_SMOAStatus;
	ObjectID_t m_MonoObjectID;
	Timeval m_EndTime;
	Timeval m_RegenTime;

	int m_States;

	int m_ZoneID;
	int m_ZoneX;
	int m_ZoneY;

	int	m_Indun;

	int	m_TreasureCheck;

};


DECLARE_DYNAMIC_ZONE_FACTORY( DynamicZoneCastleOfDefense )

#endif

