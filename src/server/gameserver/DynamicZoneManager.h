/////////////////////////////////////////////////////////////////////////////
// DynamicZoneManager.h
// �������� ����� ��������ϴ� ���� �����ϴ� ��
/////////////////////////////////////////////////////////////////////////////

#ifndef __DYNAMIC_ZONE_MANAGER_H__
#define __DYNAMIC_ZONE_MANAGER_H__

#include "Types.h"
#include "Mutex.h"
#include <hash_map>

class DynamicZoneGroup;

///////////////////////////////////////////////////////////
// class DynamicZoneManager
///////////////////////////////////////////////////////////
class DynamicZoneManager
{
public:
	typedef hash_map<int,DynamicZoneGroup*>			HashMapDynamicZoneGroup;
	typedef HashMapDynamicZoneGroup::iterator		HashMapDynamicZoneGroupItor;
	typedef HashMapDynamicZoneGroup::const_iterator	HashMapDynamicZoneGroupConstItor;

public:
	DynamicZoneManager();
	~DynamicZoneManager();

public:
	void init();
	void clear();

	// ���� DynamicZoneGroup �� �߰��Ѵ�.
	void addDynamicZoneGroup( DynamicZoneGroup* pDynamicZoneGroup );

	// DynamicZoneGroup �� ã�Ƽ� ��ȯ�Ѵ�.
	DynamicZoneGroup* getDynamicZoneGroup( int dynamicZoneType );

	// get new dynamic zone id
	ZoneID_t getNewDynamicZoneID();

	static bool isDynamicZone( ZoneID_t zoneID );

private:
	Mutex m_Mutex;
	ZoneID_t m_DynamicZoneID;

	HashMapDynamicZoneGroup m_DynamicZoneGroups;
};

// global variable
extern DynamicZoneManager* g_pDynamicZoneManager;

#endif

