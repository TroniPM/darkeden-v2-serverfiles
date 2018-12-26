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
// 액션을 실행한다.
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
	cout << " 여긴 문제 없음! 01" << endl;
	// 인벤토리에서 재료 아이템?だ?받아온다.
	Item* pItem = pInventory->SerchItemCall( (Item::ItemClass)m_ItemClass, m_ItemType, m_ItemNum);

	cout << " 여긴 문제 없음! 0" << endl;
	// 조건 아이템의 갯수가 Num값 초과일 경우에는 아이템 갯수만 변동이 있다는걸 알린다.
	// 반드시 초과시에만 갯수 변동이 있는것이고, 딱 Num값 일 경우에는 삭제 시켜야 한다.
	if(pItem->getNum() > m_ItemNum){ 
	
	cout << " 여긴 문제 없음! 1" << endl;
	// 초과일시 아이템 값 변동.
	//decreaseItemNum(pItem, pInventory, pCreature2->getName(), STORAGE_INVENTORY, 0, pItem->getX(), pItem->getY());
	pItem->setNum(pItem->getNum() - m_ItemNum); // 아이?邦?갯수를 하나 줄인다.

	char pField[80];
	sprintf(pField, "Num=%d", pItem->getNum());
	pItem->tinysave(pField);

	cout << " 여긴 문제 없음! 2" << endl;
	// 클라이언트에 아이템을 삭제시켜줘야 한다.
	GCDeleteInventoryItem gcDeleteInventoryItem;
	gcDeleteInventoryItem.setObjectID(pItem->getObjectID());
	pPlayer->sendPacket(&gcDeleteInventoryItem);

						CoordInven_t X = -1, Y;
						pPC->getInventory()->findItemOID( pItem->getObjectID(), X, Y );
						Assert( X != -1 );

	GCCreateItem gcCreateItem;
	// 다시 재생성 시켜준다.
	makeGCCreateItem( &gcCreateItem, pItem, X, Y );
	pPlayer->sendPacket(&gcCreateItem);

	}else if(pItem->getNum() == m_ItemNum){

	// 서버 자체에서도 없애준다. 
	pInventory->deleteItem(pItem->getObjectID());
	
	// 안전하게 아예 없앤다.
	pItem->destroy();

	// 클라이언트에 아이템을 삭제시킨다.
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
