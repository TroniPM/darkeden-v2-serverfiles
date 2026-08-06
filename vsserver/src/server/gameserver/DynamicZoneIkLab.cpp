/////////////////////////////////////////////////////////////////////////////
// DynamicZoneOustersMirrorOfAbyss.cpp
/////////////////////////////////////////////////////////////////////////////

#include "DynamicZoneIkLab.h"
#include "DynamicZoneInfo.h"
#include "Zone.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Ousters.h"
#include "Monster.h"
#include "PCManager.h"
#include "MonsterManager.h"
#include "EffectKillTimer.h"
#include "GQuestManager.h"
#include "Assert.h"
#include "PlayerCreature.h"
#include "Player.h"
#include "Timeval.h"
#include "InstantDungeonMonster.h"
#include "Gpackets/GCSystemMessage.h"
#include "Gpackets/GCNoticeEvent.h"

#include <stdio.h>
#include <stdlib.h>

enum OUSTERS_MIRROR_OF_ABYSS
{
	WAIT_FOR_PC,
	ADD_MONO,
	WAIT_FOR_COMPLETE,
	CLEAR_MONO,
	WAIT_FOR_CLEAR,
	OUSTERS_MIRROR_OF_ABYSS_END,

	OUSTERS_MIRROR_OF_ABYSS_MAX
};

// 타일에 블럭을 걸어야 한다.
// 하나하나 입장을 클리어 할 수 있게 해야 한다.
struct OFFERING_COORDINATE
{
	ZoneCoord_t X;
	ZoneCoord_t Y;
};

/*
IK 연구소에서는 총 스테이지 3개를 제공한다.
각 스테이지마다 몬스터가 나오며 해당 몬스터를 처치해야 스테이지가 풀리도록 만든다.
그리고, 총 6자리 비밀번호중 2자리씩 스테이지를 클리어할때마다 몬스터가 얘기하게 한다.
얘기할때 몬스터 시체가 얘기할수 있게 한다. 다음 스테이지 앞에서 비밀번호를 말해야 스테이지가 풀리도록 한다.
스테이지 비밀번호는 매번 다르게 설정해줘야 한다.
*/
const OFFERING_COORDINATE OfferingCoordinate[3] =
{
	{ 64, 97 },
	{ 76, 60 },
	{ 89, 72 },
};


DynamicZoneIkLab::DynamicZoneIkLab()
{
	m_MonoObjectID = 0;
	m_MonoObjectID2 = 0;
	m_MonoObjectID3 = 0;
}

DynamicZoneIkLab::~DynamicZoneIkLab()
{
}

void DynamicZoneIkLab::init()
{
	Assert( m_pZone != NULL );

	m_OMOAStatus = WAIT_FOR_PC;
	getCurrentTime( m_Deadline );
	m_Deadline.tv_sec += 60;
	getCurrentTime( m_EndTime );
	m_EndTime.tv_sec += 10 * 60;
}

void DynamicZoneIkLab::heartbeat()
{
	switch ( m_OMOAStatus )
	{
	case WAIT_FOR_PC:
		if ( checkPC() )
		{
			processEntering();
			m_OMOAStatus = ADD_MONO;
			cout << "-----------------------ADD_MONO" << endl;
		}
		break;

	case ADD_MONO:
		if ( addMono() )
		{
			// 보스형 나오신다.
			timecheck();
			m_OMOAStatus = WAIT_FOR_COMPLETE;
			cout << "-----------------------WAIT_FOR_COMPLETE" << endl;
		}
		break;

	case WAIT_FOR_COMPLETE:
		if ( checkComplete() )
		{
			// 10분이라는 시간이 주어지는데 클리어를 못했을 경우 내보내버린다.
			openGateToOut();
			m_OMOAStatus = CLEAR_MONO;
			cout << "-----------------------CLEAR_MONO" << endl;
		}

		if ( !checkMono() )
		{
			// 보스형을 잡았다. 그래도 내보내버린다.
			openGateToOut();
			m_OMOAStatus = WAIT_FOR_CLEAR;
		}

		break;

	case CLEAR_MONO:
		if ( clearMono() )
		{
			m_OMOAStatus = WAIT_FOR_CLEAR;
			cout << "-----------------------WAIT_FOR_CLEAR" << endl;
		}
		break;

	case WAIT_FOR_CLEAR:
		if ( !checkPC() && !checkMono() )
		{
			m_OMOAStatus = OUSTERS_MIRROR_OF_ABYSS_END;
			m_Status = DYNAMIC_ZONE_STATUS_READY;
			cout << "-----------------------READY" << endl;
		}
		break;
	}

	if ( !checkPC() )
	{
		if ( m_OMOAStatus == WAIT_FOR_PC )
		{
			Timeval current;
			getCurrentTime( current );

			if ( current > m_Deadline )
			{
				m_OMOAStatus = CLEAR_MONO;
				cout << "-----------------------Time out" << endl;
			}
		}
		else if ( m_OMOAStatus == WAIT_FOR_COMPLETE )
		{
			m_OMOAStatus = CLEAR_MONO;
		}
	}
}

bool DynamicZoneIkLab::checkPC()
{
	Assert( m_pZone != NULL );

	// PC 수 체크
	uint size = m_pZone->getPCManager()->getSize();

	return size != 0;
}

bool DynamicZoneIkLab::addMono()
{
	InstantDungeonMonster* pInstantDungeonMonster = g_pInstantDungeonMonsterManager->getInstantDungeonMonster(m_Indun);
	if(pInstantDungeonMonster == NULL) return false;
	Assert( m_pZone != NULL );

	// 이성의 봉인을 생성한다.
	Monster* pMonster = new Monster( pInstantDungeonMonster->getMonsterType() );
	Assert( pMonster != NULL );

	try
	{
		m_pZone->addCreature( pMonster, 62, 119, 2 );
		m_MonoObjectID = pMonster->getObjectID();
	}
	catch ( EmptyTileNotExistException& )
	{
		SAFE_DELETE( pMonster );
	}

	// 이성의 봉인을 생성한다.
	Monster* pMonster2 = new Monster( pInstantDungeonMonster->getMonsterType() );
	Assert( pMonster != NULL );

	try
	{
		m_pZone->addCreature( pMonster2, 58, 31, 2 );
		m_MonoObjectID2 = pMonster2->getObjectID();
	}
	catch ( EmptyTileNotExistException& )
	{
		SAFE_DELETE( pMonster2 );
	}

	// 이성의 봉인을 생성한다.
	Monster* pMonster3 = new Monster( pInstantDungeonMonster->getMonsterType() );
	Assert( pMonster != NULL );

	try
	{
		m_pZone->addCreature( pMonster3, 124, 73, 2 );
		m_MonoObjectID3 = pMonster3->getObjectID();
	}
	catch ( EmptyTileNotExistException& )
	{
		SAFE_DELETE( pMonster3 );
	}

	return true;
}

bool DynamicZoneIkLab::clearMono()
{
	Assert( m_pZone != NULL );

	MonsterManager* pMonsterManager = m_pZone->getMonsterManager();
	Assert( pMonsterManager != NULL );

	Creature* pCreature = pMonsterManager->getCreature( m_MonoObjectID );
	if ( pCreature != NULL )
	{
		if ( pCreature->isMonster() )
		{
			EffectKillTimer* pEffect = new EffectKillTimer( pCreature, true );
			pCreature->setFlag( pEffect->getEffectClass() );
			pEffect->setDeadline(50);
			pCreature->addEffect( pEffect );
		}
	}

	Creature* pCreature2 = pMonsterManager->getCreature( m_MonoObjectID2 );
	if ( pCreature2 != NULL )
	{
		if ( pCreature2->isMonster() )
		{
			EffectKillTimer* pEffect = new EffectKillTimer( pCreature2, true );
			pCreature2->setFlag( pEffect->getEffectClass() );
			pEffect->setDeadline(50);
			pCreature2->addEffect( pEffect );
		}
	}

	Creature* pCreature3 = pMonsterManager->getCreature( m_MonoObjectID3 );
	if ( pCreature3 != NULL )
	{
		if ( pCreature3->isMonster() )
		{
			EffectKillTimer* pEffect = new EffectKillTimer( pCreature3, true );
			pCreature3->setFlag( pEffect->getEffectClass() );
			pEffect->setDeadline(50);
			pCreature3->addEffect( pEffect );
		}
	}

	return true;
}

bool DynamicZoneIkLab::openGateToOut()
{
	Assert( m_pZone != NULL );

    // 퀘스트를 진행시킨다.
    hash_map<ObjectID_t, Creature*>::const_iterator itr = m_pZone->getPCManager()->getCreatures().begin();
    hash_map<ObjectID_t, Creature*>::const_iterator endItr = m_pZone->getPCManager()->getCreatures().end();

    for ( ; itr != endItr; ++itr )
    {
        Assert( itr->second != NULL );

        if ( itr->second->isPC() )
        {
            PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(itr->second);
            Assert( pPC != NULL );

	m_pZone->getPCManager()->transportAllCreatures( m_ZoneID, m_ZoneX, m_ZoneY );
        }
    }

	return true;
}

void DynamicZoneIkLab::timecheck()
{
	const PCManager* pPCManager = m_pZone->getPCManager();
	const hash_map< ObjectID_t, Creature* > & creatures2 = pPCManager->getCreatures();
	hash_map< ObjectID_t, Creature* >::const_iterator itr2;

	if (creatures2.empty())
		return;

	for (itr2=creatures2.begin(); itr2!=creatures2.end(); itr2++)
	{
		Creature* pCreature = itr2->second;
		if (pCreature->isPC())
		{
		Timeval currentTime;
		getCurrentTime(currentTime);

		int Times = m_EndTime.tv_sec - currentTime.tv_sec;

		GCNoticeEvent gcNoticeEvent;
		gcNoticeEvent.setCode( 3 );
		gcNoticeEvent.setParameter( Times );
		pCreature->getPlayer()->sendPacket( &gcNoticeEvent );
		}
		else
		{
			throw Error("PCManager에 PC아닌게 들어있노 -_-");
		}
	}
}

bool DynamicZoneIkLab::checkComplete()
{
	Timeval current;
	getCurrentTime( current );
	if ( current > m_EndTime )
	{
		return true;
	}
	else
	{
		return false;
	}
}

void DynamicZoneIkLab::processEntering()
{
	Assert( m_pZone != NULL );

    // 퀘스트 존에 들어왔음을 알린다.
    hash_map<ObjectID_t, Creature*>::const_iterator itr = m_pZone->getPCManager()->getCreatures().begin();
    hash_map<ObjectID_t, Creature*>::const_iterator endItr = m_pZone->getPCManager()->getCreatures().end();

    for ( ; itr != endItr; ++itr )
    {
        Assert( itr->second != NULL );

        if ( itr->second->isPC() )
        {
            PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(itr->second);
            Assert( pPC != NULL );
        }
    }
}

bool DynamicZoneIkLab::checkMono()
{
	Assert( m_pZone != NULL );

	MonsterManager* pMonsterManager = m_pZone->getMonsterManager();
	Assert( pMonsterManager != NULL );

	Creature* pCreature = pMonsterManager->getCreature( m_MonoObjectID );
	Creature* pCreature2 = pMonsterManager->getCreature( m_MonoObjectID2 );
	Creature* pCreature3 = pMonsterManager->getCreature( m_MonoObjectID3 );
	return pCreature != NULL || pCreature2 != NULL || pCreature3 != NULL;
}

void DynamicZoneIkLab::killPC()
{
	Assert( m_pZone != NULL );

    // PC 를 죽인다.
    hash_map<ObjectID_t, Creature*>::const_iterator itr = m_pZone->getPCManager()->getCreatures().begin();
    hash_map<ObjectID_t, Creature*>::const_iterator endItr = m_pZone->getPCManager()->getCreatures().end();

    for ( ; itr != endItr; ++itr )
    {
        Assert( itr->second != NULL );

        if ( itr->second->isPC() )
        {
            PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(itr->second);
            Assert( pPC != NULL );

			if ( pPC->isSlayer() )
			{
				Slayer* pSlayer = dynamic_cast<Slayer*>(pPC);
				Assert( pSlayer != NULL );

				pSlayer->setHP(0);
			}
			else if ( pPC->isVampire() )
			{
				Vampire* pVampire = dynamic_cast<Vampire*>(pPC);
				Assert( pVampire != NULL );

				pVampire->setHP(0);
			}
			else if ( pPC->isOusters() )
			{
				Ousters* pOusters = dynamic_cast<Ousters*>(pPC);
				Assert( pOusters != NULL );

				pOusters->setHP(0);
			}
        }
    }
}

DEFINE_DYNAMIC_ZONE_FACTORY( DynamicZoneIkLab, DYNAMIC_ZONE_IK_LAB )


