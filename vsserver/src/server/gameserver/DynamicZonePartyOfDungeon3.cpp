/////////////////////////////////////////////////////////////////////////////
// DynamicZonePartyOfDungeon.cpp
/////////////////////////////////////////////////////////////////////////////

#include "DynamicZonePartyOfDungeon3.h"
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
#include "EffectKillTimer.h"
#include "GQuestManager.h"
#include "Assert.h"
#include "Item.h"
#include "ItemUtil.h"
#include "ItemInfo.h"
#include "ItemInfoManager.h"
#include "MonsterInfo.h"
#include "ZoneUtil.h"

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

DynamicZonePartyOfDungeon3::DynamicZonePartyOfDungeon3()
{
	// 최종 남은 몬스터 수를 위한 부분
	m_CountMonster = 1;
	m_MonsterSize = 0;
	m_ItemCreate = 0;
	// 인던 그룹?
	m_GroupID = 0;
}

DynamicZonePartyOfDungeon3::~DynamicZonePartyOfDungeon3()
{
}

void DynamicZonePartyOfDungeon3::init()
{
	Assert( m_pZone != NULL );

	m_OMOAStatus = WAIT_FOR_PC;
	getCurrentTime( m_Deadline );
	m_Deadline.tv_sec += 60;
	getCurrentTime( m_EndTime );
	m_EndTime.tv_sec += 60;
}

void DynamicZonePartyOfDungeon3::heartbeat()
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
			m_MonsterSize += 10;
			getCurrentTime( m_EndTime );
			m_EndTime.tv_sec += 60;
			m_ItemCreate++;
			if(m_ItemCreate == 10) addItem2();
			timecheck();
			m_OMOAStatus = WAIT_FOR_COMPLETE;
			cout << "몬스터 난이도 : " << m_MonsterSize << endl;
			cout << "-----------------------WAIT_FOR_COMPLETE" << endl;
		}
		break;

	case WAIT_FOR_COMPLETE:
		if ( CountMonster() )
		{
			openGateToOut();
			m_OMOAStatus = CLEAR_MONO;
			cout << "-----------------------CLEAR_MONO" << endl;
		}
	
		// 60마리가 넘어가지 않았을 경우 다음 단계로 보내버린다.
		// 60초 딜레이가 넘어 갔을 경우 다시 컨트롤 시켜야 한다.
		if ( !CountMonster() && checkComplete())
		{
			// 다시 1분 추가한다.
			m_OMOAStatus = ADD_MONO;
		}

		//cout << " 개체수 : " << m_CountMonster << endl;
		// 몬스터가 60마리를 넘어갔을 경우 내보내기.
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
			if(m_MonsterSize >= 60){
			addItem();
			}
			openGateToOut();
			m_OMOAStatus = WAIT_FOR_CLEAR;
			cout << "-----------------------WAIT_FOR_CLEAR" << endl;
		}
		break;
		
	case WAIT_FOR_CLEAR:
			m_MonsterSize = 0;
			m_CountMonster = 0;
			m_ItemCreate = 0;
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

bool DynamicZonePartyOfDungeon3::checkPC()
{
	Assert( m_pZone != NULL );

	// PC 수 체크
	uint size = m_pZone->getPCManager()->getSize();

	return size != 0;
}

bool DynamicZonePartyOfDungeon3::addMono()
{
			cout << " 실행되나.. " << endl;
	Assert( m_pZone != NULL );
	int i = g_pInstantDungeonMonsterManager->getMinInt(m_GroupID);;
	int s = g_pInstantDungeonMonsterManager->getMaxInt(m_GroupID);;
			cout << " 실행되나.. 2" << endl;
	while(i<=s){
			cout << " 실행되나.. 3" << endl;
		InstantDungeonMonster* pInstantDungeonMonster = g_pInstantDungeonMonsterManager->getInstantDungeonMonster(i);
			cout << " 실행되나.. 4" << endl;
		MonsterType_t 	MonsterType 	= pInstantDungeonMonster->getMonsterType();

		if(pInstantDungeonMonster != NULL){
			cout << " 실행되나.. 5" << endl;
		for(int s =0; s<pInstantDungeonMonster->getMonsterNumber(); s++){
			cout << " 실행되나.. 6" << endl;
		// 이성의 봉인을 생성한다.
		Monster* pMonster = new Monster( MonsterType );
		Assert( pMonster != NULL );
		
		pMonster->setName("내면의 괴물");
		cout << " 몬스터 체력 : " << pMonster->getHP() << endl;
		pMonster->setHP(pMonster->getHP()+getPercentValue(pMonster->getHP(), m_MonsterSize),pMonster->getHP()+getPercentValue(pMonster->getHP(), m_MonsterSize));
		pMonster->setSTR(pMonster->getSTR()+getPercentValue(pMonster->getSTR(), m_MonsterSize));
		pMonster->setDEX(pMonster->getDEX()+getPercentValue(pMonster->getDEX(), m_MonsterSize));
		pMonster->setINT(pMonster->getINT()+getPercentValue(pMonster->getINT(), m_MonsterSize));
		pMonster->setExp(pMonster->getExp()+getPercentValue(pMonster->getExp(), m_MonsterSize));
		pMonster->setProtection(pMonster->getProtection()+getPercentValue(pMonster->getProtection(), m_MonsterSize));
		pMonster->setToHit(pMonster->getToHit()+getPercentValue(pMonster->getToHit(), m_MonsterSize));
		pMonster->setDamage(pMonster->getDamage()+getPercentValue(pMonster->getDamage(), m_MonsterSize),pMonster->getDamage()+getPercentValue(pMonster->getDamage(), m_MonsterSize));
		cout << " 몬스터 변경 체력 : " << pMonster->getHP() << endl;
		
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
			m_pZone->addCreature( pMonster, x, y, 2 );
		}
		catch ( EmptyTileNotExistException& )
		{
			SAFE_DELETE( pMonster );
		}
			}//for
		}
		i++;
	}
	return true;
}

bool DynamicZonePartyOfDungeon3::clearMono()
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

bool DynamicZonePartyOfDungeon3::openGateToOut()
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

bool DynamicZonePartyOfDungeon3::checkComplete()
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
bool DynamicZonePartyOfDungeon3::CountMonster()
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

	// 몬스터가 60마리를 넘어 설 경우 TRUE
	if(m_CountMonster > 60)	return true;
	
	// 60마리가 아직 넘지 않았으므로 FALSE
	return false;
}
void DynamicZonePartyOfDungeon3::timecheck()
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
void DynamicZonePartyOfDungeon3::addItem()
{

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

			PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);
			Inventory* pInventory = pPC->getInventory();
			
			list<OptionType_t> nullList;
			Item* pItem = g_pItemFactoryManager->createItem(Item::ITEM_CLASS_EVENT_GIFT_BOX, 29, nullList);

			(m_pZone->getObjectRegistry()).registerObject(pItem);

			_TPOINT p;
			if (pInventory->getEmptySlot(pItem, p))
			{
				// 인벤토리에 추가한다.
				pInventory->addItem(p.x, p.y, pItem);

	           			pItem->create(pCreature->getName(), STORAGE_INVENTORY, 0, p.x, p.y);

				// ItemTrace 에 Log 를 남긴다
				if ( pItem != NULL && pItem->isTraceItem() )
				{
					remainTraceLog( pItem, "InstantDungeon", pCreature->getName(), ITEM_LOG_CREATE, DETAIL_EVENTNPC);
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
						remainTraceLog( pItem, "InstantDungeon", zoneName, ITEM_LOG_CREATE, DETAIL_EVENTNPC);
						remainTraceLogNew( pItem, zoneName, ITL_GET , ITLD_EVENTNPC, m_pZone->getZoneID(), p.x, p.y);
					}
				}
				else
				{
					SAFE_DELETE(pItem);
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
void DynamicZonePartyOfDungeon3::addItem2()
{

	m_ItemCreate = 0;
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

			PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);
			Inventory* pInventory = pPC->getInventory();
			
			list<OptionType_t> nullList;
			Item* pItem = g_pItemFactoryManager->createItem(Item::ITEM_CLASS_COMMON_ITEM, 63, nullList);

			(m_pZone->getObjectRegistry()).registerObject(pItem);

			_TPOINT p;
			if (pInventory->getEmptySlot(pItem, p))
			{
				// 인벤토리에 추가한다.
				pInventory->addItem(p.x, p.y, pItem);

	           			pItem->create(pCreature->getName(), STORAGE_INVENTORY, 0, p.x, p.y);

				// ItemTrace 에 Log 를 남긴다
				if ( pItem != NULL && pItem->isTraceItem() )
				{
					remainTraceLog( pItem, "InstantDungeon", pCreature->getName(), ITEM_LOG_CREATE, DETAIL_EVENTNPC);
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
						remainTraceLog( pItem, "InstantDungeon", zoneName, ITEM_LOG_CREATE, DETAIL_EVENTNPC);
						remainTraceLogNew( pItem, zoneName, ITL_GET , ITLD_EVENTNPC, m_pZone->getZoneID(), p.x, p.y);
					}
				}
				else
				{
					SAFE_DELETE(pItem);
				}
			}
		}
		else
		{
			throw Error("PCManager에 PC아닌게 들어있노 -_-");
		}
	}
}
void DynamicZonePartyOfDungeon3::processEntering()
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

           // pPC->getGQuestManager()->enterDynamicZone(m_TemplateZoneID);
        }
    }
}
/*
bool DynamicZonePartyOfDungeon3::checkMono()
{
	Assert( m_pZone != NULL );

	MonsterManager* pMonsterManager = m_pZone->getMonsterManager();
	Assert( pMonsterManager != NULL );

	Creature* pCreature = pMonsterManager->getCreature( m_MonoObjectID );
	return pCreature != NULL;
}
*/

void DynamicZonePartyOfDungeon3::killPC()
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

DEFINE_DYNAMIC_ZONE_FACTORY( DynamicZonePartyOfDungeon3, DYNAMIC_ZONE_PARTY_OF_DUNGEON3 )


