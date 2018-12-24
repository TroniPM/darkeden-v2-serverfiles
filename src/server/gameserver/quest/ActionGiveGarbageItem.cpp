////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionGiveGarbageEventItem.cpp
// Written By  : excel96
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "ActionGiveGarbageEventItem.h"
#include "PlayerCreature.h"
#include "GamePlayer.h"
#include "Item.h"
#include "ItemUtil.h"
#include "Inventory.h"
#include "Zone.h"
#include "ItemFactoryManager.h"
#include "DB.h"
#include "Thread.h"
#include "StringPool.h"
#include <list>

#include "item/Key.h"

#include "Gpackets/GCCreateItem.h"
#include "Gpackets/GCNPCResponse.h"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void ActionGiveGarbageEventItem::read (PropertyBuffer & propertyBuffer)
    throw (Error)
{
    __BEGIN_TRY
    __END_CATCH
}

////////////////////////////////////////////////////////////////////////////////
// �׼��� �����Ѵ�.
////////////////////////////////////////////////////////////////////////////////
void ActionGiveGarbageEventItem::execute (Creature * pCreature1 , Creature * pCreature2) 
	throw (Error)
{
	__BEGIN_TRY

	Assert(pCreature1 != NULL);
	Assert(pCreature2 != NULL);
	Assert(pCreature1->isNPC());
	Assert(pCreature2->isPC());

	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature2);
	Assert(pPC != NULL);

	Player* pPlayer = pPC->getPlayer();
	Assert(pPlayer != NULL);

	// ���� Ŭ���̾�Ʈ�� ���� GCNPCResponse�� �����ش�.
	GCNPCResponse okpkt;
	pPlayer->sendPacket(&okpkt);

	// ������ ����Ʈ�� �������� �����Ѵٸ�...
	if (pPC->getGarbageSize() > 0)
	{
		TPOINT pt;

		Item* pItem = pPC->popItemFromGarbage();
		Assert(pItem != NULL);

		// �κ��丮�� �ڸ��� �ִٸ� �κ��丮���ٰ� ���ϰ� �÷��̾�� �˷��ش�.
		if (pInventory->addItem(pItem, pt))
		{
			pItem->save(pPC->getName(), STORAGE_INVENTORY, 0, pt.x, pt.y);

			GCCreateItem gcCreateItem;
			gcCreateItem.setObjectID(pItem->getObjectID());
			gcCreateItem.setItemClass(pItem->getItemClass());
			gcCreateItem.setItemType(pItem->getItemType());
			gcCreateItem.setOptionType(pItem->getOptionType());
			gcCreateItem.setDurability(pItem->getDurability());
			gcCreateItem.setSilver(pItem->getSilver());
			gcCreateItem.setItemNum(pItem->getNum());
			gcCreateItem.setInvenX(pt.x);
			gcCreateItem.setInvenY(pt.y);

			pPlayer->sendPacket(&gcCreateItem);

			// ItemTraceLog �� �����
			if ( pItem != NULL && pItem->isTraceItem() )
			{
				remainTraceLog( pItem, pCreature1->getName(), pCreature2->getName(), ITEM_LOG_CREATE, DETAIL_EVENTNPC);
				remainTraceLogNew( pItem, pCreature2->getName(), ITL_GET, ITLD_EVENTNPC, pCreature1->getZone()->getZoneID(), pCreature1->getX(), pCreature1->getY() );
			}
		}
		// �κ��丮�� �ڸ��� ���ٸ�, �ٽ� ������ ����Ʈ���ٰ� ���ϰ�
		// �÷��̾�� �� ����� �˷��ش�.
		else
		{
			pPC->addItemToGarbage(pItem);

			GCSystemMessage gcSystemMessage;
			gcSystemMessage.setMessage( g_pStringPool->getString( STRID_NOT_ENOUGH_INVENTORY_SPACE ) );
			pPlayer->sendPacket(&gcSystemMessage);
		}
	}
	else
	{
		GCSystemMessage gcSystemMessage;
		gcSystemMessage.setMessage( g_pStringPool->getString( STRID_ITEM_NOT_EXIST ) );
		pPlayer->sendPacket(&gcSystemMessage);
	}

	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string ActionGiveGarbageEventItem::toString () const 
	throw ()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "ActionGiveGarbageEventItem("
	    << ")";
	return msg.toString();

	__END_CATCH
}
