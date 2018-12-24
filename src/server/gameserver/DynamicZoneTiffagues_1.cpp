/////////////////////////////////////////////////////////////////////////////
// DynamicZoneOustersMirrorOfAbyss.cpp
/////////////////////////////////////////////////////////////////////////////

#include "DynamicZoneTiffagues_1.h"
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
#include "Item.h"
#include "ItemUtil.h"
#include "ItemInfo.h"
#include "ItemInfoManager.h"
#include "InstantDungeonMonster.h"
#include "Gpackets/GCSystemMessage.h"
#include "Gpackets/GCNoticeEvent.h"
#include "VariableManager.h"
#include "MonsterDropSetup.h"
#include "MonsterItemDrop.h"
#include "MonsterItemDropOption.h"
#include "ItemGradeManager.h"
#include "ItemFactoryManager.h"
#include "PacketUtil.h"

#include "Gpackets/GCCreateItem.h"
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

DynamicZoneTiffagues_1::DynamicZoneTiffagues_1()
{
	m_MonoObjectID = 0;
}

DynamicZoneTiffagues_1::~DynamicZoneTiffagues_1()
{
}

void DynamicZoneTiffagues_1::init()
{
	Assert( m_pZone != NULL );

	m_OMOAStatus = WAIT_FOR_PC;
	getCurrentTime( m_Deadline );
	m_Deadline.tv_sec += 60;
	getCurrentTime( m_EndTime );
	m_EndTime.tv_sec += (10 * 60)*2;
}

void DynamicZoneTiffagues_1::heartbeat()
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
			TreasureCheck();
			// 보스형을 잡았다. 그래도 내보내버린다.
			openGateToOut();
			m_OMOAStatus = CLEAR_MONO;
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

bool DynamicZoneTiffagues_1::checkPC()
{
	Assert( m_pZone != NULL );

	// PC 수 체크
	uint size = m_pZone->getPCManager()->getSize();

	return size != 0;
}

bool DynamicZoneTiffagues_1::addMono()
{
	InstantDungeonMonster* pInstantDungeonMonster = g_pInstantDungeonMonsterManager->getInstantDungeonMonster(m_Indun);
	if(pInstantDungeonMonster == NULL) return false;
	Assert( m_pZone != NULL );

	// 이성의 봉인을 생성한다.
	Monster* pMonster = new Monster( pInstantDungeonMonster->getMonsterType() );
	Assert( pMonster != NULL );

	try
	{
		m_pZone->addCreature( pMonster, 80, 99, 2 );

		m_MonoObjectID = pMonster->getObjectID();
	}
	catch ( EmptyTileNotExistException& )
	{
		SAFE_DELETE( pMonster );
	}

	return true;
}

bool DynamicZoneTiffagues_1::clearMono()
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

void DynamicZoneTiffagues_1::TreasureCheck()
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
		if (pCreature->isPC())
		{

			Statement* pStmt;
			BEGIN_DB
			{
				pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
				pStmt->executeQuery( "INSERT INTO EventSimyunTime (OwnerID, GameTower, GameTime, DateTime, DungeonType) VALUES('%s', 0, 0, now(), 3)",
							pCreature->getName().c_str() );
			SAFE_DELETE(pStmt);
			}
			END_DB(pStmt)

			Item* pItem1 = NULL;

			Creature::CreatureClass ownerCreatureClass;
			ownerCreatureClass = pCreature->getCreatureClass();

			MonsterDropSetup* pMonsterItemDrop = g_pMonsterDropSetupManager->getMonsterDropSetup(68);
		if ( pMonsterItemDrop != NULL && pMonsterItemDrop->IsDrop() )
		{
			if (ownerCreatureClass == Creature::CREATURE_CLASS_SLAYER)
			{
				pTreasureList = g_pMonsterItemDropManager->getMonsterItemDrop(pMonsterItemDrop->getSlayerRandomDrop1())->getSlayerTreasureList();
			}
			else if (ownerCreatureClass == Creature::CREATURE_CLASS_VAMPIRE)
			{
				pTreasureList = g_pMonsterItemDropManager->getMonsterItemDrop(pMonsterItemDrop->getSlayerRandomDrop1())->getVampireTreasureList();
			}
			else if (ownerCreatureClass == Creature::CREATURE_CLASS_OUSTERS)
			{
				pTreasureList = g_pMonsterItemDropManager->getMonsterItemDrop(pMonsterItemDrop->getSlayerRandomDrop1())->getOustersTreasureList();
			}
		}

		if ( pTreasureList != NULL )
		{
			const list<Treasure*>& treasures = pTreasureList->getTreasures();

			list<Treasure*>::const_iterator itr = treasures.begin();

			ITEM_TEMPLATE it;
			for (; itr != treasures.end(); itr++)
			{
				Treasure* pTreasure = (*itr);
				ITEM_TEMPLATE it;

				it.ItemClass  = Item::ITEM_CLASS_MAX;
				it.ItemType   = 0;

				it.NextOptionRatio = g_pVariableManager->getChiefMonsterRareItemPercent();
				it.NextOptionRatio += pMonsterItemDrop->getItemRareOptionBounsRatio();

				pTreasure->setRndItemOptionMax(g_pMonsterItemDropManager->getMonsterItemDrop(pMonsterItemDrop->getSlayerRandomDrop1())->getOptionCount());

				if ( pTreasure->getRandomItem(&it) )
				{
					pItem1 = g_pItemFactoryManager->createItem(it.ItemClass, it.ItemType, it.OptionType);
					pItem1->setGrade( ItemGradeManager::Instance().getRandomGrade() );
					if(pMonsterItemDrop->getItemSetOptionSetup() && pMonsterItemDrop->getItemSetOptionRatio() > rand()%100000){
					pItem1->setOptionType2( it.OptionType2 );
					}
					pItem1->setHeroOption( 0 );
					pItem1->setHeroOptionAttr( 0 );
					if(pMonsterItemDrop->getItemSetHeroOptionSetup() && pMonsterItemDrop->getItemSetHeroOptionRatio() > rand()%100000){
					int HeroOptionSetting = rand()%13;
					int HeroOption = g_pMonsterItemDropOptionManager->getRandomOption(HeroOptionSetting);
					int HeroOptionAttrSetting = g_pMonsterItemDropOptionManager->getRandomItem(HeroOptionSetting);
					if(HeroOptionAttrSetting != 0 ){
					pItem1->setHeroOption( HeroOption+1 );
					pItem1->setHeroOptionAttr( HeroOptionAttrSetting );
					}
				}

					Assert(pItem1 != NULL);
				}
			}
		}
		if(pItem1 != NULL)
		{
			PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);
			Inventory* pInventory = pPC->getInventory();

			(m_pZone->getObjectRegistry()).registerObject(pItem1);

			_TPOINT p;
			if (pInventory->getEmptySlot(pItem1, p))
			{
				// 인벤토리에 추가한다.
				pInventory->addItem(p.x, p.y, pItem1);

	           			pItem1->create(pCreature->getName(), STORAGE_INVENTORY, 0, p.x, p.y);

				// ItemTrace 에 Log 를 남긴다
				if ( pItem1 != NULL && pItem1->isTraceItem() )
				{
					remainTraceLog( pItem1, "InstantDungeon", pCreature->getName(), ITEM_LOG_CREATE, DETAIL_EVENTNPC);
					remainTraceLogNew( pItem1, pCreature->getName(), ITL_GET, ITLD_EVENTNPC, m_pZone->getZoneID() );
				}

				// 인벤토리에 아이템 생성 패킷을 보내준다.
				GCCreateItem gcCreateItem;

				makeGCCreateItem( &gcCreateItem, pItem1, p.x, p.y );

				pCreature->getPlayer()->sendPacket(&gcCreateItem);
			}
			else
			{
				// 인벤토리에 자리가 없어서 바닥에 떨어뜨린다.

				TPOINT p = m_pZone->addItem(pItem1, pCreature->getX(), pCreature->getY());
				if (p.x != -1)
				{
					pItem1->create("", STORAGE_ZONE, m_pZone->getZoneID(), p.x, p.y );

					// ItemTrace 에 Log 를 남긴다
					if ( pItem1 != NULL && pItem1->isTraceItem() )
					{
						char zoneName[15];
						sprintf( zoneName , "%4d%3d%3d", m_pZone->getZoneID(), p.x, p.y);
						remainTraceLog( pItem1, "InstantDungeon", zoneName, ITEM_LOG_CREATE, DETAIL_EVENTNPC);
						remainTraceLogNew( pItem1, zoneName, ITL_GET , ITLD_EVENTNPC, m_pZone->getZoneID(), p.x, p.y);
					}
				}
				else
				{
					SAFE_DELETE(pItem1);
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

bool DynamicZoneTiffagues_1::openGateToOut()
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

void DynamicZoneTiffagues_1::timecheck()
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

bool DynamicZoneTiffagues_1::checkComplete()
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

void DynamicZoneTiffagues_1::processEntering()
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

bool DynamicZoneTiffagues_1::checkMono()
{
	Assert( m_pZone != NULL );

	MonsterManager* pMonsterManager = m_pZone->getMonsterManager();
	Assert( pMonsterManager != NULL );

	Creature* pCreature = pMonsterManager->getCreature( m_MonoObjectID );
	return pCreature != NULL;
}

void DynamicZoneTiffagues_1::killPC()
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

DEFINE_DYNAMIC_ZONE_FACTORY( DynamicZoneTiffagues_1, DYNAMIC_ZONE_TIFFAGUES_1 )


