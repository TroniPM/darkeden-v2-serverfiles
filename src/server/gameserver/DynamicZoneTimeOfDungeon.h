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
	void init();		// ���̳��� �� �ʱ�ȭ
	void heartbeat();	// ���̳��� �� ��Ʈ��Ʈ

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
	// ���� ���� ��ġ�� �����Ѵ�.
	int m_ZoneID;
	int m_ZoneX;
	int m_ZoneY;
	
	// �ν���Ʈ ���� ����
	int	m_Indun;
};


DECLARE_DYNAMIC_ZONE_FACTORY( DynamicZoneTimeOfDungeon )

#endif

