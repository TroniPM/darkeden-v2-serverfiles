/////////////////////////////////////////////////////////////////////////////
// DynamicZoneOustersMirrorOfAbyss.h
/////////////////////////////////////////////////////////////////////////////

#ifndef __DYNAMIC_ZONE_HILANOM_H__
#define __DYNAMIC_ZONE_HILANOM_H__

#include "DynamicZone.h"


///////////////////////////////////////////////////////////
// class DynamicZoneBossRoom
///////////////////////////////////////////////////////////
class DynamicZoneHilanom : public DynamicZone
{
public:
	DynamicZoneHilanom();
	virtual ~DynamicZoneHilanom();

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

	void addBlock(int blockType);
	void clearBlock(int blockType);
	bool checkMonsterMsgComplete();
	void TreasureCheck(int Type);
	void addMonster(int Type);
	void SubaddMonster(int Type);
	bool checkMonster();
	bool sayMonster();

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

	// 인스턴트 던전 정보
	int	m_Indun;
	int m_Stage;
	Timeval m_TimeMonsterMsg;
};


DECLARE_DYNAMIC_ZONE_FACTORY( DynamicZoneHilanom )

#endif

