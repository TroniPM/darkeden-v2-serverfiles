/////////////////////////////////////////////////////////////////////////////
// DynamicZonePartyOfDungeon.cpp
/////////////////////////////////////////////////////////////////////////////

#include "DynamicZonePartyOfDungeon4.h"
#include "DynamicZoneInfo.h"
#include "Zone.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Ousters.h"
#include "Inventory.h"
#include "Monster.h"
#include "PCManager.h"
#include "Player.h"
#include "MonsterManager.h"
#include "InstantDungeonMonster.h"
#include "Treasure.h"
#include "EffectKillTimer.h"
#include "GQuestManager.h"
#include "Assert.h"
#include "Item.h"
#include "ItemUtil.h"
#include "ItemInfo.h"
#include "ItemInfoManager.h"
#include "MonsterInfo.h"
#include "ZoneUtil.h"
#include "VariableManager.h"
#include "MonsterDropSetup.h"
#include "MonsterItemDrop.h"
#include "MonsterItemDropOption.h"
#include "ItemGradeManager.h"

#include "ItemFactoryManager.h"
#include "PacketUtil.h"
#include "Gpackets/GCSystemMessage.h"
#include "Gpackets/GCCreateItem.h"
#include "Gpackets/GCNoticeEvent.h"
#include "Gpackets/GCModifyInformation.h" 
#include <stdio.h>
#include <stdlib.h>

enum COMMON_PARTY_OF_DUNGEON
{
	WAIT_FOR_PC,
	ADD_MONO,
	WAIT_FOR_COMPLETE,
	CLEAR_MONO,
	CREATURE_ADD_ITEM,
	WAIT_FOR_CLEAR,
	COMMON_PARTY_OF_DUNGEON_END,

	COMMON_PARTY_OF_DUNGEON_MAX
};

DynamicZonePartyOfDungeon4::DynamicZonePartyOfDungeon4()
{
	// 최종 남은 몬스터 수를 위한 부분
	m_CountMonster = 0;

	// 스테이지를 위한 선언부분
	m_NextStage = 0;
	m_PrevStage = 0;
	// 인던 그룹?
	m_GroupID = 0;
	m_TowerEnd = 0;
	m_SaveTime = 0;
}

DynamicZonePartyOfDungeon4::~DynamicZonePartyOfDungeon4()
{
}

void DynamicZonePartyOfDungeon4::init()
{
	Assert( m_pZone != NULL );

	m_OMOAStatus = WAIT_FOR_PC;
	getCurrentTime( m_Deadline );
	m_Deadline.tv_sec += 60;
	getCurrentTime( m_EndTime );
	m_EndTime.tv_sec += 300;

}

void DynamicZonePartyOfDungeon4::heartbeat()
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
			getCurrentTime( m_EndTime );
			m_EndTime.tv_sec += 300;

			// 다음 스테이지가 이전스테이지보다 높을경우 이전스테이지의 수를 올린다.
			if(m_NextStage > m_PrevStage){
			m_PrevStage++;
			}

			// 스테이지 난이도를 올린다.
			m_NextStage += 1;

			// 3분이라는 시간을 안내해준다.
			timecheck();
			
			// 상태 표시를 넘긴다.
			m_OMOAStatus = WAIT_FOR_COMPLETE;
			cout << "-----------------------WAIT_FOR_COMPLETE" << endl;
		}
		break;

	case WAIT_FOR_COMPLETE:

		// 몬스터가 살아있고, 180초를 넘겼을 경우 그대로 패배처리한다.
		if ( CountMonster() && checkComplete() && m_NextStage <= m_TowerEnd)
		{
			clearMono();
			openGateToOut();
			m_OMOAStatus = WAIT_FOR_CLEAR;
			cout << "-----------------------WAIT_FOR_CLEAR" << endl;
		}
		if(!CountMonster() && checkComplete() && m_NextStage > m_TowerEnd){
			m_OMOAStatus = CLEAR_MONO;
			cout << "-----------------------CLEAR_MONO" << endl;
		}
	
		// 몬스터가 다 죽어있고, 180초를 넘겼을 경우 다음 스테이지로 올려보낸다.
		if ( !CountMonster() && checkComplete() && m_NextStage <= m_TowerEnd)
		{
			// 다시 1분 추가한다.
			m_OMOAStatus = ADD_MONO;
		}

		// 몬스터가 다 죽어있고, 180초가 안넘어갔을 경우.
		if ( !CountMonster() && !checkComplete() && m_NextStage <= m_TowerEnd)
		{
			// 다시 1분 추가한다.
			m_OMOAStatus = ADD_MONO;
		}

		// 몬스터가 다 죽고 스테이지도 끝났다. 캐릭터도 살아 남았으므로 끝낸다.
		if(!CountMonster() && !checkComplete() && m_NextStage > m_TowerEnd){
			m_OMOAStatus = CLEAR_MONO;
			cout << "-----------------------CLEAR_MONO" << endl;
		}
		break;

	case CLEAR_MONO:
		if ( clearMono() )
		{
			// 몬스터 카운터를 먼저 보낸다.
			m_OMOAStatus = CREATURE_ADD_ITEM;
			cout << "-----------------------CREATURE_ADD_ITEM" << endl;
		}
		break;

	case CREATURE_ADD_ITEM :
		if ( checkPC() )
		{
			addItem();
			openGateToOut();
			m_OMOAStatus = WAIT_FOR_CLEAR;
			cout << "-----------------------WAIT_FOR_CLEAR" << endl;
		}
		break;
		
	case WAIT_FOR_CLEAR:

			// 선언된 모든 부분을 초기화 한다.
			m_NextStage = 0;
			m_PrevStage = 0;
			m_CountMonster = 0;

		if ( checkPC() )
		{
			m_OMOAStatus = COMMON_PARTY_OF_DUNGEON_END;
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

bool DynamicZonePartyOfDungeon4::checkPC()
{
	Assert( m_pZone != NULL );

	// PC 수 체크
	uint size = m_pZone->getPCManager()->getSize();

	return size != 0;
}

bool DynamicZonePartyOfDungeon4::addMono()
{
			cout << " 실행되나.. " << endl;
	Assert( m_pZone != NULL );

	Timeval currentTime;
	getCurrentTime(currentTime);
	int Times = m_EndTime.tv_sec - currentTime.tv_sec;
	m_SaveTime += Times;

	list<WORD> m_Monster_list2;
	m_Monster_list2 = g_pInstantDungeonMonsterManager->getTowerMonsterList(m_GroupID, m_NextStage);

			cout << " 실행되나..2 " << endl;
	list<WORD>::const_iterator itr = m_Monster_list2.begin();
	list<WORD>::const_iterator endItr = m_Monster_list2.end();
		for ( ; itr != endItr ; itr++ )
		{

		InstantDungeonMonster* pInstantDungeonMonster = g_pInstantDungeonMonsterManager->getInstantDungeonMonster(*itr);
			for(int s =0; s<pInstantDungeonMonster->getMonsterNumber(); s++){
			Monster* pMonster = new Monster(pInstantDungeonMonster->getMonsterType());

			Assert( pMonster != NULL );
			ZoneCoord_t x, y;
				try
				{
					if (!m_pZone->getMonsterManager()->findPosition(pMonster->getMonsterType(), x, y))
					{
					Assert(false);
					return true;
					}
				m_pZone->addCreature( pMonster, x, y, Directions(rand()%8) );
				}
					catch ( EmptyTileNotExistException& )
				{
					SAFE_DELETE( pMonster );
				}
			}
		}
	return true;
	/*for(int i=0; i<Monster_list.size(); i++;){
		InstantDungeonMonster* pInstantDungeonMonster = g_pInstantDungeonMonsterManager->getInstantDungeonMonster(i);
	}

	//int s = g_pInstantDungeonMonsterManager->getTowerMaxInt(m_GroupID, m_NextStage);
			cout << " 실행되나..3 " << endl;
	while(i<=s){
			cout << " 실행되나..4 " << endl;
		InstantDungeonMonster* pInstantDungeonMonster = g_pInstantDungeonMonsterManager->getInstantDungeonMonster(i);
		MonsterType_t 	MonsterType 	= pInstantDungeonMonster->getMonsterType();
			cout << " 실행되나..4 " << pInstantDungeonMonster->getMonsterType() << endl;
			cout << " 실행되나..4 " << m_NextStage << endl;
		if(pInstantDungeonMonster != NULL && pInstantDungeonMonster->IsBoss() == m_NextStage){
		for(int s =0; s<pInstantDungeonMonster->getMonsterNumber(); s++){
		// 이성의 봉인을 생성한다.
		Monster* pMonster = new Monster( MonsterType );
		Assert( pMonster != NULL );
		
		ZoneCoord_t x, y;
		if(pInstantDungeonMonster->getX() > 0){x = pInstantDungeonMonster->getX();}
		if(pInstantDungeonMonster->getY() > 0){y = pInstantDungeonMonster->getY();}
		try
		{
			if (!m_pZone->getMonsterManager()->findPosition(pMonster->getMonsterType(), x, y))
			{
				Assert(false);
				return true;
			}
			m_pZone->addCreature( pMonster, x, y, Directions(rand()%8) );
		}
		catch ( EmptyTileNotExistException& )
		{
			SAFE_DELETE( pMonster );
		}
			}//for
		}
			//SAFE_DELETE( pInstantDungeonMonster );
		i++;
	}
	return true;*/
}

bool DynamicZonePartyOfDungeon4::clearMono()
{
		Assert( m_pZone != NULL );

		// 모든 몬스터를 죽인다.
		MonsterManager* pMM = m_pZone->getMonsterManager();
		hash_map< ObjectID_t, Creature* > & monsters = pMM->getCreatures();
		hash_map< ObjectID_t, Creature* >::iterator itr = monsters.begin();

		for (; itr!=monsters.end(); itr++)
		{
				Creature* pCreature = itr->second;
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

bool DynamicZonePartyOfDungeon4::openGateToOut()
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

bool DynamicZonePartyOfDungeon4::checkComplete()
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
bool DynamicZonePartyOfDungeon4::CountMonster()
{
			m_CountMonster = 0;
			MonsterManager* pMM = m_pZone->getMonsterManager();
			hash_map< ObjectID_t, Creature* > & monsters = pMM->getCreatures();
			hash_map< ObjectID_t, Creature* >::iterator itr = monsters.begin();

			for (; itr!=monsters.end(); itr++)
			{
				Creature* pCreature = itr->second;
				// 몬스터 일경우 몬스터 카운터 1 증가
				if(pCreature != NULL && pCreature->isMonster()){
				m_CountMonster++;
				}
			}
	
	// 60마리가 아직 넘지 않았으므로 FALSE
	return m_CountMonster;
}
void DynamicZonePartyOfDungeon4::timecheck()
{
	const PCManager* pPCManager = m_pZone->getPCManager();
	const hash_map< ObjectID_t, Creature* > & creatures2 = pPCManager->getCreatures();
	hash_map< ObjectID_t, Creature* >::const_iterator itr2;
	int i2;

	if (creatures2.empty())
		return;

	for (i2=0, itr2=creatures2.begin(); itr2!=creatures2.end(); i2++, itr2++)
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
			throw Error("PCManager에 PC아닌게 들어있노 -_-");
		}
	}
}
void DynamicZonePartyOfDungeon4::addItem()
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
				pStmt->executeQuery( "INSERT INTO EventSimyunTime (OwnerID, GameTower, GameTime, DateTime, DungeonType) VALUES('%s', %d, %d, now(),2)",
							pCreature->getName().c_str(), (int)m_NextStage, (int)m_SaveTime );
			SAFE_DELETE(pStmt);
			}
			END_DB(pStmt)

			Item* pItem1 = NULL;

			Creature::CreatureClass ownerCreatureClass;
			ownerCreatureClass = pCreature->getCreatureClass();

			MonsterDropSetup* pMonsterItemDrop = g_pMonsterDropSetupManager->getMonsterDropSetup(9);
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
	// 10초후 이동시킨다.
	pPCManager->transportAllCreatures( m_ZoneID, m_ZoneX, m_ZoneY );
}
void DynamicZonePartyOfDungeon4::processEntering()
{
	Assert( m_pZone != NULL );

	// 들어왔으니 인던에 대한 정보를 저장한다.
	m_TowerEnd = g_pInstantDungeonMonsterManager->getTowerEndStatge(m_GroupID);

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

           // pPC->getGQuestManager()->enterDynamicZone(m_TemplateZoneID);
        }
    }
}
/*
bool DynamicZonePartyOfDungeon4::checkMono()
{
	Assert( m_pZone != NULL );

	MonsterManager* pMonsterManager = m_pZone->getMonsterManager();
	Assert( pMonsterManager != NULL );

	Creature* pCreature = pMonsterManager->getCreature( m_MonoObjectID );
	return pCreature != NULL;
}
*/

void DynamicZonePartyOfDungeon4::killPC()
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

DEFINE_DYNAMIC_ZONE_FACTORY( DynamicZonePartyOfDungeon4, DYNAMIC_ZONE_PARTY_OF_DUNGEON4 )


