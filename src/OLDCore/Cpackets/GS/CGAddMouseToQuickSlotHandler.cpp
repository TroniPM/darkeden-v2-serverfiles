//////////////////////////////////////////////////////////////////////////////
// Filename    : CGAddMouseToQuickSlotHandler.cc
// Written By  : elca@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CGAddMouseToQuickSlot.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
	#include "Zone.h"
	#include "Slayer.h"
	#include "Ousters.h"
	#include "Inventory.h"
	#include "Item.h"
	#include "ItemUtil.h"
	#include "item/Belt.h"
	#include "item/OustersArmsband.h"

	#include "Gpackets/GCCannotAdd.h"
	#include <stdio.h>
#endif

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGAddMouseToQuickSlotHandler::execute (CGAddMouseToQuickSlot* pPacket , Player* pPlayer)
	throw (ProtocolException, Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	GamePlayer*    pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	Creature*      pCreature   = pGamePlayer->getCreature();
	bool           Success     = false;

	if (pCreature->isSlayer())
	{
		Slayer*        pSlayer    = dynamic_cast<Slayer*>(pCreature);
		InventorySlot* pExtraSlot = pSlayer->getExtraInventorySlot();
		Item*          pItem      = pExtraSlot->getItem();

		if (pItem == NULL)
		{
			GCCannotAdd _GCCannotAdd;
			_GCCannotAdd.setObjectID(pPacket->getObjectID());
			pPlayer->sendPacket(&_GCCannotAdd);
			return;
		}

		ObjectID_t      ItemObjectID = pItem->getObjectID();
		SlotID_t        SlotID       = pPacket->getSlotID();
		Item::ItemClass IClass       = pItem->getItemClass();

		// �������� ObjectID�� ��ġ�ϴ��� üũ�Ѵ�.
		if (ItemObjectID != pPacket->getObjectID()) 
		{
			GCCannotAdd _GCCannotAdd;
			_GCCannotAdd.setObjectID(pPacket->getObjectID());
			pPlayer->sendPacket(&_GCCannotAdd);
			return;
		}

		// ��Ʈ�� �԰� ���� �ʴٸ� ��Ʈ���� �������� ���� ���� ����.
		if (!pSlayer->isWear(Slayer::WEAR_BELT))
		{
			GCCannotAdd _GCCannotAdd;
			_GCCannotAdd.setObjectID(pPacket->getObjectID());
			pPlayer->sendPacket(&_GCCannotAdd);
			return;
		}

		// ���ǵ� �ƴϰ�, źâ�� �ƴ϶�� ���� ���� ����.
		if (IClass != Item::ITEM_CLASS_POTION && IClass != Item::ITEM_CLASS_MAGAZINE && IClass != Item::ITEM_CLASS_EVENT_ETC && IClass != Item::ITEM_CLASS_KEY)
		{
			GCCannotAdd _GCCannotAdd;
			_GCCannotAdd.setObjectID(pPacket->getObjectID());
			pPlayer->sendPacket(&_GCCannotAdd);
			return;
		}
		if ( IClass == Item::ITEM_CLASS_EVENT_ETC && pItem->getItemType() < 14 )
		{
			GCCannotAdd _GCCannotAdd;
			_GCCannotAdd.setObjectID(pPacket->getObjectID());
			pPlayer->sendPacket(&_GCCannotAdd);
			return;
		}

		Item*      pBelt          = pSlayer->getWearItem(Slayer::WEAR_BELT);
		Inventory* pBeltInventory = ((Belt*)pBelt)->getInventory();

		if (pBeltInventory->canAdding(SlotID, 0,  pItem)) 
		{
			// ���� ��Ʈ�� �ִ� Item�� �޾ƿ´�.
			Item* pPrevItem = pBeltInventory->getItem(SlotID, 0);

			// ������ �ڸ��� �������� �ִٸ�...
			if (pPrevItem != NULL)
			{
				// �������� ������ ���� �������̶��...
				if (isStackable(pItem) && isSameItem(pItem, pPrevItem))
				{
					int MaxStack = ItemMaxStack[pItem->getItemClass()];

					if (pItem->getNum() + pPrevItem->getNum() > MaxStack) 
					{
						ItemNum_t CurrentNum = pPrevItem->getNum();
						ItemNum_t AddNum     = pItem->getNum();
						ItemNum_t NewNum	 = AddNum + CurrentNum - MaxStack;

						pPrevItem->setNum(MaxStack);
						pItem->setNum(NewNum);
						pBeltInventory->increaseNum(MaxStack - CurrentNum);
						pBeltInventory->increaseWeight(pItem->getWeight()* (MaxStack - CurrentNum));
						//pPrevItem->save(pSlayer->getName(), STORAGE_BELT, pBelt->getItemID(), SlotID, 0);
						// item���� ����ȭ. by sigi. 2002.5.13
						char pField[80];
						sprintf(pField, "Num=%d, Storage=%d, StorageID=%lu, X=%d", MaxStack, STORAGE_BELT, pBelt->getItemID(), SlotID);
						pPrevItem->tinysave(pField);

						//pItem->save(pSlayer->getName(), STORAGE_EXTRASLOT, 0, 0, 0);
						// item���� ����ȭ. by sigi. 2002.5.13
						sprintf(pField, "Num=%d, Storage=%d", NewNum, STORAGE_EXTRASLOT);
						pItem->tinysave(pField);


						Success = true;
					} 
					else // ���ڰ� 9���� ���� ���� ��.
					{
						pSlayer->deleteItemFromExtraInventorySlot();
						pPrevItem->setNum(pPrevItem->getNum() + pItem->getNum());
						pBeltInventory->increaseNum(pItem->getNum());
						pBeltInventory->increaseWeight(pItem->getWeight()* pItem->getNum());
						//pPrevItem->save(pSlayer->getName(), STORAGE_BELT , pBelt->getItemID(), SlotID, 0);
						// item���� ����ȭ. by sigi. 2002.5.13
						char pField[80];
						sprintf(pField, "Num=%d, Storage=%d, StorageID=%lu, X=%d", pPrevItem->getNum(), STORAGE_BELT, pBelt->getItemID(), SlotID);
						pPrevItem->tinysave(pField);

						pItem->destroy();
						SAFE_DELETE(pItem);
						Success = true;
					}
				} 
				else // Ŭ������ Ÿ���� ���� ������
				{
					// ���콺�� �޷��ִ� �����۰� ��Ʈ�� �ִ� �������� �����Ѵ�.
					pSlayer->deleteItemFromExtraInventorySlot();
					pBeltInventory->deleteItem(pPrevItem->getObjectID());

					// ���� ��ġ�� �ٲ� �ش�.
					pSlayer->addItemToExtraInventorySlot(pPrevItem);
					pBeltInventory->addItem(SlotID , 0 , pItem);

					// DB���ٰ� ������ �Ѵ�.
					//pPrevItem->save(pSlayer->getName(), STORAGE_EXTRASLOT, 0, 0, 0);
					// item���� ����ȭ. by sigi. 2002.5.13
					char pField[80];
					sprintf(pField, "Storage=%d", STORAGE_EXTRASLOT);
					pPrevItem->tinysave(pField);

					//pItem->save(pSlayer->getName(), STORAGE_BELT , pBelt->getItemID(), SlotID, 0);
					// item���� ����ȭ. by sigi. 2002.5.13
					sprintf(pField, "Storage=%d, StorageID=%lu, X=%d", STORAGE_BELT, pBelt->getItemID(), SlotID);
					pItem->tinysave(pField);


					Success = true;
				}
			} 
			else // ������ �ƹ��� ������ �������� ������.
			{
				// Inventory�� Ư�� �������� �ִ´�.
				pBeltInventory->addItem(SlotID, 0 , pItem);

				// �ֱ⿡ �����ϸ� ���콺�� �޷��ִ� �������� ���ش�.
				pSlayer->deleteItemFromExtraInventorySlot();
				//pItem->save(pSlayer->getName(), STORAGE_BELT, pBelt->getItemID(), SlotID, 0);
				// item���� ����ȭ. by sigi. 2002.5.13
				char pField[80];
				sprintf(pField, "Storage=%d, StorageID=%lu, X=%d", STORAGE_BELT, pBelt->getItemID(), SlotID);
				pItem->tinysave(pField);

				Success = true;
			}
		} // end of if (pBeltInventory->canAdding(SlotID, 0,  pItem)) 
	} // if (pCreature->isSlayer())
	else if (pCreature->isOusters())
	{
		Ousters*        pOusters  = dynamic_cast<Ousters*>(pCreature);
		InventorySlot* pExtraSlot = pOusters->getExtraInventorySlot();
		Item*          pItem      = pExtraSlot->getItem();

		if (pItem == NULL)
		{
			GCCannotAdd _GCCannotAdd;
			_GCCannotAdd.setObjectID(pPacket->getObjectID());
			pPlayer->sendPacket(&_GCCannotAdd);
			return;
		}

		ObjectID_t      ItemObjectID = pItem->getObjectID();
		SlotID_t        SlotID       = pPacket->getSlotID();
		Item::ItemClass IClass       = pItem->getItemClass();

		// �������� ObjectID�� ��ġ�ϴ��� üũ�Ѵ�.
		if (ItemObjectID != pPacket->getObjectID()) 
		{
			GCCannotAdd _GCCannotAdd;
			_GCCannotAdd.setObjectID(pPacket->getObjectID());
			pPlayer->sendPacket(&_GCCannotAdd);
			return;
		}

		Ousters::WearPart part = ( SlotID > 2 ? Ousters::WEAR_ARMSBAND2 : Ousters::WEAR_ARMSBAND1 );
		if ( SlotID > 2 ) SlotID -= 3;

		// �ش� �Ͻ���尡 ����
		if (!pOusters->isWear(part)) 
		{
			GCCannotAdd _GCCannotAdd;
			_GCCannotAdd.setObjectID(pPacket->getObjectID());
			pPlayer->sendPacket(&_GCCannotAdd);
			return;
		}

		// Ǫ�ĵ� �ƴϰ�, ���������̵� �ƴ϶�� ���� ���� ����.
		if (IClass != Item::ITEM_CLASS_PUPA && IClass != Item::ITEM_CLASS_COMPOS_MEI && IClass != Item::ITEM_CLASS_EVENT_ETC )
		{
			GCCannotAdd _GCCannotAdd;
			_GCCannotAdd.setObjectID(pPacket->getObjectID());
			pPlayer->sendPacket(&_GCCannotAdd);
			return;
		}

		if ( IClass == Item::ITEM_CLASS_EVENT_ETC && pItem->getItemType() < 14 )
		{
			GCCannotAdd _GCCannotAdd;
			_GCCannotAdd.setObjectID(pPacket->getObjectID());
			pPlayer->sendPacket(&_GCCannotAdd);
			return;
		}

		Item*      pArmsband          = pOusters->getWearItem(part);
		Inventory* pArmsbandInventory = ((OustersArmsband*)pArmsband)->getInventory();

		if (pArmsbandInventory->canAdding(SlotID, 0,  pItem)) 
		{
			// ���� ��Ʈ�� �ִ� Item�� �޾ƿ´�.
			Item* pPrevItem = pArmsbandInventory->getItem(SlotID, 0);

			// ������ �ڸ��� �������� �ִٸ�...
			if (pPrevItem != NULL)
			{
				// �������� ������ ���� �������̶��...
				if (isSameItem(pItem, pPrevItem))
				{
					int MaxStack = ItemMaxStack[pItem->getItemClass()];

					if (pItem->getNum() + pPrevItem->getNum() > MaxStack) 
					{
						ItemNum_t CurrentNum = pPrevItem->getNum();
						ItemNum_t AddNum     = pItem->getNum();
						ItemNum_t NewNum	 = AddNum + CurrentNum - MaxStack;

						pPrevItem->setNum(MaxStack);
						pItem->setNum(NewNum);
						pArmsbandInventory->increaseNum(MaxStack - CurrentNum);
						pArmsbandInventory->increaseWeight(pItem->getWeight()* (MaxStack - CurrentNum));
						//pPrevItem->save(pOusters->getName(), STORAGE_BELT, pArmsband->getItemID(), SlotID, 0);
						// item���� ����ȭ. by sigi. 2002.5.13
						char pField[80];
						sprintf(pField, "Num=%d, Storage=%d, StorageID=%lu, X=%d", MaxStack, STORAGE_BELT, pArmsband->getItemID(), SlotID);
						pPrevItem->tinysave(pField);

						//pItem->save(pOusters->getName(), STORAGE_EXTRASLOT, 0, 0, 0);
						// item���� ����ȭ. by sigi. 2002.5.13
						sprintf(pField, "Num=%d, Storage=%d", NewNum, STORAGE_EXTRASLOT);
						pItem->tinysave(pField);


						Success = true;
					} 
					else // ���ڰ� 9���� ���� ���� ��.
					{
						pOusters->deleteItemFromExtraInventorySlot();
						pPrevItem->setNum(pPrevItem->getNum() + pItem->getNum());
						pArmsbandInventory->increaseNum(pItem->getNum());
						pArmsbandInventory->increaseWeight(pItem->getWeight()* pItem->getNum());
						//pPrevItem->save(pOusters->getName(), STORAGE_BELT , pArmsband->getItemID(), SlotID, 0);
						// item���� ����ȭ. by sigi. 2002.5.13
						char pField[80];
						sprintf(pField, "Num=%d, Storage=%d, StorageID=%lu, X=%d", pPrevItem->getNum(), STORAGE_BELT, pArmsband->getItemID(), SlotID);
						pPrevItem->tinysave(pField);

						pItem->destroy();
						SAFE_DELETE(pItem);
						Success = true;
					}
				} 
				else // Ŭ������ Ÿ���� ���� ������
				{
					// ���콺�� �޷��ִ� �����۰� ��Ʈ�� �ִ� �������� �����Ѵ�.
					pOusters->deleteItemFromExtraInventorySlot();
					pArmsbandInventory->deleteItem(pPrevItem->getObjectID());

					// ���� ��ġ�� �ٲ� �ش�.
					pOusters->addItemToExtraInventorySlot(pPrevItem);
					pArmsbandInventory->addItem(SlotID , 0 , pItem);

					// DB���ٰ� ������ �Ѵ�.
					//pPrevItem->save(pOusters->getName(), STORAGE_EXTRASLOT, 0, 0, 0);
					// item���� ����ȭ. by sigi. 2002.5.13
					char pField[80];
					sprintf(pField, "Storage=%d", STORAGE_EXTRASLOT);
					pPrevItem->tinysave(pField);

					//pItem->save(pOusters->getName(), STORAGE_BELT , pArmsband->getItemID(), SlotID, 0);
					// item���� ����ȭ. by sigi. 2002.5.13
					sprintf(pField, "Storage=%d, StorageID=%lu, X=%d", STORAGE_BELT, pArmsband->getItemID(), SlotID);
					pItem->tinysave(pField);


					Success = true;
				}
			} 
			else // ������ �ƹ��� ������ �������� ������.
			{
				// Inventory�� Ư�� �������� �ִ´�.
				pArmsbandInventory->addItem(SlotID, 0 , pItem);

				// �ֱ⿡ �����ϸ� ���콺�� �޷��ִ� �������� ���ش�.
				pOusters->deleteItemFromExtraInventorySlot();
				//pItem->save(pOusters->getName(), STORAGE_BELT, pArmsband->getItemID(), SlotID, 0);
				// item���� ����ȭ. by sigi. 2002.5.13
				char pField[80];
				sprintf(pField, "Storage=%d, StorageID=%lu, X=%d", STORAGE_BELT, pArmsband->getItemID(), SlotID);
				pItem->tinysave(pField);

				Success = true;
			}
		} // end of if (pArmsbandInventory->canAdding(SlotID, 0,  pItem)) 
	} // if (pCreature->isOusters())

	// QuickSlot�� �ִ� ���� ���� �Ͽ����� ���� ��Ŷ�� ������.
	if (!Success) 
	{
		GCCannotAdd _GCCannotAdd;
		_GCCannotAdd.setObjectID(pPacket->getObjectID());
		pPlayer->sendPacket(&_GCCannotAdd);
	}

#endif	// __GAME_SERVER__

    __END_DEBUG_EX __END_CATCH

}

