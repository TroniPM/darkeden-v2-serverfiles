#include <stdio.h>
#include "CastleShrineInfoManager.h"
#include "StringStream.h"
#include "DB.h"
#include "ZoneItemPosition.h"
#include "Zone.h"
#include "ZoneUtil.h"
#include "MonsterCorpse.h"
#include "Item.h"
#include "ItemFactoryManager.h"
#include "EffectShrineGuard.h"
#include "EffectShrineHoly.h"
#include "EffectShrineShield.h"
#include "War.h"
#include "WarSystem.h"
#include "RelicUtil.h"
#include "CastleInfoManager.h"
#include "GlobalItemPosition.h"
#include "GlobalItemPositionLoader.h"
#include "ZoneGroupManager.h"
#include "Player.h"
#include "GuildWar.h"
#include "PlayerCreature.h"
#include "CreatureUtil.h"
#include "StringPool.h"

#include "Gpackets/GCSystemMessage.h"
#include "Gpackets/GCRemoveEffect.h"
#include "Gpackets/GCAddEffect.h"
#include "Gpackets/GCAddEffectToTile.h"
#include "Gpackets/GCDeleteInventoryItem.h"

#include "CastleSymbol.h"

string CastleShrineSet::toString() const
	throw()
{
	__BEGIN_TRY

	StringStream msg;

	msg << "ShrineSet("
		<< "ShrineID:" << (int)m_ShrineID
		<< ","
		<< m_GuardShrine.toString()
		<< ","
		<< m_HolyShrine.toString()
		<< ",ItemType:" << (int)m_ItemType
		<< ")";

	return msg.toString();

	__END_CATCH
}

CastleShrineInfoManager::~CastleShrineInfoManager()
{
	clear();
}

void CastleShrineInfoManager::clear()
{
	HashMapShrineSetItor itr = m_ShrineSets.begin();
	for ( ; itr != m_ShrineSets.end() ; itr++ )
	{
		SAFE_DELETE( itr->second );
	}
	m_ShrineSets.clear();
}

void CastleShrineInfoManager::init()
	
{ 
	__BEGIN_TRY

	load();

	addAllShrineToZone();

	__END_CATCH
}

void CastleShrineInfoManager::load()
	
{
	__BEGIN_TRY

	Statement* pStmt = NULL;
	Result* pResult = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		pResult = pStmt->executeQuery( "SELECT ID, Name, ItemType, GuardZoneID, GuardX, GuardY, GuardMType, HolyZoneID, HolyX, HolyY, HolyMType FROM CastleShrineInfo" );

		while ( pResult->next() )
		{
			int i = 0;

			CastleShrineSet* pShrineSet = new CastleShrineSet();

			pShrineSet->m_ShrineID = pResult->getInt( ++i );
			pShrineSet->m_GuardShrine.setName( pResult->getString( ++i ) );
			pShrineSet->m_HolyShrine.setName( pShrineSet->m_GuardShrine.getName() );
			pShrineSet->m_ItemType = pResult->getInt( ++i );
			pShrineSet->m_GuardShrine.setZoneID( pResult->getInt( ++i ) );
			pShrineSet->m_GuardShrine.setX( pResult->getInt( ++i ) );
			pShrineSet->m_GuardShrine.setY( pResult->getInt( ++i ) );
			pShrineSet->m_GuardShrine.setMonsterType( pResult->getInt( ++i ) );
			pShrineSet->m_HolyShrine.setZoneID( pResult->getInt( ++i ) );
			pShrineSet->m_HolyShrine.setX( pResult->getInt( ++i ) );
			pShrineSet->m_HolyShrine.setY( pResult->getInt( ++i ) );
			pShrineSet->m_HolyShrine.setMonsterType( pResult->getInt( ++i ) );

			pShrineSet->m_GuardShrine.setShrineType( ShrineInfo::SHRINE_GUARD );
			pShrineSet->m_HolyShrine.setShrineType( ShrineInfo::SHRINE_HOLY );

			// ItemType�� Shrine ID�� ���ƾ� �Ѵ�. ���� ���� ��� DB���� ������ �ε��������� ���´�.
			if ( pShrineSet->m_ItemType != pShrineSet->m_ShrineID )
			{
				cout << "ShrineID �� ItemType�� ���� �ʽ��ϴ�. DB������ �����ϼ���." << endl;
				Assert( false );
			}

			addShrineSet( pShrineSet );
		}
	}
	END_DB( pStmt )

	__END_CATCH
}

ZoneID_t CastleShrineInfoManager::getGuardShrineZoneID( ZoneID_t castleZoneID ) const 
	
{
	__BEGIN_TRY

	HashMapShrineSetConstItor itr = m_ShrineSets.begin();

	// castleZoneID�� shrineID�� �˻��Ҽ��� ��� �ϳ��ϳ� ���Ѵ�. -_-;
	for (; itr!=m_ShrineSets.end(); itr++)
	{
		CastleShrineSet* pShrineSet = itr->second;

		ZoneID_t guardZoneID = pShrineSet->m_GuardShrine.getZoneID();
		ZoneID_t guardCastleZoneID;

		if (g_pCastleInfoManager->getCastleZoneID(guardZoneID, guardCastleZoneID))
		{
			if (castleZoneID==guardCastleZoneID)
			{
				return guardZoneID;
			}
		}
	}

	StringStream msg;
	msg << "CastleZoneID�� ���õ� GuardZoneID�� ����[" << (int)castleZoneID  << "]";
	throw Error(msg.toString());

	__END_CATCH
}

void CastleShrineInfoManager::addAllShrineToZone()
	
{
	__BEGIN_TRY

	HashMapShrineSetItor itr = m_ShrineSets.begin();
	for ( ; itr != m_ShrineSets.end() ; itr++ )
	{
		CastleShrineSet* pShrineSet = itr->second;

		if ( pShrineSet == NULL ) continue;

		Item* pItem = addShrineToZone( pShrineSet->m_GuardShrine, pShrineSet->m_ItemType );
		
		if (pItem==NULL)
		{
			pShrineSet->setCastleSymbolItemID( 0 );
		}
		else
		{
			pShrineSet->setCastleSymbolItemID( pItem->getItemID() );
		}

		addShrineToZone( pShrineSet->m_HolyShrine, pShrineSet->m_ItemType );
	}

	__END_CATCH
}

Item* CastleShrineInfoManager::addShrineToZone( ShrineInfo& shrineInfo, ItemType_t itemType )
	
{
	__BEGIN_TRY

	// ������ ���� ���� �����´�.
	Zone* pZone = getZoneByZoneID( shrineInfo.getZoneID() );
	Assert( pZone != NULL );

	MonsterCorpse* pShrine = new MonsterCorpse( shrineInfo.getMonsterType(), shrineInfo.getName(), 2 );
	Assert( pShrine != NULL );

	pShrine->setShrine( true );
	pShrine->setZone( pZone );

	pZone->getObjectRegistry().registerObject( pShrine );
	shrineInfo.setObjectID( pShrine->getObjectID() );

	cout << "AddShrine[" << (int)shrineInfo.getZoneID() << "] " 
			<< (shrineInfo.getShrineType()==ShrineInfo::SHRINE_GUARD? "Guard":"Holy")
			<< ", mtype=" << shrineInfo.getMonsterType()
			<< ", oid=" << pShrine->getObjectID() << endl;

	Item* pItem =  NULL;

/*	if ( shrineInfo.getShrineType() == ShrineInfo::SHRINE_GUARD )
	{
		pShrine->setFlag( Effect::EFFECT_CLASS_SHRINE_GUARD );

		EffectShrineGuard* pEffect = new EffectShrineGuard(pShrine);
		pEffect->setShrineID( itemType );
		pEffect->setTick( 60 * 10 );

		pShrine->getEffectManager().addEffect( pEffect );
	}
	else if ( shrineInfo.getShrineType() == ShrineInfo::SHRINE_HOLY )
	{
		pShrine->setFlag( Effect::EFFECT_CLASS_SHRINE_HOLY );

		EffectShrineHoly* pEffect = new EffectShrineHoly(pShrine);
		pEffect->setShrineID( itemType );
		pEffect->setTick( 60 * 10 );

		pShrine->getEffectManager().addEffect( pEffect );
	}*/

	TPOINT tp = pZone->addItem( pShrine, shrineInfo.getX(), shrineInfo.getY(), true );
	Assert( tp.x != -1 );

	// ���� ��¡�� �߰��� �ʿ䰡 �ִٸ� �߰��Ѵ�.
	if ( shrineInfo.getShrineType() == ShrineInfo::SHRINE_GUARD )
	{
		//if ( AddBible[ itemType ] )
		{
			list<OptionType_t> optionNULL;
			pItem = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_CASTLE_SYMBOL, itemType, optionNULL );
			Assert( pItem != NULL );

			char strZoneID[10];
			sprintf(strZoneID, "%d", (int)pZone->getZoneID());

			pZone->registerObject( pItem );
			pItem->create( strZoneID, STORAGE_CORPSE, pShrine->getObjectID(), 0, 0 );

			pShrine->addTreasure( pItem );
		}

		// ��ȣ�����̶�°� ǥ���صд�.
		pShrine->setFlag( Effect::EFFECT_CLASS_CASTLE_SHRINE_GUARD );

		// ��� ��ȣ���ܿ� Shield Effect ���δ�
		pShrine->setFlag( Effect::EFFECT_CLASS_SHRINE_SHIELD );

		EffectShrineShield* pEffect = new EffectShrineShield(pShrine);
		pEffect->setShrineID( itemType );
		pEffect->setTick( 60 * 10 );

		pShrine->getEffectManager().addEffect( pEffect );
	}
	else
	{
		// ���������̶�°� ǥ���صд�.
		pShrine->setFlag( Effect::EFFECT_CLASS_CASTLE_SHRINE_HOLY );
	}

	// ���� ��ǥ�� ���� �����Ѵ�.
	shrineInfo.setX( tp.x );
	shrineInfo.setY( tp.y );

	return pItem;

	__END_CATCH
}

void CastleShrineInfoManager::addShrineSet( CastleShrineSet* pShrineSet )
	
{
	__BEGIN_TRY

	if ( pShrineSet == NULL ) return;

	ShrineID_t shrineID = pShrineSet->m_ShrineID;

	HashMapShrineSetItor itr = m_ShrineSets.find( shrineID );

	if ( itr != m_ShrineSets.end() )
	{
		filelog( "ShrineInfoError.log", "CastleShrineInfoManager::addShrineSet DuplicatedException : %d", (int)shrineID );
		return;
	}

	m_ShrineSets[ shrineID ] = pShrineSet;

	__END_CATCH
}

void CastleShrineInfoManager::deleteShrineSet( ShrineID_t shrineID )
	
{
	__BEGIN_TRY

	HashMapShrineSetItor itr = m_ShrineSets.find( shrineID );

	if ( itr != m_ShrineSets.end() )
	{
		SAFE_DELETE( itr->second );
		m_ShrineSets.erase( shrineID );
	}
	
	__END_CATCH
}

CastleShrineSet* CastleShrineInfoManager::getShrineSet( ShrineID_t shrineID ) const
	
{
	__BEGIN_TRY

	HashMapShrineSetConstItor itr = m_ShrineSets.find( shrineID );

	if ( itr != m_ShrineSets.end() )
	{
		return itr->second;
	}

	return NULL;

	__END_CATCH
}

bool CastleShrineInfoManager::isMatchHolyShrine(Item* pItem, MonsterCorpse* pMonsterCorpse) const
	
{
	__BEGIN_TRY

	if ( pItem->getItemClass() != Item::ITEM_CLASS_CASTLE_SYMBOL )
		return false;
	
	ItemType_t itemType = pItem->getItemType();
	ShrineID_t shrineID = itemType;					// ShrineID = ItemType(of CastleSymbol)

	CastleShrineSet* pShrineSet = getShrineSet( shrineID );

	if( pShrineSet == NULL )
	{
		// �� ���� ��¡�� �ش��ϴ� Shrine Set�� ����.
		return false;
	}

	// �� ���� ��¡�� �ش��ϴ� Shrine set�� ���������� MonsterType��
	// �Ѿ�� MonsterCorpse�� MonsterType�� ���� ObjectID�� ������ true
	return pShrineSet->m_HolyShrine.getMonsterType() == pMonsterCorpse->getMonsterType()
		&& pShrineSet->m_HolyShrine.getObjectID() == pMonsterCorpse->getObjectID();

	__END_CATCH
}

bool CastleShrineInfoManager::isDefenderOfGuardShrine( PlayerCreature* pPC, MonsterCorpse* pShrine ) const
	
{
	__BEGIN_TRY

	Zone* pZone = pShrine->getZone();
	Assert( pZone != NULL );

	// ���� �ƴϸ� ��~
	/*
	if ( !pZone->isCastle() )
	{
		return false;
	}
	*/


	ZoneID_t guardZoneID = pZone->getZoneID();
	ZoneID_t castleZoneID;

	bool isCastle = g_pCastleInfoManager->getCastleZoneID( guardZoneID, castleZoneID );
	Assert(isCastle==true);

	War* pWar = g_pWarSystem->getActiveWar( castleZoneID );
	if ( pWar == NULL )
		return false;

	CastleInfo* pCastleInfo = g_pCastleInfoManager->getCastleInfo( castleZoneID );
	if ( pCastleInfo == NULL )
		return false;

	/*
	if ( pWar->getWarType() == WAR_RACE )
	{
		// ���� ���� �߿��� ���� ���� ������ ���� �����̸� defender �̴�.
		if ( pPC->getRace() == pCastleInfo->getRace() )
			return true;
	}
	else 
	*/
	if ( pWar->getWarType() == WAR_GUILD )
	{
		GuildWar* pGuildWar = dynamic_cast<GuildWar*>(pWar);
		Assert(pGuildWar!=NULL);

		if ( pCastleInfo->isCommon() )
		{
			// ���뼺�� ���� ���ݱ�常 �ƴϸ� defender�̴�.
			return pPC->getGuildID()!=pGuildWar->getChallangerGuildID();
		}
		else
		{
			// ���� ���� �߿��� ���뼺�� �ƴ� ��� ���� ���� ��尡 defender �̴�.
			if ( pPC->getGuildID() == pCastleInfo->getGuildID() )
				return true;
		}
	}

	return false;

	__END_CATCH
}

// �� ������ ���� ��¡ ������ �� �� �ִ°�?
bool CastleShrineInfoManager::canPickupCastleSymbol( Race_t race, CastleSymbol* pCastleSymbol ) const
	
{
	__BEGIN_TRY

	// �ϴ� �� ���� ��¡ ������ ��� ���￡ �ҼӵǾ� �ִ��� �˾ƿ´�.
	CastleShrineSet* pShrineSet = getShrineSet( pCastleSymbol->getItemType() );

	if ( pShrineSet == NULL )
	{
		return false;
	}

	ZoneID_t guardZoneID = pShrineSet->m_GuardShrine.getZoneID();
	ZoneID_t castleZoneID;

	bool isCastle = g_pCastleInfoManager->getCastleZoneID( guardZoneID, castleZoneID );
	Assert(isCastle==true);

	War* pWar = g_pWarSystem->getActiveWar( castleZoneID );

	if ( pWar == NULL )
	{
		// �ƽ� ��縮��~
		filelog( "WarError.log", "���ﵵ ���ϴµ� ���� ��¡������ �ֿ���� �Ѵ�. ItemType: %u", (int)pCastleSymbol->getItemType() );
		return false;
	}

	/*
	if ( pWar->getWarType() == WAR_RACE )
	{
		// ���� �����̸� �������� �� �޴´�.
		return true;
	}
	else 
	*/
	if ( pWar->getWarType() == WAR_GUILD )
	{
		CastleInfo* pCastleInfo = g_pCastleInfoManager->getCastleInfo( castleZoneID );

		if ( pCastleInfo == NULL )
		{
			// �ƽ� ��縮��~
			filelog( "WarError.log", "���� �ƴϴ�. ItemType: %u, ZoneID : %u", (int)pCastleSymbol->getItemType(), (int)castleZoneID );
			return false;
		}

		return ( race == pCastleInfo->getRace() );
	}

	// �ƽ� ��縮��~
	filelog( "WarError.log", "�̻��� �����̴�. WarType : %u", (int)pWar->getWarType() );

	return false;
	__END_CATCH
}

bool CastleShrineInfoManager::getMatchGuardShrinePosition( Item* pItem, ZoneItemPosition& zip ) const
	
{
	__BEGIN_TRY

	if ( pItem->getItemClass() != Item::ITEM_CLASS_CASTLE_SYMBOL )
		return false;
	
	ItemType_t itemType = pItem->getItemType();
	ShrineID_t shrineID = itemType;					// ShrineID = ItemType(of CastleSymbol)

	CastleShrineSet* pShrineSet = getShrineSet( shrineID );

	if ( pShrineSet == NULL )
	{
		// �� ���� ��¡�� �ش��ϴ� Shrine Set�� ����.
		return false;
	}

	zip.setZoneID( pShrineSet->m_GuardShrine.getZoneID() );
	zip.setZoneX( pShrineSet->m_GuardShrine.getX() );
	zip.setZoneY( pShrineSet->m_GuardShrine.getY() );

	return true;

	__END_CATCH
}

// putCastleSymbol ( ������ �������ܿ� ���� ��¡�� �������� ) �� �ҷ����� bLock = false
// returnAllCastleSymbol ( �ð��� �� �Ǿ��� �� ) �� �ҷ����� bLock = true
// true�� ��� �ٸ� ������ (WarSystem�� ���ư��� ������)���� �ҷ����Ƿ� ���ο��� ���� �ɾ���� �ϰ�
// false�� ��� ���������� �ִ� ���� ���� ���׷콺���忡�� ���ư��Ƿ� ���ο��� ���� �ɾ����� �ʾƾ� �Ѵ�.
// 2003. 2. 5. by Sequoia
bool CastleShrineInfoManager::returnCastleSymbol( ShrineID_t shrineID, bool bLock ) const
	
{
	__BEGIN_TRY

	// shrineID�� ���õ� CastleSymbol�� DB������ �̿��ؼ� ã�´�.
	CastleShrineSet* pShrineSet = getShrineSet( shrineID );
	
	if (pShrineSet==NULL) return false;

	Item::ItemClass ItemClass 	= Item::ITEM_CLASS_CASTLE_SYMBOL;
	ItemID_t 		ItemID 		= pShrineSet->getCastleSymbolItemID();

	if (ItemID==0) return false;

	GlobalItemPosition* pItemPosition = GlobalItemPositionLoader::getInstance()->load( ItemClass, ItemID );

	if (pItemPosition==NULL) return false;

	Item* pItem = pItemPosition->popItem( bLock );

	if (pItem!=NULL && pItem->getItemClass()==Item::ITEM_CLASS_CASTLE_SYMBOL)
	{
		Zone* pZone = pItemPosition->getZone();
		Assert(pZone!=NULL);

		CastleSymbol* pCastleSymbol = dynamic_cast<CastleSymbol*>(pItem);
		Assert(pCastleSymbol!=NULL);

		return returnCastleSymbol(pZone, pCastleSymbol);
	}

	return false;

	__END_CATCH
}

// WarSystem������ �θ���.
bool CastleShrineInfoManager::returnAllCastleSymbol( ZoneID_t castleZoneID ) const 
	
{
	__BEGIN_TRY

	bool bReturned = false;

	HashMapShrineSetConstItor itr = m_ShrineSets.begin();

	// castleZoneID�� shrineID�� �˻��Ҽ��� ��� �ϳ��ϳ� ���Ѵ�. -_-;
	for (; itr!=m_ShrineSets.end(); itr++)
	{
		CastleShrineSet* pShrineSet = itr->second;

		ZoneID_t guardZoneID = pShrineSet->m_GuardShrine.getZoneID();
		ZoneID_t guardCastleZoneID;

		if (g_pCastleInfoManager->getCastleZoneID(guardZoneID, guardCastleZoneID))
		{
			if (castleZoneID==guardCastleZoneID)
			{
				bReturned = returnCastleSymbol( pShrineSet->m_ShrineID ) || bReturned;
			}
		}
	}
	
	return bReturned;

	__END_CATCH
}


bool CastleShrineInfoManager::returnCastleSymbol(Zone* pZone, CastleSymbol* pCastleSymbol) const
	
{
	__BEGIN_TRY

	Assert(pZone!=NULL);
	Assert(pCastleSymbol!=NULL);

	// TargetZone, Shrine�� ã�´�.
	ShrineID_t shrineID = pCastleSymbol->getItemType();
	CastleShrineSet* pShrineSet = getShrineSet( shrineID );
	
	if (pShrineSet==NULL) return false;

	ShrineInfo& GuardShrine = pShrineSet->m_GuardShrine;

	Zone* pTargetZone = getZoneByZoneID( GuardShrine.getZoneID() );
	Assert( pTargetZone!=NULL );

	ObjectID_t CorpseObjectID = GuardShrine.getObjectID();

	pZone->transportItemToCorpse( pCastleSymbol, pTargetZone, CorpseObjectID );

//	StringStream msg;
//	msg << "���� ��¡ ����(" << GuardShrine.getName() << ")�� ��ȣ����(" << GuardShrine.getName() << ")���� ���ư����ϴ�.";

	char msg[200];
	sprintf( msg, g_pStringPool->c_str( STRID_RETURN_TO_GUARD_SHRINE_CASTLE_SYMBOL ),
					GuardShrine.getName().c_str(), GuardShrine.getName().c_str() );

	GCSystemMessage msgPkt;
	msgPkt.setMessage( msg );

	g_pCastleInfoManager->broadcastShrinePacket( shrineID, &msgPkt );

	return true;
		
	__END_CATCH
}

bool CastleShrineInfoManager::putCastleSymbol(PlayerCreature* pPC, Item* pItem, MonsterCorpse* pCorpse) const
	
{
	__BEGIN_TRY

	Assert(pPC!=NULL);
	Assert(pItem!=NULL);
	Assert(pCorpse!=NULL);

	ShrineID_t shrineID = pItem->getItemType();

	filelog( "WarLog.txt", "%s�� ���� ��¡[%u]�� ���� ����[%s]�� �־����ϴ�.",
			pPC->getName().c_str(), (uint)shrineID, pCorpse->getName().c_str() );

	// ���� ��¡�� �� �������κ��� ���� ��¡�� ���Ƽ� ���ư��� ��Ÿ���� ����Ʈ�� �ٿ��ش�.
//	sendCastleSymbolEffect( pCorpse, Effect::EFFECT_CLASS_SHRINE_HOLY_WARP );

	// PC���Լ� ���� ��¡�� ���Ѿ� ���� �ȿ� �ִ´�.
	Assert( pItem->getObjectID() == pPC->getExtraInventorySlotItem()->getObjectID() );
	pPC->deleteItemFromExtraInventorySlot();

	GCDeleteInventoryItem gcDeleteInventoryItem;
	gcDeleteInventoryItem.setObjectID( pItem->getObjectID() );

	pPC->getPlayer()->sendPacket( &gcDeleteInventoryItem );

	deleteRelicEffect( pPC, pItem );

	pCorpse->addTreasure( pItem );

	CastleShrineSet* pShrineSet = getShrineSet( shrineID );
	if (pShrineSet==NULL) return false;

	ZoneID_t guardZoneID = pShrineSet->m_GuardShrine.getZoneID();
	ZoneID_t castleZoneID;

	bool isCastle = g_pCastleInfoManager->getCastleZoneID( guardZoneID, castleZoneID );
	Assert(isCastle==true);

    // �˸��� ���ܿ� ������ ������ ������ ��ȣ�������� ���ư���
    if (isMatchHolyShrine( pItem, pCorpse ) && g_pWarSystem->isModifyCastleOwner( castleZoneID, pPC ))
    {
        g_pWarSystem->endWar(pPC, castleZoneID);

		// ���� ������ War::executeEnd���� �˾Ƽ� �ǵ����ش�.
//        returnCastleSymbol( shrineID, false );

		return true;
    }

    // �ٸ� ���ܿ� �ְų� ������ ���� ��Ȳ�� �ƴϸ� ��ȣ�������� �׳� ���ư���
   	returnCastleSymbol( shrineID, false );

	return false;

	__END_CATCH
}

// pZone�� guardZone�̴�.
bool CastleShrineInfoManager::removeShrineShield( Zone *pZone )
	
{
	__BEGIN_TRY

	Assert(pZone != NULL);
	HashMapShrineSetConstItor itr = m_ShrineSets.begin();

	ZoneID_t guardZoneID = pZone->getZoneID();

	// castleZoneID�� shrineID�� �˻��Ҽ��� ��� �ϳ��ϳ� ���Ѵ�. -_-;
	for (; itr!=m_ShrineSets.end(); itr++)
	{
		CastleShrineSet* pShrineSet = itr->second;

		ZoneID_t currentGuardZoneID = pShrineSet->m_GuardShrine.getZoneID();

		if (guardZoneID==currentGuardZoneID)
		{
			Item* pItem = pZone->getItem( pShrineSet->m_GuardShrine.getObjectID() );

			if (pItem != NULL 
				&& pItem->getItemClass() == Item::ITEM_CLASS_CORPSE
				&& pItem->isFlag(Effect::EFFECT_CLASS_HAS_CASTLE_SYMBOL)
				&& pItem->isFlag(Effect::EFFECT_CLASS_SHRINE_SHIELD) ) 
			{
				pItem->removeFlag(Effect::EFFECT_CLASS_SHRINE_SHIELD);

				Corpse* pCorpse = dynamic_cast<Corpse*>(pItem);

				EffectManager& EM = pItem->getEffectManager();
				EM.deleteEffect(Effect::EFFECT_CLASS_SHRINE_SHIELD);

				GCRemoveEffect gcRemoveEffect;
				gcRemoveEffect.setObjectID(pItem->getObjectID());
				gcRemoveEffect.addEffectList(Effect::EFFECT_CLASS_SHRINE_SHIELD);
				pZone->broadcastPacket(pCorpse->getX(), pCorpse->getY(), &gcRemoveEffect);

			}
		}
	}

	return true;
	
	__END_CATCH
}

// pZone�� guardZone�̴�.
bool CastleShrineInfoManager::addShrineShield(Zone *pZone)
	
{
	__BEGIN_TRY

	Assert(pZone!=NULL);

	bool bAdded = false;

    __ENTER_CRITICAL_SECTION( (*pZone) )

	bAdded = addShrineShield_LOCKED( pZone );

    __LEAVE_CRITICAL_SECTION( (*pZone) )

	return bAdded;

	__END_CATCH
}

// pZone�� guardZone�̴�.
bool CastleShrineInfoManager::addShrineShield_LOCKED( Zone *pZone )
	
{
	__BEGIN_TRY

	Assert(pZone != NULL);
	HashMapShrineSetConstItor itr = m_ShrineSets.begin();

	ZoneID_t guardZoneID = pZone->getZoneID();

	// castleZoneID�� shrineID�� �˻��Ҽ��� ��� �ϳ��ϳ� ���Ѵ�. -_-;
	for (; itr!=m_ShrineSets.end(); itr++)
	{
		CastleShrineSet* pShrineSet = itr->second;

		ZoneID_t currentGuardZoneID = pShrineSet->m_GuardShrine.getZoneID();

		if (guardZoneID==currentGuardZoneID)
		{
			Item* pItem = pZone->getItem( pShrineSet->m_GuardShrine.getObjectID() );

			if (pItem != NULL 
				&& pItem->getItemClass() == Item::ITEM_CLASS_CORPSE
				&& !pItem->isFlag(Effect::EFFECT_CLASS_SHRINE_SHIELD) ) 
			{
				pItem->setFlag(Effect::EFFECT_CLASS_SHRINE_SHIELD);

				Corpse* pCorpse = dynamic_cast<Corpse*>(pItem);
				Assert(pCorpse!=NULL);

				EffectManager& EM = pItem->getEffectManager();
				EffectShrineShield* pEffect = new EffectShrineShield(pCorpse);
				pEffect->setShrineID( pCorpse->getItemType() );
				pEffect->setTick( 60 * 10 );
				EM.addEffect(pEffect);

				GCAddEffect gcAddEffect;
				gcAddEffect.setObjectID( pItem->getObjectID() );
				gcAddEffect.setEffectID( Effect::EFFECT_CLASS_SHRINE_SHIELD );
				gcAddEffect.setDuration( 65000 );

				pZone->broadcastPacket(pCorpse->getX(), pCorpse->getY(), &gcAddEffect);
			}
		}
	}

	return true;

	__END_CATCH
}

string CastleShrineInfoManager::toString() const 
	throw()
{
	__BEGIN_TRY

	StringStream msg;

	msg << "ShrineInfoManager("
		<< "Size:" << size()
		<< ",(\n";

	HashMapShrineSetConstItor itr = m_ShrineSets.begin();

	for( ; itr != m_ShrineSets.end() ; itr++ )
	{
		msg << "\t" << itr->second->toString() << "\n";
	}

	msg << "))";

	return msg.toString();

	__END_CATCH
}

CastleShrineInfoManager* g_pCastleShrineInfoManager = NULL;
