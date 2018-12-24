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

// Ÿ�Ͽ� ���� �ɾ�� �Ѵ�.
// �ϳ��ϳ� ������ Ŭ���� �� �� �ְ� �ؾ� �Ѵ�.
struct OFFERING_COORDINATE
{
	ZoneCoord_t X;
	ZoneCoord_t Y;
};

/*
IK �����ҿ����� �� �������� 3���� �����Ѵ�.
�� ������������ ���Ͱ� ������ �ش� ���͸� óġ�ؾ� ���������� Ǯ������ �����.
�׸���, �� 6�ڸ� ��й�ȣ�� 2�ڸ��� ���������� Ŭ�����Ҷ����� ���Ͱ� ����ϰ� �Ѵ�.
����Ҷ� ���� ��ü�� ����Ҽ� �ְ� �Ѵ�. ���� �������� �տ��� ��й�ȣ�� ���ؾ� ���������� Ǯ������ �Ѵ�.
�������� ��й�ȣ�� �Ź� �ٸ��� ��������� �Ѵ�.
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
			// ������ �����Ŵ�.
			timecheck();
			m_OMOAStatus = WAIT_FOR_COMPLETE;
			cout << "-----------------------WAIT_FOR_COMPLETE" << endl;
		}
		break;

	case WAIT_FOR_COMPLETE:
		if ( checkComplete() )
		{
			// 10���̶�� �ð��� �־����µ� Ŭ��� ������ ��� ������������.
			openGateToOut();
			m_OMOAStatus = CLEAR_MONO;
			cout << "-----------------------CLEAR_MONO" << endl;
		}

		if ( !checkMono() )
		{
			// �������� ��Ҵ�. �׷��� ������������.
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

	// PC �� üũ
	uint size = m_pZone->getPCManager()->getSize();

	return size != 0;
}

bool DynamicZoneIkLab::addMono()
{
	InstantDungeonMonster* pInstantDungeonMonster = g_pInstantDungeonMonsterManager->getInstantDungeonMonster(m_Indun);
	if(pInstantDungeonMonster == NULL) return false;
	Assert( m_pZone != NULL );

	// �̼��� ������ �����Ѵ�.
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

	// �̼��� ������ �����Ѵ�.
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

	// �̼��� ������ �����Ѵ�.
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

    // ����Ʈ�� �����Ų��.
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
			throw Error("PCManager�� PC�ƴѰ� ����ֳ� -_-");
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

    // ����Ʈ ���� �������� �˸���.
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

    // PC �� ���δ�.
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


