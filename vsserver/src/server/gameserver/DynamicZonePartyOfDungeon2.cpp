/////////////////////////////////////////////////////////////////////////////
// DynamicZonePartyOfDungeon2.cpp
/////////////////////////////////////////////////////////////////////////////

#include "DynamicZonePartyOfDungeon2.h"
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
#include "Gpackets/GCModifyInformation.h" 
#include <stdio.h>
#include <stdlib.h>

enum COMMON_PARTY_OF_DUNGEON
{
	WAIT_FOR_PC,
	ADD_MONO,
	WAIT_FOR_COMPLETE,
	ADD_MONO2,
	WAIT_FOR_COMPLETE2,
	CLEAR_MONO2,
	CLEAR_MONO,
	CREATURE_ADD_ITEM,
	WAIT_FOR_CLEAR,
	COMMON_PARTY_OF_DUNGEON_END,

	COMMON_PARTY_OF_DUNGEON_MAX
};

DynamicZonePartyOfDungeon2::DynamicZonePartyOfDungeon2()
{
	// 최종 남은 몬스터 수를 위한 부분
	m_CountMonster = 1;
	m_PersentMonster = 1;
	m_SkullPrice = 0;

	// 보스 몬스터 오브젝트 아이디
	m_MonoObjectID = 0;
	m_MonoObjectID1 = 0;
	m_MonoObjectID2 = 0;
	m_MonoObjectID3 = 0;
	// 인던 그룹?
	m_GroupID = 0;
	m_BossID = 0;
}

DynamicZonePartyOfDungeon2::~DynamicZonePartyOfDungeon2()
{
}

void DynamicZonePartyOfDungeon2::init()
{
	Assert( m_pZone != NULL );

	m_OMOAStatus = WAIT_FOR_PC;
	getCurrentTime( m_Deadline );
	m_Deadline.tv_sec += 60;
	getCurrentTime( m_EndTime );
	m_EndTime.tv_sec += 10 * 60;
}

void DynamicZonePartyOfDungeon2::heartbeat()
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
			m_OMOAStatus = WAIT_FOR_COMPLETE;
			cout << "-----------------------WAIT_FOR_COMPLETE" << endl;
		}
		break;

	case WAIT_FOR_COMPLETE:
		if ( checkComplete() )
		{
			openGateToOut();
			m_OMOAStatus = CLEAR_MONO;
			cout << "-----------------------CLEAR_MONO" << endl;
		}

		if ( !checkMono2() && !checkComplete() )
		{
			m_OMOAStatus = ADD_MONO2;
		}

		break;

	case ADD_MONO2:
		if ( addMono2() )
		{
			m_OMOAStatus = WAIT_FOR_COMPLETE2;
			cout << "-----------------------WAIT_FOR_COMPLETE" << endl;
		}
		break;

	case WAIT_FOR_COMPLETE2:
		if ( checkComplete() )
		{
			openGateToOut();
			m_OMOAStatus = CLEAR_MONO;
			cout << "-----------------------CLEAR_MONO" << endl;
		}
		if ( !checkMono() && !checkComplete() )
		{
			m_OMOAStatus = CLEAR_MONO;
		}

		break;

	case CLEAR_MONO:
		if ( clearMono() )
		{
			// 몬스터 카운터를 먼저 보낸다.
			CountMonster();
			m_OMOAStatus = CREATURE_ADD_ITEM;
			cout << "-----------------------CREATURE_ADD_ITEM" << endl;
		}
		if(checkComplete()){
			openGateToOut();
		}
		break;

	case CREATURE_ADD_ITEM :
		if ( clearMono() && checkPC() && !checkComplete() )
		{
			addItem();
			openGateToOut();
			m_OMOAStatus = WAIT_FOR_CLEAR;
			cout << "-----------------------WAIT_FOR_CLEAR" << endl;
		}
		break;
		
	case WAIT_FOR_CLEAR:
			m_CountMonster = 1;
			m_PersentMonster = 1;
			m_SkullPrice = 0;
		if ( checkPC() && !checkMono() )
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

bool DynamicZonePartyOfDungeon2::checkPC()
{
	Assert( m_pZone != NULL );

	// PC 수 체크
	uint size = m_pZone->getPCManager()->getSize();

	return size != 0;
}

bool DynamicZonePartyOfDungeon2::addMono()
{
			cout << " 실행되나.. " << endl;
	Assert( m_pZone != NULL );
	int i = g_pInstantDungeonMonsterManager->getMinInt(m_GroupID);
	int s = g_pInstantDungeonMonsterManager->getMaxInt(m_GroupID);
			cout << " 실행되나.. 2" << endl;
	while(i<=s){
			cout << " 실행되나.. 3" << endl;
		InstantDungeonMonster* pInstantDungeonMonster = g_pInstantDungeonMonsterManager->getInstantDungeonMonster(i);

			if(pInstantDungeonMonster->IsBoss() == 4){
			cout << "지정되나?"<<endl;
			setBossID(pInstantDungeonMonster->getID());
			}

			cout << " 실행되나.. 4" << endl;
		MonsterType_t 	MonsterType 	= pInstantDungeonMonster->getMonsterType();

		if(pInstantDungeonMonster != NULL){
			cout << " 실행되나.. 5" << endl;
		for(int s =0; s<pInstantDungeonMonster->getMonsterNumber(); s++){
			cout << " 실행되나.. 6" << endl;
		// 이성의 봉인을 생성한다.
		Monster* pMonster = new Monster( MonsterType );

			cout << " 실행되나..7" << endl;
		const MonsterInfo* pMonsterInfo = g_pMonsterInfoManager->getMonsterInfo(pMonster->getMonsterType());
		Assert( pMonster != NULL );

		ZoneCoord_t x, y;
		if(pInstantDungeonMonster->getX() > 0){x = pInstantDungeonMonster->getX();}
		if(pInstantDungeonMonster->getY() > 0){y = pInstantDungeonMonster->getY();}
		try
		{
		if(pInstantDungeonMonster->IsBoss() != 4){
			if (!m_pZone->getMonsterManager()->findPosition(pMonster->getMonsterType(), x, y))
			{
				Assert(false);
				return true;
			}
			m_pZone->addCreature( pMonster, x, y, 2 );
		}
			//m_pZone->getMonsterManager()->addEnemy(NULL, pMonster);
			if(pInstantDungeonMonster->IsBoss() == 1){
			m_MonoObjectID1 = pMonster->getObjectID();
			}
			if(pInstantDungeonMonster->IsBoss() == 2){
			m_MonoObjectID2 = pMonster->getObjectID();
			}
			if(pInstantDungeonMonster->IsBoss() == 3){
			m_MonoObjectID3 = pMonster->getObjectID();
			}
		}
		catch ( EmptyTileNotExistException& )
		{
			SAFE_DELETE( pMonster );
		}
			if(pMonsterInfo->getSkullType() != 0){
			ItemInfo* pItemInfo = g_pItemInfoManager->getItemInfo(Item::ITEM_CLASS_SKULL, pMonsterInfo->getSkullType());
			m_SkullPrice += pItemInfo->getPrice(); // 스컬 가격을 저장한다.
			cout << " 총 머리 값 : " << m_SkullPrice << endl;
			}

			}//for

			// 초기 퍼센트 및 몬스터 개체수 파악을 위한 부분.
			m_PersentMonster += pInstantDungeonMonster->getMonsterNumber();
			cout << " 총 마리 수 : " << m_PersentMonster << endl;
		}
		i++;
	}
	return true;
}

bool DynamicZonePartyOfDungeon2::addMono2()
{
			cout << " 실행되나.. " << endl;
	Assert( m_pZone != NULL );
			cout << " 실행되나.. 2" << endl;
		InstantDungeonMonster* pInstantDungeonMonster = g_pInstantDungeonMonsterManager->getInstantDungeonMonster(getBossID());
			cout << " 실행되나.. 4" << endl;
		MonsterType_t 	MonsterType 	= pInstantDungeonMonster->getMonsterType();
		if(pInstantDungeonMonster != NULL){
			cout << " 실행되나.. 5" << endl;
			cout << " 실행되나.. 6" << endl;
		// 이성의 봉인을 생성한다.
		Monster* pMonster = new Monster( MonsterType );

			cout << " 실행되나..7" << endl;
		const MonsterInfo* pMonsterInfo = g_pMonsterInfoManager->getMonsterInfo(pMonster->getMonsterType());
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
			m_pZone->addCreature( pMonster, x, y, 2 );
			m_MonoObjectID = pMonster->getObjectID();
		}
		catch ( EmptyTileNotExistException& )
		{
			SAFE_DELETE( pMonster );
		}
	}
	return true;
}

bool DynamicZonePartyOfDungeon2::clearMono()
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

bool DynamicZonePartyOfDungeon2::openGateToOut()
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

            //pPC->getGQuestManager()->clearDynamicZone(m_TemplateZoneID);
        }
    }

	return true;
}

bool DynamicZonePartyOfDungeon2::checkComplete()
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
void DynamicZonePartyOfDungeon2::CountMonster()
{

			MonsterManager* pMM = m_pZone->getMonsterManager();
			hash_map< ObjectID_t, Creature* > & monsters = pMM->getCreatures();
			hash_map< ObjectID_t, Creature* >::iterator itr = monsters.begin();

			for (; itr!=monsters.end(); itr++)
			{
				Creature* pCreature = itr->second;
				Monster* pMonster = dynamic_cast<Monster*>(pCreature);
				const MonsterInfo* pMonsterInfo = g_pMonsterInfoManager->getMonsterInfo(pMonster->getMonsterType());
				if (!pMonster->isFlag(Effect::EFFECT_CLASS_NO_DAMAGE))
				{
					pMonster->setHP( 0 );
				}

				if(pMonsterInfo->getSkullType() != 0){
				ItemInfo* pItemInfo = g_pItemInfoManager->getItemInfo(Item::ITEM_CLASS_SKULL, pMonsterInfo->getSkullType());
				m_SkullPrice -= pItemInfo->getPrice(); // 스컬 가격을 저장한다.
				cout << " 머리 값 감소: " << m_SkullPrice << endl;
				}

				m_CountMonster++;
			}

	cout << " 최종 결산 : " << m_CountMonster << "/" << m_PersentMonster << endl;
}
void DynamicZonePartyOfDungeon2::addItem()
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
			if(pCreature->isSlayer()){
			Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);
			pSlayer->setGold(pSlayer->getGold()+(m_CountMonster+m_PersentMonster/m_CountMonster*100) + getPercentValue(m_SkullPrice,(m_CountMonster/m_PersentMonster)*100));
			GCModifyInformation gcMI;
			gcMI.addLongData(MODIFY_GOLD, pSlayer->getGold());
			pCreature->getPlayer()->sendPacket(&gcMI);
			}else if(pCreature->isVampire()){
			Vampire* pSlayer = dynamic_cast<Vampire*>(pCreature);
			pSlayer->setGold(pSlayer->getGold()+(m_CountMonster+m_PersentMonster/m_CountMonster*100) + getPercentValue(m_SkullPrice,(m_CountMonster/m_PersentMonster)*100));
			GCModifyInformation gcMI;
			gcMI.addLongData(MODIFY_GOLD, pSlayer->getGold());
			pCreature->getPlayer()->sendPacket(&gcMI);
			}else if(pCreature->isOusters()){
			Ousters* pSlayer = dynamic_cast<Ousters*>(pCreature);
			pSlayer->setGold(pSlayer->getGold()+(m_CountMonster+m_PersentMonster/m_CountMonster*100) + getPercentValue(m_SkullPrice,(m_CountMonster/m_PersentMonster)*100));
			GCModifyInformation gcMI;
			gcMI.addLongData(MODIFY_GOLD, pSlayer->getGold());
			pCreature->getPlayer()->sendPacket(&gcMI);

			}

			
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
void DynamicZonePartyOfDungeon2::processEntering()
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

bool DynamicZonePartyOfDungeon2::checkMono()
{
	Assert( m_pZone != NULL );

	MonsterManager* pMonsterManager = m_pZone->getMonsterManager();
	Assert( pMonsterManager != NULL );

	Creature* pCreature = pMonsterManager->getCreature( m_MonoObjectID );
	return pCreature != NULL;
}

bool DynamicZonePartyOfDungeon2::checkMono2()
{
	Assert( m_pZone != NULL );

	MonsterManager* pMonsterManager = m_pZone->getMonsterManager();
	Assert( pMonsterManager != NULL );

	Creature* pCreature = pMonsterManager->getCreature( m_MonoObjectID1 );
	Creature* pCreature2 = pMonsterManager->getCreature( m_MonoObjectID2 );
	Creature* pCreature3 = pMonsterManager->getCreature( m_MonoObjectID3 );
	return pCreature != NULL && pCreature2 != NULL && pCreature3 != NULL;
}


void DynamicZonePartyOfDungeon2::killPC()
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

DEFINE_DYNAMIC_ZONE_FACTORY( DynamicZonePartyOfDungeon2, DYNAMIC_ZONE_PARTY_OF_DUNGEON2 )


