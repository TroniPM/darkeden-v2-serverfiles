////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionPcGetItem.cpp
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "ActionCreateGetItemRand.h"
#include "Creature.h"
#include "PlayerCreature.h"
#include "GamePlayer.h"
#include "ItemFactoryManager.h"
#include "Inventory.h"
#include "ItemUtil.h"
#include "Zone.h"
#include "MonsterItemDrop.h"
#include "PacketUtil.h"

#include "Gpackets/GCCreateItem.h"
#include "Gpackets/GCDeleteInventoryItem.h"

////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////
void ActionCreateGetItemRand::read (PropertyBuffer & propertyBuffer)
    
{
    __BEGIN_TRY

	try 
	{
		m_ItemGroupID = (int)propertyBuffer.getPropertyInt("ItemGroupID1");
		m_ItemGroupID2 = (int)propertyBuffer.getPropertyInt("ItemGroupID2");
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
void ActionCreateGetItemRand::execute (Creature * pCreature1 , Creature * pCreature2) 
	
{
	__BEGIN_TRY
/*
	Assert(pCreature2 != NULL);
	Assert(pCreature2->isPC());

	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature2);
	Assert( pPC != NULL );

	Player* pPlayer = pCreature2->getPlayer();
	Assert( pPlayer != NULL );

	Inventory* pInventory = pPC->getInventory();
	Assert( pInventory != NULL );
	
	// ���� �Ǵ� �������� �޾ƿ´�.
	Item* pGItem = g_pMonsterItemDropManager->getPayItem( m_ItemGroupID,m_ItemGroupID2 );
		cout << "��������� �Ǵµ�...2" << endl;
	//m_ItemGroupID = 0;
	//m_ItemGroupID2 = 0;
	Assert( pGItem != NULL );
			cout << "��������� �Ǵµ�..3." << endl;
	_TPOINT pt;

	// ����ǿ��� ������ �̹� ����߱⶧���� �κ��丮�� �ڸ��� �ִ��� ���θ� �ľ��Ѵ�.
	if (!pInventory->getEmptySlot(pGItem, pt))
	{
		// ConditionHasInvenSpace ����ǰ� �ݵ�� �Բ� ��߸� �Ѵ�.
		throw Error("ActionCreateGetItemRand: ���� ConditionHasInvenSpace�� ���� ����. �κ��丮�� �ڸ�����.");
	}

	// �̺κ��� ���� �����ϴ� �����ۿ� ����Ѵ�.
	CoordInven_t X = pt.x;
	CoordInven_t Y = pt.y;

	pPC->getZone()->getObjectRegistry().registerObject( pGItem );
	pInventory->addItem( X, Y, pGItem);
	pGItem->create( pPC->getName(), STORAGE_INVENTORY, 0, X, Y );

	if ( pGItem != NULL && pGItem->isTraceItem() )
	{
		remainTraceLog( pGItem, "ActionCreateGetItemRand", pCreature2->getName(), ITEM_LOG_CREATE, DETAIL_EVENTNPC);
		remainTraceLogNew( pGItem, pCreature2->getName(), ITL_GET, ITLD_EVENTNPC , pCreature2->getZone()->getZoneID() );
	}

	// Ŭ���̾�Ʈ�� ������ �߰��Ǿ����� �˸���.
	GCCreateItem gcCreateItem;
	makeGCCreateItem( &gcCreateItem, pGItem, X, Y );
	pPlayer->sendPacket(&gcCreateItem);
*/
	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string ActionCreateGetItemRand::toString () const 
	
{
	__BEGIN_TRY

	StringStream msg;
	msg << "ActionCreateGetItemRand("
	    << ")";

	return msg.toString();

	__END_CATCH
}
