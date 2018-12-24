/////////////////////////////////////////////////////////////////////////////
// DynamicZoneAlterOfBlood.cpp
/////////////////////////////////////////////////////////////////////////////

#include "DynamicZoneAsylion.h"
#include "DynamicZoneInfo.h"
#include "Zone.h"
#include "PlayerCreature.h"
#include "GQuestManager.h"
#include "PCManager.h"
#include "Monster.h"
#include "MonsterManager.h"
#include "EffectKillTimer.h"
#include "EffectCauseCriticalWounds.h"
#include "Timeval.h"
#include "Assert.h"
#include "NPCInfo.h"
#include "Player.h"
#include "Inventory.h"
#include "InstantDungeonMonster.h"
#include "Gpackets/GCSystemMessage.h"
#include "Gpackets/GCAddEffectToTile.h"
#include "Gpackets/GCNoticeEvent.h"

#include <stdio.h>
#include <stdlib.h>

enum ALTER_OF_BLOOD_STATUS
{
	WAIT_FOR_PC,
	ADD_OFFERING,
	WAIT_FOR_CLEAR_OFFERING,
	CLEAR_OFFERING,
	ADD_BOSS_MONSTER,
	CLEAR_BOSS_MONSTER,
	WAIT_FOR_CLEAR,
	ALTER_OF_BLOOD_STATUS_END,

	ALTER_OF_BLOOD_STATUS_MAX
};

struct OFFERING_TEMPLATE
{
	MonsterType_t	MonsterType;
	string			Name[5];
};

const OFFERING_TEMPLATE OfferingTemplate[3] =
{
	{ 256, { "���̾�Ƽ��", "���̾�Ƽ��", "���̾�Ƽ��", "���̾�Ƽ��", "���̾�Ƽ��" } },
	{ 794, { "�����̾� ����1", "�����̾� ����2", "�����̾� ����3", "�����̾� ����4", "�����̾� ����5" } },
	{ 795, { "�ƿ콺���� ����1", "�ƿ콺���� ����2", "�ƿ콺���� ����3", "�ƿ콺���� ����4", "�ƿ콺���� ����5" } }
};

struct OFFERING_COORDINATE
{
	ZoneCoord_t X;
	ZoneCoord_t Y;
};

const OFFERING_COORDINATE OfferingCoordinate[5] =
{
	{ 9, 16 },
	{ 60, 75 },
	{ 83, 115 },
	{ 109, 69 },
	{ 116, 17 }
};

DynamicZoneAsylion::DynamicZoneAsylion()
{
	m_MonoObjectID = 0;

	for ( int i=0; i<5; ++i )
	{
		m_OfferingObjectID[i] = 0;
	}
}

DynamicZoneAsylion::~DynamicZoneAsylion()
{
}

void DynamicZoneAsylion::init()
{
	Assert( m_pZone != NULL );

	m_AOBStatus = WAIT_FOR_PC;
	getCurrentTime( m_Deadline );
	m_Deadline.tv_sec += 60;
	getCurrentTime( m_EndTime );
	m_EndTime.tv_sec += 3600;
}

void DynamicZoneAsylion::heartbeat()
{
	switch ( m_AOBStatus )
	{
	case WAIT_FOR_PC:
		if ( checkPC() )
		{
			timecheck();
			m_AOBStatus = ADD_OFFERING;
			cout << "--------------------------------------------ADD_OFFERING" << endl;
		}
		break;

	case ADD_OFFERING:
		if ( addOffering() )
		{
			m_AOBStatus = WAIT_FOR_CLEAR_OFFERING;
			cout << "--------------------------------------------WAIT_FOR_CLEAR_OFFERING" << endl;
		}
		break;

	case WAIT_FOR_CLEAR_OFFERING:
		// �������� ��� ���� �ɰ��.
		if ( checkNoOffering() )
		{
			// ���� ���Ͱ� ���´�
			m_AOBStatus = ADD_BOSS_MONSTER;
			//m_AOBStatus = CLEAR_OFFERING;
			cout << "--------------------------------------------ADD_BOSS_MONSTER" << endl;
		}
		break;
	case ADD_BOSS_MONSTER :
		// ���� ���ʹ��� �����Ŵ�.
		addMono();
		m_AOBStatus = CLEAR_BOSS_MONSTER;
		break;
	case CLEAR_BOSS_MONSTER :
		// ���� ���Ͱ� �׾���.
		if(!checkMono()){
		openGateToOut();
		m_AOBStatus = CLEAR_OFFERING;
		cout << "--------------------------------------------WAIT_FOR_CLEAR" << endl;
		}
		break;
	case CLEAR_OFFERING:
		if ( clearOffering() )
		{
			m_AOBStatus = WAIT_FOR_CLEAR;
			cout << "--------------------------------------------WAIT_FOR_CLEAR" << endl;
		}
		break;

	case WAIT_FOR_CLEAR:
		if ( !checkPC() && checkNoOffering() )
		{
			m_AOBStatus = ALTER_OF_BLOOD_STATUS_END;
			m_Status = DYNAMIC_ZONE_STATUS_READY;
			cout << "--------------------------------------------READY" << endl;
		}
		break;
	}

	if ( !checkPC() )
	{
		if ( m_AOBStatus == WAIT_FOR_PC )
		{
			Timeval current;
			getCurrentTime( current );

			if ( current > m_Deadline )
			{
				clearMono();
				cout << "--------------------------------------------TIME_OUT" << endl;
				m_AOBStatus = CLEAR_OFFERING;
			}
		}
		else if ( m_AOBStatus == WAIT_FOR_CLEAR_OFFERING )
		{
			clearMono();
			m_AOBStatus = CLEAR_OFFERING;
			cout << "--------------------------------------------FAIL" << endl;
		}
	}
	if ( checkPC() )
	{
			Timeval current;
			getCurrentTime( current );

			if ( current > m_EndTime )
			{
				openGateToOut();
				clearMono();
				cout << "--------------------------------------------TIME_OUT" << endl;
				m_AOBStatus = CLEAR_OFFERING;
			}
	}
}

bool DynamicZoneAsylion::checkPC()
{
	Assert( m_pZone != NULL );

	// PC �� üũ
	uint size = m_pZone->getPCManager()->getSize();

	return size != 0;
}

bool DynamicZoneAsylion::addOffering()
{
	Assert( m_pZone != NULL );

	InstantDungeonMonster* pInstantDungeonMonster = g_pInstantDungeonMonsterManager->getInstantDungeonMonster(m_Indun);
	if(pInstantDungeonMonster == NULL) return false;
	for ( int i = 0; i < pInstantDungeonMonster->getMonsterNumber(); ++i )
	{
		// ������ �����Ͽ� �߰��Ѵ�. ������ ���� ���� ���ʹ�
		Monster* pMonster = new Monster( pInstantDungeonMonster->getMonsterType() );
		Assert( pMonster != NULL );

		pMonster->setFlag( Effect::EFFECT_CLASS_NO_DAMAGE );

		EffectCauseCriticalWounds* pEffect = new EffectCauseCriticalWounds( pMonster );
		pEffect->setDeadline( 999999 );
		pMonster->addEffect( pEffect );
		pMonster->setFlag( Effect::EFFECT_CLASS_CAUSE_CRITICAL_WOUNDS );

		try
		{
			m_pZone->addCreature( pMonster, OfferingCoordinate[i].X, OfferingCoordinate[i].Y, 2 );

			m_OfferingObjectID[i] = pMonster->getObjectID();
		}
		catch ( EmptyTileNotExistException& )
		{
			SAFE_DELETE( pMonster );
		}
	}

	return true;
}

bool DynamicZoneAsylion::checkNoOffering()
{
	Assert( m_pZone != NULL );

	MonsterManager* pMonsterManager = m_pZone->getMonsterManager();
	Assert( pMonsterManager != NULL );

	for ( int i=0; i<5; ++i )
	{
		if ( pMonsterManager->getCreature( m_OfferingObjectID[i] ) != NULL )
			return false;
	}

	return true;
}

bool DynamicZoneAsylion::clearOffering()
{
	Assert( m_pZone != NULL );

	MonsterManager* pMonsterManager = m_pZone->getMonsterManager();
	Assert( pMonsterManager != NULL );

	for ( int i=0; i<5; ++i )
	{
		Creature* pCreature = pMonsterManager->getCreature( m_OfferingObjectID[i] );
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
	}

	return true;
}

bool DynamicZoneAsylion::openGateToOut()
{
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

	// �����鼭 ���踦 �����ؾ� �Ѵ�.
	Inventory* pInventory = pPC->getInventory();
	pInventory->DeleteKeyItem();
	
	m_pZone->getPCManager()->transportAllCreatures( m_ZoneID, m_ZoneX, m_ZoneY );
	cout << "---------------------------------Clear Alter of Blood" << endl;
        }
    }

	return true;
}

bool DynamicZoneAsylion::checkComplete()
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

void DynamicZoneAsylion::timecheck()
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
		//m_pZone->broadcastPacket( &gcNoticeEvent );
		pCreature->getPlayer()->sendPacket( &gcNoticeEvent );
		}
		else
		{
			throw Error("PCManager�� PC�ƴѰ� ����ֳ� -_-");
		}
	}
}

bool DynamicZoneAsylion::addMono()
{
	Assert( m_pZone != NULL );
	InstantDungeonMonster* pInstantDungeonMonster = g_pInstantDungeonMonsterManager->getInstantDungeonMonster(m_Indun);
	if(pInstantDungeonMonster == NULL) return false;

	// �̼��� ������ �����Ѵ�.
	Monster* pMonster = new Monster( g_pInstantDungeonMonsterManager->getGroupBoss(pInstantDungeonMonster->getGroupID(), 1) );
	Assert( pMonster != NULL );

	try
	{
		m_pZone->addCreature( pMonster, 116, 18, 2 );

		m_MonoObjectID = pMonster->getObjectID();
	}
	catch ( EmptyTileNotExistException& )
	{
		SAFE_DELETE( pMonster );
	}

	const PCManager* pPCManager = m_pZone->getPCManager();
	const hash_map< ObjectID_t, Creature* > & creatures2 = pPCManager->getCreatures();
	hash_map< ObjectID_t, Creature* >::const_iterator itr2;

	for (itr2=creatures2.begin(); itr2!=creatures2.end(); itr2++)
	{
		Creature* pCreature = itr2->second;
		if (pCreature->isPC())
		{
		GCNoticeEvent gcNoticeEvent;
		gcNoticeEvent.setCode( NOTICE_EVENT_CONTINUAL_GROUND_ATTACK );
		gcNoticeEvent.setParameter( 50 );
		pCreature->getPlayer()->sendPacket( &gcNoticeEvent );
		}
		else
		{
			throw Error("PCManager�� PC�ƴѰ� ����ֳ� -_-");
		}
	}
	return true;
}

bool DynamicZoneAsylion::checkMono()
{
	Assert( m_pZone != NULL );

	MonsterManager* pMonsterManager = m_pZone->getMonsterManager();
	Assert( pMonsterManager != NULL );

	Creature* pCreature = pMonsterManager->getCreature( m_MonoObjectID );
	return pCreature != NULL;
}

bool DynamicZoneAsylion::clearMono()
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

	return true;
}

DEFINE_DYNAMIC_ZONE_FACTORY( DynamicZoneAsylion, DYNAMIC_ZONE_ASYLION )

