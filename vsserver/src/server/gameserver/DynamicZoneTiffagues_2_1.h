/////////////////////////////////////////////////////////////////////////////
// DynamicZoneOustersMirrorOfAbyss.h
/////////////////////////////////////////////////////////////////////////////

#ifndef __DYNAMIC_ZONE_TIFFAGUES_2_1_H__
#define __DYNAMIC_ZONE_TIFFAGUES_2_1_H__

#include "DynamicZone.h"


///////////////////////////////////////////////////////////
// class DynamicZoneBossRoom
///////////////////////////////////////////////////////////
class DynamicZoneTiffagues_2_1 : public DynamicZone
{
public:
	DynamicZoneTiffagues_2_1();
	virtual ~DynamicZoneTiffagues_2_1();

public:
	void init();		// 다이나믹 존 초기화
	void heartbeat();	// 다이나믹 존 하트비트

public:
	bool checkPC();
	bool addMono();
	void addBlock(int blockType);
	void clearBlock(int blockType);
	void addMsg(int blockType);
	void addMonster(int Type);
	void AddEffect(int blockType);
	bool clearMono();
	bool openGateToOut();
	bool checkComplete();
	bool checkMono();
	bool checkMsgComplete();
	bool checkMonsterMsgComplete();
	bool sayMonster();
	void timecheck();
	void processEntering();
	bool openGateToStage();
	void killPC();
	void TreasureCheck();
	void TreasureCheck2();
	bool checkMonster();

	int getInstantID() { return m_Indun; }
	void setInstantID( int Indun) { m_Indun = Indun; }

	void setZoneID( int ZoneID) { m_ZoneID = ZoneID; }
	void setZoneX( int ZoneX) { m_ZoneX = ZoneX; }
	void setZoneY( int ZoneY) { m_ZoneY = ZoneY; }

private:
	int m_OMOAStatus;
	ObjectID_t m_MonoObjectID;
	Timeval m_EndTime;
	Timeval m_TimeMsg;
	Timeval m_TimeMonsterMsg;
	int m_ZoneID;
	int m_ZoneX;
	int m_ZoneY;

	int m_Stage;
	int m_StageMessage;
	int m_TrapStage;

	// 인스턴트 던전 정보
	int	m_Indun;
};


DECLARE_DYNAMIC_ZONE_FACTORY( DynamicZoneTiffagues_2_1 )

#endif

