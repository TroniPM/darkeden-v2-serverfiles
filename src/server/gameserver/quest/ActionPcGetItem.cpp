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
// �׼��� �����Ѵ�.
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

	// �κ��丮���� ��� �����۰��� �޾ƿ´�.
	Item* pItem = pInventory->SerchItemCall( (Item::ItemClass)m_ItemClass, m_ItemType, m_ItemNum);

	// ���� �������� ������ Num�� �ʰ��� ��쿡�� ������ ������ ������ �ִٴ°� �˸���.
	// �ݵ�� �ʰ��ÿ��� ���� ������ �ִ°��̰�, �� Num�� �� ��쿡�� ���� ���Ѿ� �Ѵ�.
	if(pItem->getNum() > m_ItemNum){ 
	
	// �ʰ��Ͻ� ������ �� ����.
	pItem->setNum(pItem->getNum()-m_ItemNum);

	// Ŭ���̾�Ʈ�� �������� ����������� �Ѵ�.
	GCDeleteInventoryItem gcDeleteInventoryItem;
	gcDeleteInventoryItem.setObjectID(pItem->getObjectID());
	pPlayer->sendPacket(&gcDeleteInventoryItem);

	GCCreateItem gcCreateItem;
	// �ٽ� ����� �����ش�.
	makeGCCreateItem( &gcCreateItem, pItem, pItem->getX(), pItem->getY() );
	pPlayer->sendPacket(&gcCreateItem);

	}else if(pItem->getNum() == m_ItemNum){

	// Ŭ���̾�Ʈ�� �������� ������Ų��.
	GCDeleteInventoryItem gcDeleteInventoryItem;
	gcDeleteInventoryItem.setObjectID(pItem->getObjectID());
	pPlayer->sendPacket(&gcDeleteInventoryItem);

	// ���� ��ü������ �����ش�. 
	pInventory->deleteItem(pItem->getObjectID());

	// �αױ���� ���ƾ� ���Ŀ� ������ �α� ��� ������ �ս��� ã�Ƴ���.
	if ( pItem != NULL )
	{
			remainTraceLog( pItem, pCreature2->getName(), pCreature1->getName(), ITEM_LOG_DELETE, DETAIL_EVENTNPC);
	}
	
	// �����ϰ� �ƿ� ���ش�.
	pItem->destroy();
	SAFE_DELETE(pItem);
	}

	list<OptionType_t> optionTypeList;

	// ���� �Ǵ� �������� �޾ƿ´�.
	Item* pGItem = g_pItemFactoryManager->createItem( m_GItemClass, m_GItemType, optionTypeList );
	// ���� �Ǵ� �������� ������ �����Ǿ����� ��� �������־�� �Ѵ�.
	if(m_GItemNum > 0){pGItem->setNum(m_GItemNum);}
	Assert( pGItem != NULL );
	
	_TPOINT pt;

	// ����ǿ��� ������ �̹� ����߱⶧���� �κ��丮�� �ڸ��� �ִ��� ���θ� �ľ��Ѵ�.
	if (!pInventory->getEmptySlot(pGItem, pt))
	{
		// ConditionHasInvenSpace ����ǰ� �ݵ�� �Բ� ��߸� �Ѵ�.
		throw Error("ActionPcGetItem: ���� ConditionHasInvenSpace�� ���� ����. �κ��丮�� �ڸ�����.");
	}

	// �̺κ��� ���� �����ϴ� �����ۿ� ����Ѵ�.
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

	// Ŭ���̾�Ʈ�� ������ �߰��Ǿ����� �˸���.
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
