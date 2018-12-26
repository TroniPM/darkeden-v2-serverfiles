////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionPcGetItem.cpp
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include "ActionOriginalDeleteGetItem.h"
#include "Creature.h"
#include "PlayerCreature.h"
#include "GamePlayer.h"
#include "ItemFactoryManager.h"
#include "Inventory.h"
#include "ItemUtil.h"
#include "Zone.h"
#include "PacketUtil.h"

#include "Gpackets/GCCreateItem.h"
#include "Gpackets/GCDeleteInventoryItem.h"

////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////
void ActionOriginalDeleteGetItem::read (PropertyBuffer & propertyBuffer)
    
{
    __BEGIN_TRY

	try 
	{
		m_ItemClass = (Item::ItemClass)propertyBuffer.getPropertyInt("ItemClass");
		m_ItemType = (ItemType_t)propertyBuffer.getPropertyInt("ItemType");
		m_ItemNum = (ItemNum_t)propertyBuffer.getPropertyInt("ItemNum");
	} 
	catch (NoSuchElementException & nsee)
	{
		throw Error(nsee.toString());
	}
	
    __END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// �׼��� �����Ѵ�.
////////////////////////////////////////////////////////////////////////////////
void ActionOriginalDeleteGetItem::execute (Creature * pCreature1 , Creature * pCreature2) 
	
{
	__BEGIN_TRY

	Assert(pCreature2 != NULL);
	Assert(pCreature2->isPC());

	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature2);
	Assert( pPC != NULL );

	Player* pPlayer = pCreature2->getPlayer();
	Assert( pPlayer != NULL );

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pCreature2->getPlayer());
	Assert( pGamePlayer != NULL );

	Inventory* pInventory = pPC->getInventory();
	Assert( pInventory != NULL );
	cout << " ���� ���� ����! 01" << endl;
	// �κ��丮���� ��� ������?��?�޾ƿ´�.
	Item* pItem = pInventory->SerchItemCall( (Item::ItemClass)m_ItemClass, m_ItemType, m_ItemNum);

	cout << " ���� ���� ����! 0" << endl;
	// ���� �������� ������ Num�� �ʰ��� ��쿡�� ������ ������ ������ �ִٴ°� �˸���.
	// �ݵ�� �ʰ��ÿ��� ���� ������ �ִ°��̰�, �� Num�� �� ��쿡�� ���� ���Ѿ� �Ѵ�.
	if(pItem->getNum() > m_ItemNum){ 
	
	cout << " ���� ���� ����! 1" << endl;
	// �ʰ��Ͻ� ������ �� ����.
	//decreaseItemNum(pItem, pInventory, pCreature2->getName(), STORAGE_INVENTORY, 0, pItem->getX(), pItem->getY());
	pItem->setNum(pItem->getNum() - m_ItemNum); // ����?��?������ �ϳ� ���δ�.

	char pField[80];
	sprintf(pField, "Num=%d", pItem->getNum());
	pItem->tinysave(pField);

	cout << " ���� ���� ����! 2" << endl;
	// Ŭ���̾�Ʈ�� �������� ����������� �Ѵ�.
	GCDeleteInventoryItem gcDeleteInventoryItem;
	gcDeleteInventoryItem.setObjectID(pItem->getObjectID());
	pPlayer->sendPacket(&gcDeleteInventoryItem);

						CoordInven_t X = -1, Y;
						pPC->getInventory()->findItemOID( pItem->getObjectID(), X, Y );
						Assert( X != -1 );

	GCCreateItem gcCreateItem;
	// �ٽ� ����� �����ش�.
	makeGCCreateItem( &gcCreateItem, pItem, X, Y );
	pPlayer->sendPacket(&gcCreateItem);

	}else if(pItem->getNum() == m_ItemNum){

	// ���� ��ü������ �����ش�. 
	pInventory->deleteItem(pItem->getObjectID());
	
	// �����ϰ� �ƿ� ���ش�.
	pItem->destroy();

	// Ŭ���̾�Ʈ�� �������� ������Ų��.
	GCDeleteInventoryItem gcDeleteInventoryItem;
	gcDeleteInventoryItem.setObjectID(pItem->getObjectID());
	pPlayer->sendPacket(&gcDeleteInventoryItem);
	}
	//SAFE_DELETE(pItem);
	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string ActionOriginalDeleteGetItem::toString () const 
	throw ()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "ActionOriginalDeleteGetItem("
	    << ")";

	return msg.toString();

	__END_CATCH
}
