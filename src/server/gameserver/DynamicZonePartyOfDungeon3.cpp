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
	// ���� ���� ���� ���� ���� �κ�
	m_CountMonster = 1;
	m_MonsterSize = 0;
	m_ItemCreate = 0;
	// �δ� �׷�?
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
			cout << "���� ���̵� : " << m_MonsterSize << endl;
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
	
		// 60������ �Ѿ�� �ʾ��� ��� ���� �ܰ�� ����������.
		// 60�� �����̰� �Ѿ� ���� ��� �ٽ� ��Ʈ�� ���Ѿ� �Ѵ�.
		if ( !CountMonster() && checkComplete())
		{
			// �ٽ� 1�� �߰��Ѵ�.
			m_OMOAStatus = ADD_MONO;
		}

		//cout << " ��ü�� : " << m_CountMonster << endl;
		// ���Ͱ� 60������ �Ѿ�� ��� ��������.
		break;

	case CLEAR_MONO:
		if ( clearMono() )
		{
			// ���� ī���͸� ���� ������.
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

	// PC �� üũ
	uint size = m_pZone->getPCManager()->getSize();

	return size != 0;
}

bool DynamicZonePartyOfDungeon3::addMono()
{
			cout << " ����ǳ�.. " << endl;
	Assert( m_pZone != NULL );
	int i = g_pInstantDungeonMonsterManager->getMinInt(m_GroupID);;
	int s = g_pInstantDungeonMonsterManager->getMaxInt(m_GroupID);;
			cout << " ����ǳ�.. 2" << endl;
	while(i<=s){
			cout << " ����ǳ�.. 3" << endl;
		InstantDungeonMonster* pInstantDungeonMonster = g_pInstantDungeonMonsterManager->getInstantDungeonMonster(i);
			cout << " ����ǳ�.. 4" << endl;
		MonsterType_t 	MonsterType 	= pInstantDungeonMonster->getMonsterType();

		if(pInstantDungeonMonster != NULL){
			cout << " ����ǳ�.. 5" << endl;
		for(int s =0; s<pInstantDungeonMonster->getMonsterNumber(); s++){
			cout << " ����ǳ�.. 6" << endl;
		// �̼��� ������ �����Ѵ�.
		Monster* pMonster = new Monster( MonsterType );
		Assert( pMonster != NULL );
		
		pMonster->setName("������ ����");
		cout << " ���� ü�� : " << pMonster->getHP() << endl;
		pMonster->setHP(pMonster->getHP()+getPercentValue(pMonster->getHP(), m_MonsterSize),pMonster->getHP()+getPercentValue(pMonster->getHP(), m_MonsterSize));
		pMonster->setSTR(pMonster->getSTR()+getPercentValue(pMonster->getSTR(), m_MonsterSize));
		pMonster->setDEX(pMonster->getDEX()+getPercentValue(pMonster->getDEX(), m_MonsterSize));
		pMonster->setINT(pMonster->getINT()+getPercentValue(pMonster->getINT(), m_MonsterSize));
		pMonster->setExp(pMonster->getExp()+getPercentValue(pMonster->getExp(), m_MonsterSize));
		pMonster->setProtection(pMonster->getProtection()+getPercentValue(pMonster->getProtection(), m_MonsterSize));
		pMonster->setToHit(pMonster->getToHit()+getPercentValue(pMonster->getToHit(), m_MonsterSize));
		pMonster->setDamage(pMonster->getDamage()+getPercentValue(pMonster->getDamage(), m_MonsterSize),pMonster->getDamage()+getPercentValue(pMonster->getDamage(), m_MonsterSize));
		cout << " ���� ���� ü�� : " << pMonster->getHP() << endl;
		
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

		// ��� ���͸� ���δ�.
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
				// ���� �ϰ�� ���� ī���� 1 ����
				if(pCreature != NULL && pCreature->isMonster()){
				m_CountMonster++;
				}
			}

	// ���Ͱ� 60������ �Ѿ� �� ��� TRUE
	if(m_CountMonster > 60)	return true;
	
	// 60������ ���� ���� �ʾ����Ƿ� FALSE
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
			throw Error("PCManager�� PC�ƴѰ� ����ֳ� -_-");
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
				// �κ��丮�� �߰��Ѵ�.
				pInventory->addItem(p.x, p.y, pItem);

	           			pItem->create(pCreature->getName(), STORAGE_INVENTORY, 0, p.x, p.y);

				// ItemTrace �� Log �� �����
				if ( pItem != NULL && pItem->isTraceItem() )
				{
					remainTraceLog( pItem, "InstantDungeon", pCreature->getName(), ITEM_LOG_CREATE, DETAIL_EVENTNPC);
					remainTraceLogNew( pItem, pCreature->getName(), ITL_GET, ITLD_EVENTNPC, m_pZone->getZoneID() );
				}

				// �κ��丮�� ������ ���� ��Ŷ�� �����ش�.
				GCCreateItem gcCreateItem;

				makeGCCreateItem( &gcCreateItem, pItem, p.x, p.y );

				pCreature->getPlayer()->sendPacket(&gcCreateItem);
			}
			else
			{
				// �κ��丮�� �ڸ��� ��� �ٴڿ� ����߸���.

				TPOINT p = m_pZone->addItem(pItem, pCreature->getX(), pCreature->getY());
				if (p.x != -1)
				{
					pItem->create("", STORAGE_ZONE, m_pZone->getZoneID(), p.x, p.y );

					// ItemTrace �� Log �� �����
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
			throw Error("PCManager�� PC�ƴѰ� ����ֳ� -_-");
		}
	}
	// 10���� �̵���Ų��.
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
				// �κ��丮�� �߰��Ѵ�.
				pInventory->addItem(p.x, p.y, pItem);

	           			pItem->create(pCreature->getName(), STORAGE_INVENTORY, 0, p.x, p.y);

				// ItemTrace �� Log �� �����
				if ( pItem != NULL && pItem->isTraceItem() )
				{
					remainTraceLog( pItem, "InstantDungeon", pCreature->getName(), ITEM_LOG_CREATE, DETAIL_EVENTNPC);
					remainTraceLogNew( pItem, pCreature->getName(), ITL_GET, ITLD_EVENTNPC, m_pZone->getZoneID() );
				}

				// �κ��丮�� ������ ���� ��Ŷ�� �����ش�.
				GCCreateItem gcCreateItem;

				makeGCCreateItem( &gcCreateItem, pItem, p.x, p.y );

				pCreature->getPlayer()->sendPacket(&gcCreateItem);
			}
			else
			{
				// �κ��丮�� �ڸ��� ��� �ٴڿ� ����߸���.

				TPOINT p = m_pZone->addItem(pItem, pCreature->getX(), pCreature->getY());
				if (p.x != -1)
				{
					pItem->create("", STORAGE_ZONE, m_pZone->getZoneID(), p.x, p.y );

					// ItemTrace �� Log �� �����
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
			throw Error("PCManager�� PC�ƴѰ� ����ֳ� -_-");
		}
	}
}
void DynamicZonePartyOfDungeon3::processEntering()
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

DEFINE_DYNAMIC_ZONE_FACTORY( DynamicZonePartyOfDungeon3, DYNAMIC_ZONE_PARTY_OF_DUNGEON3 )


