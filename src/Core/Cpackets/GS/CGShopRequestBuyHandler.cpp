//////////////////////////////////////////////////////////////////////////////
// Filename    : CGShopRequestBuyHandler.cpp
// Written By  : �輺��
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGShopRequestBuy.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
	#include "NPC.h"
	#include "Slayer.h"
	#include "Vampire.h"
	#include "ItemInfo.h"
	#include "ItemInfoManager.h"
	#include "ItemFactoryManager.h"
	#include "PriceManager.h"
	#include "Tile.h"
	#include "ParkingCenter.h"
	#include "ItemUtil.h"
	#include "LogClient.h"
	#include "ZoneUtil.h"
	#include "CastleInfoManager.h"
	#include "Utility.h"

	#include "item/Key.h"
	#include "item/Potion.h"
	#include "item/Magazine.h"

	#include "Gpackets/GCShopBuyOK.h"
	#include "Gpackets/GCShopBuyFail.h"
	#include "Gpackets/GCShopSold.h"

	#include "SystemAvailabilitiesManager.h"
	#include "GuildManager.h"

	#include <stdio.h>
#endif

//////////////////////////////////////////////////////////////////////////////
// �÷��̾ ���ϴ� ������ �Ĵ� NPC�� �� �������� �ִ���
// Ȯ���ϰ�, �Ϲ� �����۰� ���� ����Ŭ ó���κ����� �б��Ѵ�.
//////////////////////////////////////////////////////////////////////////////
void CGShopRequestBuyHandler::execute (CGShopRequestBuy* pPacket , Player* pPlayer)
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__
	
	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	// ��Ŷ ������ �̾Ƴ���.
	ObjectID_t      NPCID       = pPacket->getObjectID();
	ShopRackType_t  shopType    = pPacket->getShopType();
	BYTE            shopIndex   = pPacket->getShopIndex();
	ItemNum_t       itemNum     = pPacket->getItemNum();
	GamePlayer*     pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	Creature*       pNPCBase    = NULL;

	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pGamePlayer->getCreature());
	Assert(pPC != NULL);

	Zone* pZone = pPC->getZone();
	Assert(pZone != NULL);

	if ( shopType == SHOP_RACK_MYSTERIOUS )
	{
		SYSTEM_ASSERT( SYSTEM_GAMBLE );
	}

	//try 
	//{ 

	// NoSuch����. by sigi. 2002.5.2
	pNPCBase = pZone->getCreature(NPCID); 
	//}	
	if (pNPCBase==NULL)//catch (NoSuchElementException) 
	{ 
		GCShopBuyFail gcShopBuyFail;
		gcShopBuyFail.setCode(GC_SHOP_BUY_FAIL_NPC_NOT_EXIST);
		gcShopBuyFail.setAmount(0);
		pPlayer->sendPacket(&gcShopBuyFail);
		return;
	}

	if (!pNPCBase->isNPC())
	{
		GCShopBuyFail gcShopBuyFail;
		gcShopBuyFail.setCode(GC_SHOP_BUY_FAIL_NOT_NPC);
		gcShopBuyFail.setAmount(0);
		pPlayer->sendPacket(&gcShopBuyFail);
		return;
	}

	NPC* pNPC = dynamic_cast<NPC*>(pNPCBase);

	/*
	// ������ ������ �ִ��� ������ üũ��
	for (int i=0; i<=2; i++)
	{
		for (int j=0; j<20; j++)
		{
			cout << (int)pNPC->isExistShopItem(i, j) << " ";
		}

		cout << endl;
	}
	*/

	if (pNPC->getShopType() == SHOPTYPE_NORMAL)
	{
		// �÷��̾ �����ϰ��� �ϴ� �������� NPC�� ������ �ִ��� �˻�
		if (pNPC->isExistShopItem(shopType, shopIndex) == false) 
		{
			GCShopBuyFail gcShopBuyFail;
			gcShopBuyFail.setCode(GC_SHOP_BUY_FAIL_ITEM_NOT_EXIST);
			gcShopBuyFail.setAmount(0);
			pPlayer->sendPacket(&gcShopBuyFail);
			return;
		}

		Item* pItem = pNPC->getShopItem(shopType, shopIndex);

		if ( pItem->getItemClass() == Item::ITEM_CLASS_TRAP_ITEM )
		{
			if( !g_pGuildManager->isGuildMaster ( pPC->getGuildID(), pPC ) || !pPC->isFlag( Effect::EFFECT_CLASS_SIEGE_DEFENDER ) )
			{
				GCShopBuyFail gcShopBuyFail;
				gcShopBuyFail.setCode(GC_SHOP_BUY_FAIL_ITEM_NOT_EXIST);
				gcShopBuyFail.setAmount(0);
				pPlayer->sendPacket(&gcShopBuyFail);
				return;
			}
		}

		// ������ ������ ������������ �˻�
		if (itemNum < 1 || itemNum > ItemMaxStack[pItem->getItemClass()])
		{
			throw ProtocolException("CGShopRequestBuyHandler::execute() : ������ ���� ����!");
		}

		// ������ ������ 2�� �̻��̶�� �������� ������������ �˻�
		// ���� �� �ִ� �������� �ƴ϶�� ������ 1�� ������ �ش�.
		if (itemNum > 1 && !isStackable(pItem->getItemClass()))
			pPacket->setItemNum(1);

		if (pItem->getItemClass() == Item::ITEM_CLASS_MOTORCYCLE) executeMotorcycle(pPacket, pPlayer);
		else executeNormal(pPacket, pPlayer);
	}

///////////////////////////////////////////////////////////////////////
// 2001�� ũ�������� �̺�Ʈ�� ���ؼ� ���� �Լ��̴�.
// 2002�� ��̳� �̺�Ʈ�� ���ؼ� �����. 
// XMAS_EVENT���� STAR_EVENT�� �����Ǿ�� �� ������ ����
//  2002.5.2 ��ȫâ(changaya@metrotech.co.kr)
//////////////////////////////////////////////////////////////////////
#ifdef __XMAS_EVENT_CODE__
	else if (pNPC->getShopType() == SHOPTYPE_EVENT)
	{
		// �÷��̾ �����ϰ��� �ϴ� �������� NPC�� ������ �ִ��� �˻�
		if (pNPC->isExistShopItem(shopType, shopIndex) == false) 
		{
			GCShopBuyFail gcShopBuyFail;
			gcShopBuyFail.setCode(GC_SHOP_BUY_FAIL_ITEM_NOT_EXIST);
			gcShopBuyFail.setAmount(0);
			pPlayer->sendPacket(&gcShopBuyFail);
			return;
		}

		// ������ ������ ������������ �˻�
		if (itemNum != 1) 
			throw ProtocolException("CGShopRequestBuyHandler::execute() : ������ ���� ����!");

		executeEvent(pPacket, pPlayer);
	}
#endif

	//cout << "Buy ok" << endl;

#endif

	__END_DEBUG_EX __END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// �Ϲ� �������� ������ ó���Ѵ�.
//////////////////////////////////////////////////////////////////////////////
void CGShopRequestBuyHandler::executeNormal (CGShopRequestBuy* pPacket , Player* pPlayer)
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	ObjectID_t      NPCID       = pPacket->getObjectID();
	ShopRackType_t  shopType    = pPacket->getShopType();
	BYTE            shopIndex   = pPacket->getShopIndex();
	ItemNum_t       itemNum     = pPacket->getItemNum();
	Coord_t         x           = pPacket->getX();
	Coord_t         y           = pPacket->getY();
	GamePlayer*     pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	Creature*       pCreature   = pGamePlayer->getCreature();
	PlayerCreature* pPC         = dynamic_cast<PlayerCreature*>(pCreature);
	Zone*           pZone       = pPC->getZone();
	NPC*            pNPC        = dynamic_cast<NPC*>(pZone->getCreature(NPCID));
	Gold_t			itemTax		= 0;

	// NoSuch����. by sigi. 2002.5.2
	if (pNPC==NULL) return;

	Item*           pItem       = pNPC->getShopItem(shopType, shopIndex);
	Price_t         itemMoney;
	bool 			bMysteriousRack = (shopType==SHOP_RACK_MYSTERIOUS);

	// Mysterious item�� ���� ����� �ٸ���.
	if (bMysteriousRack)
	{
		//cout << pPacket->toString().c_str() << endl;
		itemMoney = g_pPriceManager->getMysteriousPrice(pItem->getItemClass(), pCreature);
		//cout << "CGShopRequestBuyHandler::MysteriousItem Price = " << itemMoney << endl;
	}
	else
	{
		itemMoney = g_pPriceManager->getPrice(pItem, pNPC->getMarketCondSell(), shopType, pPC) * itemNum;
		//cout << "CGShopRequestBuyHandler::normalItem Price = " << itemMoney << endl;
	}

	if ( pNPC->getTaxingCastleZoneID() != 0 )
	{
		int itemTaxRatio = pNPC->getTaxRatio( pPC );
		if (itemTaxRatio > 100)
		{
//			int NewItemMoney = getPercentValue((int)itemMoney, itemTaxRatio);
			int NewItemMoney = (int)(itemMoney * (itemTaxRatio/100.0));
			itemTax = ( NewItemMoney - itemMoney );

			itemMoney = NewItemMoney;
		}
	}

	Item::ItemClass IClass     	 	= pItem->getItemClass();
	ItemType_t      IType   	    = pItem->getItemType();
	const list<OptionType_t>& OType = pItem->getOptionTypeList();
	pItem->setHeroOption(0);
	pItem->setSilver(0);
	pItem->setEnchantLevel(0);

	Inventory* pInventory  = pPC->getInventory();
	Gold_t     playerMoney = pPC->getGold();

	if (playerMoney < itemMoney)
	{
		GCShopBuyFail gcShopBuyFail;
		gcShopBuyFail.setCode(GC_SHOP_BUY_FAIL_NOT_ENOUGH_MONEY);
		gcShopBuyFail.setAmount(0);
		pPlayer->sendPacket(&gcShopBuyFail);

		//cout << "Not Enough Money for Mysterious Item" << endl;

		return;
	}
	
	// mysterious item�� �����ع�����.
	if (bMysteriousRack)
	{
		if (pZone->isPremiumZone() || pZone->isPayPlay())
		{
			pItem = getRandomMysteriousItem( pCreature, IClass );
		}
		else
		{
			// premium zone�� �ƴϸ� gamble level�� 30���� �����Ѵ�.
			pItem = getRandomMysteriousItem( pCreature, IClass, 30 );
		}

		Assert(pItem!=NULL);
		(pZone->getObjectRegistry()).registerObject(pItem);
	}

	// ���� �����̳�, źâ ���� ��쿡�� ������ ������ ������ �ְ� ����...
	if (isStackable(pItem))
	{
		pItem->setNum(itemNum);
	}
	else
	{
		pItem->setNum(1);
	}

	if (!pInventory->canAddingEx(x, y, pItem))
	{
		GCShopBuyFail gcShopBuyFail;
		gcShopBuyFail.setCode(GC_SHOP_BUY_FAIL_NOT_ENOUGH_SPACE);
		gcShopBuyFail.setAmount(0);
		pPlayer->sendPacket(&gcShopBuyFail);

		// mysterious item�� ������ getRandomMysteriousItem()�� ���ؼ�
		// �����Ǿ��� ������ ������� �Ѵ�.
		if (bMysteriousRack) SAFE_DELETE(pItem);

		//cout << "Can't Add to Inventory" << endl;

		return;
	}

	if ( pItem != NULL ) pItem->whenPCTake( pPC );

	// �÷��̾ �� �������� ����� �������̶�� ���� ������ �ø���.
	if (shopType == SHOP_RACK_SPECIAL)
	{
		pNPC->increaseShopVersion(shopType);
	}

	// �÷��̾��� ���� ���δ�.
	//pPC->setGoldEx(playerMoney - itemMoney);

	// by sigi. 2002.9.4
	pPC->decreaseGoldEx(itemMoney);
	filelog("Tax.log", "%s �� %s ���� %u ��ŭ�� �������� �½��ϴ�.", pPC->getName().c_str(), pNPC->getName().c_str(), itemTax);
	g_pCastleInfoManager->increaseTaxBalance( pNPC->getTaxingCastleZoneID(), itemTax );

	//cout << "addItemEx" << endl;

	Item* pReturnItem = pInventory->addItemEx(x, y, pItem);
	if (pReturnItem == pItem)
	{
		//cout << "add ok" << endl;
		// pReturnItem�� pItem�� ���ٴ� ���� �������� ���̴� �������� 
		// �ƴϾ��ٴ� ���̴�.


		// ������ ItemID�� �״�� �����Ѵ�. 
		// ItemID�� 0�̸�.. create()�Ҷ� �ٽ� ItemID�� �޴´�.
		// by sigi. 2002.10.28
		pItem->create(pPC->getName(), STORAGE_INVENTORY, 0, x, y, pItem->getItemID());
		// �ܼ��� create�� �θ��� DB���� ������ ���� ���� ���� 1���� �����.
		// �׷��Ƿ� �ٽ� ���̺긦 �ҷ��� ?������?������ ��������� �Ѵ�.
		//pItem->save(pPC->getName(), STORAGE_INVENTORY, 0, x, y);

		// ������ �ٷ� �����ϵ��� create�� �����ߴ�.
		// item���� ����ȭ. by sigi. 2002.5.13

		// OK ��Ŷ�� ������.
		GCShopBuyOK OKPacket;
		OKPacket.setObjectID(NPCID);
		OKPacket.setShopVersion(pNPC->getShopVersion(shopType));
		OKPacket.setItemObjectID(pItem->getObjectID());
		OKPacket.setItemClass(pItem->getItemClass());
		OKPacket.setItemType(pItem->getItemType());
		OKPacket.setOptionType(pItem->getOptionTypeList());
		OKPacket.setDurability(pItem->getDurability());
		OKPacket.setItemNum(pItem->getNum());
		OKPacket.setSilver(pItem->getSilver());
		OKPacket.setGrade(pItem->getGrade());
		OKPacket.setEnchantLevel(pItem->getEnchantLevel());
		OKPacket.setHeroOption(pItem->getHeroOption());
		OKPacket.setPrice(playerMoney-itemMoney);
		pPlayer->sendPacket(&OKPacket);

		log(LOG_BUY_ITEM, pPC->getName(), "", pItem->toString());
	}
	else
	{
		//cout << "pile ok" << endl;
		log(LOG_BUY_ITEM, pPC->getName(), "", pItem->toString());

		// pReturnItem�� pItem�� �ٸ��ٴ� ���� �������� 
		// ���̴� �������̾��ٴ� ���̴�. �׷��Ƿ� ���϶�� ���� pItem�� 
		// ������ ��� �Ѵ�.
		SAFE_DELETE(pItem);
		//pReturnItem->save(pPC->getName(), STORAGE_INVENTORY, 0, x, y);
		// item���� ����ȭ. by sigi. 2002.5.13
		char pField[80];
		sprintf(pField, "Num=%d", pReturnItem->getNum());
		pReturnItem->tinysave(pField);


		// OK ��Ŷ�� ������.
		GCShopBuyOK OKPacket;
		OKPacket.setObjectID(NPCID);
		OKPacket.setShopVersion(pNPC->getShopVersion(shopType));
		OKPacket.setItemObjectID(pReturnItem->getObjectID());
		OKPacket.setItemClass(pReturnItem->getItemClass());
		OKPacket.setItemType(pReturnItem->getItemType());
		OKPacket.setOptionType(pReturnItem->getOptionTypeList());
		OKPacket.setDurability(pReturnItem->getDurability());
		OKPacket.setItemNum(pReturnItem->getNum());
		OKPacket.setSilver(pReturnItem->getSilver());
		OKPacket.setGrade(pReturnItem->getGrade());
		OKPacket.setEnchantLevel(pReturnItem->getEnchantLevel());
		OKPacket.setHeroOption(pReturnItem->getHeroOption());
		OKPacket.setPrice(playerMoney-itemMoney);
		pPlayer->sendPacket(&OKPacket);
	}

	// ItemTrace �α׸� �����
	if ( pItem != NULL && pItem->isTraceItem() )
	{
		remainTraceLog( pItem, pNPC->getName(), pCreature->getName(), ITEM_LOG_CREATE, DETAIL_SHOPBUY);
	}
	//cout << "send OK" << endl;

	// mysterious item�� �ƴ� ���..
	if (!bMysteriousRack)
	{
		pNPC->removeShopItem(shopType, shopIndex);
	}

	if (shopType == SHOP_RACK_NORMAL)
	{
		// �ȸ� �������� ��� �������̶�� ���� Ÿ��, Ŭ������ �������� �����Ѵ�.
		Item* pNewItem = g_pItemFactoryManager->createItem(IClass, IType, OType);
		Assert(pNewItem != NULL);
		(pZone->getObjectRegistry()).registerObject(pNewItem);
		pNPC->insertShopItem(shopType, shopIndex, pNewItem);
	}
	else if (bMysteriousRack)
	{
		// mysterious item�� ���� ������ �״�� �θ� �ȴ�.
		//cout << "mysterious item" << endl;
	}
	else
	{
		// �ȸ� �������� ��� �������� �ƴ϶��,
		// ��ó�� �÷��̾�鿡�� ������ ������ �ȷȴٴ� ����� �˷���� �Ѵ�.
		int CenterX = pNPC->getX();
		int CenterY = pNPC->getY();
		GCShopSold soldpkt;
		soldpkt.setObjectID(NPCID);
		soldpkt.setShopVersion(pNPC->getShopVersion(shopType));
		soldpkt.setShopType(shopType);
		soldpkt.setShopIndex(shopIndex);

		try
		{
			for (int zx=CenterX-5; zx<=CenterX+5; zx++)
			{
				for (int zy=CenterY-5; zy<=CenterY+5; zy++)
				{
					// �ٿ�带 �Ѿ�� �ʴ°� üũ
					if (!isValidZoneCoord(pZone, zx, zy)) continue;

					Tile & tile = pZone->getTile(zx, zy);

					// �ɾ�ٴϴ� ũ���ĸ� �˻�
					if (tile.hasCreature(Creature::MOVE_MODE_WALKING))
					{
						Creature* pNearCreature = tile.getCreature(Creature::MOVE_MODE_WALKING);
						if (pNearCreature != NULL)
						{
							// ��� �������� ������ �÷��̾��� ����
							if (pNearCreature->getObjectID() == pPC->getObjectID()) continue;
							// ���� �÷��̾��� ��Ŷ�� �����ش�.
							if (pNearCreature->isPC())
							{
								Player* pNearPlayer = pNearCreature->getPlayer();
								if (pNearPlayer != NULL) pNearPlayer->sendPacket(&soldpkt);
							}
						}
					}
					// ���ƴٴϴ� ũ���ĸ� �˻�
					if (tile.hasCreature(Creature::MOVE_MODE_FLYING))
					{
						Creature* pNearCreature = tile.getCreature(Creature::MOVE_MODE_FLYING);
						if (pNearCreature != NULL)
						{
							// ��� �������� ������ �÷��̾��� ����
							if (pNearCreature->getObjectID() == pPC->getObjectID()) continue;
							// ���� �÷��̾��� ��Ŷ�� �����ش�.
							if (pNearCreature->isPC())
							{
								Player* pNearPlayer = pNearCreature->getPlayer();
								if (pNearPlayer != NULL) pNearPlayer->sendPacket(&soldpkt);
							}
						}
					}
				} // for (ZoneCoord_t zy...) ��
			} // for (ZoneCoord_t zx...) ��
		}
		catch (Throwable& t)
		{
			filelog("shopbug_packet.log", "%s", t.toString().c_str());
		}
	} 

#endif

	__END_DEBUG_EX __END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// ���� ����Ŭ�� ������ ó���Ѵ�.
//////////////////////////////////////////////////////////////////////////////
void CGShopRequestBuyHandler::executeMotorcycle (CGShopRequestBuy* pPacket , Player* pPlayer)
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	// ��Ŷ ������ �̾Ƴ���.
	ObjectID_t      NPCID       = pPacket->getObjectID();
	ShopRackType_t  shopType    = pPacket->getShopType();
	BYTE            shopIndex   = pPacket->getShopIndex();
	ZoneCoord_t     x           = pPacket->getX();
	ZoneCoord_t     y           = pPacket->getY();
	GamePlayer*     pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	Creature*       pCreature   = pGamePlayer->getCreature();
	PlayerCreature* pPC         = dynamic_cast<PlayerCreature*>(pCreature);
	Zone*           pZone       = pPC->getZone();
	NPC*            pNPC        = dynamic_cast<NPC*>(pZone->getCreature(NPCID));

	// NoSuch����. by sigi. 2002.5.2
	if (pNPC==NULL) return;

	Item*           pItem       = pNPC->getShopItem(shopType, shopIndex);
	Price_t         itemMoney   = g_pPriceManager->getPrice(pItem, pNPC->getMarketCondSell(), shopType, pPC);
	Item::ItemClass IClass;
	ItemType_t      IType;

	Inventory* pInventory  = pPC->getInventory();
	Gold_t     playerMoney = pPC->getGold();

	list<OptionType_t> optionNULL;
	Item* pTestKey = g_pItemFactoryManager->createItem(Item::ITEM_CLASS_KEY, 0, optionNULL);
	Assert(pTestKey != NULL);

	if (playerMoney < itemMoney)
	{
		GCShopBuyFail gcShopBuyFail;
		gcShopBuyFail.setCode(GC_SHOP_BUY_FAIL_NOT_ENOUGH_MONEY);
		gcShopBuyFail.setAmount(0);
		pPlayer->sendPacket(&gcShopBuyFail);
		SAFE_DELETE(pTestKey);
		return;
	}

	if (!pInventory->canAddingEx(x, y, pTestKey))
	{
		GCShopBuyFail gcShopBuyFail;
		gcShopBuyFail.setCode(GC_SHOP_BUY_FAIL_NOT_ENOUGH_SPACE);
		gcShopBuyFail.setAmount(0);
		pPlayer->sendPacket(&gcShopBuyFail);
		SAFE_DELETE(pTestKey);
		return;
	}
	
	// �÷��̾ �� �������� ����� �������̶�� ���� ������ �ø���.
	if (shopType == SHOP_RACK_SPECIAL) pNPC->increaseShopVersion(shopType);

	// �÷��̾��� ���� ���δ�.
	//pPC->setGoldEx(playerMoney - itemMoney);
	// by sigi. 2002.9.4
	pPC->decreaseGoldEx(itemMoney);
	
	// ���� ���� ����Ŭ�� NPC�� �����忡�� ������ ������ ���δ�.
	// �۰� DB���ٰ� ���� ����Ŭ�� �ȷȴٴ� ���� ����.
	TPOINT pt = pZone->addItem(pItem, pPC->getX(), pPC->getY(), false);
	if (pt.x == -1)
	{
		// ���� ���� NPC���Լ� ��� �ȸ� ���� ����Ŭ�� �����.
		//pNPC->removeShopItem(shopType, shopIndex);

		//SAFE_DELETE(pItem);
		// ������̸� ������ ���� ���� ������. ��Ʈ... �� ��������.
		cerr << "######################################################" << endl;
		cerr << "# CRITICAL ERROR!!! Cannot add MOTORCYCLE to ZONE!!! #" << endl;
		cerr << "######################################################" << endl;
		return;
	}
	pItem->create(pPC->getName(), STORAGE_ZONE, pZone->getZoneID(), pt.x, pt.y);
	ItemID_t MotorcycleID = pItem->getItemID();

	// ���ͻ���Ŭ�� ��ŷ ���Ϳ� ����� �ش�.
	MotorcycleBox* pBox = new MotorcycleBox(dynamic_cast<Motorcycle*>(pItem), pZone, pt.x, pt.y);
	Assert(pBox != NULL);
	g_pParkingCenter->addMotorcycleBox(pBox);

	// �������� ��� ������ ���� ����Ŭ�� �´� Ű�� �����Ѵ�.
	// �۰� DB���ٰ� ���� ����Ŭ Ű�� �÷��̾�� �Ѿ�ٴ� ���� ����.
	Item* pKey = g_pItemFactoryManager->createItem(Item::ITEM_CLASS_KEY, 2, optionNULL);
	Assert(pKey != NULL);
	(pZone->getObjectRegistry()).registerObject(pKey);
	dynamic_cast<Key*>(pKey)->setTarget(MotorcycleID);
	pKey->create(pPC->getName(), STORAGE_INVENTORY, 0, x, y);

	// ���� ����Ŭ Ű�� �÷��̾��� �κ��丮�� ���Ѵ�.
	pInventory->addItemEx(x, y, pKey);

	// ���� ���� NPC���Լ� ��� �ȸ� ���� ����Ŭ�� �����.
	pNPC->removeShopItem(shopType, shopIndex);

	// OK ��Ŷ�� ������.
	GCShopBuyOK OKPacket;
	OKPacket.setObjectID(NPCID);
	OKPacket.setShopVersion(pNPC->getShopVersion(shopType));
	OKPacket.setItemObjectID(pKey->getObjectID());
	OKPacket.setItemClass(pKey->getItemClass());
	OKPacket.setItemType(pKey->getItemType());
	OKPacket.setOptionType(pKey->getOptionTypeList());
	OKPacket.setDurability(pKey->getDurability());
	OKPacket.setItemNum(1);
	OKPacket.setSilver(pKey->getSilver());
	OKPacket.setGrade(pKey->getGrade());
	OKPacket.setEnchantLevel(pKey->getEnchantLevel());
		OKPacket.setHeroOption(pItem->getHeroOption());
	OKPacket.setPrice(playerMoney-itemMoney);
	pPlayer->sendPacket(&OKPacket);

	// �ȸ� ���� ����Ŭ�� ��� ���� ����Ŭ�̶��...
	// ���� Ÿ��, Ŭ������ ���� ����Ŭ�� �����Ѵ�.
	if (shopType == SHOP_RACK_NORMAL)
	{
		IClass = Item::ITEM_CLASS_MOTORCYCLE;
		IType  = pItem->getItemType();
		const list<OptionType_t>& OType  = pItem->getOptionTypeList();
		Item* pNewItem = g_pItemFactoryManager->createItem(IClass, IType, OType);
		Assert(pNewItem != NULL);
		(pZone->getObjectRegistry()).registerObject(pNewItem);
		pNPC->insertShopItem(shopType, shopIndex, pNewItem);
	}
	else if (shopType == SHOP_RACK_MYSTERIOUS)
	{
	}
	else
	{
		// �ȸ� ���� ����Ŭ�� ��� ���� ����Ŭ�� �ƴ϶�� ��ó�� �÷��̾�鿡��
		// ������ ���� ����Ŭ�� �ȷȴٴ� ����� �˷���� �Ѵ�.
		
		int         CenterX       = pNPC->getX();
		int         CenterY       = pNPC->getY();
		Creature*   pNearCreature = NULL;
		Player*     pNearPlayer   = NULL;
		GCShopSold  soldpkt;

		soldpkt.setObjectID(NPCID);
		soldpkt.setShopVersion(pNPC->getShopVersion(shopType));
		soldpkt.setShopType(shopType);
		soldpkt.setShopIndex(shopIndex);

		try
		{
			for (int zx=CenterX-5; zx<=CenterX+5; zx++)
			{
				for (int zy=CenterY-5; zy<=CenterY+5; zy++)
				{
					// �ٿ�带 �Ѿ�� �ʴ°� üũ
					if (!isValidZoneCoord(pZone, zx, zy)) continue;

					Tile & tile = pZone->getTile(zx, zy);

					if (tile.hasCreature(Creature::MOVE_MODE_WALKING)) 
					{
						// �ɾ�ٴϴ� ũ���ĸ� �˻�
						pNearCreature = tile.getCreature(Creature::MOVE_MODE_WALKING);
						if (pNearCreature != NULL)
						{
							// ��� �������� ������ �÷��̾��� ����
							if (pNearCreature->getObjectID() == pPC->getObjectID()) continue;
							// ���� �÷��̾��� ��Ŷ�� �����ش�.
							if (pNearCreature->isPC())
							{
								pNearPlayer = pNearCreature->getPlayer();
								if (pNearPlayer != NULL) pNearPlayer->sendPacket(&soldpkt);
							}
						}
					}
					if (tile.hasCreature(Creature::MOVE_MODE_FLYING)) 
					{
						// ���ƴٴϴ� ũ���ĸ� �˻�
						pNearCreature = tile.getCreature(Creature::MOVE_MODE_FLYING);
						if (pNearCreature != NULL)
						{
							// ��� �������� ������ �÷��̾��� ����
							if (pNearCreature->getObjectID() == pPC->getObjectID()) continue;
							// ���� �÷��̾��� ��Ŷ�� �����ش�.
							if (pNearCreature->isPC())
							{
								pNearPlayer = pNearCreature->getPlayer();
								if (pNearPlayer != NULL) pNearPlayer->sendPacket(&soldpkt);
							}
						}
					}
				} // for (ZoneCoord_t zy...) ��
			} // for (ZoneCoord_t zx...) ��
		}
		catch (Throwable& t)
		{
			filelog("shopbug_packet.log", "%s", t.toString().c_str());
		}
	} // if (shopType == SHOP_RACK_NORMAL) else ��

	SAFE_DELETE(pTestKey);

#endif

	__END_DEBUG_EX __END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// �̺�Ʈ �������� ������ ó���Ѵ�.
//////////////////////////////////////////////////////////////////////////////
void CGShopRequestBuyHandler::executeEvent(CGShopRequestBuy* pPacket , Player* pPlayer)
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

#ifdef __XMAS_EVENT_CODE__

	//cout << "CGShopRequestBuy::executeChildrenEvent() : BEGIN" << endl;

	ObjectID_t      NPCID       = pPacket->getObjectID();
	ShopRackType_t  shopType    = pPacket->getShopType();
	BYTE            shopIndex   = pPacket->getShopIndex();
	ItemNum_t       itemNum     = pPacket->getItemNum();
	Coord_t         x           = pPacket->getX();
	Coord_t         y           = pPacket->getY();
	GamePlayer*     pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	Creature*       pCreature   = pGamePlayer->getCreature();
	PlayerCreature* pPC         = dynamic_cast<PlayerCreature*>(pCreature);
	Zone*           pZone       = pPC->getZone();
	NPC*            pNPC        = dynamic_cast<NPC*>(pZone->getCreature(NPCID));

	// NoSuch����. by sigi. 2002.5.2
	if (pNPC==NULL) return;

	Item*           pItem       = pNPC->getShopItem(shopType, shopIndex);
	Item::ItemClass IClass      = pItem->getItemClass();
	ItemType_t      IType       = pItem->getItemType();
	const list<OptionType_t>& OType  = pItem->getOptionTypeList();

	Inventory* pInventory  = pPC->getInventory();
	Gold_t     playerMoney = pPC->getGold();
	XMAS_STAR  star;

	// �̺�Ʈ�� �������� �̺�Ʈ ������ ���Ѵ�.
	g_pPriceManager->getStarPrice(pItem, star);

	//cout << "����� �ϴ� ������:" << endl << pItem->toString() << endl;
	//cout << "����� �ϴ� �������� ����:" << endl
	//	<< "COLOR:" << star.color << ",AMOUNT:" << star.amount << endl;

	// ���� �����̳�, źâ ���� ��쿡�� ������ ������ ������ �ְ� ����...
	// ��� ?̺��?�����ۿ��� �����̳� źâ�� ���ԵǾ� ���� ������...
	switch (pItem->getItemClass())
	{
		case Item::ITEM_CLASS_POTION:
			dynamic_cast<Potion*>(pItem)->setNum(itemNum);
			break;
		case Item::ITEM_CLASS_MAGAZINE:
			dynamic_cast<Magazine*>(pItem)->setNum(itemNum);
			break;
		default:
			break;
	}

	// �� �κп��� �ش��ϴ� ���ݸ�ŭ�� ���� ������ �ִ����� üũ�Ѵ�.
	if (!pInventory->hasEnoughStar(star))
	{
		//cout << "�÷��̾�� �ش��ϴ� ��ŭ�� ���� ������ ���� ���մϴ�." << endl;

		GCShopBuyFail gcShopBuyFail;
		gcShopBuyFail.setCode(GC_SHOP_BUY_FAIL_NOT_ENOUGH_MONEY);
		gcShopBuyFail.setAmount(0);
		pPlayer->sendPacket(&gcShopBuyFail);
		return;
	}

	//cout << "�÷��̾�� �ش��ϴ� ��ŭ �̻��� ���� ������ �ֽ��ϴ�." << endl;

	// Ȥ�ö� �ڸ��� ���ٸ�...
	if (!pInventory->canAddingEx(x, y, pItem))
	{
		//cout << "�κ��丮�� �ڸ��� �����ϴ�." << endl;

		GCShopBuyFail gcShopBuyFail;
		gcShopBuyFail.setCode(GC_SHOP_BUY_FAIL_NOT_ENOUGH_SPACE);
		gcShopBuyFail.setAmount(0);
		pPlayer->sendPacket(&gcShopBuyFail);
		return;
	}

	// �÷��̾ �� �������� ����� �������̶�� ���� ������ �ø���.
	if (shopType == SHOP_RACK_SPECIAL)
	{
		pNPC->increaseShopVersion(shopType);
	}

	// �� �κп��� �÷��̾��� ���� ���δ�.
	pInventory->decreaseStar(star);

	//cout << "�÷��̾��� ���� �ٿ����ϴ�." << endl;

	Item* pReturnItem = pInventory->addItemEx(x, y, pItem);
	if (pReturnItem == pItem)
	{
		// pReturnItem�� pItem�� ���ٴ� ���� �������� ���̴� �������� 
		// �ƴϾ��ٴ� ���̴�.
		pItem->create(pPC->getName(), STORAGE_INVENTORY, 0, x, y);
		// �ܼ��� create�� �θ��� DB���� ������ ���� ���� ���� 1���� �����.
		// �׷��Ƿ� �ٽ� ���̺긦 �ҷ��� �������� ������ ��������� �Ѵ�.
		//pItem->save(pPC->getName(), STORAGE_INVENTORY, 0, x, y);

		// item�� create���� ������ �����ϵ��� �ٲ��.
        // item���� ����ȭ. by sigi. 2002.5.13
		        
		// OK ��Ŷ�� ������.
		GCShopBuyOK OKPacket;
		OKPacket.setObjectID(NPCID);
		OKPacket.setShopVersion(pNPC->getShopVersion(shopType));
		OKPacket.setItemObjectID(pItem->getObjectID());
		OKPacket.setItemClass(pItem->getItemClass());
		OKPacket.setItemType(pItem->getItemType());
		OKPacket.setOptionType(pItem->getOptionTypeList());
		OKPacket.setDurability(pItem->getDurability());
		OKPacket.setItemNum(pItem->getNum());
		OKPacket.setSilver(pItem->getSilver());
		OKPacket.setGrade(pItem->getGrade());
		OKPacket.setEnchantLevel(pItem->getEnchantLevel());
		OKPacket.setHeroOption(pItem->getHeroOption());
		OKPacket.setPrice(playerMoney);
		pPlayer->sendPacket(&OKPacket);

		log(LOG_BUY_ITEM, pPC->getName(), "", pItem->toString());
	}
	else
	{
		log(LOG_BUY_ITEM, pPC->getName(), "", pItem->toString());

		// pReturnItem�� pItem�� �ٸ��ٴ� ���� �������� 
		// ���̴� �������̾��ٴ� ���̴�. �׷��Ƿ� ���϶�� ���� pItem�� 
		// ������ ��� �Ѵ�.
		SAFE_DELETE(pItem);
		//pReturnItem->save(pPC->getName(), STORAGE_INVENTORY, 0, x, y);
		// item���� ����ȭ. by sigi. 2002.5.13
		char pField[80];
		sprintf(pField, "Num=%d", pReturnItem->getNum());
		pReturnItem->tinysave(pField);


		// OK ��Ŷ�� ������.
		GCShopBuyOK OKPacket;
		OKPacket.setObjectID(NPCID);
		OKPacket.setShopVersion(pNPC->getShopVersion(shopType));
		OKPacket.setItemObjectID(pReturnItem->getObjectID());
		OKPacket.setItemClass(pReturnItem->getItemClass());
		OKPacket.setItemType(pReturnItem->getItemType());
		OKPacket.setOptionType(pReturnItem->getOptionTypeList());
		OKPacket.setDurability(pReturnItem->getDurability());
		OKPacket.setItemNum(pReturnItem->getNum());
		OKPacket.setSilver(pReturnItem->getSilver());
		OKPacket.setGrade(pReturnItem->getGrade());
		OKPacket.setEnchantLevel(pReturnItem->getEnchantLevel());
		OKPacket.setHeroOption(pReturnItem->getHeroOption());
		OKPacket.setPrice(playerMoney);
		pPlayer->sendPacket(&OKPacket);
	}

	pNPC->removeShopItem(shopType, shopIndex);

	if (shopType == SHOP_RACK_NORMAL)
	{
		// �ȸ� �������� ��� �������̶�� ���� Ÿ��, Ŭ������ �������� �����Ѵ�.
		Item* pNewItem = g_pItemFactoryManager->createItem(IClass, IType, OType);
		Assert(pNewItem != NULL);
		(pZone->getObjectRegistry()).registerObject(pNewItem);
		pNPC->insertShopItem(shopType, shopIndex, pNewItem);
	}
	else if (shopType == SHOP_RACK_MYSTERIOUS)
	{
	}
	else
	{
		// �ȸ� �������� ��� �������� �ƴ϶��,
		// ��ó�� �÷��̾�鿡�� ������ ������ �ȷȴٴ� ����� �˷���� �Ѵ�.
		int CenterX = pNPC->getX();
		int CenterY = pNPC->getY();
		GCShopSold soldpkt;
		soldpkt.setObjectID(NPCID);
		soldpkt.setShopVersion(pNPC->getShopVersion(shopType));
		soldpkt.setShopType(shopType);
		soldpkt.setShopIndex(shopIndex);

		//VSRect rect(0, 0, pZone->getWidth()-1, pZone->getHeight()-1);

		try
		{
			for (int zx=CenterX-5; zx<=CenterX+5; zx++)
			{
				for (int zy=CenterY-5; zy<=CenterY+5; zy++)
				{
					// �ٿ�带 �Ѿ�� �ʴ°� üũ
					if (!isValidZoneCoord(pZone, zx, zy)) continue;

					Tile & tile = pZone->getTile(zx, zy);

					// �ɾ�ٴϴ� ũ���ĸ� �˻�
					if (tile.hasCreature(Creature::MOVE_MODE_WALKING))
					{
						Creature* pNearCreature = tile.getCreature(Creature::MOVE_MODE_WALKING);
						if (pNearCreature != NULL)
						{
							// ��� �������� ������ �÷��̾��� ����
							if (pNearCreature->getObjectID() == pPC->getObjectID()) continue;
							// ���� �÷��̾��� ��Ŷ�� �����ش�.
							if (pNearCreature->isPC())
							{
								Player* pNearPlayer = pNearCreature->getPlayer();
								if (pNearPlayer != NULL) pNearPlayer->sendPacket(&soldpkt);
							}
						}
					}
					// ���ƴٴϴ� ũ���ĸ� �˻�
					if (tile.hasCreature(Creature::MOVE_MODE_FLYING))
					{
						Creature* pNearCreature = tile.getCreature(Creature::MOVE_MODE_FLYING);
						if (pNearCreature != NULL)
						{
							// ��� �������� ������ �÷��̾��� ����
							if (pNearCreature->getObjectID() == pPC->getObjectID()) continue;
							// ���� �÷��̾��� ��Ŷ�� �����ش�.
							if (pNearCreature->isPC())
							{
								Player* pNearPlayer = pNearCreature->getPlayer();
								if (pNearPlayer != NULL) pNearPlayer->sendPacket(&soldpkt);
							}
						}
					}
				} // for (ZoneCoord_t zy...) ��
			} // for (ZoneCoord_t zx...) ��
		}
		catch (Throwable& t)
		{
			filelog("shopbug_packet.log", "%s", t.toString().c_str());
		}
	} 

	//cout << "CGShopRequestBuy::executeEvent() : END" << endl;

#endif
#endif

	__END_DEBUG_EX __END_CATCH
}

