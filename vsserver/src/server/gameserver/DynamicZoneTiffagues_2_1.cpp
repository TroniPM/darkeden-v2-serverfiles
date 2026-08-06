/////////////////////////////////////////////////////////////////////////////
// DynamicZoneOustersMirrorOfAbyss.cpp
/////////////////////////////////////////////////////////////////////////////

#include "DynamicZoneTiffagues_2_1.h"
#include "DynamicZoneTiffagues_2_2.h"
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
#include "EffectCastingTrap.h"

#include "EffectTiffaugesRealWorldLeftUP.h"
#include "ZoneGroupManager.h"
#include "StringPool.h"
#include <stdio.h>
#include <stdlib.h>

enum OUSTERS_MIRROR_OF_ABYSS
{
	WAIT_FOR_PC,
	SAY_TIFFAUGE,
	ADD_BLOCK,
	ADD_EFFECT,
	ADD_STAGE,
	STAGE_ING,
	STAGE_TIME_MSG,
	ADD_MONO,
	WAIT_FOR_COMPLETE,
	CLEAR_MONO,
	WAIT_FOR_CLEAR,
	OUSTERS_MIRROR_OF_ABYSS_END,

	OUSTERS_MIRROR_OF_ABYSS_MAX
};
struct TRAP_COORDINATE
{
	ZoneCoord_t X;
	ZoneCoord_t Y;
	int Langth;
	Effect::EffectClass EffectClassType;
	bool EffectTrue;
};

const TRAP_COORDINATE TrapCoordinate[6] =
{
	{ 123, 103, 25, Effect::EFFECT_CLASS_ICICLE_DROP, false },
	{ 136, 102, 43, Effect::EFFECT_CLASS_ICICLE_DROP, false },
	{ 71, 34, 20, Effect::EFFECT_CLASS_ICICLE_AUGER_LARGE, true },
	{ 60, 43, 20, Effect::EFFECT_CLASS_ICICLE_AUGER_LARGE, true },
	{ 89, 137, 30, Effect::EFFECT_CLASS_ICICLE_DROP,false },
	{ 99, 119, 20, Effect::EFFECT_CLASS_ICICLE_AUGER_LARGE,true}
};

struct OFFERING_COORDINATE
{
	ZoneCoord_t X;
	ZoneCoord_t Y;
};

const OFFERING_COORDINATE OfferingCoordinate[6] =
{
	{ 78, 40 },
	{ 22, 48 },
	{ 34, 84 },
	{ 58, 116 },
	{ 86, 104 },
	{ 102, 128}
};

struct STAGE_MONSTER_REGEN
{
	MonsterType_t	MonsterType[4];
	int	MonsterNum[4];
	ZoneCoord_t X[2];
	ZoneCoord_t Y[2];
	uint MonsterAI[4];
};

struct STRING_MONSTER
{
	string MonsterSay;
};

const STRING_MONSTER StageMonsterSay[10] =
{
	{"어디서 피 비린내가 나는군?!"},
	{"어디서 굴러 들어 온 놈들이지"},
	{"동료들을 불러야겠군!"},
	{"도망가지 못하게 죽이겠어!!"},
	{"죽여야돼! 죽여야돼!!!"},
	{"피가 모잘라 피가!!"},
	{"내 구역에 침범하면 다 죽여버리겠어!"},
	{"내 잔에는 가득찰 놈이군!"},
	{"하하하하하!!!"},
	{"우리를 무시한놈은 다 죽이겠어!"}
};

const STAGE_MONSTER_REGEN StageMonsterRegen[4] =
{
	{ {909,910,911,912},{5,7,3,1},{88, 97},{37,47},{188,189,190,186} },
	{ {909,910,911,916},{5,7,3,1},{15, 24},{27,37},{188,189,190,184} },
	{ {909,910,911,913},{5,7,3,1},{33, 48},{88,112},{188,189,190,187} },
	{ {909,910,911,914},{5,7,3,1},{63, 76},{73,87},{188,189,190,185} },
};

DynamicZoneTiffagues_2_1::DynamicZoneTiffagues_2_1()
{
	m_MonoObjectID = 0;
	m_Stage = 0;
	m_StageMessage = 0;
}

DynamicZoneTiffagues_2_1::~DynamicZoneTiffagues_2_1()
{
}

void DynamicZoneTiffagues_2_1::init()
{
	Assert( m_pZone != NULL );

	m_OMOAStatus = WAIT_FOR_PC;
	getCurrentTime( m_Deadline );
	m_Deadline.tv_sec += 60;
	getCurrentTime( m_EndTime );
	getCurrentTime( m_TimeMsg );
	getCurrentTime( m_TimeMonsterMsg );
	m_EndTime.tv_sec += (10 * 6)*30;
	m_TimeMsg.tv_sec += (10 * 6)*5;
	m_TimeMonsterMsg.tv_sec += (10 * 3);
}

void DynamicZoneTiffagues_2_1::heartbeat()
{
	switch ( m_OMOAStatus )
	{
	case WAIT_FOR_PC:
		if ( checkPC() )
		{
			m_Stage = 0;
			m_StageMessage = 0;
			clearMono();
			processEntering();
			m_OMOAStatus = SAY_TIFFAUGE;
			cout << "-----------------------ADD_MONO" << endl;
		}
		break;
	case SAY_TIFFAUGE:
		{
			// 처음에 들어올때 말을 한마디 한다.
			addMsg(m_StageMessage);
			m_OMOAStatus = ADD_BLOCK;
		}
		break;
	case ADD_BLOCK:
		{
			// 블럭을 막아야 한다.
			for(int type=0; type <=5; type++){
			addBlock(type);
			}
			timecheck();
			m_OMOAStatus = ADD_EFFECT;
		}	
		break;
	case ADD_EFFECT:
	{
		//AddEffect(0);
		//AddEffect(1);
		m_OMOAStatus = ADD_STAGE;
	}
	break;
	case ADD_STAGE:
		{
			addMonster(m_Stage);
			timecheck();
			m_OMOAStatus = STAGE_ING;
		}
		break;
	case STAGE_ING:
		{
		// 5분이 지났다, 전체 채팅말로 약올려야 한다.
		if(checkMsgComplete()){
			m_StageMessage++;
			m_TimeMsg.tv_sec += (10 * 6)*5;
			m_OMOAStatus = STAGE_TIME_MSG;
		}

		// 30초 간격으로 몬스터가 말을 해야한다.
		if(checkMonsterMsgComplete()){
			sayMonster();
			m_TimeMonsterMsg.tv_sec += (10 * 3);
		}


		// 스테이지 클리어
		if( checkMonster() ){
			if(m_Stage == 0){
			clearBlock(m_Stage);
			clearBlock(m_Stage+1);
			//AddEffect(2);
			//AddEffect(3);
			}
			if(m_Stage == 1){
			clearBlock(m_Stage+1);
			}
			if(m_Stage == 2){
			//AddEffect(4);
			//AddEffect(5);
			clearBlock(m_Stage+1);
			clearBlock(m_Stage+2);
			}

		if(m_Stage == 3){
			openGateToStage();
			m_OMOAStatus = WAIT_FOR_CLEAR;
		}

		// 아이템을 지급한다.
		TreasureCheck2();

		GCNoticeEvent gcNoticeEvent;
		gcNoticeEvent.setCode( NOTICE_EVENT_CONTINUAL_GROUND_ATTACK );
		gcNoticeEvent.setParameter( 3 );	// 초

		m_pZone->broadcastPacket( &gcNoticeEvent );

		GCSystemMessage gcSystemMessage;
		gcSystemMessage.setType(SYSTEM_MESSAGE_NORMAL);
		gcSystemMessage.setMessage( " 새로운 게이트 문이 열렸습니다. "  );
		m_pZone->broadcastPacket( &gcSystemMessage );
		if(m_Stage != 3){
		m_Stage++;
		m_OMOAStatus = ADD_STAGE;
		}
		}

		if ( checkComplete() )
		{
			// 10분이라는 시간이 주어지는데 클리어를 못했을 경우 내보내버린다.
			killPC();
			m_OMOAStatus = CLEAR_MONO;
			cout << "-----------------------CLEAR_MONO" << endl;
		}

		}
	break;
	case STAGE_TIME_MSG:
		{
			addMsg(m_StageMessage);
			m_OMOAStatus = STAGE_ING;
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

	/*	if ( !checkMono() )
		{
			TreasureCheck();
			// 보스형을 잡았다. 그래도 내보내버린다.
			openGateToOut();
			m_OMOAStatus = CLEAR_MONO;
		}*/

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

bool DynamicZoneTiffagues_2_1::checkPC()
{
	Assert( m_pZone != NULL );

	// PC 수 체크
	uint size = m_pZone->getPCManager()->getSize();

	return size != 0;
}
bool DynamicZoneTiffagues_2_1::checkMonster()
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
bool DynamicZoneTiffagues_2_1::addMono()
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
void DynamicZoneTiffagues_2_1::addMonster(int Type)
{
	Assert( m_pZone != NULL );

		for(int s=0; s <4; s++){
			for(int v=0; v <StageMonsterRegen[Type].MonsterNum[s]; v++){

				ZoneCoord_t cx = Random(StageMonsterRegen[Type].X[0],StageMonsterRegen[Type].X[1]);
				ZoneCoord_t cy = Random(StageMonsterRegen[Type].Y[0],StageMonsterRegen[Type].Y[1]);				

				Monster* pMonster = new Monster( StageMonsterRegen[Type].MonsterType[s] );
				Assert( pMonster != NULL );
				MonsterAI* m_pBrain = new MonsterAI(pMonster, StageMonsterRegen[Type].MonsterAI[s]);
				pMonster->setBrain(m_pBrain);
				try
				{	
					m_pZone->addCreature( pMonster, cx, cy, 2 );

				}
				catch ( EmptyTileNotExistException& )
				{	
					SAFE_DELETE( pMonster );
				}
			}
		}
}
void DynamicZoneTiffagues_2_1::addMsg(int blockType)
{
	StringStream msg;
	msg << "티포쥬 성" << " " << g_pStringPool->getString( STRID_TIFFAGUES_1+blockType );

	GCGlobalChat gcGlobalChat;
	gcGlobalChat.setMessage(msg.toString());
	gcGlobalChat.setRace(2);
	gcGlobalChat.setColor( 0x1f78dc );
	m_pZone->broadcastPacket( &gcGlobalChat);
}

bool DynamicZoneTiffagues_2_1::clearMono()
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
void DynamicZoneTiffagues_2_1::addBlock(int blockType)
{
	for(int i=0; i <= 3; i++){
		for(int s=0; s<3; s++){
			m_pZone->getTile(OfferingCoordinate[blockType].X+i, OfferingCoordinate[blockType].Y-s).setBlocked(Creature::MOVE_MODE_WALKING);
		}
	}

	Tile& tile = m_pZone->getTile(OfferingCoordinate[blockType].X,OfferingCoordinate[blockType].Y);
	EffectTiffaugesRealWorldLeftUP* pEffect = new EffectTiffaugesRealWorldLeftUP(m_pZone, OfferingCoordinate[blockType].X, OfferingCoordinate[blockType].Y);
	pEffect->setDeadline(99999999);

	m_pZone->registerObject(pEffect);
	m_pZone->addEffect(pEffect);
	tile.addEffect(pEffect);
}
void DynamicZoneTiffagues_2_1::clearBlock(int blockType)
{
	for(int i=0; i <= 3; i++){
		for(int s=0; s<3; s++){
			m_pZone->getTile(OfferingCoordinate[blockType].X+i, OfferingCoordinate[blockType].Y-s).clearBlocked(Creature::MOVE_MODE_WALKING);
		}
	}

	Tile& tile = m_pZone->getTile(OfferingCoordinate[blockType].X,OfferingCoordinate[blockType].Y);

	Effect* pDeleteEffect=NULL;
	pDeleteEffect = tile.getEffect(Effect::EFFECT_CLASS_TIFFAUGES_REALWORLD_LEFT_UP);
	pDeleteEffect->setDeadline(0);
	ObjectID_t effectID = pDeleteEffect->getObjectID();

	m_pZone->deleteEffect(effectID);
	tile.deleteEffect(effectID);
}
void DynamicZoneTiffagues_2_1::AddEffect(int blockType)
{
		EffectCastingIcicleTrap* pEffect = new EffectCastingIcicleTrap( TrapCoordinate[blockType].EffectClassType, m_pZone);

		pEffect->setStartXY( TrapCoordinate[blockType].X, TrapCoordinate[blockType].Y);
		pEffect->setLength( TrapCoordinate[blockType].Langth);
		pEffect->setTick( 10 );
		pEffect->setUnit( 10 );
		if(TrapCoordinate[blockType].EffectTrue){
		pEffect->setLarge( true );
		}
		pEffect->setDir( 7 );
		pEffect->setNextTime(0);
		pEffect->setDeadline(4800);
		m_pZone->addEffect_LOCKING( pEffect );
}
void DynamicZoneTiffagues_2_1::TreasureCheck()
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

void DynamicZoneTiffagues_2_1::TreasureCheck2()
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
			PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);
			Inventory* pInventory = pPC->getInventory();
			bool ItemType = Random(0,1);

			list<OptionType_t> nullList;
			Item* pItem = g_pItemFactoryManager->createItem(Item::ITEM_CLASS_EVENT_STAR, ItemType ? 42:45, nullList);
 			pItem->setNum(rand()%10);
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
		else
		{
			throw Error("PCManager에 PC아닌게 들어?簾?-_-");
		}
	}

}

bool DynamicZoneTiffagues_2_1::sayMonster()
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

bool DynamicZoneTiffagues_2_1::openGateToOut()
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

bool DynamicZoneTiffagues_2_1::openGateToStage()
{
	Assert( m_pZone != NULL );

	int targetDynamicZoneType = g_pDynamicZoneInfoManager->getDynamicZoneTypeByZoneID( 1804 );

	DynamicZoneGroup* pDynamicZoneGroup = g_pDynamicZoneManager->getDynamicZoneGroup( targetDynamicZoneType );
	Assert( pDynamicZoneGroup != NULL );

	DynamicZone* pDynamicZone = pDynamicZoneGroup->getAvailableDynamicZone();
	Assert( pDynamicZone != NULL );


	DynamicZoneTiffagues_2_2* pAlterOfBlood = dynamic_cast<DynamicZoneTiffagues_2_2*>(pDynamicZone);
	Assert( pAlterOfBlood != NULL );
	pAlterOfBlood->setZoneID(m_ZoneID);
	pAlterOfBlood->setZoneX(m_ZoneX);
	pAlterOfBlood->setZoneY(m_ZoneY);
	pAlterOfBlood->setInstantID(m_Indun);

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

	m_pZone->getPCManager()->transportAllCreatures( pDynamicZone->getZoneID(), 119, 138);
        }
    }

	return true;
}

void DynamicZoneTiffagues_2_1::timecheck()
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

bool DynamicZoneTiffagues_2_1::checkComplete()
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

bool DynamicZoneTiffagues_2_1::checkMsgComplete()
{
	Timeval current;
	getCurrentTime( current );
	if ( current > m_TimeMsg )
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool DynamicZoneTiffagues_2_1::checkMonsterMsgComplete()
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

void DynamicZoneTiffagues_2_1::processEntering()
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

bool DynamicZoneTiffagues_2_1::checkMono()
{
	Assert( m_pZone != NULL );

	MonsterManager* pMonsterManager = m_pZone->getMonsterManager();
	Assert( pMonsterManager != NULL );

	Creature* pCreature = pMonsterManager->getCreature( m_MonoObjectID );
	return pCreature != NULL;
}

void DynamicZoneTiffagues_2_1::killPC()
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

DEFINE_DYNAMIC_ZONE_FACTORY( DynamicZoneTiffagues_2_1, DYNAMIC_ZONE_TIFFAGUES_2_1 )