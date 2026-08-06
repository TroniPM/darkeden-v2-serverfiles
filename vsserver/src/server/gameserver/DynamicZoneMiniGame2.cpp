/////////////////////////////////////////////////////////////////////////////
// DynamicZoneOustersMirrorOfAbyss.cpp
/////////////////////////////////////////////////////////////////////////////

#include "DynamicZoneMiniGame2.h"
#include "DynamicZoneTimeOfDungeon.h"
#include "DynamicZoneGroup.h"
#include "DynamicZoneManager.h"
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
#include "Timeval.h"
#include "Player.h"
#include "Item.h"
#include "ItemUtil.h"
#include "ItemInfo.h"
#include "ItemInfoManager.h"
#include "ZoneUtil.h"
#include "InstantDungeonMonster.h"
#include "VariableManager.h"
#include "MonsterDropSetup.h"
#include "MonsterItemDrop.h"
#include "MonsterItemDropOption.h"
#include "ItemGradeManager.h"
#include "ItemFactoryManager.h"
#include "EffectCastingTrap.h"
#include "PacketUtil.h"
#include "EffectContinualGroundAttack.h"
#include "ObjectRegistry.h"
#include "Tile.h"
#include "Creature.h"
#include "CreatureUtil.h"
#include "Gpackets/GCSystemMessage.h"
#include "Gpackets/GCNoticeEvent.h"
#include "Gpackets/GCCreateItem.h"
#include "Gpackets/GCModifyInformation.h"
#include <stdio.h>
#include <stdlib.h>

enum OUSTERS_MIRROR_OF_ABYSS
{
	WAIT_FOR_PC,
	START_GAME,
	ADD_MONO,
	WAIT_FOR_COMPLETE,
	CLEAR_MONO,
	WAIT_FOR_CLEAR,
	OUSTERS_MIRROR_OF_ABYSS_END,

	OUSTERS_MIRROR_OF_ABYSS_MAX
};

DynamicZoneMiniGame2::DynamicZoneMiniGame2()
{
}

DynamicZoneMiniGame2::~DynamicZoneMiniGame2()
{
}

void DynamicZoneMiniGame2::init()
{
	Assert( m_pZone != NULL );

//	m_addTimesec = 0;
	m_States = 0;
	m_States_trasure = 0;
	m_OMOAStatus = WAIT_FOR_PC;
	getCurrentTime( m_Deadline );
	m_Deadline.tv_sec += 60;
	getCurrentTime( m_RegenEffectTime);
	m_RegenEffectTime.tv_sec += 1;
}

void DynamicZoneMiniGame2::heartbeat()
{
	switch ( m_OMOAStatus )
	{
	case WAIT_FOR_PC:
		if ( checkPC() )
		{
		processEntering();
		m_OMOAStatus = START_GAME;

		GCSystemMessage gcSystemMessage;
		gcSystemMessage.setType(SYSTEM_MESSAGE_NORMAL);
		gcSystemMessage.setMessage( " 60초간 아이템이 땅에 떨어집니다!!! "  );
		m_pZone->broadcastPacket( &gcSystemMessage );
			cout << "-----------------------ADD_MONO" << endl;
		}
		break;
	case START_GAME :
		if ( !checkComplete() )
		{
			m_OMOAStatus = ADD_MONO;
		}
		break;
	case ADD_MONO:
			{
			TreasureCheck();
			m_OMOAStatus = WAIT_FOR_COMPLETE;
			cout << "-----------------------WAIT_FOR_COMPLETE" << endl;
			}
		break;

	case WAIT_FOR_COMPLETE:
		if( checkComplete2() ){
			m_RegenEffectTime.tv_sec += 1;
			m_OMOAStatus = ADD_MONO;
		}
		// 시간이 다 되면 내보낸다.
		if ( checkComplete() )
		{
			m_OMOAStatus = CLEAR_MONO;
			cout << "-----------------------REGEN_ADD_MONO" << endl;
		}
		break;

	case CLEAR_MONO:
			// 맵안에 있는 모든 몬스터를 죽였으므로 내보낸다.
			openGateToOut();
			m_OMOAStatus = WAIT_FOR_CLEAR;
			cout << "-----------------------WAIT_FOR_CLEAR" << endl;
		break;

	case WAIT_FOR_CLEAR:
		if ( !checkPC() )
		{
			m_OMOAStatus = OUSTERS_MIRROR_OF_ABYSS_END;
			m_Status = DYNAMIC_ZONE_STATUS_READY;
			cout << "-----------------------READY" << endl;
		}
		break;
	}

	// PC플레이어가 없는 경우다. 이때는 바로 종료시켜버려야 한다.
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

bool DynamicZoneMiniGame2::checkPC()
{
	Assert( m_pZone != NULL );

	// PC 수 체크
	uint size = m_pZone->getPCManager()->getSize();

	return size != 0;
}
bool DynamicZoneMiniGame2::addMono()
{
	return true;
}

bool DynamicZoneMiniGame2::openGateToOut()
{
	Assert( m_pZone != NULL );

	int targetDynamicZoneType = g_pDynamicZoneInfoManager->getDynamicZoneTypeByZoneID( 9003 );
	DynamicZoneGroup* pDynamicZoneGroup = g_pDynamicZoneManager->getDynamicZoneGroup( targetDynamicZoneType );
	Assert( pDynamicZoneGroup != NULL );

	DynamicZone* pDynamicZone = pDynamicZoneGroup->getAvailableDynamicZone();
	Assert( pDynamicZone != NULL );

	DynamicZoneTimeOfDungeon* pAlterOfBlood = dynamic_cast<DynamicZoneTimeOfDungeon*>(pDynamicZone);
	Assert( pAlterOfBlood != NULL );
	pAlterOfBlood->setZoneID(getZoneID());
	pAlterOfBlood->setZoneX(getZoneX());
	pAlterOfBlood->setZoneY(getZoneY());
	pAlterOfBlood->setInstantID(getInstantID());
	pAlterOfBlood->setStates(getStates());

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

	m_pZone->getPCManager()->transportAllCreatures( pDynamicZone->getZoneID(), 25, 25 );
	cout << "---------------------------------Clear Time Of Dungeon" << endl;
        }
    }

	return true;
}
void DynamicZoneMiniGame2::TreasureCheck()
{
    hash_map<ObjectID_t, Creature*>::const_iterator itr = m_pZone->getPCManager()->getCreatures().begin();
    hash_map<ObjectID_t, Creature*>::const_iterator endItr = m_pZone->getPCManager()->getCreatures().end();
    for ( ; itr != endItr; ++itr )
    {
        Assert( itr->second != NULL );

        if ( itr->second->isPC() )
        {
	Creature* pCreature = itr->second;

	ItemType_t ItemType = Random(40,45);
	int RadomMapX = Random(0,5);
	int RadomMapY = Random(0,5);
	list<OptionType_t> nullList;
	Item* pItem = g_pItemFactoryManager->createItem(Item::ITEM_CLASS_EVENT_STAR, ItemType, nullList);
 	pItem->setNum(1);
	pItem->setHeroOption(0);
	pItem->setHeroOptionAttr(0);
	(m_pZone->getObjectRegistry()).registerObject(pItem);

	// 인벤토리에 자리가 없어서 바닥에 떨어뜨린다.

	TPOINT p = m_pZone->addItem(pItem, pCreature->getX()+RadomMapX , pCreature->getY()+RadomMapY);
	if (p.x != -1)
	{
		pItem->create("", STORAGE_ZONE, m_pZone->getZoneID(), p.x, p.y );

					// ItemTrace 에 Log 를 남긴다
		if ( pItem != NULL && pItem->isTraceItem() )
		{
			char zoneName[15];
			sprintf( zoneName , "%4d%3d%3d", m_pZone->getZoneID(), p.x, p.y);
			remainTraceLog( pItem, "LairMaster", zoneName, ITEM_LOG_CREATE, DETAIL_EVENTNPC);
			remainTraceLogNew( pItem, zoneName, ITL_GET , ITLD_EVENTNPC, m_pZone->getZoneID(), p.x, p.y);
		}
	}
	else
	{
		SAFE_DELETE(pItem);
	}
	}
}

}

void DynamicZoneMiniGame2::timecheck()
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
			GCModifyInformation gcMI;
			if ( pCreature->isSlayer() )
			{
				Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);
				pSlayer->setGoldEx(pSlayer->getGold()+(8500+getPercentValue(17000,m_States)));

				gcMI.addLongData( MODIFY_GOLD, pSlayer->getGold() );
			}
			else if (pCreature->isVampire() )
			{
				Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);
				pVampire->setGoldEx(pVampire->getGold()+(8500+getPercentValue(17000,m_States*10)));

				gcMI.addLongData( MODIFY_GOLD, pVampire->getGold() );
			}
			else if (pCreature->isOusters() )
			{
				Ousters* pOusters = dynamic_cast<Ousters*>(pCreature);
				pOusters->setGoldEx(pOusters->getGold()+(8500+getPercentValue(17000,m_States*10)));

				gcMI.addLongData( MODIFY_GOLD, pOusters->getGold() );
			}

			pCreature->getPlayer()->sendPacket( &gcMI );

		Timeval currentTime;
		getCurrentTime(currentTime);

		int Times = m_Deadline.tv_sec - currentTime.tv_sec;

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

bool DynamicZoneMiniGame2::checkComplete()
{
	Timeval current;
	getCurrentTime( current );
	if ( current > m_Deadline )
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool DynamicZoneMiniGame2::checkComplete2()
{
	Timeval current;
	getCurrentTime( current );
	if ( current > m_RegenEffectTime)
	{
		return true;
	}
	else
	{
		return false;
	}
}


void DynamicZoneMiniGame2::processEntering()
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
void DynamicZoneMiniGame2::addEffect()
{
	Assert( m_pZone != NULL );

    hash_map<ObjectID_t, Creature*>::const_iterator itr = m_pZone->getPCManager()->getCreatures().begin();
    hash_map<ObjectID_t, Creature*>::const_iterator endItr = m_pZone->getPCManager()->getCreatures().end();
    for ( ; itr != endItr; ++itr )
    {
        Assert( itr->second != NULL );

        if ( itr->second->isPC() )
        {
			Creature* pCreature = itr->second;

			EffectCastingIcicleTrap* pEffect = new EffectCastingIcicleTrap( Effect::EFFECT_CLASS_ICICLE_DROP, m_pZone);

			pEffect->setStartXY( pCreature->getX(), pCreature->getY());
			pEffect->setLength( 50 );
			pEffect->setTick( 10 );
			pEffect->setUnit( 10 );
			pEffect->setLarge( true );
			pEffect->setDir( 7 );
			pEffect->setNextTime(0);
			pEffect->setDeadline(10);
			m_pZone->addEffect_LOCKING( pEffect );
	}
   }
}
void DynamicZoneMiniGame2::killPC()
{
	Assert( m_pZone != NULL );

    // PC ??죽인다.
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

DEFINE_DYNAMIC_ZONE_FACTORY( DynamicZoneMiniGame2, DYNAMIC_ZONE_MINI_GAME2 )


