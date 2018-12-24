/////////////////////////////////////////////////////////////////////////////
// DynamicZoneOustersMirrorOfAbyss.cpp
/////////////////////////////////////////////////////////////////////////////

#include "DynamicZoneTimeOfDungeon.h"
#include "DynamicZoneMiniGame2.h"
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
#include "PacketUtil.h"

#include "Gpackets/GCSystemMessage.h"
#include "Gpackets/GCNoticeEvent.h"
#include "Gpackets/GCCreateItem.h"
#include "Gpackets/GCModifyInformation.h"
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

DynamicZoneTimeOfDungeon::DynamicZoneTimeOfDungeon()
{
}

DynamicZoneTimeOfDungeon::~DynamicZoneTimeOfDungeon()
{
}

void DynamicZoneTimeOfDungeon::init()
{
	Assert( m_pZone != NULL );

	m_addTimesec = 0;
	m_States = 0;
	m_States_trasure = 0;
	m_OMOAStatus = WAIT_FOR_PC;
	getCurrentTime( m_Deadline );
	m_Deadline.tv_sec += 30;
}

void DynamicZoneTimeOfDungeon::heartbeat()
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

		if( !checkMono() ){
			// 몬스터가 총 60마리를 넘었을 경우 자동으로 종료되어진다.
			m_OMOAStatus = CLEAR_MONO;
		}
		else if ( addMono() )
		{
			// 플레이어들에게 타이머가 동작했다고 알린다.
			timecheck();
			// 10단계를 넘었으므로 스킬북 상자를 줘야 한다.
			if(m_States_trasure == 10){
			m_States_trasure = 0;
			TreasureCheck();
			openGateToMiniGame();
			}
			// 몬스터가 아직 150마리를 넘지 않은 관계로 소환한다.
			m_OMOAStatus = WAIT_FOR_COMPLETE;
			cout << "-----------------------WAIT_FOR_COMPLETE" << endl;
		}
		break;

	case WAIT_FOR_COMPLETE:
		if ( checkComplete() )
		{
			// 미니게임으로 보내버린다.
			// 시간이 오버되었다.
			m_OMOAStatus = ADD_MONO;
			// 시간 재 추가
			m_Deadline.tv_sec += 30;
			// 보상을 위해 시간을 누적해논다.
			m_addTimesec += 30;
			// 몬스터의 난이도가 올라간다.
			m_States += 1;
			m_States_trasure += 1;
			cout << "-----------------------REGEN_ADD_MONO" << endl;
		}
		break;

	case CLEAR_MONO:
		if ( clearMono() )
		{
			// 맵안에 있는 모든 몬스터를 죽였으므로 내보낸다.
			openGateToOut();
			m_OMOAStatus = WAIT_FOR_CLEAR;
			cout << "-----------------------WAIT_FOR_CLEAR" << endl;
		}
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

bool DynamicZoneTimeOfDungeon::checkPC()
{
	Assert( m_pZone != NULL );

	// PC 수 체크
	uint size = m_pZone->getPCManager()->getSize();

	return size != 0;
}

bool DynamicZoneTimeOfDungeon::addMono()
{
	Assert( m_pZone != NULL );

	InstantDungeonMonster* pInstantDungeonMonster = g_pInstantDungeonMonsterManager->getInstantDungeonMonster(m_Indun);
	if(pInstantDungeonMonster == NULL) return false;

	for ( int i = 0; i < pInstantDungeonMonster->getMonsterNumber(); ++i )
	{
		// 이성의 봉인을 생성한다.
		Monster* pMonster = new Monster( pInstantDungeonMonster->getMonsterType() );
		Assert( pMonster != NULL );

		ZoneCoord_t x, y;
		
		if(m_States > 0){
			pMonster->setSTR(pMonster->getSTR()+getPercentValue(pMonster->getSTR(),(m_States*10)));	
			pMonster->setDEX(pMonster->getDEX()+getPercentValue(pMonster->getDEX(),(m_States*10)));	
			pMonster->setINT(pMonster->getINT()+getPercentValue(pMonster->getINT(),(m_States*10)));
			pMonster->setExp(pMonster->getExp()+getPercentValue(pMonster->getExp(),(m_States*1)));	
			pMonster->setHP(pMonster->getHP(ATTR_MAX)+getPercentValue(pMonster->getHP(ATTR_MAX),(m_States*10)), ATTR_MAX);
			pMonster->setHP(pMonster->getHP(ATTR_MAX), ATTR_CURRENT);
			pMonster->setToHit(pMonster->getToHit()+getPercentValue(pMonster->getToHit(),(m_States*10)));
			pMonster->setProtection(pMonster->getProtection()+getPercentValue(pMonster->getProtection(),(m_States*10)));	
			pMonster->setDefense(pMonster->getDefense()+getPercentValue(pMonster->getDefense(),(m_States*10)));
		}

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
		char msg[20];
		sprintf( msg, "현재 난이도 : %d단계", m_States);

		GCSystemMessage gcmsg;
		gcmsg.setMessage( msg );
		m_pZone->broadcastPacket( &gcmsg );

	return true;
}

bool DynamicZoneTimeOfDungeon::clearMono()
{

	Assert( m_pZone != NULL );

	MonsterManager* pMonsterManager = m_pZone->getMonsterManager();
	Assert( pMonsterManager != NULL );

	hash_map< ObjectID_t, Creature* > & monsters = pMonsterManager->getCreatures();
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

bool DynamicZoneTimeOfDungeon::openGateToOut()
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

bool DynamicZoneTimeOfDungeon::openGateToMiniGame()
{
	Assert( m_pZone != NULL );

	int targetDynamicZoneType = g_pDynamicZoneInfoManager->getDynamicZoneTypeByZoneID( 9010 );
	DynamicZoneGroup* pDynamicZoneGroup = g_pDynamicZoneManager->getDynamicZoneGroup( targetDynamicZoneType );
	Assert( pDynamicZoneGroup != NULL );

	DynamicZone* pDynamicZone = pDynamicZoneGroup->getAvailableDynamicZone();
	Assert( pDynamicZone != NULL );

	DynamicZoneMiniGame2* pAlterOfBlood = dynamic_cast<DynamicZoneMiniGame2*>(pDynamicZone);
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

	m_pZone->getPCManager()->transportAllCreatures( pDynamicZone->getZoneID(), 15, 15 );
	cout << "---------------------------------Clear Time Of Dungeon" << endl;
        }
    }

	return true;
}

void DynamicZoneTimeOfDungeon::TreasureCheck()
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
				pStmt->executeQuery( "INSERT INTO EventSimyunTime (OwnerID, GameTower, GameTime, DateTime, DungeonType) VALUES('%s', %d, %d, now(), 1)",
							pCreature->getName().c_str(), (int)m_States, (int)m_addTimesec );
			SAFE_DELETE(pStmt);
			}
			END_DB(pStmt)

			Item* pItem1 = NULL;

			Creature::CreatureClass ownerCreatureClass;
			ownerCreatureClass = pCreature->getCreatureClass();

			MonsterDropSetup* pMonsterItemDrop = g_pMonsterDropSetupManager->getMonsterDropSetup(39);
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

void DynamicZoneTimeOfDungeon::timecheck()
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

bool DynamicZoneTimeOfDungeon::checkComplete()
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

void DynamicZoneTimeOfDungeon::processEntering()
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

bool DynamicZoneTimeOfDungeon::checkMono()
{
	Assert( m_pZone != NULL );

	int m_CountMonster = 0;

	MonsterManager* pMonsterManager = m_pZone->getMonsterManager();
	Assert( pMonsterManager != NULL );

	hash_map< ObjectID_t, Creature* > & monsters = pMonsterManager->getCreatures();
	hash_map< ObjectID_t, Creature* >::iterator itr = monsters.begin();

	for (; itr!=monsters.end(); itr++)
	{
		Creature* pCreature = itr->second;
				// 몬스터 일경우 몬스터 카운터 1 증가
		if(pCreature != NULL && pCreature->isMonster()){
		m_CountMonster++;
		}
	}

	if(m_CountMonster >= 150){
	return false;
	}else{
	return true;
	}

}

void DynamicZoneTimeOfDungeon::killPC()
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

DEFINE_DYNAMIC_ZONE_FACTORY( DynamicZoneTimeOfDungeon, DYNAMIC_ZONE_TIME_OF_DUNGEON )


