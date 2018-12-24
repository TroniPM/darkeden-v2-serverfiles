/////////////////////////////////////////////////////////////////////////////
// DynamicZoneOustersMirrorOfAbyss.cpp
/////////////////////////////////////////////////////////////////////////////

#include "DynamicZoneMenegroth5.h"
#include "DynamicZoneInfo.h"
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
#include "EffectCauseCriticalWounds.h"
#include "Player.h"
#include "Timeval.h"
#include "InstantDungeonMonster.h"
#include "DynamicZoneMenegroth6.h"
#include "Gpackets/GCCreateItem.h"
#include "Gpackets/GCSystemMessage.h"
#include "Gpackets/GCNoticeEvent.h"
#include "Item.h"
#include "ItemUtil.h"
#include "ItemInfo.h"
#include "ItemInfoManager.h"
#include "VariableManager.h"
#include "MonsterDropSetup.h"
#include "MonsterItemDrop.h"
#include "MonsterItemDropOption.h"
#include "ItemGradeManager.h"
#include "ItemFactoryManager.h"
#include "PacketUtil.h"

#include <stdio.h>
#include <stdlib.h>

enum OUSTERS_MIRROR_OF_ABYSS
{
	WAIT_FOR_PC,
	ADD_MONO,
	WAIT_FOR_COMPLETE,
	ADD_BOSS,
	WAIT_FOR_BOSS_COMPLETE,
	CLEAR_MONO,
	WAIT_FOR_CLEAR,
	OUSTERS_MIRROR_OF_ABYSS_END,

	OUSTERS_MIRROR_OF_ABYSS_MAX
};

struct MONSTER_TEMPLATE
{
	MonsterType_t	MonsterType;
	int	MonsterNum;
};

const MONSTER_TEMPLATE MonsterTemplate[2] =
{
	{ 902, 40 },
	{ 904, 1 }
};
const MONSTER_TEMPLATE BossTemplate[2] =
{
	{ 902, 10 },
	{ 905, 2 }
};

struct OFFERING_COORDINATE
{
	ZoneCoord_t X;
	ZoneCoord_t Y;
};

const OFFERING_COORDINATE OfferingCoordinate[1] =
{
	{ 63, 63 }
};

DynamicZoneMenegroth5::DynamicZoneMenegroth5()
{
	m_MonoObjectID = 0;
	m_CabracamHP = 0;
}

DynamicZoneMenegroth5::~DynamicZoneMenegroth5()
{
}

void DynamicZoneMenegroth5::init()
{
	Assert( m_pZone != NULL );

	m_OMOAStatus = WAIT_FOR_PC;
	getCurrentTime( m_Deadline );
	m_Deadline.tv_sec += 60;
	getCurrentTime( m_EndTime );
	m_EndTime.tv_sec += (10 * 60)*3;
}

void DynamicZoneMenegroth5::heartbeat()
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
		if ( addMonster() )
		{
			m_CabracamHP = 0;
			// ���͸� ���� ��������.
			timecheck();
			m_OMOAStatus = WAIT_FOR_COMPLETE;
			cout << "-----------------------WAIT_FOR_COMPLETE" << endl;
		}
		break;

	case WAIT_FOR_COMPLETE:
		// 30���̶�� �ð��� �־����µ� Ŭ��� ������ ��� ������������.
		if ( checkComplete() )
		{
			openGateToOut();
			m_OMOAStatus = CLEAR_MONO;
			cout << "-----------------------CLEAR_MONO" << endl;
		}

		// ���͸� �� �������, ī���į�� ��ȯ����� �Ѵ�.
		if ( checkMonster() )
		{
			m_OMOAStatus = ADD_BOSS;
			cout << "-----------------------ADD_BOSS" << endl;
		}

		break;

	case ADD_BOSS:
		if ( addMono() )
		{
			// ������ �����Ŵ�. �̶� �ð�üũ �ȵȻ���� �߻��Ҽ��� ������ �־�д�.
			// ���� ������ 10���� �߰����ش�.
			m_EndTime.tv_sec += 10 * 60;
			timecheck();
			m_OMOAStatus = WAIT_FOR_BOSS_COMPLETE;
			cout << "-----------------------WAIT_FOR_COMPLETE" << endl;
		}
		break;

	case WAIT_FOR_BOSS_COMPLETE:		
		// ī���į�� ü���� 30% ���Ϸ� �������� ��� 
		// ���Ϳ� �Բ� �ڽ��� �н��� ��ȯ�Ѵ�.	
		if(checkMono() && checkMonoHPcount() && m_CabracamHP == 0){
		addMonster_boss_regen();
		m_CabracamHP = 1;
		}

		if(checkMono() && checkbossmonster() && m_CabracamHP == 1){
		checkMonoEffect();
		}

		// 10���̶�� �ð��� �־����µ� Ŭ��� ������ ��� ������������.
		if ( checkComplete() )
		{
			openGateToOut();
			m_OMOAStatus = CLEAR_MONO;
			cout << "-----------------------CLEAR_MONO" << endl;
		}

		// ī���į�� ��Ҵ�.
		if ( !checkMono() && m_CabracamHP == 1)
		{
			m_OMOAStatus = CLEAR_MONO;
			cout << "-----------------------CLEAR_MONO" << endl;
		}

		break;

	case CLEAR_MONO:
		if ( clearMono() )
		{
			// ���������� ����������.
				clearMonster();
			if(checkPC()){
			TreasureCheck();
			openGateToOutNextStage();
			}
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

bool DynamicZoneMenegroth5::checkPC()
{
	Assert( m_pZone != NULL );

	// PC �� üũ
	uint size = m_pZone->getPCManager()->getSize();

	return size != 0;
}
/* �ųױ׷ν� ���Ͱ� �����ϴ� �κ��̴�. */
bool DynamicZoneMenegroth5::addMonster()
{
	Assert( m_pZone != NULL );

	for ( int i = 0; i < MonsterTemplate[0].MonsterNum; ++i )
	{
		Monster* pMonster = new Monster( MonsterTemplate[0].MonsterType );
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

	return true;
}

bool DynamicZoneMenegroth5::addMonster_boss_regen()
{
	Assert( m_pZone != NULL );
	MonsterManager* pMonsterManager = m_pZone->getMonsterManager();
	Assert( pMonsterManager != NULL );

	Creature* pCreature = pMonsterManager->getCreature( m_MonoObjectID );
	Assert( pCreature != NULL );

for(int b=0; b <= 1; ++b){
	for ( int i = 0; i < BossTemplate[b].MonsterNum; ++i )
	{
		Monster* pMonster = new Monster( BossTemplate[b].MonsterType );
		Assert( pMonster != NULL );

		ZoneCoord_t x, y;

		try
		{
			m_pZone->addCreature( pMonster, pCreature->getX(), pCreature->getY(), Directions(rand()%8) );
		}
		catch ( EmptyTileNotExistException& )
		{
			SAFE_DELETE( pMonster );
		}
	}
}
	return true;
}
// ī���į�� ������ �κ��̴�. �� �κ��� ���Ŀ� �ٽ� ������!
bool DynamicZoneMenegroth5::addMono()
{
	Assert( m_pZone != NULL );

	for ( int i = 0; i < MonsterTemplate[1].MonsterNum; ++i )
	{
		Monster* pMonster = new Monster( MonsterTemplate[1].MonsterType );
		Assert( pMonster != NULL );

		try
		{
			m_pZone->addCreature( pMonster, OfferingCoordinate[0].X, OfferingCoordinate[0].Y, Directions(rand()%8) );

			m_MonoObjectID = pMonster->getObjectID();
		}
		catch ( EmptyTileNotExistException& )
		{
			SAFE_DELETE( pMonster );
		}
	}

		char msg[20];
		sprintf( msg, "ī���į�� X : %d Y: %d ��ġ�� ��� �Ͽ����ϴ�.", OfferingCoordinate[0].X, OfferingCoordinate[0].Y);

		GCSystemMessage gcmsg;
		gcmsg.setMessage( msg );
		m_pZone->broadcastPacket( &gcmsg );


	return true;
}

bool DynamicZoneMenegroth5::clearMono()
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

bool DynamicZoneMenegroth5::checkMonoHPcount()
{
	Assert( m_pZone != NULL );

	MonsterManager* pMonsterManager = m_pZone->getMonsterManager();
	Assert( pMonsterManager != NULL );

	Creature* pCreature = pMonsterManager->getCreature( m_MonoObjectID );
	if ( pCreature != NULL )
	{
		if ( pCreature->isMonster())
		{
			Monster* pMonster = dynamic_cast<Monster*>(pCreature);
			Assert( pMonster  != NULL );
			int HPCount = getPercentValue(pMonster->getHP(ATTR_MAX),30);
			// ī���į�� ü���� 30%���ϰ� �Ǿ��� ���
			if(HPCount  > pMonster->getHP(ATTR_CURRENT)){
			// ī���į ���Ϳ��� ������ �ɾ������.
			pMonster->setFlag( Effect::EFFECT_CLASS_NO_DAMAGE );

			EffectCauseCriticalWounds* pEffect = new EffectCauseCriticalWounds( pMonster );
			pEffect->setDeadline( 999999 );
			pMonster->addEffect( pEffect );
			pMonster->setFlag( Effect::EFFECT_CLASS_CAUSE_CRITICAL_WOUNDS );
				return true;
			}
		}
	}

	return false;
}

bool DynamicZoneMenegroth5::checkMonoEffect()
{
	Assert( m_pZone != NULL );

	MonsterManager* pMonsterManager = m_pZone->getMonsterManager();
	Assert( pMonsterManager != NULL );

	Creature* pCreature = pMonsterManager->getCreature( m_MonoObjectID );
	if ( pCreature != NULL )
	{
		if ( pCreature->isMonster())
		{
			Monster* pMonster = dynamic_cast<Monster*>(pCreature);
			Assert( pMonster  != NULL );
			// ī���į ���Ϳ��� ������ �ɾ������.
			pMonster->removeFlag( Effect::EFFECT_CLASS_NO_DAMAGE );
			pMonster->removeFlag( Effect::EFFECT_CLASS_CAUSE_CRITICAL_WOUNDS );
			return true;
		}
	}

	return false;
}

bool DynamicZoneMenegroth5::openGateToOut()
{
	Assert( m_pZone != NULL );

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

	m_pZone->getPCManager()->transportAllCreatures( m_ZoneID, m_ZoneX, m_ZoneY );
        }
    }

	return true;
}

bool DynamicZoneMenegroth5::clearMonster()
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

bool DynamicZoneMenegroth5::openGateToOutNextStage()
{
	Assert( m_pZone != NULL );

	int targetDynamicZoneType = g_pDynamicZoneInfoManager->getDynamicZoneTypeByZoneID( 1706 );

	DynamicZoneGroup* pDynamicZoneGroup = g_pDynamicZoneManager->getDynamicZoneGroup( targetDynamicZoneType );
	Assert( pDynamicZoneGroup != NULL );

	DynamicZone* pDynamicZone = pDynamicZoneGroup->getAvailableDynamicZone();
	Assert( pDynamicZone != NULL );

	DynamicZoneMenegroth6* pAlterOfBlood = dynamic_cast<DynamicZoneMenegroth6*>(pDynamicZone);
	Assert( pAlterOfBlood != NULL );

	pAlterOfBlood->setZoneID(m_ZoneID);
	pAlterOfBlood->setZoneX(m_ZoneX);
	pAlterOfBlood->setZoneY(m_ZoneY);
	pAlterOfBlood->setInstantID(m_Indun);

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

	m_pZone->getPCManager()->transportAllCreatures( pDynamicZone->getZoneID(), 56, 19 );
        }
    }

	return true;
}


void DynamicZoneMenegroth5::timecheck()
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
			throw Error("PCManager�� PC�ƴѰ� ����ֳ� -_-");
		}
	}
}

bool DynamicZoneMenegroth5::checkComplete()
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

void DynamicZoneMenegroth5::processEntering()
{
	Assert( m_pZone != NULL );

    // ����Ʈ ���� �������� �˸���.
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

bool DynamicZoneMenegroth5::checkMonster()
{
	Assert( m_pZone != NULL );

	MonsterManager* pMonsterManager = m_pZone->getMonsterManager();
	Assert( pMonsterManager != NULL );

	hash_map< ObjectID_t, Creature* > & monsters = pMonsterManager->getCreatures();
	hash_map< ObjectID_t, Creature* >::iterator itr = monsters.begin();

	for (; itr!=monsters.end(); itr++)
	{
		Creature* pCreature = itr->second;
				// ���� �ϰ�� ���� ī���� 1 ����
		if(pCreature != NULL && pCreature->isMonster()){
		return false;
		}
	}

	return true;
}

bool DynamicZoneMenegroth5::checkbossmonster()
{
	Assert( m_pZone != NULL );

	MonsterManager* pMonsterManager = m_pZone->getMonsterManager();
	Assert( pMonsterManager != NULL );

	Creature* pMonoCreature = pMonsterManager->getCreature( m_MonoObjectID );
	Assert( pMonoCreature != NULL );

	hash_map< ObjectID_t, Creature* > & monsters = pMonsterManager->getCreatures();
	hash_map< ObjectID_t, Creature* >::iterator itr = monsters.begin();

	for (; itr!=monsters.end(); itr++)
	{
		Creature* pCreature = itr->second;
				// ���� �ϰ�� ���� ī���� 1 ����
		if(pMonoCreature != pCreature && pCreature != NULL && pCreature->isMonster()){
		return false;
		}
	}

	return true;
}

bool DynamicZoneMenegroth5::checkMono()
{
	Assert( m_pZone != NULL );

	MonsterManager* pMonsterManager = m_pZone->getMonsterManager();
	Assert( pMonsterManager != NULL );

	Creature* pCreature = pMonsterManager->getCreature( m_MonoObjectID );
	return pCreature != NULL;
}
void DynamicZoneMenegroth5::TreasureCheck()
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

			MonsterDropSetup* pMonsterItemDrop = g_pMonsterDropSetupManager->getMonsterDropSetup(62);
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
					pItem1->setNum( 7 );
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
				// �κ��丮�� �߰��Ѵ�.
				pInventory->addItem(p.x, p.y, pItem1);

	           			pItem1->create(pCreature->getName(), STORAGE_INVENTORY, 0, p.x, p.y);

				// ItemTrace �� Log �� �����
				if ( pItem1 != NULL && pItem1->isTraceItem() )
				{
					remainTraceLog( pItem1, "InstantDungeon", pCreature->getName(), ITEM_LOG_CREATE, DETAIL_EVENTNPC);
					remainTraceLogNew( pItem1, pCreature->getName(), ITL_GET, ITLD_EVENTNPC, m_pZone->getZoneID() );
				}

				// �κ��丮�� ������ ���� ��Ŷ�� �����ش�.
				GCCreateItem gcCreateItem;

				makeGCCreateItem( &gcCreateItem, pItem1, p.x, p.y );

				pCreature->getPlayer()->sendPacket(&gcCreateItem);
			}
			else
			{
				// �κ��丮�� �ڸ��� ��� �ٴڿ� ����߸���.

				TPOINT p = m_pZone->addItem(pItem1, pCreature->getX(), pCreature->getY());
				if (p.x != -1)
				{
					pItem1->create("", STORAGE_ZONE, m_pZone->getZoneID(), p.x, p.y );

					// ItemTrace �� Log �� �����
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
			throw Error("PCManager�� PC�ƴѰ� ����ֳ� -_-");
		}
	}
}

void DynamicZoneMenegroth5::killPC()
{
	Assert( m_pZone != NULL );

    // PC �� ���δ�.
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

DEFINE_DYNAMIC_ZONE_FACTORY( DynamicZoneMenegroth5, DYNAMIC_ZONE_MENEGROTH5 )


