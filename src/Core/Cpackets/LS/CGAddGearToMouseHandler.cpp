//////////////////////////////////////////////////////////////////////////////
// Filename    : CGAddGearToMouseHandler.cc
// Written By  : elca@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CGAddGearToMouse.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
	#include "Zone.h"
	#include "Slayer.h"
	#include "Vampire.h"
	#include "Ousters.h"
	#include "Inventory.h"
	#include "Item.h"
	#include "ItemInfo.h"
	#include "ItemInfoManager.h"

	#include "Gpackets/GCCannotAdd.h"
#endif

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGAddGearToMouseHandler::execute (CGAddGearToMouse* pPacket , Player* pPlayer)
	
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	try 
	{
		GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
		Creature*   pCreature   = pGamePlayer->getCreature();
		bool        bSuccess    = false;
		SlotID_t    SlotID      = pPacket->getSlotID();

		Assert(pCreature != NULL);	

		if (pCreature->isSlayer()) 
		{
			Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);
			Assert(pSlayer != NULL);	

			// ���콺�� ������ ��� �־ �� �ǰ�,
			// �������� �κп� �������� �԰� ���� �ʾƼ��� �� �ȴ�.
			if (pSlayer->getExtraInventorySlotItem() == NULL &&
				pSlayer->isWear((Slayer::WearPart)SlotID)) 
			{
				// �����ϰ� �ִ� Item�� �޾ƿ´�.
				Item* pItem = pSlayer->getWearItem((Slayer::WearPart)SlotID);

				// �������� �ִ��� �� �������� ObjectID�� ��ġ�ϴ��� üũ�Ѵ�.
				if (pItem != NULL && pItem->getObjectID() == pPacket->getObjectID())
				{
					// �������� ����â���� ����� Mouse�� �̵���Ų��.
					// ���� ����鼭 �ɷ�ġ�� �ٿ��Ű�� ���� �������� Mouse�� �̵���Ų��.
					pSlayer->takeOffItem((Slayer::WearPart)SlotID, true, true);
					bSuccess = true;
				}
			} 
		} 
		else if (pCreature->isVampire())
		{
			Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);

			Assert(pVampire != NULL);

			// ���콺�� ������ ��� �־ �� �ǰ�,
			// �������� �κп� �������� �԰� ���� �ʾƼ��� �� �ȴ�.
			if (pVampire->getExtraInventorySlotItem() == NULL &&
				pVampire->isWear((Vampire::WearPart)SlotID))
			{
				// �����ϰ� �ִ� Item�� �޾ƿ´�.
				Item* pItem = pVampire->getWearItem((Vampire::WearPart)SlotID);

				// �������� �ִ��� �� �������� ObjectID�� ��ġ�ϴ��� üũ�Ѵ�.
				if (pItem != NULL && pItem->getObjectID() == pPacket->getObjectID()) 
				{
					// �������� ����â���� ����� Mouse�� �̵���Ų��.
					// ���� ����鼭 �ɷ�ġ�� �ٿ��Ű�� ���� �������� Mouse�� �̵���Ų��.
					pVampire->takeOffItem((Vampire::WearPart)SlotID, true, true);
					bSuccess = true;
				}
			} 
		}
		else if (pCreature->isOusters())
		{
			Ousters* pOusters = dynamic_cast<Ousters*>(pCreature);

			Assert(pOusters != NULL);

			// ���콺�� ������ ��� �־ �� �ǰ�,
			// �������� �κп� �������� �԰� ���� �ʾƼ��� �� �ȴ�.
			if (pOusters->getExtraInventorySlotItem() == NULL &&
				pOusters->isWear((Ousters::WearPart)SlotID))
			{
				// �����ϰ� �ִ� Item�� �޾ƿ´�.
				Item* pItem = pOusters->getWearItem((Ousters::WearPart)SlotID);

				// �������� �ִ��� �� �������� ObjectID�� ��ġ�ϴ��� üũ�Ѵ�.
				if (pItem != NULL && pItem->getObjectID() == pPacket->getObjectID()) 
				{
					// �������� ����â���� ����� Mouse�� �̵���Ų��.
					// ���� ����鼭 �ɷ�ġ�� �ٿ��Ű�� ���� �������� Mouse�� �̵���Ų��.
					pOusters->takeOffItem((Ousters::WearPart)SlotID, true, true);
					bSuccess = true;
				}
			} 
		}

		if (!bSuccess) 
		{
			GCCannotAdd _GCCannotAdd;
			_GCCannotAdd.setObjectID(pPacket->getObjectID());
			pPlayer->sendPacket(&_GCCannotAdd);
		}
	} 
	catch (Throwable & t) 
	{
		//cerr << t.toString();
	}

#endif	// __GAME_SERVER__

    __END_DEBUG_EX __END_CATCH
}
