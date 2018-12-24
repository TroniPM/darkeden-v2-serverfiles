//////////////////////////////////////////////////////////////////////////////
// Filename    : CGShopRequestListHandler.cpp
// Written By  : �輺��
// Description : CGShopRequestList�� �ڵ鷯�̴�.
//////////////////////////////////////////////////////////////////////////////

#include "CGShopRequestList.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
	#include "NPC.h"
	#include "PlayerCreature.h"

	#include "quest/TriggerManager.h"
	#include "quest/Trigger.h"
	#include "quest/Condition.h"
	#include "quest/Action.h"

	#include "Gpackets/GCNPCResponse.h"
	#include "Gpackets/GCShopList.h"
	#include "Gpackets/GCShopListMysterious.h"
#endif

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGShopRequestListHandler::execute(CGShopRequestList* pPacket , Player* pPlayer)
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	// ��Ŷ���� ������ �̾Ƴ���.	
	ObjectID_t     NPCID = pPacket->getObjectID();
	ShopRackType_t type  = pPacket->getRackType();

	// �Ķ���� �� ��Ŷ���� �̾Ƴ� ������ ����
	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	PlayerCreature*   pPC         = dynamic_cast<PlayerCreature*>(pGamePlayer->getCreature());
	Zone*       pZone       = pPC->getZone();
	Creature*   pNPCBase    = NULL;
	
	/*
	try
	{
		pNPCBase = pZone->getCreature(NPCID);
	}
	catch (NoSuchElementException & nsee)
	{
		pNPCBase = NULL;
	}
	*/

	// NoSuch����. by sigi. 2002.5.2
	pNPCBase = pZone->getCreature(NPCID);

	if (pNPCBase == NULL || pNPCBase->isNPC() == false)
	{
		GCNPCResponse gcNPCResponse;
		pPlayer->sendPacket(&gcNPCResponse);
		return;
	}

	NPC* pNPC = dynamic_cast<NPC*>(pNPCBase);

	if (type == SHOP_RACK_SPECIAL)
	{
		// ��ǰ�� ����Ʈ�� ��Ŷ���� �ۼ��Ѵ�.
		GCShopList pkt;
		pkt.setNPCShopType(pNPC->getShopType());
		pkt.setObjectID(NPCID);
		pkt.setShopVersion(pNPC->getShopVersion(type));
		pkt.setShopType(type);

		for (BYTE i=0; i<SHOP_RACK_INDEX_MAX; i++) 
		{
			// ������ ������ ������ ���´�.
			Item* pItem = pNPC->getShopItem(type, i);
			if (pItem != NULL) pkt.setShopItem(i, pItem);
		}

		pkt.setMarketCondBuy(pNPC->getMarketCondBuy());
//		pkt.setMarketCondSell(pNPC->getMarketCondSell());
		pkt.setMarketCondSell(pNPC->getTaxRatio(pPC));

		// ��Ŷ�� ������.
		pPlayer->sendPacket(&pkt);
	}
	else if (type == SHOP_RACK_MYSTERIOUS)
	{
		// ��ǰ�� ����Ʈ�� ��Ŷ���� �ۼ��Ѵ�.
		GCShopListMysterious pkt;
		pkt.setObjectID(NPCID);
		pkt.setShopVersion(pNPC->getShopVersion(type));
		pkt.setShopType(type);

		for (BYTE i=0; i<SHOP_RACK_INDEX_MAX; i++) 
		{
			// ������ ������ ������ ���´�.
			Item* pItem = pNPC->getShopItem(type, i);
			if (pItem != NULL)
				pkt.setShopItem(i, pItem);
		}

		pkt.setMarketCondBuy(pNPC->getMarketCondBuy());
//		pkt.setMarketCondSell(pNPC->getMarketCondSell());
		pkt.setMarketCondSell(pNPC->getTaxRatio(pPC));

		// ��Ŷ�� ������.
		pPlayer->sendPacket(&pkt);
	}
	else 
	{
		throw ProtocolException("NORMAL shop item list not allowed!!!");
	}

#endif

	__END_DEBUG_EX __END_CATCH
}
