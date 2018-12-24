/////////////////////////////////////////////////////////////////////////////
// DynamicZoneOustersMirrorOfAbyss.h
/////////////////////////////////////////////////////////////////////////////

#ifndef __DYNAMIC_ZONE_MINI_GAME2_H__
#define __DYNAMIC_ZONE_MINI_GAME2_H__

#include "DynamicZone.h"


///////////////////////////////////////////////////////////
// class DynamicZoneTimeOfDungeon
///////////////////////////////////////////////////////////
class DynamicZoneMiniGame2 : public DynamicZone
{
public:
	DynamicZoneMiniGame2();
	virtual ~DynamicZoneMiniGame2();

public:
	void init();		// ���̳��� �� �ʱ�ȭ
	void heartbeat();	// ���̳��� �� ��Ʈ��Ʈ

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

	void setStates( int States) { m_States = States; }
	int getStates() { return m_States; }

private:
	int m_OMOAStatus;
	Timeval m_RegenEffectTime;
	int m_States;
	int m_States_trasure;
	// ���� ���� ��ġ�� �����Ѵ�.
	int m_ZoneID;
	int m_ZoneX;
	int m_ZoneY;
	
	// �ν���Ʈ ���� ����
	int	m_Indun;
};


DECLARE_DYNAMIC_ZONE_FACTORY( DynamicZoneMiniGame2 )

#endif

