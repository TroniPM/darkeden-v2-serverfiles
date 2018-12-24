/////////////////////////////////////////////////////////////////////////////
// DynamicZoneSlayerMirrorOfAbyss.h
/////////////////////////////////////////////////////////////////////////////

#ifndef __DYNAMIC_ZONE_SLAYER_MIRROR_OF_ABYSS_H__
#define __DYNAMIC_ZONE_SLAYER_MIRROR_OF_ABYSS_H__

#include "DynamicZone.h"


///////////////////////////////////////////////////////////
// class DynamicZoneSlayerMirrorOfAbyss
///////////////////////////////////////////////////////////
class DynamicZoneSlayerMirrorOfAbyss : public DynamicZone
{
public:
	DynamicZoneSlayerMirrorOfAbyss();
	virtual ~DynamicZoneSlayerMirrorOfAbyss();

public:
	void init();		// ���̳��� �� �ʱ�ȭ
	void heartbeat();	// ���̳��� �� ��Ʈ��Ʈ

public:
	bool checkPC();
	bool addMono();
	bool clearMono();
	bool openGateToOut();
	bool checkComplete();
	bool checkMono();

	void processEntering();
	void killPC();

private:
	int m_SMOAStatus;
	ObjectID_t m_MonoObjectID;
	Timeval m_EndTime;
};


DECLARE_DYNAMIC_ZONE_FACTORY( DynamicZoneSlayerMirrorOfAbyss )

#endif

