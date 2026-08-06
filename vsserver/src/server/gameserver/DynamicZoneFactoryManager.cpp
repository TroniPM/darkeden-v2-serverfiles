////////////////////////////////////////////////////////////////////////////////
// Filename    : DynamicZoneFactoryManager.cpp 
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "DynamicZoneFactoryManager.h"
#include "DynamicZoneInfo.h"
#include "Assert.h"
#include "StringStream.h"

#include "DynamicZoneGateOfAlter.h"
#include "DynamicZoneAlterOfBlood.h"
#include "DynamicZoneSlayerMirrorOfAbyss.h"
#include "DynamicZoneVampireMirrorOfAbyss.h"
#include "DynamicZoneOustersMirrorOfAbyss.h"
#include "DynamicZonePartyOfDungeon.h"
#include "DynamicZonePartyOfDungeon2.h"
#include "DynamicZonePartyOfDungeon3.h"
// 헬가든 타워
#include "DynamicZonePartyOfDungeon4.h"

// 아실리온 인질 구출 작전
#include "DynamicZoneAsylion.h"

// 폭젠존
#include "DynamicZoneTimeOfDungeon.h"

// 보스 레이드 전용 방
#include "DynamicZoneBossRoom.h"
#include "DynamicZoneBossRoom2.h"

// 매네그로스
#include "DynamicZoneMenegroth1.h"
#include "DynamicZoneMenegroth2.h"
#include "DynamicZoneMenegroth3.h"
#include "DynamicZoneMenegroth4.h"
#include "DynamicZoneMenegroth5.h"
#include "DynamicZoneMenegroth6.h"

#include "DynamicZoneCastleOfDefense.h"

// IK LAB
#include "DynamicZoneIkLab.h"
#include "DynamicZoneIkLabSercet.h"

#include "DynamicZoneTiffagues_1.h"
#include "DynamicZoneMiniGame.h"

#include "DynamicZoneTiffagues_2_1.h"
#include "DynamicZoneTiffagues_2_2.h"

#include "DynamicZoneMiniGame2.h"
#include "DynamicZoneHilanom.h"
////////////////////////////////////////////////////////////////////////////////
// constructor
////////////////////////////////////////////////////////////////////////////////
DynamicZoneFactoryManager::DynamicZoneFactoryManager() 
: m_Factories(NULL) , m_Size(DYNAMIC_ZONE_MAX)
{
	Assert( m_Size > 0 );
	
	// 컨디션팩토리배열을 생성한다.
	m_Factories = new DynamicZoneFactory*[m_Size];
	
	// 팩토리에 대한 포인터들을 NULL 로 초기화한다.
	for (int i = 0 ; i < m_Size ; i ++) 
		m_Factories[i] = NULL;
}

	
////////////////////////////////////////////////////////////////////////////////
// destructor
////////////////////////////////////////////////////////////////////////////////
DynamicZoneFactoryManager::~DynamicZoneFactoryManager() 
{
	Assert( m_Factories != NULL );

	// 각각의 컨디션팩토리들을 삭제한다.
	for ( int i = 0 ; i < m_Size ; i ++ )
	{
		if ( m_Factories[i] != NULL )
		{
			delete m_Factories[i];
			m_Factories[i] = NULL;
		}
	}
	
	// 컨디션팩토리배열을 삭제한다.
	delete [] m_Factories;
	m_Factories = NULL;
}


////////////////////////////////////////////////////////////////////////////////
// 정의된 모든 컨디션팩토리들을 여기에 추가한다.
////////////////////////////////////////////////////////////////////////////////
void DynamicZoneFactoryManager::init()
{
	addFactory( new DynamicZoneGateOfAlterFactory() );
	addFactory( new DynamicZoneAlterOfBloodFactory() );
	addFactory( new DynamicZoneSlayerMirrorOfAbyssFactory() );
	addFactory( new DynamicZoneVampireMirrorOfAbyssFactory() );
	addFactory( new DynamicZoneOustersMirrorOfAbyssFactory() );
	addFactory( new DynamicZonePartyOfDungeonFactory() );
	addFactory( new DynamicZonePartyOfDungeon2Factory() );
	addFactory( new DynamicZonePartyOfDungeon3Factory() );
	addFactory( new DynamicZonePartyOfDungeon4Factory() );
	addFactory( new DynamicZoneAsylionFactory() );
	addFactory( new DynamicZoneTimeOfDungeonFactory() );
	addFactory( new DynamicZoneBossRoomFactory() );
	addFactory( new DynamicZoneBossRoom2Factory() );
	addFactory( new DynamicZoneMenegroth1Factory() );
	addFactory( new DynamicZoneMenegroth2Factory() );
	addFactory( new DynamicZoneMenegroth3Factory() );
	addFactory( new DynamicZoneMenegroth4Factory() );
	addFactory( new DynamicZoneMenegroth5Factory() );
	addFactory( new DynamicZoneMenegroth6Factory() );
	addFactory( new DynamicZoneCastleOfDefenseFactory() );
	addFactory( new DynamicZoneIkLabFactory() );
	addFactory( new DynamicZoneIkLabSercetFactory() );
	addFactory( new DynamicZoneTiffagues_1Factory() );
	addFactory( new DynamicZoneMiniGameFactory() );
	addFactory( new DynamicZoneTiffagues_2_1Factory() );
	addFactory( new DynamicZoneTiffagues_2_2Factory() );
	addFactory( new DynamicZoneMiniGame2Factory() );
	addFactory( new DynamicZoneHilanomFactory() );
}


////////////////////////////////////////////////////////////////////////////////
// add dynamiczone factory to factories array
////////////////////////////////////////////////////////////////////////////////
void DynamicZoneFactoryManager::addFactory( DynamicZoneFactory * pFactory ) 
{
	Assert(pFactory != NULL);

	if (m_Factories[pFactory->getDynamicZoneType()] != NULL )
	{
		StringStream msg;
		msg << "duplicate DynamicZone factories, " << pFactory->getDynamicZoneName() ;
		cout << msg.toString() << endl;
		Assert( false );
	}
	
	// 컨디션팩토리를 등록한다.
	m_Factories[pFactory->getDynamicZoneType()] = pFactory;
}

	
////////////////////////////////////////////////////////////////////////////////
// create dynamiczone object with dynamiczone type
////////////////////////////////////////////////////////////////////////////////
DynamicZone* DynamicZoneFactoryManager::createDynamicZone( int dynamicZoneType ) const
{
	if ( dynamicZoneType >= m_Size || m_Factories[dynamicZoneType] == NULL ) 
	{
		StringStream msg;
		msg << "dynamiczone factory [" << dynamicZoneType << "] not exist.";
		cout << msg.toString() << endl;
		Assert( false );
	}

	return m_Factories[dynamicZoneType]->createDynamicZone();
}


////////////////////////////////////////////////////////////////////////////////
// get dynamiczone name with dynamiczone type
////////////////////////////////////////////////////////////////////////////////
string DynamicZoneFactoryManager::getDynamicZoneName( int dynamicZoneType ) const
{
	// 타입이 범위를 넘어섬으로 인해??Seg.Fault 가 발생하지 않도록.
	// 이런 사용자는 당장 짤라야 한다.
	if ( dynamicZoneType >= m_Size || m_Factories[dynamicZoneType] == NULL ) 
	{
		StringStream msg;
		msg << "invalid dynamiczone type (" << dynamicZoneType << ")";
		cout << msg.toString() << endl;
		Assert( false );
	}

	return m_Factories[dynamicZoneType]->getDynamicZoneName();
}


////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
int DynamicZoneFactoryManager::getDynamicZoneType( const string& dynamicZoneName ) const
{
	for ( int i = 0 ; i < m_Size ; i++ )
	{
		if ( m_Factories[i] != NULL )
		{
			if ( m_Factories[i]->getDynamicZoneName() == dynamicZoneName )
			{
				return i;
			}
		}
	}

	string msg = "no such dynamiczone type : " + dynamicZoneName;
	cout << msg << endl;
	Assert( false );

	return DYNAMIC_ZONE_MAX;
}


////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string DynamicZoneFactoryManager::toString() const
{
	StringStream msg;

	msg << "DynamicZoneFactoryManager(\n";

	for ( int i = 0 ; i < m_Size ; i++ )
	{
		msg << "DynamicZoneFactories[" << i << "] == ";
		msg << (m_Factories[i] == NULL ? "NULL" : m_Factories[i]->getDynamicZoneName()) ;
		msg << "\n";
	}

	msg << ")";

	return msg.toString();
}

// global variable declaration
DynamicZoneFactoryManager * g_pDynamicZoneFactoryManager = NULL;

