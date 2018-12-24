/////////////////////////////////////////////////////////////////////////////
// DynamicZoneManager.cpp
// 서버에서 생겼다 사라졌다하는 존을 관리하는 넘
/////////////////////////////////////////////////////////////////////////////

// include files
#include "DynamicZoneManager.h"
#include "DynamicZoneGroup.h"
#include "DynamicZoneInfo.h"
#include "Assert.h"

// global variable
DynamicZoneManager* g_pDynamicZoneManager = NULL;

// 새로 만들기 시작할 DynamicZoneID 시작 위치
// 만들때마다 1 씩 증가
const ZoneID_t StartDynamicZoneID = 15001;

// constructor
DynamicZoneManager::DynamicZoneManager()
	: m_DynamicZoneID( StartDynamicZoneID )
{
	m_Mutex.setName( "DynamicZoneManager" );
}

// destructor
DynamicZoneManager::~DynamicZoneManager()
{
	clear();
}

void DynamicZoneManager::init()
{
	// DynamicZoneGroup 추가. 수동
	
	{
		// 제단 입구
		DynamicZoneGroup* pDynamicZoneGroup = new DynamicZoneGroup();
		pDynamicZoneGroup->setDynamicZoneType( DYNAMIC_ZONE_GATE_OF_ALTER );
		pDynamicZoneGroup->setTemplateZoneID( g_pDynamicZoneInfoManager->getDynamicZoneInfo( DYNAMIC_ZONE_GATE_OF_ALTER )->getTemplateZoneID() );

		addDynamicZoneGroup( pDynamicZoneGroup );
	}

	{
		// 피의 제단
		DynamicZoneGroup* pDynamicZoneGroup = new DynamicZoneGroup();
		pDynamicZoneGroup->setDynamicZoneType( DYNAMIC_ZONE_ALTER_OF_BLOOD );
		pDynamicZoneGroup->setTemplateZoneID( g_pDynamicZoneInfoManager->getDynamicZoneInfo( DYNAMIC_ZONE_ALTER_OF_BLOOD )->getTemplateZoneID() );

		addDynamicZoneGroup( pDynamicZoneGroup );
	}

	{
		// 슬레이어 심연의 거울
		DynamicZoneGroup* pDynamicZoneGroup = new DynamicZoneGroup();
		pDynamicZoneGroup->setDynamicZoneType( DYNAMIC_ZONE_SLAYER_MIRROR_OF_ABYSS );
		pDynamicZoneGroup->setTemplateZoneID( g_pDynamicZoneInfoManager->getDynamicZoneInfo( DYNAMIC_ZONE_SLAYER_MIRROR_OF_ABYSS )->getTemplateZoneID() );

		addDynamicZoneGroup( pDynamicZoneGroup );
	}

	{
		// 뱀파이어 심연의 거울
		DynamicZoneGroup* pDynamicZoneGroup = new DynamicZoneGroup();
		pDynamicZoneGroup->setDynamicZoneType( DYNAMIC_ZONE_VAMPIRE_MIRROR_OF_ABYSS );
		pDynamicZoneGroup->setTemplateZoneID( g_pDynamicZoneInfoManager->getDynamicZoneInfo( DYNAMIC_ZONE_VAMPIRE_MIRROR_OF_ABYSS )->getTemplateZoneID() );

		addDynamicZoneGroup( pDynamicZoneGroup );
	}

	{
		// 아우스터즈 심연의 거울
		DynamicZoneGroup* pDynamicZoneGroup = new DynamicZoneGroup();
		pDynamicZoneGroup->setDynamicZoneType( DYNAMIC_ZONE_OUSTERS_MIRROR_OF_ABYSS );
		pDynamicZoneGroup->setTemplateZoneID( g_pDynamicZoneInfoManager->getDynamicZoneInfo( DYNAMIC_ZONE_OUSTERS_MIRROR_OF_ABYSS )->getTemplateZoneID() );

		addDynamicZoneGroup( pDynamicZoneGroup );
	}

	{
		// 아우스터즈 심연의 거울
		DynamicZoneGroup* pDynamicZoneGroup = new DynamicZoneGroup();
		pDynamicZoneGroup->setDynamicZoneType( DYNAMIC_ZONE_PARTY_OF_DUNGEON );
		pDynamicZoneGroup->setTemplateZoneID( g_pDynamicZoneInfoManager->getDynamicZoneInfo( DYNAMIC_ZONE_PARTY_OF_DUNGEON )->getTemplateZoneID() );

		addDynamicZoneGroup( pDynamicZoneGroup );
	}

	{
		// 아우스터즈 심연의 거울
		DynamicZoneGroup* pDynamicZoneGroup = new DynamicZoneGroup();
		pDynamicZoneGroup->setDynamicZoneType( DYNAMIC_ZONE_PARTY_OF_DUNGEON2 );
		pDynamicZoneGroup->setTemplateZoneID( g_pDynamicZoneInfoManager->getDynamicZoneInfo( DYNAMIC_ZONE_PARTY_OF_DUNGEON2 )->getTemplateZoneID() );

		addDynamicZoneGroup( pDynamicZoneGroup );
	}

	{
		// 아우스터즈 심연의 거울
		DynamicZoneGroup* pDynamicZoneGroup = new DynamicZoneGroup();
		pDynamicZoneGroup->setDynamicZoneType( DYNAMIC_ZONE_PARTY_OF_DUNGEON3 );
		pDynamicZoneGroup->setTemplateZoneID( g_pDynamicZoneInfoManager->getDynamicZoneInfo( DYNAMIC_ZONE_PARTY_OF_DUNGEON3 )->getTemplateZoneID() );

		addDynamicZoneGroup( pDynamicZoneGroup );
	}

	{
		// 헬가든 타워
		DynamicZoneGroup* pDynamicZoneGroup = new DynamicZoneGroup();
		pDynamicZoneGroup->setDynamicZoneType( DYNAMIC_ZONE_PARTY_OF_DUNGEON4 );
		pDynamicZoneGroup->setTemplateZoneID( g_pDynamicZoneInfoManager->getDynamicZoneInfo( DYNAMIC_ZONE_PARTY_OF_DUNGEON4 )->getTemplateZoneID() );

		addDynamicZoneGroup( pDynamicZoneGroup );
	}

	{
		// 아실리온
		DynamicZoneGroup* pDynamicZoneGroup = new DynamicZoneGroup();
		pDynamicZoneGroup->setDynamicZoneType( DYNAMIC_ZONE_ASYLION );
		pDynamicZoneGroup->setTemplateZoneID( g_pDynamicZoneInfoManager->getDynamicZoneInfo( DYNAMIC_ZONE_ASYLION )->getTemplateZoneID() );

		addDynamicZoneGroup( pDynamicZoneGroup );
	}

	{
		// 타임오브존
		DynamicZoneGroup* pDynamicZoneGroup = new DynamicZoneGroup();
		pDynamicZoneGroup->setDynamicZoneType( DYNAMIC_ZONE_TIME_OF_DUNGEON );
		pDynamicZoneGroup->setTemplateZoneID( g_pDynamicZoneInfoManager->getDynamicZoneInfo( DYNAMIC_ZONE_TIME_OF_DUNGEON )->getTemplateZoneID() );

		addDynamicZoneGroup( pDynamicZoneGroup );
	}

	{
		// 보스 전용 방이다.
		DynamicZoneGroup* pDynamicZoneGroup = new DynamicZoneGroup();
		pDynamicZoneGroup->setDynamicZoneType( DYNAMIC_ZONE_BOSS_ROOM );
		pDynamicZoneGroup->setTemplateZoneID( g_pDynamicZoneInfoManager->getDynamicZoneInfo( DYNAMIC_ZONE_BOSS_ROOM )->getTemplateZoneID() );

		addDynamicZoneGroup( pDynamicZoneGroup );
	}

	{
		// 보스 전용 방이다.
		DynamicZoneGroup* pDynamicZoneGroup = new DynamicZoneGroup();
		pDynamicZoneGroup->setDynamicZoneType( DYNAMIC_ZONE_BOSS_ROOM2 );
		pDynamicZoneGroup->setTemplateZoneID( g_pDynamicZoneInfoManager->getDynamicZoneInfo( DYNAMIC_ZONE_BOSS_ROOM2 )->getTemplateZoneID() );

		addDynamicZoneGroup( pDynamicZoneGroup );
	}
	//
	// 매네그로스
	//

	{
		// 보스 전용 방이다.
		DynamicZoneGroup* pDynamicZoneGroup = new DynamicZoneGroup();
		pDynamicZoneGroup->setDynamicZoneType( DYNAMIC_ZONE_MENEGROTH1 );
		pDynamicZoneGroup->setTemplateZoneID( g_pDynamicZoneInfoManager->getDynamicZoneInfo( DYNAMIC_ZONE_MENEGROTH1 )->getTemplateZoneID() );

		addDynamicZoneGroup( pDynamicZoneGroup );
	}

	{
		// 보스 전용 방이다.
		DynamicZoneGroup* pDynamicZoneGroup = new DynamicZoneGroup();
		pDynamicZoneGroup->setDynamicZoneType( DYNAMIC_ZONE_MENEGROTH2 );
		pDynamicZoneGroup->setTemplateZoneID( g_pDynamicZoneInfoManager->getDynamicZoneInfo( DYNAMIC_ZONE_MENEGROTH2 )->getTemplateZoneID() );

		addDynamicZoneGroup( pDynamicZoneGroup );
	}

	{
		// 보스 전용 방이다.
		DynamicZoneGroup* pDynamicZoneGroup = new DynamicZoneGroup();
		pDynamicZoneGroup->setDynamicZoneType( DYNAMIC_ZONE_MENEGROTH3);
		pDynamicZoneGroup->setTemplateZoneID( g_pDynamicZoneInfoManager->getDynamicZoneInfo( DYNAMIC_ZONE_MENEGROTH3 )->getTemplateZoneID() );

		addDynamicZoneGroup( pDynamicZoneGroup );
	}

	{
		// 보스 전용 방이다.
		DynamicZoneGroup* pDynamicZoneGroup = new DynamicZoneGroup();
		pDynamicZoneGroup->setDynamicZoneType( DYNAMIC_ZONE_MENEGROTH4);
		pDynamicZoneGroup->setTemplateZoneID( g_pDynamicZoneInfoManager->getDynamicZoneInfo( DYNAMIC_ZONE_MENEGROTH4 )->getTemplateZoneID() );

		addDynamicZoneGroup( pDynamicZoneGroup );
	}

	{
		// 보스 전용 방이다.
		DynamicZoneGroup* pDynamicZoneGroup = new DynamicZoneGroup();
		pDynamicZoneGroup->setDynamicZoneType( DYNAMIC_ZONE_MENEGROTH5);
		pDynamicZoneGroup->setTemplateZoneID( g_pDynamicZoneInfoManager->getDynamicZoneInfo( DYNAMIC_ZONE_MENEGROTH5 )->getTemplateZoneID() );

		addDynamicZoneGroup( pDynamicZoneGroup );
	}
	{
		// 보스 전용 방이다.
		DynamicZoneGroup* pDynamicZoneGroup = new DynamicZoneGroup();
		pDynamicZoneGroup->setDynamicZoneType( DYNAMIC_ZONE_MENEGROTH6);
		pDynamicZoneGroup->setTemplateZoneID( g_pDynamicZoneInfoManager->getDynamicZoneInfo( DYNAMIC_ZONE_MENEGROTH6)->getTemplateZoneID() );

		addDynamicZoneGroup( pDynamicZoneGroup );
	}
	{
		// 보스 전용 방이다.
		DynamicZoneGroup* pDynamicZoneGroup = new DynamicZoneGroup();
		pDynamicZoneGroup->setDynamicZoneType( DYNAMIC_ZONE_CASTLE_OF_DEFENSE);
		pDynamicZoneGroup->setTemplateZoneID( g_pDynamicZoneInfoManager->getDynamicZoneInfo( DYNAMIC_ZONE_CASTLE_OF_DEFENSE)->getTemplateZoneID() );

		addDynamicZoneGroup( pDynamicZoneGroup );
	}
	{
		// 보스 전용 방이다.
		DynamicZoneGroup* pDynamicZoneGroup = new DynamicZoneGroup();
		pDynamicZoneGroup->setDynamicZoneType( DYNAMIC_ZONE_IK_LAB );
		pDynamicZoneGroup->setTemplateZoneID( g_pDynamicZoneInfoManager->getDynamicZoneInfo( DYNAMIC_ZONE_IK_LAB)->getTemplateZoneID() );

		addDynamicZoneGroup( pDynamicZoneGroup );
	}
	{
		// 보스 전용 방이다.
		DynamicZoneGroup* pDynamicZoneGroup = new DynamicZoneGroup();
		pDynamicZoneGroup->setDynamicZoneType( DYNAMIC_ZONE_IK_LAB_SERCET);
		pDynamicZoneGroup->setTemplateZoneID( g_pDynamicZoneInfoManager->getDynamicZoneInfo( DYNAMIC_ZONE_IK_LAB_SERCET)->getTemplateZoneID() );

		addDynamicZoneGroup( pDynamicZoneGroup );
	}

	{
		// 보스 전용 방이다.
		DynamicZoneGroup* pDynamicZoneGroup = new DynamicZoneGroup();
		pDynamicZoneGroup->setDynamicZoneType( DYNAMIC_ZONE_TIFFAGUES_1 );
		pDynamicZoneGroup->setTemplateZoneID( g_pDynamicZoneInfoManager->getDynamicZoneInfo( DYNAMIC_ZONE_TIFFAGUES_1 )->getTemplateZoneID() );

		addDynamicZoneGroup( pDynamicZoneGroup );
	}

	{
		// 보스 전용 방이다.
		DynamicZoneGroup* pDynamicZoneGroup = new DynamicZoneGroup();
		pDynamicZoneGroup->setDynamicZoneType( DYNAMIC_ZONE_MINI_GAME );
		pDynamicZoneGroup->setTemplateZoneID( g_pDynamicZoneInfoManager->getDynamicZoneInfo( DYNAMIC_ZONE_MINI_GAME )->getTemplateZoneID() );

		addDynamicZoneGroup( pDynamicZoneGroup );
	}

	{
		// 보스 전용 방이다.
		DynamicZoneGroup* pDynamicZoneGroup = new DynamicZoneGroup();
		pDynamicZoneGroup->setDynamicZoneType( DYNAMIC_ZONE_TIFFAGUES_2_1 );
		pDynamicZoneGroup->setTemplateZoneID( g_pDynamicZoneInfoManager->getDynamicZoneInfo( DYNAMIC_ZONE_TIFFAGUES_2_1 )->getTemplateZoneID() );

		addDynamicZoneGroup( pDynamicZoneGroup );
	}

	{
		// 보스 전용 방이다.
		DynamicZoneGroup* pDynamicZoneGroup = new DynamicZoneGroup();
		pDynamicZoneGroup->setDynamicZoneType( DYNAMIC_ZONE_TIFFAGUES_2_2 );
		pDynamicZoneGroup->setTemplateZoneID( g_pDynamicZoneInfoManager->getDynamicZoneInfo( DYNAMIC_ZONE_TIFFAGUES_2_2 )->getTemplateZoneID() );

		addDynamicZoneGroup( pDynamicZoneGroup );
	}

	{
		// 보스 전용 방이다.
		DynamicZoneGroup* pDynamicZoneGroup = new DynamicZoneGroup();
		pDynamicZoneGroup->setDynamicZoneType( DYNAMIC_ZONE_MINI_GAME2 );
		pDynamicZoneGroup->setTemplateZoneID( g_pDynamicZoneInfoManager->getDynamicZoneInfo( DYNAMIC_ZONE_MINI_GAME2 )->getTemplateZoneID() );

		addDynamicZoneGroup( pDynamicZoneGroup );
	}

	{
		// 보스 전용 방이다.
		DynamicZoneGroup* pDynamicZoneGroup = new DynamicZoneGroup();
		pDynamicZoneGroup->setDynamicZoneType( DYNAMIC_ZONE_HILANOM );
		pDynamicZoneGroup->setTemplateZoneID( g_pDynamicZoneInfoManager->getDynamicZoneInfo( DYNAMIC_ZONE_HILANOM )->getTemplateZoneID() );

		addDynamicZoneGroup( pDynamicZoneGroup );
	}

}

void DynamicZoneManager::clear()
{
	HashMapDynamicZoneGroupItor itr = m_DynamicZoneGroups.begin();
	HashMapDynamicZoneGroupItor endItr = m_DynamicZoneGroups.end();

	for ( ; itr != endItr; ++itr )
	{
		SAFE_DELETE( itr->second );
	}

	m_DynamicZoneGroups.clear();
}

void DynamicZoneManager::addDynamicZoneGroup( DynamicZoneGroup* pDynamicZoneGroup )
{
	Assert( pDynamicZoneGroup != NULL );

	HashMapDynamicZoneGroupItor itr = m_DynamicZoneGroups.find( pDynamicZoneGroup->getDynamicZoneType() );

	if ( itr != m_DynamicZoneGroups.end() )
	{
		cerr << "Duplicated DynamicZoneGroup. DynamicZoneManager::addDynamicZoneGroup" << endl;
		Assert( false );
	}

	m_DynamicZoneGroups[ pDynamicZoneGroup->getDynamicZoneType() ] = pDynamicZoneGroup;
}

DynamicZoneGroup* DynamicZoneManager::getDynamicZoneGroup( int dynamicZoneType )
{
	HashMapDynamicZoneGroupItor itr = m_DynamicZoneGroups.find( dynamicZoneType );

	if ( itr == m_DynamicZoneGroups.end() )
	{
		return NULL;
	}

	return itr->second;
}

ZoneID_t DynamicZoneManager::getNewDynamicZoneID()
{
	ZoneID_t zoneID = 0;

	__ENTER_CRITICAL_SECTION( m_Mutex )

	zoneID = m_DynamicZoneID++;

	__LEAVE_CRITICAL_SECTION( m_Mutex )

	return zoneID;
}

bool DynamicZoneManager::isDynamicZone( ZoneID_t zoneID )
{
	return zoneID >= StartDynamicZoneID;
}

