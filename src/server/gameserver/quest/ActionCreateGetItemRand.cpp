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
// 액션을 실행한다.
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
	
	// 지급 되는 아이템을 받아온다.
	Item* pGItem = g_pMonsterItemDropManager->getPayItem( m_ItemGroupID,m_ItemGroupID2 );
		cout << "여기까지는 되는데...2" << endl;
	//m_ItemGroupID = 0;
	//m_ItemGroupID2 = 0;
	Assert( pGItem != NULL );
			cout << "여기까지는 되는데..3." << endl;
	_TPOINT pt;

	// 컨디션에서 조건을 이미 통과했기때문에 인벤토리에 자리가 있는지 여부만 파악한다.
	if (!pInventory->getEmptySlot(pGItem, pt))
	{
		// ConditionHasInvenSpace 컨디션과 반드시 함께 써야만 한다.
		throw Error("ActionCreateGetItemRand: 제발 ConditionHasInvenSpace랑 같이 쓰자. 인벤토리에 자리없다.");
	}

	// 이부분은 새로 지급하는 아이템에 사용한다.
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

	// 클라이언트에 선물이 추가되었음을 알린다.
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
