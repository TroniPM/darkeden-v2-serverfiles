/////////////////////////////////////////////////////////////////////////////
// DynamicZoneOustersMirrorOfAbyss.cpp
/////////////////////////////////////////////////////////////////////////////

#include "DynamicZoneHilanom.h"
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
#include "Tile.h"
#include "MonsterAI.h"
#include "Gpackets/GCCreateItem.h"
#include "Gpackets/GCSystemMessage.h"
#include "Gpackets/GCNoticeEvent.h"
#include "Gpackets/GCGlobalChat.h"
#include "Gpackets/GCAddEffectToTile.h"
#include "Gpackets/GCSay.h"

#include "ZoneGroupManager.h"
#include "StringPool.h"

#include <stdio.h>
#include <stdlib.h>

enum OUSTERS_MIRROR_OF_ABYSS
{
	WAIT_FOR_PC,
	ADD_BLOCK,
	ADD_MONO,
	WAIT_FOR_COMPLETE,
	CLEAR_MONO,
	WAIT_FOR_CLEAR,
	OUSTERS_MIRROR_OF_ABYSS_END,

	OUSTERS_MIRROR_OF_ABYSS_MAX
};

struct OFFERING_COORDINATE
{
	ZoneCoord_t X;
	ZoneCoord_t Y;
};

const OFFERING_COORDINATE OfferingCoordinate[3] =
{
	{ 35, 52 },
	{ 71, 117 },
	{ 87, 100 }
};

struct STAGE_MONSTER_REGEN
{
	MonsterType_t	MonsterType[4];
	int	MonsterNum[4];
	ZoneCoord_t X[4];
	ZoneCoord_t Y[4];
	int	Succes;
};

const STAGE_MONSTER_REGEN StageMonsterRegen[4] =
{
	{ {646,646,910,910},{1,1,0,0},{12, 37, 0, 0},{42,18, 0, 0}, {56} },
	{ {646,646,910,910},{1,1,0,0},{28, 56, 0, 0},{105,119, 0, 0},{57} },
	{ {646,646,910,910},{1,1,0,0},{115, 92, 0, 0},{94,107, 0, 0},{56} },
	{ {646,646,646,646},{1,1,1,1},{79, 74, 103, 104},{56,29, 33, 54},{57} }
};

struct STAGE_MONSTER_REGEN2
{
	MonsterType_t	MonsterType[4];
	int	MonsterNum[4];
	ZoneCoord_t X[4];
	ZoneCoord_t Y[4];
};

const STAGE_MONSTER_REGEN2 StageMonsterRegen2[4] =
{
	{ {387,387,387,387},{30,30,30,30},{14, 31, 19, 35},{14,21, 41, 25} },
	{ {387,407,387,407},{30,5,30,5},{18, 47, 0, 50},{105,119, 88, 91} },
	{ {387,387,387,407},{30,30,30,5},{115, 92, 0, 0},{94,107, 0, 0} },
	{ {387,387,387,407},{30,30,30,5},{79, 74, 103, 104},{56,29, 33, 54} }
};

struct STRING_MONSTER
{
	string MonsterSay;
};

const STRING_MONSTER StageMonsterSay[10] =
{
	{"어디서 굴러 들어온 뼈다귀야?"},
	{"내 도끼맛에 한번 죽어봐야 정신차리지?"},
	{"니놈들은 단 한방이면 죽일수 있지."},
	{"내 도끼의 피에 놀라지말라구!"},
	{"하하하하, 괜히 이곳에 온걸 후회하지말라구"},
	{"니놈들 따위는 죽어도 마땅해!"},
	{"이런 신성한 구역에 오다니 감히 놀랍군?"},
	{"땅에는 묻어 드리지."},
	{"죽??좋은 날씨구만!"},
	{"죽여는 드릴께~"}
};

DynamicZoneHilanom::DynamicZoneHilanom()
{
	m_Stage = 0;
}

DynamicZoneHilanom::~DynamicZoneHilanom()
{
}

void DynamicZoneHilanom::init()
{
	Assert( m_pZone != NULL );

	m_OMOAStatus = WAIT_FOR_PC;
	getCurrentTime( m_Deadline );
	m_Deadline.tv_sec += 60;
	getCurrentTime( m_EndTime );
	getCurrentTime( m_TimeMonsterMsg );
	m_EndTime.tv_sec += 600 * 20;
	m_TimeMonsterMsg.tv_sec += (10 * 3);
}

void DynamicZoneHilanom::heartbeat()
{
	switch ( m_OMOAStatus )
	{
	case WAIT_FOR_PC:
		if ( checkPC() )
		{
			m_Stage = 0;
			processEntering();
			m_OMOAStatus = ADD_BLOCK;
			cout << "-----------------------ADD_MONO" << endl;
		}
		break;

	case ADD_BLOCK:
		{
			// 블럭을 막아야 한다.
			for(int type=0; type <=2; type++){
			addBlock(type);
			}
			timecheck();
			m_OMOAStatus = ADD_MONO;
		}	
		break;

	case ADD_MONO:
		{
			addMonster(m_Stage);
			SubaddMonster(m_Stage);
			timecheck();
			m_OMOAStatus = WAIT_FOR_COMPLETE;
			cout << "-----------------------WAIT_FOR_COMPLETE" << endl;
		}
		break;
	case WAIT_FOR_COMPLETE:
		if(checkMonsterMsgComplete()){
			sayMonster();
			m_TimeMonsterMsg.tv_sec += (10 * 3);
		}
		if(m_Stage <= 3 && checkMonster() ){
			// 보상을하고 스테이지를 넘겨야한다.
			TreasureCheck(StageMonsterRegen[m_Stage].Succes);
			if(m_Stage < 3)clearBlock(m_Stage);
			m_Stage++;

			GCNoticeEvent gcNoticeEvent;
			gcNoticeEvent.setCode( NOTICE_EVENT_CONTINUAL_GROUND_ATTACK );
			gcNoticeEvent.setParameter( 3 );	// 초

			m_pZone->broadcastPacket( &gcNoticeEvent );

			GCSystemMessage gcSystemMessage;
			gcSystemMessage.setType(SYSTEM_MESSAGE_NORMAL);
			gcSystemMessage.setMessage( " 다음 스테이지에서 몬스터가 기다리고 있습니다. "  );
			m_pZone->broadcastPacket( &gcSystemMessage );

			m_OMOAStatus = ADD_MONO;

		}
		if(m_Stage >= 4 && checkMonster() ){
			TreasureCheck(StageMonsterRegen[m_Stage].Succes);
			GCSystemMessage gcSystemMessage;
			gcSystemMessage.setType(SYSTEM_MESSAGE_NORMAL);
			gcSystemMessage.setMessage( " 축하합니다. 힐라놈 성지를 정복하셨습니다. "  );
			m_pZone->broadcastPacket( &gcSystemMessage );

			openGateToOut();
			m_OMOAStatus = CLEAR_MONO;
		}
		if ( checkComplete() )
		{
			// 10분이라는 시간이 주어지는데 클리어를 못했을 경우 내보내버린다.
			openGateToOut();
			m_OMOAStatus = CLEAR_MONO;
			cout << "-----------------------CLEAR_MONO" << endl;
		}

		break;

	case CLEAR_MONO:
		{
			clearMono();
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

bool DynamicZoneHilanom::checkPC()
{
	Assert( m_pZone != NULL );

	// PC 수 체크
	uint size = m_pZone->getPCManager()->getSize();

	return size != 0;
}

bool DynamicZoneHilanom::addMono()
{
	InstantDungeonMonster* pInstantDungeonMonster = g_pInstantDungeonMonsterManager->getInstantDungeonMonster(m_Indun);
	if(pInstantDungeonMonster == NULL) return false;
	Assert( m_pZone != NULL );

	// 이성의 봉인을 생성한다.
	Monster* pMonster = new Monster( pInstantDungeonMonster->getMonsterType() );
	Assert( pMonster != NULL );

	try
	{
		m_pZone->addCreature( pMonster, 16, 27, 2 );

		m_MonoObjectID = pMonster->getObjectID();
	}
	catch ( EmptyTileNotExistException& )
	{
		SAFE_DELETE( pMonster );
	}

	return true;
}
bool DynamicZoneHilanom::checkMonsterMsgComplete()
{
	Timeval current;
	getCurrentTime( current );
	if ( current > m_TimeMonsterMsg )
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool DynamicZoneHilanom::sayMonster()
{
	Assert( m_pZone != NULL );

	MonsterManager* pMonsterManager = m_pZone->getMonsterManager();
	Assert( pMonsterManager != NULL );

	hash_map< ObjectID_t, Creature* > & monsters = pMonsterManager->getCreatures();
	hash_map< ObjectID_t, Creature* >::iterator itr = monsters.begin();

	for (; itr!=monsters.end(); itr++)
	{
		Creature* pCreature = itr->second;
		if(pCreature != NULL && pCreature->isMonster()){
			int RadomSay = rand()%9;
			if(rand()%100 < 30){
			string MonsterSay = StageMonsterSay[RadomSay].MonsterSay;
			GCSay gcSay;
			gcSay.setObjectID( pCreature->getObjectID() );
			gcSay.setMessage( MonsterSay );
			gcSay.setColor( 0x00ffffff );
			m_pZone->broadcastPacket( pCreature->getX(), pCreature->getY(), &gcSay );
			}
		}
	}

	return true;

}
bool DynamicZoneHilanom::checkMonster()
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

	if(m_CountMonster == 0){
	return true;
	}else{
	return false;
	}

}
void DynamicZoneHilanom::addMonster(int Type)
{
	Assert( m_pZone != NULL );

		for(int s=0; s <4; s++){
			for(int v=0; v <StageMonsterRegen[Type].MonsterNum[s]; v++){			

				Monster* pMonster = new Monster( StageMonsterRegen[Type].MonsterType[s] );
				Assert( pMonster != NULL );

				try
				{	
					m_pZone->addCreature( pMonster, StageMonsterRegen[Type].X[s], StageMonsterRegen[Type].Y[s], 2 );

				}
				catch ( EmptyTileNotExistException& )
				{	
					SAFE_DELETE( pMonster );
				}
			}
		}
}
void DynamicZoneHilanom::SubaddMonster(int Type)
{
	Assert( m_pZone != NULL );

		for(int s=0; s <4; s++){
			for(int v=0; v <StageMonsterRegen2[Type].MonsterNum[s]; v++){	
	
				ZoneCoord_t X = StageMonsterRegen[Type].X[0+Random(0,1)];
				ZoneCoord_t Y = StageMonsterRegen[Type].Y[0+Random(0,1)];

				if(Type == 3){
				X = StageMonsterRegen[Type].X[s];	
				Y = StageMonsterRegen[Type].Y[s];
				}

				Monster* pMonster = new Monster( StageMonsterRegen2[Type].MonsterType[s] );
				Assert( pMonster != NULL );

				try
				{	
					m_pZone->addCreature( pMonster, X+rand()%5, Y+rand()%5, 2 );

				}
				catch ( EmptyTileNotExistException& )
				{	
					SAFE_DELETE( pMonster );
				}
			}
		}
}
bool DynamicZoneHilanom::clearMono()
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

bool DynamicZoneHilanom::openGateToOut()
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
void DynamicZoneHilanom::timecheck()
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

void DynamicZoneHilanom::addBlock(int blockType)
{
	for(int i=0; i <= 8; i++){
		for(int s=0; s<8; s++){
			m_pZone->getTile(OfferingCoordinate[blockType].X, OfferingCoordinate[blockType].Y).setBlocked(Creature::MOVE_MODE_WALKING);
			m_pZone->getTile(OfferingCoordinate[blockType].X+i, OfferingCoordinate[blockType].Y-s).setBlocked(Creature::MOVE_MODE_WALKING);
		}
	}
}
void DynamicZoneHilanom::clearBlock(int blockType)
{
	for(int i=0; i <= 8; i++){
		for(int s=0; s<8; s++){
			m_pZone->getTile(OfferingCoordinate[blockType].X, OfferingCoordinate[blockType].Y).clearBlocked(Creature::MOVE_MODE_WALKING);
			m_pZone->getTile(OfferingCoordinate[blockType].X+i, OfferingCoordinate[blockType].Y-s).clearBlocked(Creature::MOVE_MODE_WALKING);
		}
	}

}

void DynamicZoneHilanom::TreasureCheck(int Type)
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
			Item* pItem1 = NULL;

			Creature::CreatureClass ownerCreatureClass;
			ownerCreatureClass = pCreature->getCreatureClass();

			MonsterDropSetup* pMonsterItemDrop = g_pMonsterDropSetupManager->getMonsterDropSetup(Type);
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

				// ItemTrace 에 Log 를 남긴??
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

bool DynamicZoneHilanom::checkComplete()
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

void DynamicZoneHilanom::processEntering()
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

void DynamicZoneHilanom::killPC()
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

DEFINE_DYNAMIC_ZONE_FACTORY( DynamicZoneHilanom, DYNAMIC_ZONE_HILANOM )


