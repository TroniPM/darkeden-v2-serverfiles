/////////////////////////////////////////////////////////////////////////////
// Dynamic Zone Info
/////////////////////////////////////////////////////////////////////////////

#ifndef __DYNAMIC_ZONE_INFO__
#define __DYNAMIC_ZONE_INFO__

#include "Types.h"
#include <hash_map>

enum DYNAMIC_ZONE_TYPE
{
	DYNAMIC_ZONE_GATE_OF_ALTER = 0,
	DYNAMIC_ZONE_ALTER_OF_BLOOD,
	DYNAMIC_ZONE_SLAYER_MIRROR_OF_ABYSS,
	DYNAMIC_ZONE_VAMPIRE_MIRROR_OF_ABYSS,
	DYNAMIC_ZONE_OUSTERS_MIRROR_OF_ABYSS,
	DYNAMIC_ZONE_PARTY_OF_DUNGEON,
	DYNAMIC_ZONE_PARTY_OF_DUNGEON2,
	DYNAMIC_ZONE_PARTY_OF_DUNGEON3,
	// �ﰡ�� Ÿ��
	DYNAMIC_ZONE_PARTY_OF_DUNGEON4,
	// �ƽǸ��� ���� ����
	DYNAMIC_ZONE_ASYLION,
	DYNAMIC_ZONE_TIME_OF_DUNGEON,
	DYNAMIC_ZONE_BOSS_ROOM,
	DYNAMIC_ZONE_BOSS_ROOM2,
	DYNAMIC_ZONE_MENEGROTH1,
	DYNAMIC_ZONE_MENEGROTH2,
	DYNAMIC_ZONE_MENEGROTH3,
	DYNAMIC_ZONE_MENEGROTH4,
	DYNAMIC_ZONE_MENEGROTH5,
	DYNAMIC_ZONE_MENEGROTH6,
	DYNAMIC_ZONE_CASTLE_OF_DEFENSE,
	DYNAMIC_ZONE_IK_LAB,
	DYNAMIC_ZONE_IK_LAB_SERCET,
	DYNAMIC_ZONE_TIFFAGUES_1,
	DYNAMIC_ZONE_MINI_GAME,
	DYNAMIC_ZONE_TIFFAGUES_2_1,
	DYNAMIC_ZONE_TIFFAGUES_2_2,
	DYNAMIC_ZONE_MINI_GAME2,
	DYNAMIC_ZONE_HILANOM,
	DYNAMIC_ZONE_MAX
};

///////////////////////////////////////////////////////////
// class DynamicZoneInfo
///////////////////////////////////////////////////////////
class DynamicZoneInfo
{
public:
	DynamicZoneInfo();
	~DynamicZoneInfo();

public:
	// get / set methods
	int getDynamicZoneType() const { return m_DynamicZoneType; }
	void setDynamicZoneType( int dynamicZoneType ) { m_DynamicZoneType = dynamicZoneType; }

	ZoneID_t getTemplateZoneID() const { return m_TemplateZoneID; }
	void setTemplateZoneID( ZoneID_t templateZoneID ) { m_TemplateZoneID = templateZoneID; }

private:
	int			m_DynamicZoneType;		// DynamicZoneType
	ZoneID_t	m_TemplateZoneID;		// ���̳��� ���� Ʋ�̵Ǵ� �� ID
};


///////////////////////////////////////////////////////////
// class DynamicZoneInfoManager
///////////////////////////////////////////////////////////
class DynamicZoneInfoManager
{
public:
	typedef hash_map<int,DynamicZoneInfo*>			HashMapDynamicZoneInfo;
	typedef HashMapDynamicZoneInfo::iterator		HashMapDynamicZoneInfoItor;
	typedef HashMapDynamicZoneInfo::const_iterator	HashMapDynamicZoneInfoConstItor;

	typedef hash_map<ZoneID_t,int>					HashMapDynamicZoneType;
	typedef HashMapDynamicZoneType::iterator		HashMapDynamicZoneTypeItor;
	typedef HashMapDynamicZoneType::const_iterator	HashMapDynamicZoneTypeConstItor;

public:
	DynamicZoneInfoManager();
	~DynamicZoneInfoManager();

public:
	void init();
	void clear();
	void addDynamicZoneInfo( DynamicZoneInfo* pDynamicZoneInfo );
	DynamicZoneInfo* getDynamicZoneInfo( int DynamicZoneType ) const;

	int getDynamicZoneTypeByZoneID( ZoneID_t zoneID ) const;

private:
	HashMapDynamicZoneInfo	m_DynamicZoneInfos;
	HashMapDynamicZoneType	m_DynamicZoneTypes;
};

// global variable
extern DynamicZoneInfoManager* g_pDynamicZoneInfoManager;

#endif

