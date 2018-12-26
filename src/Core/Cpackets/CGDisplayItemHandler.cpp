//////////////////////////////////////////////////////////////////////////////
// Filename    : CGDisplayItemHandler.cp	p
// Written By  :
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CGDisplayItem.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
	#include "PlayerCreature.h"
	#include "Store.h"
	#include "Inventory.h"
	#include "ItemUtil.h"
	#include "Zone.h"
	#include "TradeManager.h"
	#include "Gpackets/GCMyStoreInfo.h"
	#include "Gpackets/GCAddStoreItem.h"
	#include "Gpackets/GCSystemMessage.h"
	#include "Gpackets/GCNoticeEvent.h"
#endif	// __GAME_SERVER__

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGDisplayItemHandler::execute (CGDisplayItem* pPacket , Player* pPlayer)
	 
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#ifdef __GAME_SERVER__
	
//#ifndef __TEST_SERVER__
//	return;
//#endif

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	Assert(pGamePlayer != NULL);

	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pGamePlayer->getCreature());
	Assert( pPC != NULL );

	Inventory* pInventory = pPC->getInventory();
	Assert( pInventory != NULL );

	Store* pStore = pPC->getStore();
	Assert( pStore != NULL );

	GCSystemMessage errorMsg;
	GCNoticeEvent errorNotice;

	if ( pPacket->getIndex() > MAX_ITEM_NUM )
	{
		filelog("Store.log", "[%s:%s] (%u) �߸��� �ε����Դϴ�.",
				pGamePlayer->getID().c_str(), pPC->getName().c_str(), pPacket->getIndex());
		return;
	}

	if ( pPacket->getX() >= pInventory->getWidth() || pPacket->getY() >= pInventory->getHeight() )
	{
		filelog("Store.log", "[%s:%s] (%u,%u) �κ��丮 ��ǥ�� �߸� ��������ϴ�..",
				pGamePlayer->getID().c_str(), pPC->getName().c_str(), pPacket->getX(), pPacket->getY() );
		return;
	}

	Item* pItem = pInventory->getItem( pPacket->getX(), pPacket->getY() );
	if ( pItem == NULL || pItem->getObjectID() != pPacket->getItemObjectID() )
	{
		filelog("Store.log", "[%s:%s] (%u, %u) : %u ������ ��ǥ�� �߸��Ǿ��ų� ������Ʈ ���̵� �߸��Ǿ����ϴ�.",
				pGamePlayer->getID().c_str(), pPC->getName().c_str(), pPacket->getX(), pPacket->getY(), pPacket->getItemObjectID() );
		return;
	}

	if ( pPC->getZone()->getTradeManager()->getTradeInfo( pPC->getName() ) != NULL )
	{
		filelog("Store.log", "[%s:%s] : �ŷ��߿��� ������ �÷����� �� �����ϴ�.",
				pGamePlayer->getID().c_str(), pPC->getName().c_str());
		return;
	}

	if ( pStore->hasItem( pItem ) )
	{
		filelog("Store.log", "[%s:%s] (%u, %u) �̹� �������� ������ �ֽ��ϴ�.",
				pGamePlayer->getID().c_str(), pPC->getName().c_str(), pItem->getObjectID(), pPacket->getIndex() );
//		errorMsg.setMessage("�̹� ������ �������Դϴ�.");
		errorNotice.setCode(NOTICE_EVENT_ALREADY_DISPLAYED);
		pGamePlayer->sendPacket( &errorNotice );
		return;
	}

	if ( pItem->isTimeLimitItem() || !canSell( pItem ) || !canTrade( pItem ) )
	{
		filelog("Store.log", "[%s:%s] (%s) �� �� ���� �������Դϴ�.",
				pGamePlayer->getID().c_str(), pPC->getName().c_str(), pItem->toString().c_str());
//		errorMsg.setMessage("�Ǹ��� �� ���� �������Դϴ�.");
		errorNotice.setCode(NOTICE_EVENT_CANNOT_SELL);
		pGamePlayer->sendPacket( &errorNotice );
		return;
	}

	BYTE result = pStore->setStoreItem( pPacket->getIndex(), pItem, pPacket->getPrice() );
	if (  result != 0 )
	{
		filelog("Store.log", "[%s:%s] (%u) �������� ���� �� �����ϴ�.",
				pGamePlayer->getID().c_str(), pPC->getName().c_str(), result);
		return;
	}

	GCMyStoreInfo gcInfo;
	gcInfo.setStoreInfo( &(pStore->getStoreInfo()) );
	pGamePlayer->sendPacket( &gcInfo );

	if ( pStore->isOpen() )
	{
		GCAddStoreItem gcAdd;
		gcAdd.setOwnerObjectID( pPC->getObjectID() );
		gcAdd.setIndex( pPacket->getIndex() );
		pStore->getStoreItem( pPacket->getIndex() ).makeStoreItemInfo( gcAdd.getItem() );
		pPC->getZone()->broadcastPacket( pPC->getX(), pPC->getY(), &gcAdd, pPC );
	}

#endif	// __GAME_SERVER__
		
	__END_DEBUG_EX __END_CATCH
}

