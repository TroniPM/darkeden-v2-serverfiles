/////////////////////////////////////////////////////////////////////////////
// DynamicZoneGateOfAlter.h
/////////////////////////////////////////////////////////////////////////////

#ifndef __DYNAMIC_ZONE_GATE_OF_ALTER_H__
#define __DYNAMIC_ZONE_GATE_OF_ALTER_H__

#include "Types.h"
#include "DynamicZone.h"

///////////////////////////////////////////////////////////
// class DynamicZoneGateOfAlter
///////////////////////////////////////////////////////////
class DynamicZoneGateOfAlter : public DynamicZone
{
public:
	DynamicZoneGateOfAlter();
	virtual ~DynamicZoneGateOfAlter();

public:
	void init();		// ���̳��� �� �ʱ�ȭ
	void heartbeat();	// ���̳��� �� ��Ʈ��Ʈ

public:
	bool checkPC();
	bool addTileEffect();
	bool checkNoEffect();
	bool openGateToAlter();
	bool removeTileEffect();

	void processEntering();
	void removeEffect( ZoneCoord_t x, ZoneCoord_t y );
	void addFakeEffect();

private:
	int m_GOAStatus;
};


DECLARE_DYNAMIC_ZONE_FACTORY( DynamicZoneGateOfAlter )

#endif

