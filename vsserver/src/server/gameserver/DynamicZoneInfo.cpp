/////////////////////////////////////////////////////////////////////////////
// DynamicZoneInfo.cpp
/////////////////////////////////////////////////////////////////////////////

// include files
#include "DynamicZoneInfo.h"
#include "Assert.h"

///////////////////////////////////////////////////////////
// class DynamicZoneInfo
///////////////////////////////////////////////////////////
DynamicZoneInfo::DynamicZoneInfo()
{
	m_DynamicZoneType = DYNAMIC_ZONE_MAX;
	m_TemplateZoneID = 0;
}

DynamicZoneInfo::~DynamicZoneInfo()
{
}

// global variable
DynamicZoneInfoManager* g_pDynamicZoneInfoManager = NULL;

///////////////////////////////////////////////////////////
// class DynamicZoneInfoManager
///////////////////////////////////////////////////////////
DynamicZoneInfoManager::DynamicZoneInfoManager()
{
}

DynamicZoneInfoManager::~DynamicZoneInfoManager()
{
	clear();
}

void DynamicZoneInfoManager::init()
{
	// Á¦´Ü ÀÔ±¸ Á¸ Ãß°¡
	{
		DynamicZoneInfo* pDynamicZoneInfo = new DynamicZoneInfo;
		pDynamicZoneInfo->setDynamicZoneType( DYNAMIC_ZONE_GATE_OF_ALTER );
		pDynamicZoneInfo->setTemplateZoneID( 4001 );

		addDynamicZoneInfo( pDynamicZoneInfo );
	}

	// ÇÇÀÇ Á¦´Ü Á¸ Ãß°¡
	{
		DynamicZoneInfo* pDynamicZoneInfo = new DynamicZoneInfo;
		pDynamicZoneInfo->setDynamicZoneType( DYNAMIC_ZONE_ALTER_OF_BLOOD );
		pDynamicZoneInfo->setTemplateZoneID( 4002 );

		addDynamicZoneInfo( pDynamicZoneInfo );
	}

	// ½½·¹ÀÌ¾î ½É¿¬ÀÇ °Å¿ï Á¸ Ãß°¡
	{
		DynamicZoneInfo* pDynamicZoneInfo = new DynamicZoneInfo;
		pDynamicZoneInfo->setDynamicZoneType( DYNAMIC_ZONE_SLAYER_MIRROR_OF_ABYSS );
		pDynamicZoneInfo->setTemplateZoneID( 4003 );

		addDynamicZoneInfo( pDynamicZoneInfo );
	}

	// ¹ìÆÄÀÌ¾î ½É¿¬ÀÇ °Å¿ï Á¸ Ãß°¡
	{
		DynamicZoneInfo* pDynamicZoneInfo = new DynamicZoneInfo;
		pDynamicZoneInfo->setDynamicZoneType( DYNAMIC_ZONE_VAMPIRE_MIRROR_OF_ABYSS );
		pDynamicZoneInfo->setTemplateZoneID( 4004 );

		addDynamicZoneInfo( pDynamicZoneInfo );
	}

	// ¾Æ¿ì½ºÅÍÁî ?É¿¬À?°Å¿ï Á¸ Ãß°¡
	{
		DynamicZoneInfo* pDynamicZoneInfo = new DynamicZoneInfo;
		pDynamicZoneInfo->setDynamicZoneType( DYNAMIC_ZONE_OUSTERS_MIRROR_OF_ABYSS );
		pDynamicZoneInfo->setTemplateZoneID( 4005 );

		addDynamicZoneInfo( pDynamicZoneInfo );
	}

	{
		DynamicZoneInfo* pDynamicZoneInfo = new DynamicZoneInfo;
		pDynamicZoneInfo->setDynamicZoneType( DYNAMIC_ZONE_PARTY_OF_DUNGEON );
		pDynamicZoneInfo->setTemplateZoneID( 8003 );

		addDynamicZoneInfo( pDynamicZoneInfo );
	}

	{
		DynamicZoneInfo* pDynamicZoneInfo = new DynamicZoneInfo;
		pDynamicZoneInfo->setDynamicZoneType( DYNAMIC_ZONE_PARTY_OF_DUNGEON2 );
		pDynamicZoneInfo->setTemplateZoneID( 8004 );

		addDynamicZoneInfo( pDynamicZoneInfo );
	}

	{
		DynamicZoneInfo* pDynamicZoneInfo = new DynamicZoneInfo;
		pDynamicZoneInfo->setDynamicZoneType( DYNAMIC_ZONE_PARTY_OF_DUNGEON3 );
		pDynamicZoneInfo->setTemplateZoneID( 8005 );

		addDynamicZoneInfo( pDynamicZoneInfo );
	}

		// Çï°¡µç Å¸¿ö
	{
		DynamicZoneInfo* pDynamicZoneInfo = new DynamicZoneInfo;
		pDynamicZoneInfo->setDynamicZoneType( DYNAMIC_ZONE_PARTY_OF_DUNGEON4 );
		pDynamicZoneInfo->setTemplateZoneID( 5010 );

		addDynamicZoneInfo( pDynamicZoneInfo );
	}

		// Çï°¡µç Å¸¿ö
	{
		DynamicZoneInfo* pDynamicZoneInfo = new DynamicZoneInfo;
		pDynamicZoneInfo->setDynamicZoneType( DYNAMIC_ZONE_ASYLION );
		pDynamicZoneInfo->setTemplateZoneID( 1013 );

		addDynamicZoneInfo( pDynamicZoneInfo );
	}

		// Çï°¡µç Å¸¿ö
	{
		DynamicZoneInfo* pDynamicZoneInfo = new DynamicZoneInfo;
		pDynamicZoneInfo->setDynamicZoneType( DYNAMIC_ZONE_TIME_OF_DUNGEON );
		pDynamicZoneInfo->setTemplateZoneID( 9003 );

		addDynamicZoneInfo( pDynamicZoneInfo );
	}

		// º¸½º Àü¿ë ·ëÀÌ´Ù.
	{
		DynamicZoneInfo* pDynamicZoneInfo = new DynamicZoneInfo;
		pDynamicZoneInfo->setDynamicZoneType( DYNAMIC_ZONE_BOSS_ROOM );
		pDynamicZoneInfo->setTemplateZoneID( 9004 );

		addDynamicZoneInfo( pDynamicZoneInfo );
	}

		// º¸½º Àü¿ë ·ëÀÌ´Ù.
	{
		DynamicZoneInfo* pDynamicZoneInfo = new DynamicZoneInfo;
		pDynamicZoneInfo->setDynamicZoneType( DYNAMIC_ZONE_BOSS_ROOM2 );
		pDynamicZoneInfo->setTemplateZoneID( 9005 );

		addDynamicZoneInfo( pDynamicZoneInfo );
	}

		// º¸½º Àü¿ë ·ëÀÌ´Ù.
	{
		DynamicZoneInfo* pDynamicZoneInfo = new DynamicZoneInfo;
		pDynamicZoneInfo->setDynamicZoneType( DYNAMIC_ZONE_MENEGROTH1);
		pDynamicZoneInfo->setTemplateZoneID( 1701 );

		addDynamicZoneInfo( pDynamicZoneInfo );
	}

	{
		DynamicZoneInfo* pDynamicZoneInfo = new DynamicZoneInfo;
		pDynamicZoneInfo->setDynamicZoneType( DYNAMIC_ZONE_MENEGROTH2);
		pDynamicZoneInfo->setTemplateZoneID( 1702 );

		addDynamicZoneInfo( pDynamicZoneInfo );
	}

	{
		DynamicZoneInfo* pDynamicZoneInfo = new DynamicZoneInfo;
		pDynamicZoneInfo->setDynamicZoneType( DYNAMIC_ZONE_MENEGROTH3);
		pDynamicZoneInfo->setTemplateZoneID( 1703 );

		addDynamicZoneInfo( pDynamicZoneInfo );
	}

	{
		DynamicZoneInfo* pDynamicZoneInfo = new DynamicZoneInfo;
		pDynamicZoneInfo->setDynamicZoneType( DYNAMIC_ZONE_MENEGROTH4);
		pDynamicZoneInfo->setTemplateZoneID( 1704 );

		addDynamicZoneInfo( pDynamicZoneInfo );
	}

	{
		DynamicZoneInfo* pDynamicZoneInfo = new DynamicZoneInfo;
		pDynamicZoneInfo->setDynamicZoneType( DYNAMIC_ZONE_MENEGROTH5);
		pDynamicZoneInfo->setTemplateZoneID( 1705 );

		addDynamicZoneInfo( pDynamicZoneInfo );
	}

	{
		DynamicZoneInfo* pDynamicZoneInfo = new DynamicZoneInfo;
		pDynamicZoneInfo->setDynamicZoneType( DYNAMIC_ZONE_MENEGROTH6);
		pDynamicZoneInfo->setTemplateZoneID( 1706 );

		addDynamicZoneInfo( pDynamicZoneInfo );
	}

	{
		DynamicZoneInfo* pDynamicZoneInfo = new DynamicZoneInfo;
		pDynamicZoneInfo->setDynamicZoneType( DYNAMIC_ZONE_TIFFAGUES_1 );
		pDynamicZoneInfo->setTemplateZoneID( 1801 );

		addDynamicZoneInfo( pDynamicZoneInfo );
	}

	{
		DynamicZoneInfo* pDynamicZoneInfo = new DynamicZoneInfo;
		pDynamicZoneInfo->setDynamicZoneType( DYNAMIC_ZONE_CASTLE_OF_DEFENSE );
		pDynamicZoneInfo->setTemplateZoneID( 9006 );

		addDynamicZoneInfo( pDynamicZoneInfo );
	}

	{
		DynamicZoneInfo* pDynamicZoneInfo = new DynamicZoneInfo;
		pDynamicZoneInfo->setDynamicZoneType( DYNAMIC_ZONE_IK_LAB );
		pDynamicZoneInfo->setTemplateZoneID( 9007 );

		addDynamicZoneInfo( pDynamicZoneInfo );
	}

	{
		DynamicZoneInfo* pDynamicZoneInfo = new DynamicZoneInfo;
		pDynamicZoneInfo->setDynamicZoneType( DYNAMIC_ZONE_IK_LAB_SERCET );
		pDynamicZoneInfo->setTemplateZoneID( 9008 );

		addDynamicZoneInfo( pDynamicZoneInfo );
	}

	{
		DynamicZoneInfo* pDynamicZoneInfo = new DynamicZoneInfo;
		pDynamicZoneInfo->setDynamicZoneType( DYNAMIC_ZONE_MINI_GAME );
		pDynamicZoneInfo->setTemplateZoneID( 9009 );

		addDynamicZoneInfo( pDynamicZoneInfo );
	}

	{
		DynamicZoneInfo* pDynamicZoneInfo = new DynamicZoneInfo;
		pDynamicZoneInfo->setDynamicZoneType( DYNAMIC_ZONE_TIFFAGUES_2_1 );
		pDynamicZoneInfo->setTemplateZoneID( 1803 );

		addDynamicZoneInfo( pDynamicZoneInfo );
	}

	{
		DynamicZoneInfo* pDynamicZoneInfo = new DynamicZoneInfo;
		pDynamicZoneInfo->setDynamicZoneType( DYNAMIC_ZONE_TIFFAGUES_2_2 );
		pDynamicZoneInfo->setTemplateZoneID( 1804 );

		addDynamicZoneInfo( pDynamicZoneInfo );
	}

	{
		DynamicZoneInfo* pDynamicZoneInfo = new DynamicZoneInfo;
		pDynamicZoneInfo->setDynamicZoneType( DYNAMIC_ZONE_MINI_GAME2 );
		pDynamicZoneInfo->setTemplateZoneID( 9010 );

		addDynamicZoneInfo( pDynamicZoneInfo );
	}

	{
		DynamicZoneInfo* pDynamicZoneInfo = new DynamicZoneInfo;
		pDynamicZoneInfo->setDynamicZoneType( DYNAMIC_ZONE_HILANOM );
		pDynamicZoneInfo->setTemplateZoneID( 1123 );

		addDynamicZoneInfo( pDynamicZoneInfo );
	}
}

void DynamicZoneInfoManager::clear()
{
	HashMapDynamicZoneInfoItor itr = m_DynamicZoneInfos.begin();
	HashMapDynamicZoneInfoItor endItr = m_DynamicZoneInfos.end();

	for ( ; itr != endItr; ++itr )
	{
		SAFE_DELETE( itr->second );
	}

	m_DynamicZoneInfos.clear();
}

void DynamicZoneInfoManager::addDynamicZoneInfo( DynamicZoneInfo* pDynamicZoneInfo )
{
	Assert( pDynamicZoneInfo != NULL );

	HashMapDynamicZoneInfoConstItor itr = m_DynamicZoneInfos.find( pDynamicZoneInfo->getDynamicZoneType() );

	if ( itr != m_DynamicZoneInfos.end() )
	{
		cerr << "Duplicated DynamicZoneInfo" << endl;
		Assert( false );
	}

	m_DynamicZoneInfos[ pDynamicZoneInfo->getDynamicZoneType() ] = pDynamicZoneInfo;

	HashMapDynamicZoneTypeConstItor itr2 = m_DynamicZoneTypes.find( pDynamicZoneInfo->getTemplateZoneID() );

	if ( itr2 != m_DynamicZoneTypes.end() )
	{
		cerr << "Duplicated DynamicZoneInfo" << endl;
		Assert( false );
	}

	m_DynamicZoneTypes[ pDynamicZoneInfo->getTemplateZoneID() ] = pDynamicZoneInfo->getDynamicZoneType();
}

DynamicZoneInfo* DynamicZoneInfoManager::getDynamicZoneInfo( int DynamicZoneType ) const
{
	HashMapDynamicZoneInfoConstItor itr = m_DynamicZoneInfos.find( DynamicZoneType );

	if ( itr == m_DynamicZoneInfos.end() )
	{
		cerr << "No such element given DynamicZoneType" << endl;
		return NULL;
	}

	return itr->second;
}

int DynamicZoneInfoManager::getDynamicZoneTypeByZoneID( ZoneID_t zoneID ) const
{
	HashMapDynamicZoneTypeConstItor itr = m_DynamicZoneTypes.find( zoneID );

	if ( itr == m_DynamicZoneTypes.end() )
	{
		cerr << "No such element given ZoneID" << endl;
		return DYNAMIC_ZONE_MAX;
	}

	return itr->second;
}

