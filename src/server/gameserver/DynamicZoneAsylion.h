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
	void init();		// ���̳��� �� �ʱ�ȭ
	void heartbeat();	// ���̳��� �� ��Ʈ��Ʈ

public:
	bool checkPC();
	bool addOffering();
	bool checkNoOffering();
	bool clearOffering();
	bool openGateToOut();
	
	// �ð��� üũ�� �־�� �Ѵ�.
	bool checkComplete();
	void timecheck();

	// ���� ���Ͱ� ���´�
	bool addMono();
	bool clearMono();
	bool checkMono();

	// ���� �Լ�
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

	// �ð� Ÿ�̸� ���� �Լ�
	Timeval m_EndTime;

	// ���� ���� ��ġ�� �����Ѵ�.
	int m_ZoneID;
	int m_ZoneX;
	int m_ZoneY;
	
	// �ν���Ʈ ���� ����
	int	m_Indun;
};


DECLARE_DYNAMIC_ZONE_FACTORY( DynamicZoneAsylion )

#endif

