/////////////////////////////////////////////////////////////////////////////
// DynamicZoneOustersMirrorOfAbyss.cpp
/////////////////////////////////////////////////////////////////////////////

#include "DynamicZoneMiniGame.h"
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

DynamicZoneMiniGame::DynamicZoneMiniGame()
{
}

DynamicZoneMiniGame::~DynamicZoneMiniGame()
{
}

void DynamicZoneMiniGame::init()
{
	Assert( m_pZone != NULL );

//	m_addTimesec = 0;
	m_States = 0;
	m_States_trasure = 0;
	m_OMOAStatus = WAIT_FOR_PC;
	getCurrentTime( m_Deadline );
	m_Deadline.tv_sec += 30;
	getCurrentTime( m_RegenEffectTime);
	m_RegenEffectTime.tv_sec += 1;
}

void DynamicZoneMiniGame::heartbeat()
{
	switch ( m_OMOAStatus )
	{
	case WAIT_FOR_PC:
		if ( checkPC() )
		{
			m_States = 0;
			processEntering();
			m_OMOAStatus = START_GAME;

		GCSystemMessage gcSystemMessage;
		gcSystemMessage.setType(SYSTEM_MESSAGE_NORMAL);
		gcSystemMessage.setMessage( " 잠시후 미니게임이 시작되어집니다. "  );
		m_pZone->broadcastPacket( &gcSystemMessage );
			cout << "-----------------------ADD_MONO" << endl;
		}
		break;
	case START_GAME :
		if ( checkComplete() )
		{
			m_States= 1;
			m_OMOAStatus = ADD_MONO;
		}
		break;
	case ADD_MONO:
			{
			addEffect();
			m_OMOAStatus = WAIT_FOR_COMPLETE;
			cout << "-----------------------WAIT_FOR_COMPLETE" << endl;
			}
		break;

	case WAIT_FOR_COMPLETE:
		if( checkComplete2() ){
			m_RegenEffectTime.tv_sec += 1;
			m_OMOAStatus = ADD_MONO;
		}
		if ( checkComplete() )
		{
			m_Deadline.tv_sec += 30;
			// 보상을 위해 시간을 누적해논다.
			m_States += 1;
			// 몬스터의 난이도가 올라간다.
			timecheck();
			TreasureCheck();
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

bool DynamicZoneMiniGame::checkPC()
{
	Assert( m_pZone != NULL );

	// PC 수 체크
	uint size = m_pZone->getPCManager()->getSize();

	return size != 0;
}
bool DynamicZoneMiniGame::addMono()
{
	return true;
}

bool DynamicZoneMiniGame::openGateToOut()
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
	cout << "---------------------------------Clear Time Of Dungeon" << endl;
        }
    }

	return true;
}
void DynamicZoneMiniGame::TreasureCheck()
{

	TreasureList* pTreasureList = NULL;

	const PCManager* pPCManager = m_pZone->getPCManager();
	const hash_map< ObjectID_t, Creature* > & creatures = pPCManager->getCreatures();
	hash_map< ObjectID_t, Creature* >::const_iterator itr;
	int i;
	if (creatures.empty())
	return;

for (i=0, itr=creatures.begin(); itr!=creatures.end(); i++, itr++)
	{
		Creature* pCreature = itr->second;

		if (pCreature->isPC() )
		{
			if(!pCreature->isFlag(Effect::EFFECT_CLASS_COMA) && !pCreature->isDead()){
			PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);
			Inventory* pInventory = pPC->getInventory();
			bool ItemType = Random(0,1);

			list<OptionType_t> nullList;
			Item* pItem = g_pItemFactoryManager->createItem(Item::ITEM_CLASS_EVENT_STAR, ItemType ? 42:45, nullList);
 			pItem->setNum(1);
			pItem->setHeroOption(0);
			pItem->setHeroOptionAttr(0);
			(m_pZone->getObjectRegistry()).registerObject(pItem);

			// 인벤토리의 빈 곳을 찾는다.
			_TPOINT p;
			if (pInventory->getEmptySlot(pItem, p))
			{
				// 인벤토리??추가한다.
				pInventory->addItem(p.x, p.y, pItem);

	            pItem->create(pCreature->getName(), STORAGE_INVENTORY, 0, p.x, p.y);

				// ItemTrace 에 Log 를 남긴다
				if ( pItem != NULL && pItem->isTraceItem() )
				{
					remainTraceLog( pItem, "LairMaster", pCreature->getName(), ITEM_LOG_CREATE, DETAIL_EVENTNPC);
					remainTraceLogNew( pItem, pCreature->getName(), ITL_GET, ITLD_EVENTNPC, m_pZone->getZoneID() );
				}

				// 인벤토리에 아이템 생성 패킷을 보내준다.
				GCCreateItem gcCreateItem;

				makeGCCreateItem( &gcCreateItem, pItem, p.x, p.y );

				pCreature->getPlayer()->sendPacket(&gcCreateItem);
			}
			else
			{
				// 인벤토리에 자리가 없어서 바닥에 떨어뜨린다.

				TPOINT p = m_pZone->addItem(pItem, pCreature->getX(), pCreature->getY());
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
		else
		{
			throw Error("PCManager에 PC아닌게 들어있노 -_-");
		}
	}

}

void DynamicZoneMiniGame::timecheck()
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

bool DynamicZoneMiniGame::checkComplete()
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

bool DynamicZoneMiniGame::checkComplete2()
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


void DynamicZoneMiniGame::processEntering()
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
void DynamicZoneMiniGame::addEffect()
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
void DynamicZoneMiniGame::killPC()
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

DEFINE_DYNAMIC_ZONE_FACTORY( DynamicZoneMiniGame, DYNAMIC_ZONE_MINI_GAME )


