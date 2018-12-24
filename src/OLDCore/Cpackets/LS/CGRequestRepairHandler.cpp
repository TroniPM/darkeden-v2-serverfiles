//////////////////////////////////////////////////////////////////////////////
// Filename    : CGRequestRepairHandler.cpp
// Written By  : �輺��
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CGRequestRepair.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
	#include "NPC.h"
	#include "Slayer.h"
	#include "Vampire.h"
	#include "Ousters.h"
	#include "ItemUtil.h"
	#include "ItemInfo.h"
	#include "ItemInfoManager.h"
	#include "PriceManager.h"
	#include "LogClient.h"
	#include "ZoneUtil.h"

	#include "item/Key.h"
	#include "item/SlayerPortalItem.h"
	#include "item/OustersSummonItem.h"

	#include "Gpackets/GCNPCResponse.h"

	#include <stdio.h>
#endif

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGRequestRepairHandler::execute (CGRequestRepair* pPacket , Player* pPlayer)
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);
	
	ObjectID_t  ITEMOID     = pPacket->getObjectID();
	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	Creature*   pPC         = pGamePlayer->getCreature();
	bool        bSlayer     = false;
	bool        bVampire    = false;
	bool        bOusters    = false;
	Item*       pItem       = NULL;
	
	// �÷��̾ �����̾����� �����̾����� ����.
	if (pPC->isSlayer())       bSlayer = true;
	else if (pPC->isVampire()) bVampire = true;
	else if (pPC->isOusters()) bOusters = true;
	else throw ProtocolException("CGRequestRepairHandler::execute() : Unknown player creature!");

	if (ITEMOID == 0)
	{
		// ObjectID�� 0�̶�� ��� �������� �����ϰ��� �ϴ� ���̴�.
		executeAll(pPacket, pPlayer);
	}
	else
	{
		if (bSlayer) pItem = (dynamic_cast<Slayer*>(pPC))->findItemOID(ITEMOID);
		else if (bVampire) pItem = (dynamic_cast<Vampire*>(pPC))->findItemOID(ITEMOID);
		else if (bOusters) pItem = (dynamic_cast<Ousters*>(pPC))->findItemOID(ITEMOID);

		// �÷��̾ �������� ������ �ִٸ�
		if (pItem != NULL)
		{
			// �� �������� ���� ����Ŭ Ű���...
			if (pItem->getItemClass() == Item::ITEM_CLASS_KEY && pItem->getItemType() == 2)
			{
				executeMotorcycle(pPacket, pPlayer);
				return;
			}
			else executeNormal(pPacket, pPlayer);
		}
		else
		{
			// �������� ������, �翬�� ������ �� ����.
			GCNPCResponse response;
			response.setCode(NPC_RESPONSE_REPAIR_FAIL_ITEM_NOT_EXIST);
			pPlayer->sendPacket(&response);
		}
	}
	
#endif

	__END_DEBUG_EX __END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// �Ϲ� �������� ó���Ѵ�.
//////////////////////////////////////////////////////////////////////////////
void CGRequestRepairHandler::executeNormal (CGRequestRepair* pPacket , Player* pPlayer)
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	ObjectID_t    ITEMOID       = pPacket->getObjectID();
	Creature*     pPC           = dynamic_cast<GamePlayer*>(pPlayer)->getCreature();
	bool          bSlayer       = false;
	bool          bVampire      = false;
	bool          bOusters      = false;
	Gold_t        playerMoney   = 0;
	Price_t       repairPrice   = 0;
	Item*         pItem         = NULL;
	Slayer*       pSlayer       = NULL;
	Vampire*      pVampire      = NULL;
	Ousters*      pOusters      = NULL;
	int           storage       = 0;
	int           X             = 0;
	int           Y             = 0;
	GCNPCResponse response;

	// �÷��̾ �����̾����� �����̾����� ����.
	if (pPC->isSlayer())       bSlayer = true;
	else if (pPC->isVampire()) bVampire = true;
	else if (pPC->isOusters()) bOusters = true;

	// �÷��̾ �����Ϸ��� �ϴ� �������� ������ �ִ��� �˻�
	if (bSlayer)
	{
		pSlayer     = dynamic_cast<Slayer*>(pPC);
		playerMoney = pSlayer->getGold();
		pItem       = pSlayer->findItemOID(ITEMOID, storage, X, Y);
	}
	else if (bVampire)
	{
		pVampire    = dynamic_cast<Vampire*>(pPC);
		playerMoney = pVampire->getGold();
		pItem       = pVampire->findItemOID(ITEMOID, storage, X, Y);
	}
	else if (bOusters)
	{
		pOusters    = dynamic_cast<Ousters*>(pPC);
		playerMoney = pOusters->getGold();
		pItem       = pOusters->findItemOID(ITEMOID, storage, X, Y);
	}

	// �÷��̾ �����Ϸ��� �ϴ� �������� ������ �ִ��� 
	// �������� �˻縦 �ϱ� ������, pItem�� ���ϸ��� ����.
	// ��, ������ �� ���� ������������ �˻��Ѵ�.
	if (isRepairableItem(pItem) == false)
	{
		response.setCode(NPC_RESPONSE_REPAIR_FAIL_ITEM_TYPE);
		pPlayer->sendPacket(&response);
		return;
	}

	repairPrice = g_pPriceManager->getRepairPrice(pItem);

	if (repairPrice > playerMoney)
	{
		response.setCode(NPC_RESPONSE_REPAIR_FAIL_MONEY);
		pPlayer->sendPacket(&response);
		return;
	}

	// �����Ѵ�.
	repairItem(pItem);

	// ���� ���δ�.
	if (bSlayer)
	{
		//pSlayer->setGoldEx(playerMoney-repairPrice);
		// by sigi. 2002.9.4
		pSlayer->decreaseGoldEx(repairPrice);
		log(LOG_REPAIR_ITEM, pSlayer->getName(), "", pItem->toString());
	}
	else if (bVampire)
	{
		// by sigi. 2002.9.4
		pVampire->decreaseGoldEx(repairPrice);
		log(LOG_REPAIR_ITEM, pVampire->getName(), "", pItem->toString());
	}
	else if (bOusters)
	{
		// by sigi. 2002.9.4
		pOusters->decreaseGoldEx(repairPrice);
		log(LOG_REPAIR_ITEM, pOusters->getName(), "", pItem->toString());
	}

	// �������� �����ߴٴ� ������ DB���ٰ� �������ش�.
	// �� �и��� STORAGE_STASH�� ���ƿ� �� ������, 
	// �����Կ� �ִ� ���� �����Ѵٴ� ���� ���� �� �ǹǷ�,
	// �������� �ʴ´�.


	// item���� ����ȭ. by sigi. 2002.5.17
	if (repairPrice>0)
	{
		char pField[80];

		if (pItem->getItemClass()==Item::ITEM_CLASS_SLAYER_PORTAL_ITEM)
		{
			SlayerPortalItem* pSPItem = dynamic_cast<SlayerPortalItem*>(pItem);
			sprintf(pField, "Charge=%d", pSPItem->getCharge());
		}
		else if (pItem->getItemClass()==Item::ITEM_CLASS_OUSTERS_SUMMON_ITEM)
		{
			OustersSummonItem* pOSItem = dynamic_cast<OustersSummonItem*>(pItem);
			sprintf(pField, "Charge=%d", pOSItem->getCharge());
		}
		else
		{
			sprintf(pField, "Durability=%d", pItem->getDurability());
		}

		pItem->tinysave(pField);
	}

	/*
	// ���� �Ƶ�.. durability�� �ٲٸ� �ȴ�.
	// �ٵ�.. ItemObject�� Durability field�� ���� �͵� �ְ�
	// Charge�� �����ؾ� �ϴ� �͵� �ִ�.
	// �׷���.. �ϴ��� ��� �� �����ϴ� save�� �̿��ϵ��� �Ѵ�.
	switch (storage)
	{
		case STORAGE_INVENTORY:
		{
			pItem->save(pPC->getName(), STORAGE_INVENTORY, 0, X, Y);
		}
		break;

		case STORAGE_GEAR:
		{
			if (bSlayer) 
			{
				pItem->save(pSlayer->getName(),  STORAGE_GEAR, 0, X, 0);
			}
			else         
			{
				pItem->save(pVampire->getName(), STORAGE_GEAR, 0, X, 0);
			}
		}
		break;

		default:
			break;
	}
	*/

	// OK ��Ŷ�� �����ش�.
	response.setCode(NPC_RESPONSE_REPAIR_OK);
	response.setParameter(playerMoney-repairPrice);
	pPlayer->sendPacket(&response);

#endif

	__END_DEBUG_EX __END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// ���� ����Ŭ�� ó���Ѵ�.
//////////////////////////////////////////////////////////////////////////////
void CGRequestRepairHandler::executeMotorcycle (CGRequestRepair* pPacket , Player* pPlayer)
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	// ��Ŷ ������ �̾Ƴ���.
	ObjectID_t      ITEMOID     = pPacket->getObjectID();
	Creature*       pPC         = dynamic_cast<GamePlayer*>(pPlayer)->getCreature();
	Zone*           pZone       = pPC->getZone();
	Gold_t          playerMoney = 0;
	ZoneCoord_t     CenterX     = pPC->getX();
	ZoneCoord_t     CenterY     = pPC->getY();
	Item*           pItem       = NULL;
	bool            bSlayer     = false;
	bool            bVampire    = false;
	bool            bOusters    = false;
	GCNPCResponse   response;
	
	// �÷��̾ �����̾����� �����̾����� ����.
	if (pPC->isSlayer())       bSlayer = true;
	else if (pPC->isVampire()) bVampire = true;
	else if (pPC->isOusters()) bOusters = true;
	else throw ProtocolException("CGRequestRepairHandler::execute() : Unknown player creature!");

	// �÷��̾ �����Ϸ��� �ϴ� �������� ������ �ִ��� 
	// �������� �˻縦 �ϱ� ������, pItem�� ���ϸ��� ����.
	if (bSlayer)
	{
		pItem       = (dynamic_cast<Slayer*>(pPC))->findItemOID(ITEMOID);
		playerMoney = (dynamic_cast<Slayer*>(pPC))->getGold();
	}
	else if (bVampire)
	{
		pItem       = (dynamic_cast<Vampire*>(pPC))->findItemOID(ITEMOID);
		playerMoney = (dynamic_cast<Vampire*>(pPC))->getGold();
	}
	else if (bOusters)
	{
		pItem       = (dynamic_cast<Ousters*>(pPC))->findItemOID(ITEMOID);
		playerMoney = (dynamic_cast<Ousters*>(pPC))->getGold();
	}

	// ���� ���� ������ �˻��ؼ�, ���� ����Ŭ�� �ִ��� Ȯ���Ѵ�.
	for (ZoneCoord_t zx=CenterX-5; zx<=CenterX+5; zx++)
	{
		for (ZoneCoord_t zy=CenterY-5; zy<=CenterY+5; zy++)
		{
			if (!isValidZoneCoord(pZone, zx, zy)) continue;

			Tile & tile = pZone->getTile(zx, zy);

			if (tile.hasItem())
			{
				Item* pItemOnTile = tile.getItem();
				Assert(pItemOnTile != NULL);

				// ���� �������� Ÿ�� ���� ���� ���, ���� ����Ŭ���� Ȯ���Ѵ�.
				if (pItemOnTile->getItemClass() == Item::ITEM_CLASS_MOTORCYCLE)
				{
					DWORD    targetID     = dynamic_cast<Key*>(pItem)->getTarget();
					ItemID_t motorcycleID = pItemOnTile->getItemID();

					if (targetID == motorcycleID)
					{
						Price_t repairPrice = g_pPriceManager->getRepairPrice(pItemOnTile);

						if (repairPrice > playerMoney)
						{
							response.setCode(NPC_RESPONSE_REPAIR_FAIL_MONEY);
							pPlayer->sendPacket(&response);
							return;
						}

						// �����Ѵ�.
						repairItem(pItemOnTile);

						// �����Ѵ�.
						//pItemOnTile->save(pPC->getName(), STORAGE_ZONE, pZone->getZoneID(), zx, zy);
						// item���� ����ȭ. by sigi. 2002.5.13
						char pField[80];
						sprintf(pField, "Durability=%d", pItemOnTile->getDurability());
						pItemOnTile->tinysave(pField);


						// ���� ���δ�.
						//if (bSlayer) (dynamic_cast<Slayer*>(pPC))->setGoldEx(playerMoney-repairPrice);
						//else         (dynamic_cast<Vampire*>(pPC))->setGoldEx(playerMoney-repairPrice);

						// by sigi. 2002.9.4
						(dynamic_cast<PlayerCreature*>(pPC))->decreaseGoldEx(repairPrice);

						response.setCode(NPC_RESPONSE_REPAIR_OK);
						response.setParameter(playerMoney-repairPrice);
						pPlayer->sendPacket(&response);

						return;
					} // if (targetID == 
				} // if (itemclas == MOTORCYCLE
			}
		} // end of for (ZoneCoord_t zy=CenterY-5; zy<=CenterY+5; zy++)
	} // end of for (ZoneCoord_t zx=CenterX-5; zx<=CenterX+5; zx++)

	// FOR ������ �� ����, �̱��� �Դٴ� ���� ��ó�� ������̰� ���ٴ� ���̴�...
	// �׷��Ƿ� ���� ����Ŭ �ȱⰡ �����ߴٴ� ���� �˸���.
	response.setCode(NPC_RESPONSE_REPAIR_FAIL_ITEM_NOT_EXIST);
	pPlayer->sendPacket(&response);
	
#endif

	__END_DEBUG_EX __END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// ��� ������ �����ϱ�
//////////////////////////////////////////////////////////////////////////////
void CGRequestRepairHandler::executeAll(CGRequestRepair* pPacket , Player* pPlayer)
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	Creature*     pPC         = dynamic_cast<GamePlayer*>(pPlayer)->getCreature();
	Price_t       repairPrice = 0;
	GCNPCResponse response;

	if (pPC->isSlayer())
	{
		Slayer* pSlayer = dynamic_cast<Slayer*>(pPC);

		// ��� �������� ���� ������ ����Ѵ�.
		for (int i=0; i<Slayer::WEAR_MAX; i++)
		{
			Item* pItem = pSlayer->getWearItem((Slayer::WearPart)i);
			if (pItem != NULL)
			{
				if (i == Slayer::WEAR_RIGHTHAND && isTwohandWeapon(pItem))
				{
					// �������̰�, ���� ��� �ִ� ���Ⱑ ��� ������...
					// ���� ���ݿ� ���Խ�ų �ʿ䰡 ����.
				}
				else
				{
					repairPrice += g_pPriceManager->getRepairPrice(pItem);
				}
			}
		}

		// ���� ���ڶ�ٸ� �����Ѵ�.
		if (pSlayer->getGold() < repairPrice)
		{
			response.setCode(NPC_RESPONSE_REPAIR_FAIL_MONEY);
			pPlayer->sendPacket(&response);
			return;
		}

		// ������ �������� �����ϰ�, DB�� �����Ѵ�.
		char pField[80];

		for (int i=0; i<Slayer::WEAR_MAX; i++)
		{
			Item* pItem = pSlayer->getWearItem((Slayer::WearPart)i);
			if (pItem != NULL)
			{
				if (i == Slayer::WEAR_RIGHTHAND && isTwohandWeapon(pItem))
				{
					// �������̰�, ���� ��� �ִ� ���Ⱑ ��� ������...
					// ������ �ʿ䰡 ����.
				}
				else if ( isRepairableItem( pItem ) )
				{
					Durability_t oldDurability = pItem->getDurability();
					repairItem(pItem);
					if (pItem->getDurability() != oldDurability)
					{
						// DB ������ ���̱� ���ؼ�
						// �������� ��ȭ�� ���� ��쿡�� ���̺��Ѵ�.
						//pItem->save(pSlayer->getName(), STORAGE_GEAR, 0, i, 0);
						// item���� ����ȭ. by sigi. 2002.5.13
						sprintf(pField, "Durability=%d", pItem->getDurability());
						pItem->tinysave(pField);
					}
				}
			}
		}

		// ���� ���̰�...
		//pSlayer->setGoldEx(pSlayer->getGold() - repairPrice);

		// by sigi.2002.9.4
		pSlayer->decreaseGoldEx(repairPrice);

		// �α׸� �����.
		log(LOG_REPAIR_ITEM, pSlayer->getName(), "", "ALL");

		// OK ��Ŷ�� �����ش�.
		response.setCode(NPC_RESPONSE_REPAIR_OK);
		response.setParameter(pSlayer->getGold());
		pPlayer->sendPacket(&response);
	}
	else if (pPC->isVampire())
	{
		Vampire* pVampire = dynamic_cast<Vampire*>(pPC);

		// ��� �������� ���� ������ ����Ѵ�.
		for (int i=0; i<Vampire::VAMPIRE_WEAR_MAX; i++)
		{
			Item* pItem = pVampire->getWearItem((Vampire::WearPart)i);
			if (pItem != NULL) 
			{
				if (i == Vampire::WEAR_RIGHTHAND && isTwohandWeapon(pItem))
				{
					// ��չ���� ���ʸ� �����Ѵ�.
				}
				else
				{
					repairPrice += g_pPriceManager->getRepairPrice(pItem);
				}
			}
		}

		// ���� ���ڶ�ٸ� �����Ѵ�.
		if (pVampire->getGold() < repairPrice)
		{
			response.setCode(NPC_RESPONSE_REPAIR_FAIL_MONEY);
			pPlayer->sendPacket(&response);
			return;
		}
 
		// ������ �������� �����ϰ�, DB�� �����Ѵ�.
		char pField[80];

		for (int i=0; i<Vampire::VAMPIRE_WEAR_MAX; i++)
		{
			Item* pItem = pVampire->getWearItem((Vampire::WearPart)i);
			if (pItem != NULL)
			{
				if (i == Vampire::WEAR_RIGHTHAND && isTwohandWeapon(pItem))
				{
					// ��չ���� ���ʸ� �����Ѵ�.
				}
				else
				{
					Durability_t oldDurability = pItem->getDurability();
					repairItem(pItem);
					if (pItem->getDurability() != oldDurability)
					{
						// DB ������ ���̱� ���ؼ�
						// �������� ��ȭ�� ���� ��쿡�� ���̺��Ѵ�.
						//pItem->save(pVampire->getName(), STORAGE_GEAR, 0, i, 0);
						// item���� ����ȭ. by sigi. 2002.5.13
						sprintf(pField, "Durability=%d", pItem->getDurability());
						pItem->tinysave(pField);

					}
				}
			}
		}

		// ���� ���̰�...
		//pVampire->setGoldEx(pVampire->getGold() - repairPrice);
		// by sigi.2002.9.4
		pVampire->decreaseGoldEx(repairPrice);

		// �α׸� �����.
		log(LOG_REPAIR_ITEM, pVampire->getName(), "", "ALL");

		// OK ��Ŷ�� �����ش�.
		response.setCode(NPC_RESPONSE_REPAIR_OK);
		response.setParameter(pVampire->getGold());
		pPlayer->sendPacket(&response);
	}
	else if (pPC->isOusters())
	{
		Ousters* pOusters = dynamic_cast<Ousters*>(pPC);

		// ��� �������� ���� ������ ����Ѵ�.
		for (int i=0; i<Ousters::OUSTERS_WEAR_MAX; i++)
		{
			Item* pItem = pOusters->getWearItem((Ousters::WearPart)i);
			if (pItem != NULL) 
			{
				if (i == Ousters::WEAR_RIGHTHAND && isTwohandWeapon(pItem))
				{
					// ��չ���� ���ʸ� �����Ѵ�.
				}
				else
				{
					repairPrice += g_pPriceManager->getRepairPrice(pItem);
				}
			}
		}

		// ���� ���ڶ�ٸ� �����Ѵ�.
		if (pOusters->getGold() < repairPrice)
		{
			response.setCode(NPC_RESPONSE_REPAIR_FAIL_MONEY);
			pPlayer->sendPacket(&response);
			return;
		}
 
		// ������ �������� �����ϰ�, DB�� �����Ѵ�.
		char pField[80];

		for (int i=0; i<Ousters::OUSTERS_WEAR_MAX; i++)
		{
			Item* pItem = pOusters->getWearItem((Ousters::WearPart)i);
			if (pItem != NULL)
			{
				if (i == Ousters::WEAR_RIGHTHAND && isTwohandWeapon(pItem))
				{
					// ��չ���� ���ʸ� �����Ѵ�.
				}
				else
				{
					Durability_t oldDurability = pItem->getDurability();
					repairItem(pItem);
					if (pItem->getDurability() != oldDurability)
					{
						// DB ������ ���̱� ���ؼ�
						// �������� ��ȭ�� ���� ��쿡�� ���̺��Ѵ�.
						//pItem->save(pOusters->getName(), STORAGE_GEAR, 0, i, 0);
						// item���� ����ȭ. by sigi. 2002.5.13
						sprintf(pField, "Durability=%d", pItem->getDurability());
						pItem->tinysave(pField);

					}
				}
			}
		}

		// ���� ���̰�...
		//pOusters->setGoldEx(pOusters->getGold() - repairPrice);
		// by sigi.2002.9.4
		pOusters->decreaseGoldEx(repairPrice);

		// �α׸� �����.
		log(LOG_REPAIR_ITEM, pOusters->getName(), "", "ALL");

		// OK ��Ŷ�� �����ش�.
		response.setCode(NPC_RESPONSE_REPAIR_OK);
		response.setParameter(pOusters->getGold());
		pPlayer->sendPacket(&response);
	}

#endif

	__END_DEBUG_EX __END_CATCH
}
