//////////////////////////////////////////////////////////////////////////////
// Filename    : CGSilverCoatingHandler.cpp
// Written By  : �輺��
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CGSilverCoating.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
	#include "NPC.h"
	#include "Slayer.h"
	#include "Vampire.h"
	#include "ItemInfo.h"
	#include "ItemInfoManager.h"
	#include "PriceManager.h"
	#include "LogClient.h"

	#include "Gpackets/GCNPCResponse.h"
	#include <stdio.h>

#endif

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGSilverCoatingHandler::execute (CGSilverCoating* pPacket , Player* pPlayer)
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);
	
	ObjectID_t    ITEMOID      = pPacket->getObjectID();
	Creature*     pPC          = dynamic_cast<GamePlayer*>(pPlayer)->getCreature();
	bool          bSlayer      = true;
	Gold_t        playerMoney  = 0;
	Price_t       coatingPrice = 0;
	Item*         pItem        = NULL;
	Slayer*       pSlayer      = NULL;
	Vampire*      pVampire     = NULL;
	int           storage      = 0;
	int           X            = 0;
	int           Y            = 0;
	GCNPCResponse response;

	// �÷��̾ �����̾����� �����̾����� ����.
	if (pPC->isSlayer())       bSlayer = true;
	else if (pPC->isVampire()) bSlayer = false;

	// �÷��̾ �����Ϸ��� �ϴ� �������� ������ �ִ��� �˻�
	if (bSlayer)
	{
		pSlayer     = dynamic_cast<Slayer*>(pPC);
		playerMoney = pSlayer->getGold();
		pItem       = pSlayer->findItemOID(ITEMOID, storage, X, Y);
	}
	else
	{
		pVampire    = dynamic_cast<Vampire*>(pPC);
		playerMoney = pVampire->getGold();
		pItem       = pVampire->findItemOID(ITEMOID, storage, X, Y);
	}

	// �������� ���ٸ� �翬�� ������ �� ����.
	if (pItem == NULL)
	{
		response.setCode(NPC_RESPONSE_SILVER_COATING_FAIL_ITEM_NOT_EXIST);
		pPlayer->sendPacket(&response);
		return;
	}

	// �����Ϸ��� �������� ���õ� �� ���� �������̶��...
	switch (pItem->getItemClass())
	{
		case Item::ITEM_CLASS_BLADE:
		case Item::ITEM_CLASS_SWORD:
		case Item::ITEM_CLASS_CROSS:
		case Item::ITEM_CLASS_MACE:
			break;
		default:
			response.setCode(NPC_RESPONSE_SILVER_COATING_FAIL_ITEM_TYPE);
			pPlayer->sendPacket(&response);
			return;
	}

	coatingPrice = g_pPriceManager->getSilverCoatingPrice(pItem);
	if (coatingPrice > playerMoney)
	{
		response.setCode(NPC_RESPONSE_SILVER_COATING_FAIL_MONEY);
		pPlayer->sendPacket(&response);
		return;
	}

	// �ִ� �� ���ݷ��� ���ͼ�... �����Ѵ�.
	ItemInfo* pItemInfo = g_pItemInfoManager->getItemInfo(pItem->getItemClass(), pItem->getItemType());
	pItem->setSilver(pItemInfo->getMaxSilver());

	// ���� ���δ�.
	if (bSlayer)
	{
		//pSlayer->setGoldEx(playerMoney - coatingPrice);

		// by sigi. 2002.9.4
		pSlayer->decreaseGoldEx(coatingPrice);
		//log(LOG_REPAIR_ITEM, pSlayer->getName(), "", pItem->toString());
	}
	else
	{
		//pVampire->setGoldEx(playerMoney - coatingPrice);

		// by sigi. 2002.9.4
		pVampire->decreaseGoldEx(coatingPrice);
		//log(LOG_REPAIR_ITEM, pVampire->getName(), "", pItem->toString());
	}

	// silver�� �����ϸ� �ȴ�.
	// ������ ���� ����ȭ. by sigi. 2002.5.13
	char pField[80];
	sprintf(pField, "Silver=%d", pItem->getSilver());
	pItem->tinysave(pField);

	// �������� ������ �����ߴٴ� ������ DB���ٰ� �������ش�.
	// �� �и��� STORAGE_STASH�� ���ƿ� �� ������, 
	// �����Կ� �ִ� ���� �����Ѵٴ� ���� ���� �� �ǹǷ�,
	// �������� �ʴ´�.
	/*
	switch (storage)
	{
		case STORAGE_INVENTORY:
			pItem->save(pPC->getName(), STORAGE_INVENTORY, 0, X, Y);
			break;
		case STORAGE_GEAR:
			if (bSlayer) pItem->save(pSlayer->getName(),  STORAGE_GEAR, 0, X, 0);
			else         pItem->save(pVampire->getName(), STORAGE_GEAR, 0, X, 0);
			break;
		default:
			break;
	}
	*/

	// OK ��Ŷ�� �����ش�.
	response.setCode(NPC_RESPONSE_SILVER_COATING_OK);
	response.setParameter(playerMoney-coatingPrice);
	pPlayer->sendPacket(&response);
	
#endif

	__END_DEBUG_EX __END_CATCH
}

