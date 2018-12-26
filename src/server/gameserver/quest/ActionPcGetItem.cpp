////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionPcGetItem.cpp
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "ActionPcGetItem.h"
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
void ActionPcGetItem::read (PropertyBuffer & propertyBuffer)
    
{
    __BEGIN_TRY

	try 
	{
		m_ItemClass = (Item::ItemClass)propertyBuffer.getPropertyInt("ItemClass");
		m_ItemType = (ItemType_t)propertyBuffer.getPropertyInt("ItemType");
		m_ItemNum = (ItemNum_t)propertyBuffer.getPropertyInt("ItemNum");
		m_GItemClass = (Item::ItemClass)propertyBuffer.getPropertyInt("GItemClass");
		m_GItemType = (ItemType_t)propertyBuffer.getPropertyInt("GItemType");
		m_GItemNum = (ItemNum_t)propertyBuffer.getPropertyInt("GItemNum");
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
void ActionPcGetItem::execute (Creature * pCreature1 , Creature * pCreature2) 
	
{
	__BEGIN_TRY

	Assert(pCreature2 != NULL);
	Assert(pCreature2->isPC());

	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature2);
	Assert( pPC != NULL );

	Player* pPlayer = pCreature2->getPlayer();
	Assert( pPlayer != NULL );

	Inventory* pInventory = pPC->getInventory();
	Assert( pInventory != NULL );

	// 인벤토리에서 재료 아이템값을 받아온다.
	Item* pItem = pInventory->SerchItemCall( (Item::ItemClass)m_ItemClass, m_ItemType, m_ItemNum);

	// 조건 아이템의 갯수가 Num값 초과일 경우에는 아이템 갯수만 변동이 있다는걸 알린다.
	// 반드시 초과시에만 갯수 변동이 있는것이고, 딱 Num값 일 경우에는 삭제 시켜야 한다.
	if(pItem->getNum() > m_ItemNum){ 
	
	// 초과일시 아이템 값 변동.
	pItem->setNum(pItem->getNum()-m_ItemNum);

	// 클라이언트에 아이템을 삭제시켜줘야 한다.
	GCDeleteInventoryItem gcDeleteInventoryItem;
	gcDeleteInventoryItem.setObjectID(pItem->getObjectID());
	pPlayer->sendPacket(&gcDeleteInventoryItem);

	GCCreateItem gcCreateItem;
	// 다시 재생성 시켜준다.
	makeGCCreateItem( &gcCreateItem, pItem, pItem->getX(), pItem->getY() );
	pPlayer->sendPacket(&gcCreateItem);

	}else if(pItem->getNum() == m_ItemNum){

	// 클라이언트에 아이템을 삭제시킨다.
	GCDeleteInventoryItem gcDeleteInventoryItem;
	gcDeleteInventoryItem.setObjectID(pItem->getObjectID());
	pPlayer->sendPacket(&gcDeleteInventoryItem);

	// 서버 자체에서도 없애준다. 
	pInventory->deleteItem(pItem->getObjectID());

	// 로그기록이 남아야 차후에 아이템 로그 기록 추적시 손쉽게 찾아낸다.
	if ( pItem != NULL )
	{
			remainTraceLog( pItem, pCreature2->getName(), pCreature1->getName(), ITEM_LOG_DELETE, DETAIL_EVENTNPC);
	}
	
	// 안전하게 아예 없앤다.
	pItem->destroy();
	SAFE_DELETE(pItem);
	}

	list<OptionType_t> optionTypeList;

	// 지급 되는 아이템을 받아온다.
	Item* pGItem = g_pItemFactoryManager->createItem( m_GItemClass, m_GItemType, optionTypeList );
	// 지급 되는 아이템의 갯수가 설정되어있을 경우 설정해주어야 한다.
	if(m_GItemNum > 0){pGItem->setNum(m_GItemNum);}
	Assert( pGItem != NULL );
	
	_TPOINT pt;

	// 컨디션에서 조건을 이미 통과했기때문에 인벤토리에 자리가 있는지 여부만 파악한다.
	if (!pInventory->getEmptySlot(pGItem, pt))
	{
		// ConditionHasInvenSpace 컨디션과 반드시 함께 써야만 한다.
		throw Error("ActionPcGetItem: 제발 ConditionHasInvenSpace랑 같이 쓰자. 인벤토리에 자리없다.");
	}

	// 이부분은 새로 지급하는 아이템에 사용한다.
	CoordInven_t X = pt.x;
	CoordInven_t Y = pt.y;

	pPC->getZone()->getObjectRegistry().registerObject( pGItem );
	pInventory->addItem( X, Y, pGItem);
	pGItem->create( pPC->getName(), STORAGE_INVENTORY, 0, X, Y );

	if ( pGItem != NULL && pGItem->isTraceItem() )
	{
		remainTraceLog( pGItem, "ActionPcGetItem", pCreature2->getName(), ITEM_LOG_CREATE, DETAIL_EVENTNPC);
		remainTraceLogNew( pGItem, pCreature2->getName(), ITL_GET, ITLD_EVENTNPC , pCreature2->getZone()->getZoneID() );
	}

	// 클라이언트에 선물이 추가되었음을 알린다.
	GCCreateItem gcCreateItem;
	makeGCCreateItem( &gcCreateItem, pGItem, X, Y );
	pPlayer->sendPacket(&gcCreateItem);

	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string ActionPcGetItem::toString () const 
	throw ()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "ActionPcGetItem("
	    << ")";

	return msg.toString();

	__END_CATCH
}
