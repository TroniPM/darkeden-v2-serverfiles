//////////////////////////////////////////////////////////////////////////////
// Filename    : CGTradeRemoveItemHandler.cpp
// Written By  : �輺��
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGTradeRemoveItem.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
	#include "Slayer.h"
	#include "Vampire.h"
	#include "Ousters.h"
	#include "Item.h"
	#include "Inventory.h"
	#include "TradeManager.h"
	#include "ZoneUtil.h"

	#include "Gpackets/GCTradeError.h"
	#include "Gpackets/GCTradeRemoveItem.h"
	#include "Gpackets/GCTradeVerify.h"
#endif

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGTradeRemoveItemHandler::execute (CGTradeRemoveItem* pPacket , Player* pPlayer)
	 
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	ObjectID_t TargetOID = pPacket->getTargetObjectID();
	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);

	Creature* pPC = pGamePlayer->getCreature();
	Assert(pPC != NULL);

	Zone* pZone = pPC->getZone();
	Assert(pZone != NULL);

	TradeManager* pTradeManager = pZone->getTradeManager();
	Assert(pTradeManager != NULL);

	// ��ȯ�� ���ϴ� ������ ������ ã�ƺ���.
	Creature* pTargetPC = NULL;
	/*
	try { pTargetPC = pZone->getCreature(TargetOID); } 
	catch (NoSuchElementException) { pTargetPC = NULL; }
	*/

	// NoSuch����. by sigi. 2002.5.2
	pTargetPC = pZone->getCreature(TargetOID);

	// ��ȯ ��밡 ���ų�, ���� ������ �ƴ϶�� ������
	if (pTargetPC == NULL)
	{
		pTradeManager->cancelTrade(pPC);
		executeError(pPacket, pPlayer, GC_TRADE_ERROR_CODE_TARGET_NOT_EXIST);
		return;
	}

	// ��ȯ ��밡 ����� �ƴϰų�, ���� ������ �ƴ϶�� ������.
	if (!pTargetPC->isPC() || !isSameRace(pTargetPC, pPC))
	{
		pTradeManager->cancelTrade(pPC);
		executeError(pPacket, pPlayer, GC_TRADE_ERROR_CODE_RACE_DIFFER);
		return;
	}

	// �� �� ���� ���뿡 �ִ��� üũ�� �Ѵ�.
	if (!isInSafeZone(pPC) || !isInSafeZone(pTargetPC))
	{
		pTradeManager->cancelTrade(pPC);
		executeError(pPacket, pPlayer, GC_TRADE_ERROR_CODE_NOT_SAFE);
		return;
	}

	// ������̸� Ÿ�� �ִٸ� ������.
	if (pPC->isSlayer() && pTargetPC->isSlayer())
	{
		Slayer* pSlayer1 = dynamic_cast<Slayer*>(pPC);
		Slayer* pSlayer2 = dynamic_cast<Slayer*>(pTargetPC);

		if (pSlayer1->hasRideMotorcycle() || pSlayer2->hasRideMotorcycle())
		{
			pTradeManager->cancelTrade(pPC);
			executeError(pPacket, pPlayer, GC_TRADE_ERROR_CODE_MOTORCYCLE);
			return;
		}
	}

	if (pPC->isOusters() && pTargetPC->isOusters())
	{
		Ousters* pOusters1 = dynamic_cast<Ousters*>(pPC);
		Ousters* pOusters2 = dynamic_cast<Ousters*>(pTargetPC);

		if ( pOusters1->isFlag(Effect::EFFECT_CLASS_SUMMON_SYLPH)
			|| pOusters2->isFlag(Effect::EFFECT_CLASS_SUMMON_SYLPH)
		)
		{
			pTradeManager->cancelTrade(pPC);
			executeError(pPacket, pPlayer, GC_TRADE_ERROR_CODE_MOTORCYCLE);
			return;
		}
	}

	// ���̼� ��ȯ�� �ϰ� �ִ� ���°� �ƴ϶�� ������.
	if (!pTradeManager->isTrading(pPC, pTargetPC))
	{
		pTradeManager->cancelTrade(pPC);
		executeError(pPacket, pPlayer, GC_TRADE_ERROR_CODE_NOT_TRADING);
		return;
	}

	if (pPC->isSlayer()) executeSlayer(pPacket, pPlayer);
	else if (pPC->isVampire()) executeVampire(pPacket, pPlayer);
	else if (pPC->isOusters()) executeOusters(pPacket, pPlayer);
	else throw ProtocolException("CGTradeRemoveItem::execute() : �� �� ���� �÷��̾� ũ����");

#endif

	__END_DEBUG_EX __END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGTradeRemoveItemHandler::executeSlayer (CGTradeRemoveItem* pPacket, Player* pPlayer)
	 
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	// ���� �Լ����� ������ �˻��߱� ������ 
	// ���⼭�� �����Ͱ� �������� �˻����� �ʴ´�.
	ObjectID_t  TargetOID   = pPacket->getTargetObjectID();
	ObjectID_t  ItemOID     = pPacket->getItemObjectID();
	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	Creature*   pPC         = pGamePlayer->getCreature();
	Zone*       pZone       = pPC->getZone();
	Creature*   pTargetPC   = pZone->getCreature(TargetOID);

	// NoSuch����. by sigi. 2002.5.2
	if (pTargetPC==NULL) return;

	Slayer*     pSender     = dynamic_cast<Slayer*>(pPC);

	// ��ȯ ��� �߰��� �������� �����͸� ����.
	CoordInven_t X, Y;
	Inventory*   pInventory     = pSender->getInventory();
	Item*        pItem          = pInventory->findItemOID(ItemOID, X, Y);

	TradeManager* pTradeManager = pZone->getTradeManager();
	Assert(pTradeManager != NULL);

	// ������ �������� ���ٸ� �翬�� �� �̻� ó���� �Ұ����ϴ�.
	if (pItem == NULL)
	{
		pTradeManager->cancelTrade(pPC);
		executeError(pPacket, pPlayer, GC_TRADE_ERROR_CODE_REMOVE_ITEM);
		return;
	}

	TradeInfo* pInfo1 = pTradeManager->getTradeInfo(pSender->getName());
	TradeInfo* pInfo2 = pTradeManager->getTradeInfo(pTargetPC->getName());

	// TradeManager���� ��ȯ ������� �� �ִ� �������� �����Ѵ�.
	//Assert(pInfo1->removeItem(pItem));
	pInfo1->removeItem(pItem);

	Timeval currentTime;
	getCurrentTime(currentTime);
	pInfo1->setNextTime(currentTime);

	// ���� OK�� ���� ���¶��, Ŭ���̾�Ʈ���� ���� ��Ŷ�� ������� �Ѵ�.
	if (pInfo1->getStatus() == TRADE_FINISH)
	{
		//cout << "CGTradeRemoveItem [" << pSender->getName() << "]�� ���°� TRADE_FINISH�̹Ƿ�, ���� ��Ŷ�� �����ش�." << endl;

		// ������Ŷ�� �����ش�.
		GCTradeVerify gcTradeVerify;
		gcTradeVerify.setCode(GC_TRADE_VERIFY_CODE_REMOVE_ITEM);
		pPlayer->sendPacket(&gcTradeVerify);
	}
	else
	{
		//cout << "CGTradeRemoveItem [" << pSender->getName() << "]�� ���°� TRADE_FINISH�� �ƴϹǷ�, ���� ��Ŷ ������ �ʴ´�." << endl;
	}

	// �������� ���ϰų� �� ���, ���°� TRADE_FINISH��� 
	// TRADE_TRADING���� �ٲ���� �Ѵ�.
	pInfo1->setStatus(TRADE_TRADING);
	pInfo2->setStatus(TRADE_TRADING);

	// ���濡�Լ� ������ ������ ������ �����Ѵ�.
	GCTradeRemoveItem gcTradeRemoveItem;
	gcTradeRemoveItem.setTargetObjectID(pSender->getObjectID());
	gcTradeRemoveItem.setItemObjectID(pItem->getObjectID());

	// ���濡�� ������ �������� ������ �����ش�.
	Player* pTargetPlayer = pTargetPC->getPlayer();
	pTargetPlayer->sendPacket(&gcTradeRemoveItem);

#endif

	__END_DEBUG_EX __END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGTradeRemoveItemHandler::executeVampire (CGTradeRemoveItem* pPacket , Player* pPlayer)
	 
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	// ���� �Լ����� ������ �˻��߱� ������ 
	// ���⼭�� �����Ͱ� �������� �˻����� �ʴ´�.
	ObjectID_t  TargetOID   = pPacket->getTargetObjectID();
	ObjectID_t  ItemOID     = pPacket->getItemObjectID();
	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	Creature*   pPC         = pGamePlayer->getCreature();
	Zone*       pZone       = pPC->getZone();
	Creature*   pTargetPC  = pZone->getCreature(TargetOID);

	// NoSuch����. by sigi. 2002.5.2
	if (pTargetPC==NULL) return;

	Vampire*    pSender    = dynamic_cast<Vampire*>(pPC);

	TradeManager* pTradeManager = pZone->getTradeManager();
	Assert(pTradeManager != NULL);

	// ��ȯ ��� �߰��� �������� �����͸� ����.
	CoordInven_t X, Y;
	Inventory*   pInventory     = pSender->getInventory();
	Item*        pItem          = pInventory->findItemOID(ItemOID, X, Y);

	// ������ �������� ���ٸ� �翬�� �� �̻� ó���� �Ұ����ϴ�.
	if (pItem == NULL)
	{
		pTradeManager->cancelTrade(pPC);
		executeError(pPacket, pPlayer, GC_TRADE_ERROR_CODE_REMOVE_ITEM);
		return;
	}

	TradeInfo* pInfo1 = pTradeManager->getTradeInfo(pSender->getName());
	TradeInfo* pInfo2 = pTradeManager->getTradeInfo(pTargetPC->getName());

	// TradeManager���� ��ȯ ������� �� �ִ� �������� �����Ѵ�.
	//Assert(pInfo1->removeItem(pItem));
	pInfo1->removeItem(pItem);

	// ���� OK�� ���� ���¶��, Ŭ���̾�Ʈ���� ���� ��Ŷ�� ������� �Ѵ�.
	if (pInfo1->getStatus() == TRADE_FINISH)
	{
		//cout << "CGTradeRemoveItem [" << pSender->getName() << "]�� ���°� TRADE_FINISH�̹Ƿ�, ���� ��Ŷ�� �����ش�." << endl;

		// ������Ŷ�� �����ش�.
		GCTradeVerify gcTradeVerify;
		gcTradeVerify.setCode(GC_TRADE_VERIFY_CODE_REMOVE_ITEM);
		pPlayer->sendPacket(&gcTradeVerify);
	}
	else
	{
		//cout << "CGTradeRemoveItem [" << pSender->getName() << "]�� ���°� TRADE_FINISH�� �ƴϹǷ�, ���� ��Ŷ ������ �ʴ´�." << endl;
	}

	// �������� ���ϰų� �� ���, ���°� TRADE_FINISH��� 
	// TRADE_TRADING���� �ٲ���� �Ѵ�.
	pInfo1->setStatus(TRADE_TRADING);
	pInfo2->setStatus(TRADE_TRADING);

	// ���濡�Լ� ������ ������ ������ �����Ѵ�.
	GCTradeRemoveItem gcTradeRemoveItem;
	gcTradeRemoveItem.setTargetObjectID(pSender->getObjectID());
	gcTradeRemoveItem.setItemObjectID(pItem->getObjectID());

	// ���濡�� ������ �������� ������ �����ش�.
	Player* pTargetPlayer = pTargetPC->getPlayer();
	pTargetPlayer->sendPacket(&gcTradeRemoveItem);

#endif

	__END_DEBUG_EX __END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGTradeRemoveItemHandler::executeOusters (CGTradeRemoveItem* pPacket , Player* pPlayer)
	 
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	// ���� �Լ����� ������ �˻��߱� ������ 
	// ���⼭�� �����Ͱ� �������� �˻����� �ʴ´�.
	ObjectID_t  TargetOID   = pPacket->getTargetObjectID();
	ObjectID_t  ItemOID     = pPacket->getItemObjectID();
	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	Creature*   pPC         = pGamePlayer->getCreature();
	Zone*       pZone       = pPC->getZone();
	Creature*   pTargetPC  = pZone->getCreature(TargetOID);

	// NoSuch����. by sigi. 2002.5.2
	if (pTargetPC==NULL) return;

	Ousters*    pSender    = dynamic_cast<Ousters*>(pPC);

	TradeManager* pTradeManager = pZone->getTradeManager();
	Assert(pTradeManager != NULL);

	// ��ȯ ��� �߰��� �������� �����͸� ����.
	CoordInven_t X, Y;
	Inventory*   pInventory     = pSender->getInventory();
	Item*        pItem          = pInventory->findItemOID(ItemOID, X, Y);

	// ������ �������� ���ٸ� �翬�� �� �̻� ó���� �Ұ����ϴ�.
	if (pItem == NULL)
	{
		pTradeManager->cancelTrade(pPC);
		executeError(pPacket, pPlayer, GC_TRADE_ERROR_CODE_REMOVE_ITEM);
		return;
	}

	TradeInfo* pInfo1 = pTradeManager->getTradeInfo(pSender->getName());
	TradeInfo* pInfo2 = pTradeManager->getTradeInfo(pTargetPC->getName());

	// TradeManager���� ��ȯ ������� �� �ִ� �������� �����Ѵ�.
	//Assert(pInfo1->removeItem(pItem));
	pInfo1->removeItem(pItem);

	// ���� OK�� ���� ���¶��, Ŭ���̾�Ʈ���� ���� ��Ŷ�� ������� �Ѵ�.
	if (pInfo1->getStatus() == TRADE_FINISH)
	{
		//cout << "CGTradeRemoveItem [" << pSender->getName() << "]�� ���°� TRADE_FINISH�̹Ƿ�, ���� ��Ŷ�� �����ش�." << endl;

		// ������Ŷ�� �����ش�.
		GCTradeVerify gcTradeVerify;
		gcTradeVerify.setCode(GC_TRADE_VERIFY_CODE_REMOVE_ITEM);
		pPlayer->sendPacket(&gcTradeVerify);
	}
	else
	{
		//cout << "CGTradeRemoveItem [" << pSender->getName() << "]�� ���°� TRADE_FINISH�� �ƴϹǷ�, ���� ��Ŷ ������ �ʴ´�." << endl;
	}

	// �������� ���ϰų� �� ���, ���°� TRADE_FINISH��� 
	// TRADE_TRADING���� �ٲ���� �Ѵ�.
	pInfo1->setStatus(TRADE_TRADING);
	pInfo2->setStatus(TRADE_TRADING);

	// ���濡�Լ� ������ ������ ������ �����Ѵ�.
	GCTradeRemoveItem gcTradeRemoveItem;
	gcTradeRemoveItem.setTargetObjectID(pSender->getObjectID());
	gcTradeRemoveItem.setItemObjectID(pItem->getObjectID());

	// ���濡�� ������ �������� ������ �����ش�.
	Player* pTargetPlayer = pTargetPC->getPlayer();
	pTargetPlayer->sendPacket(&gcTradeRemoveItem);

#endif

	__END_DEBUG_EX __END_CATCH
}
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGTradeRemoveItemHandler::executeError (CGTradeRemoveItem* pPacket , Player* pPlayer, BYTE ErrorCode)
	 
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__
	
	GCTradeError gcTradeError;
	gcTradeError.setTargetObjectID(pPacket->getTargetObjectID());
	gcTradeError.setCode(ErrorCode);
	pPlayer->sendPacket(&gcTradeError);

#endif

	__END_DEBUG_EX __END_CATCH
}

