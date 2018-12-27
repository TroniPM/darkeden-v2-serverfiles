////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionPcGetItem.cpp
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "ActionCreateGetItem.h"
#include "Creature.h"
#include "PlayerCreature.h"
#include "GamePlayer.h"
#include "ItemFactoryManager.h"
#include "Inventory.h"
#include "Item.h"
#include "ItemUtil.h"
#include "Treasure.h"
#include "Zone.h"
#include "StringPool.h"
#include "MonsterDropSetup.h"
#include "MonsterItemDrop.h"
#include "MonsterItemDropOption.h"
#include "VariableManager.h"
#include "ItemGradeManager.h"
#include "PacketUtil.h"
#include <list>

#include "Gpackets/GCCreateItem.h"
#include "Gpackets/GCNPCResponse.h"
#include "Gpackets/GCSystemMessage.h"
#include "Gpackets/GCDeleteInventoryItem.h"

////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////
void ActionCreateGetItem::read (PropertyBuffer & propertyBuffer)
    
{
    __BEGIN_TRY

	try 
	{
		m_ItemClass = propertyBuffer.getPropertyInt("ItemDropSetup");
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
void ActionCreateGetItem::execute (Creature * pCreature1 , Creature * pCreature2) 
	
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

	Inventory* pInventory = pPC->getInventory();

	Zone* pZone = pPC->getZone();

	TreasureList* pTreasureList = NULL;
	Item* pItem1 = NULL;

	Creature::CreatureClass ownerCreatureClass;
	ownerCreatureClass = pCreature2->getCreatureClass();

	MonsterDropSetup* pMonsterItemDrop = g_pMonsterDropSetupManager->getMonsterDropSetup(m_ItemClass);

		if ( pMonsterItemDrop != NULL && pMonsterItemDrop->IsDrop() )
		{
			if (ownerCreatureClass == Creature::CREATURE_CLASS_SLAYER)
			{
				pTreasureList = g_pMonsterItemDropManager->getMonsterItemDrop(pMonsterItemDrop->getSlayerRandomDrop1())->getSlayerTreasureList();
			}
			else if (ownerCreatureClass == Creature::CREATURE_CLASS_VAMPIRE)
			{
				pTreasureList = g_pMonsterItemDropManager->getMonsterItemDrop(pMonsterItemDrop->getSlayerRandomDrop1())->getVampireTreasureList();
			}
			else if (ownerCreatureClass == Creature::CREATURE_CLASS_OUSTERS)
			{
				pTreasureList = g_pMonsterItemDropManager->getMonsterItemDrop(pMonsterItemDrop->getSlayerRandomDrop1())->getOustersTreasureList();
			}
		}

		if ( pTreasureList != NULL )
		{

			const list<Treasure*>& treasures = pTreasureList->getTreasures();
			list<Treasure*>::const_iterator itr = treasures.begin();

			ITEM_TEMPLATE it;

			for (; itr != treasures.end(); itr++)
			{

				Treasure* pTreasure = (*itr);
				ITEM_TEMPLATE it;

				it.ItemClass  = Item::ITEM_CLASS_MAX;
				it.ItemType   = 0;

				it.NextOptionRatio = g_pVariableManager->getChiefMonsterRareItemPercent();
				it.NextOptionRatio += pMonsterItemDrop->getItemRareOptionBounsRatio();

				pTreasure->setRndItemOptionMax(g_pMonsterItemDropManager->getMonsterItemDrop(pMonsterItemDrop->getSlayerRandomDrop1())->getOptionCount());

				if ( pTreasure->getRandomItem(&it) )
				{
					pItem1 = g_pItemFactoryManager->createItem(it.ItemClass, it.ItemType, it.OptionType);
					pItem1->setGrade( ItemGradeManager::Instance().getRandomGrade() );
						
						if(pMonsterItemDrop->getItemSetOptionSetup() && pMonsterItemDrop->getItemSetOptionRatio() > rand()%100000)
						{
						pItem1->setOptionType2( it.OptionType2 );
						}
					
					pItem1->setHeroOption( 0 );
					pItem1->setHeroOptionAttr( 0 );
						
						if(pMonsterItemDrop->getItemSetHeroOptionSetup() && pMonsterItemDrop->getItemSetHeroOptionRatio() > rand()%100000){
							int HeroOptionSetting = rand()%13;
							int HeroOption = g_pMonsterItemDropOptionManager->getRandomOption(HeroOptionSetting);
							int HeroOptionAttrSetting = g_pMonsterItemDropOptionManager->getRandomItem(HeroOptionSetting);
							if(HeroOptionAttrSetting != 0 )
							{
								pItem1->setHeroOption( HeroOption+1 );
								pItem1->setHeroOptionAttr( HeroOptionAttrSetting );
							}
						}

					Assert(pItem1 != NULL);
				}
			}
		}
	if (pItem1 != NULL)
	{
	TPOINT pt;
	pZone->registerObject(pItem1);

	if(pInventory->addItem(pItem1, pt))
	{

		pItem1->create(pPC->getName(), STORAGE_INVENTORY, 0, pt.x, pt.y);
		GCCreateItem gcCreateItem;
		makeGCCreateItem( &gcCreateItem, pItem1, pt.x, pt.y );

		pPlayer->sendPacket(&gcCreateItem);

		// ItemTraceLog 를 남긴다
		if ( pItem1 != NULL && pItem1->isTraceItem() )
		{
			remainTraceLog( pItem1, pCreature1->getName(), pCreature2->getName(), ITEM_LOG_CREATE, DETAIL_EVENTNPC);
		}

		GCSystemMessage gcSystemMessage;
		gcSystemMessage.setMessage( g_pStringPool->getString( STRID_TRADE_SUCCESS ) );
		pPlayer->sendPacket(&gcSystemMessage);
	}
	else
	{
		GCSystemMessage gcSystemMessage;
		gcSystemMessage.setMessage( g_pStringPool->getString( STRID_NOT_ENOUGH_INVENTORY_SPACE ) );
		pPlayer->sendPacket(&gcSystemMessage);
	}
	}
	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string ActionCreateGetItem::toString () const 
	
{
	__BEGIN_TRY

	StringStream msg;
	msg << "ActionCreateGetItem("
	    << ")";

	return msg.toString();

	__END_CATCH
}
