
////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionTakeOutGoods.cpp
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "ActionTakeOutGoods.h"
#include "PlayerCreature.h"
#include "GoodsInventory.h"
#include "NPC.h"
#include "GamePlayer.h"
#include "VariableManager.h"

#include "Gpackets/GCNPCResponse.h"
#include "Gpackets/GCGoodsList.h"

////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////
void ActionTakeOutGoods::read (PropertyBuffer & propertyBuffer)
    throw (Error)
{
    __BEGIN_TRY

	try 
	{
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
void ActionTakeOutGoods::execute (Creature * pCreature1 , Creature * pCreature2) 
	throw (Error)
{
	__BEGIN_TRY

	Assert(pCreature1 != NULL);
	Assert(pCreature2 != NULL);
	Assert(pCreature1->isNPC());
	Assert(pCreature2->isPC());

	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>( pCreature2 );
	Assert( pPC != NULL );

	if ( g_pVariableManager->getVariable( CAN_BUY_SHOP )==0 )
	{
		GCNPCResponse gcNPCResponse;
		gcNPCResponse.setCode( NPC_RESPONSE_CANNOT_BUY );
		pPC->getPlayer()->sendPacket( &gcNPCResponse );
		return;
	}

	GoodsInventory::ListItem& iList = pPC->getGoodsInventory()->getGoods();

	GoodsInventory::ListItemItr itr = iList.begin();
	GoodsInventory::ListItemItr endItr = iList.end();

	int count = 0;
	GCGoodsList gcGoodsList;

	for ( ; itr != endItr ; ++itr )
	{
		if ( count++ >= MAX_GOODS_LIST ) break;

		Item* pItem = (*itr).m_pItem;
		
		GoodsInfo* pGI = new GoodsInfo;
		pGI->objectID = pItem->getObjectID();
		pGI->itemClass = (BYTE)pItem->getItemClass();
		pGI->itemType = pItem->getItemType();
		pGI->grade = pItem->getGrade();
		pGI->optionType = pItem->getOptionTypeList();
		pGI->optionType2 = pItem->getOptionTypeList2();
		pGI->num = pItem->getNum();
		pGI->silver = pItem->getSilver();
		pGI->enchantLevel = pItem->getEnchantLevel();
		pGI->HeroOption = pItem->getHeroOption();
		pGI->HeroOptionAttr = pItem->getHeroOptionAttr();
		if ( pItem->isTimeLimitItem() )
		{
			if ( pItem->getHour() == 0 ) pGI->timeLimit = 1;
			else pGI->timeLimit = pItem->getHour() * 3600;
		}
		else
			pGI->timeLimit = 0;

		gcGoodsList.addGoodsInfo( pGI );

//		cout << pGI->toString() << endl;
	}

	pPC->getPlayer()->sendPacket( &gcGoodsList );

	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string ActionTakeOutGoods::toString () const 
	throw ()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "ActionTakeOutGoods("
	    << ")";

	return msg.toString();

	__END_CATCH
}
