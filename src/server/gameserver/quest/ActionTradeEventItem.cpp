////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionTradeEventItem.cpp
// Written By  : ��ȫâ
// Description :
////////////////////////////////////////////////////////////////////////////////
#include "ActionTradeEventItem.h"
#include "PlayerCreature.h"
#include "GamePlayer.h"
#include "Item.h"
#include "ItemUtil.h"
#include "Inventory.h"
#include "Zone.h"
#include "ItemFactoryManager.h"
#include "DB.h"
#include "Thread.h"
#include "Slayer.h"
#include "Vampire.h"
#include "StringPool.h"
#include <list>

#include <stdio.h>

#include "item/Key.h"

#include "Gpackets/GCCreateItem.h"
#include "Gpackets/GCNPCResponse.h"
#include "Gpackets/GCSystemMessage.h"

#include "PriceManager.h"

////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////
void ActionTradeEventItem::read(PropertyBuffer & propertyBuffer)
    throw (Error)
{
    __BEGIN_TRY

 	try
	{
		// ���� ���� ���� �о���δ�.
		m_GoalAmount = (Gold_t)propertyBuffer.getPropertyInt("Amount");
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
void ActionTradeEventItem::execute(Creature * pCreature1 , Creature * pCreature2) 
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

	Inventory* pInventory = pPC->getInventory();
	XMAS_STAR  star;

	// ���� Ŭ���̾�Ʈ�� ���� GCNPCResponse�� �����ش�.
	GCNPCResponse okpkt;
	pPlayer->sendPacket(&okpkt);
//	StringStream message;
	char message[100];

	// �� ����� �κ��丮�� �౸���� ������� ���ɴ�.

	//cout << "�౸�� " << m_GoalAmount << " �� ������: " << endl;

	g_pPriceManager->getBallPrice(m_GoalAmount, star);

	if(!pInventory->hasEnoughStar(star))
	{
//		StringStream buf;
//		buf << "�౸���� ������ �����մϴ�. �� ��� ������";

		GCSystemMessage gcSystemMessage;
		gcSystemMessage.setMessage( g_pStringPool->getString( STRID_REQUIRE_MORE_SOCCER_BALL ) );
		pPlayer->sendPacket(&gcSystemMessage);

		GCNPCResponse response;
		response.setCode(NPC_RESPONSE_QUIT_DIALOGUE);
		pPlayer->sendPacket(&response);

		return;
	}

	// ���� �� ����� �κ��丮�� �ڸ��� ����ϴٸ� �������� �ִ´�.
	// ���� �������� �ΰ� �����.
	Zone* pZone = pPC->getZone();
	ObjectRegistry& OR = pZone->getObjectRegistry();

	TPOINT pt, pt2;
	Item* pItem1;
	Item* pItem2;

	list<OptionType_t> option1; option1.push_back( 1 );
	list<OptionType_t> option2; option2.push_back( 2 );
	list<OptionType_t> option3; option3.push_back( 3 );
	list<OptionType_t> option4; option4.push_back( 4 );
	list<OptionType_t> option5; option5.push_back( 5 );

	if(pPC->isSlayer())
	{
		Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature2);
		if(pSlayer->getSex() == 1) // male
		{
			switch(m_GoalAmount)
			{
				case 100:
					pItem1 = g_pItemFactoryManager->createItem(Item::ITEM_CLASS_COAT, 0, option4);
					pItem2 = g_pItemFactoryManager->createItem(Item::ITEM_CLASS_TROUSER, 0, option4);
//					message << "STR+4 �÷� ��Ŷ�� STR+4 ������ ������ ��Ƚ��ϴ�. �ڸ����� ������!";
					sprintf( message, g_pStringPool->c_str( STRID_KOREA_FIGHTING_1 ) );
					break;
				case 125:
					pItem1 = g_pItemFactoryManager->createItem(Item::ITEM_CLASS_COAT, 2, option5);
					pItem2 = g_pItemFactoryManager->createItem(Item::ITEM_CLASS_TROUSER, 2, option5);
//					message << "STR+5 ����Ʈ�� STR+5 Ʈ������� ������ ��Ƚ��ϴ�. �ڸ����� ������!";
					sprintf( message, g_pStringPool->c_str( STRID_KOREA_FIGHTING_2 ) );
					break;
				case 175:
					pItem1 = g_pItemFactoryManager->createItem(Item::ITEM_CLASS_COAT, 4, option1);
					pItem2 = g_pItemFactoryManager->createItem(Item::ITEM_CLASS_TROUSER, 4, option1);
//					message << "STR+1 ��Ʋ��Ʈ�� STR+1 ����� ������ ��Ƚ��ϴ�. �ڸ����� ������!";
					sprintf( message, g_pStringPool->c_str( STRID_KOREA_FIGHTING_3 ) );
					break;
				case 225:
					pItem1 = g_pItemFactoryManager->createItem(Item::ITEM_CLASS_COAT, 4, option2);
					pItem2 = g_pItemFactoryManager->createItem(Item::ITEM_CLASS_TROUSER, 4, option2);
//					message << "STR+2 ��Ʋ��Ʈ�� STR+2 ����� ������ ��Ƚ��ϴ�. �ڸ����� ������!";
					sprintf( message, g_pStringPool->c_str( STRID_KOREA_FIGHTING_4 ) );
					break;
				case 275:
					pItem1 = g_pItemFactoryManager->createItem(Item::ITEM_CLASS_COAT, 4, option3);
					pItem2 = g_pItemFactoryManager->createItem(Item::ITEM_CLASS_TROUSER, 4, option3);
//					message << "STR+3 ��Ʋ��Ʈ�� STR+3 ����� ������ ��Ƚ��ϴ�. �ڸ����� ������!";
					sprintf( message, g_pStringPool->c_str( STRID_KOREA_FIGHTING_5 ) );
					break;
				default:
					return;
			}
		}
		else if(pSlayer->getSex() == 0)
		{
			switch(m_GoalAmount)
			{
				case 100:
					pItem1 = g_pItemFactoryManager->createItem(Item::ITEM_CLASS_COAT, 1, option4);
					pItem2 = g_pItemFactoryManager->createItem(Item::ITEM_CLASS_TROUSER, 1, option4);
//					message << "STR+4 �÷� ��Ŷ�� STR+4 ������ ������ ��Ƚ��ϴ�. �ڸ����� ������!";
					sprintf( message, g_pStringPool->c_str( STRID_KOREA_FIGHTING_6 ) );
					break;
				case 125:
					pItem1 = g_pItemFactoryManager->createItem(Item::ITEM_CLASS_COAT, 3, option5);
					pItem2 = g_pItemFactoryManager->createItem(Item::ITEM_CLASS_TROUSER, 3, option5);
//					message << "STR+5 ����Ʈ�� STR+5 Ʈ������� ������ ��Ƚ��ϴ�. �ڸ����� ������!";
					sprintf( message, g_pStringPool->c_str( STRID_KOREA_FIGHTING_7 ) );
					break;
				case 175:
					pItem1 = g_pItemFactoryManager->createItem(Item::ITEM_CLASS_COAT, 5, option1);
					pItem2 = g_pItemFactoryManager->createItem(Item::ITEM_CLASS_TROUSER, 5, option1);
//					message << "STR+1 ��Ʋ��Ʈ�� STR+1 ����� ������ ��Ƚ��ϴ�. �ڸ����� ������!";
					sprintf( message, g_pStringPool->c_str( STRID_KOREA_FIGHTING_8 ) );
					break;
				case 225:
					pItem1 = g_pItemFactoryManager->createItem(Item::ITEM_CLASS_COAT, 5, option2);
					pItem2 = g_pItemFactoryManager->createItem(Item::ITEM_CLASS_TROUSER, 5, option2);
//					message << "STR+2 ��Ʋ��Ʈ�� STR+2 ����� ������ ��Ƚ��ϴ�. �ڸ����� ������!";
					sprintf( message, g_pStringPool->c_str( STRID_KOREA_FIGHTING_9 ) );
					break;
				case 275:
					pItem1 = g_pItemFactoryManager->createItem(Item::ITEM_CLASS_COAT, 5, option3);
					pItem2 = g_pItemFactoryManager->createItem(Item::ITEM_CLASS_TROUSER, 5, option3);
//					message << "STR+3 ��Ʋ��Ʈ�� STR+3 ����� ������ ��Ƚ��ϴ�. �ڸ����� ������!";
					sprintf( message, g_pStringPool->c_str( STRID_KOREA_FIGHTING_10 ) );
					break;
				default:
					return;
			}
		}
		else
			return;
	}
	else if(pPC->isVampire())
	{
		Vampire* pVampire = dynamic_cast<Vampire*>(pCreature2);
		if(pVampire->getSex() == 0)
		{
			switch(m_GoalAmount)
			{
				case 100:
					pItem1 = g_pItemFactoryManager->createItem(Item::ITEM_CLASS_VAMPIRE_COAT, 1, option4);
					pItem2 = g_pItemFactoryManager->createItem(Item::ITEM_CLASS_VAMPIRE_NECKLACE, 2, option4);
//					message << "STR+4 �ٵ�Ʈ�� STR+4 Ŀ���ǵ� ��ũ������ ������ ��Ƚ��ϴ�. �ڸ����� ������!";
					sprintf( message, g_pStringPool->c_str( STRID_KOREA_FIGHTING_11 ) );
					break;
				case 125:
					pItem1 = g_pItemFactoryManager->createItem(Item::ITEM_CLASS_VAMPIRE_COAT, 3, option4);
					pItem2 = g_pItemFactoryManager->createItem(Item::ITEM_CLASS_VAMPIRE_NECKLACE, 3, option4);
//					message << "STR+4 ������Ʈ�� STR+4 �� ��ũ������ ������ ��Ƚ��ϴ�.�ڸ����� ������!";;
					sprintf( message, g_pStringPool->c_str( STRID_KOREA_FIGHTING_12 ) );
					break;
				case 175:
					pItem1 = g_pItemFactoryManager->createItem(Item::ITEM_CLASS_VAMPIRE_COAT, 3, option5);
					pItem2 = g_pItemFactoryManager->createItem(Item::ITEM_CLASS_VAMPIRE_NECKLACE, 4, option3);
//					message << "STR+5 ������Ʈ�� STR+4 ���̵� �Ҵ�Ʈ�� ������ ��Ƚ��ϴ�. �ڸ����� ������!";
					sprintf( message, g_pStringPool->c_str( STRID_KOREA_FIGHTING_13 ) );
					break;
				case 225:
					pItem1 = g_pItemFactoryManager->createItem(Item::ITEM_CLASS_VAMPIRE_COAT, 3, option5);
					pItem2 = g_pItemFactoryManager->createItem(Item::ITEM_CLASS_VAMPIRE_NECKLACE, 5, option3);
//					message << "STR+5 ������Ʈ�� STR+4 �����ڰ�(Anti-Cross)�� �Ҵ�Ʈ�� ������ ��Ƚ��ϴ�. �ڸ����� ������!";
					sprintf( message, g_pStringPool->c_str( STRID_KOREA_FIGHTING_14 ) );
					break;
				case 275:
					pItem1 = g_pItemFactoryManager->createItem(Item::ITEM_CLASS_VAMPIRE_COAT, 3, option5);
					pItem2 = g_pItemFactoryManager->createItem(Item::ITEM_CLASS_VAMPIRE_NECKLACE, 6, option3);
//					message << "STR+5 ������Ʈ�� STR+4 ������Ÿ(Death-Star) �Ҵ�Ʈ�� ������ ��Ƚ��ϴ�. �ڸ����� ������!";
					sprintf( message, g_pStringPool->c_str( STRID_KOREA_FIGHTING_15 ) );
					break;
				default:
					return;
			}
		}
		else if(pVampire->getSex() == 1)
		{
			switch(m_GoalAmount)
			{
				case 100:
					pItem1 = g_pItemFactoryManager->createItem(Item::ITEM_CLASS_VAMPIRE_COAT, 0, option4);
					pItem2 = g_pItemFactoryManager->createItem(Item::ITEM_CLASS_VAMPIRE_NECKLACE, 2, option4);
//					message << "STR+4 ������Ʈ�� STR+4 Ŀ���ǵ� ��ũ������ ������ ��Ƚ��ϴ�. �ڸ����� ������!";
					sprintf( message, g_pStringPool->c_str( STRID_KOREA_FIGHTING_16 ) );
					break;
				case 125:
					pItem1 = g_pItemFactoryManager->createItem(Item::ITEM_CLASS_VAMPIRE_COAT, 2, option4);
					pItem2 = g_pItemFactoryManager->createItem(Item::ITEM_CLASS_VAMPIRE_NECKLACE, 3, option4);
//					message << "STR+4 ������Ʈ�� STR+4 �� ��ũ������ ������ ��Ƚ��ϴ�.�ڸ����� ������!";;
					sprintf( message, g_pStringPool->c_str( STRID_KOREA_FIGHTING_17 ) );
					break;
				case 175:
					pItem1 = g_pItemFactoryManager->createItem(Item::ITEM_CLASS_VAMPIRE_COAT, 2, option5);
					pItem2 = g_pItemFactoryManager->createItem(Item::ITEM_CLASS_VAMPIRE_NECKLACE, 4, option3);
//					message << "STR+5 ������Ʈ�� STR+4 ���̵� �Ҵ�Ʈ�� ������ ��Ƚ��ϴ�. �ڸ����� ������!";
					sprintf( message, g_pStringPool->c_str( STRID_KOREA_FIGHTING_18 ) );
					break;
				case 225:
					pItem1 = g_pItemFactoryManager->createItem(Item::ITEM_CLASS_VAMPIRE_COAT, 2, option5);
					pItem2 = g_pItemFactoryManager->createItem(Item::ITEM_CLASS_VAMPIRE_NECKLACE, 5, option3);
//					message << "STR+5 ������Ʈ�� STR+4 �����ڰ�(Anti-Cross)�� �Ҵ�Ʈ�� ������ ��Ƚ��ϴ�. �ڸ����� ������!";
					sprintf( message, g_pStringPool->c_str( STRID_KOREA_FIGHTING_19 ) );
					break;
				case 275:
					pItem1 = g_pItemFactoryManager->createItem(Item::ITEM_CLASS_VAMPIRE_COAT, 2, option5);
					pItem2 = g_pItemFactoryManager->createItem(Item::ITEM_CLASS_VAMPIRE_NECKLACE, 6, option3);
//					message << "STR+5 ������Ʈ�� STR+4 ������Ÿ(Death-Star) �Ҵ�Ʈ�� ������ ��Ƚ��ϴ�. �ڸ����� ������!";
					sprintf( message, g_pStringPool->c_str( STRID_KOREA_FIGHTING_20 ) );
					break;
				default:
					return;
			}
		}
		else return;
	}
	else return;

	OR.registerObject(pItem1);
	OR.registerObject(pItem2);

	// ���� inventory�� ������ �ִٸ�, �ִ´�. 
	// �ΰ��� �־�� �ϱ� ������ �ϳ��� �ְ� �ٽ� �ϳ��� �̾ ���� ������
	// ���������� �ΰ� �� ���� �౸���� ������ ���δ�.
	// ���� �ι�°�� ���� �ʴ��ٸ�, ù��° �������� �����Ѵ�.
	if(pInventory->addItem(pItem1, pt))
	{
		if(pInventory->addItem(pItem2, pt2))
		{
			pItem1->create(pPC->getName(), STORAGE_INVENTORY, 0, pt.x, pt.y);
			pItem2->create(pPC->getName(), STORAGE_INVENTORY, 0, pt2.x, pt2.y);

			// ItemTraceLog �� �����
			if ( pItem1 != NULL && pItem1->isTraceItem() )
			{
				remainTraceLog( pItem1, pCreature1->getName(), pCreature2->getName(), ITEM_LOG_CREATE, DETAIL_EVENTNPC);
			}

			// ItemTraceLog �� �����
			if ( pItem2 != NULL && pItem2->isTraceItem() )
			{
				remainTraceLog( pItem2, pCreature1->getName(), pCreature2->getName(), ITEM_LOG_CREATE, DETAIL_EVENTNPC);
			}
			//pItem1->save(pPC->getName(), STORAGE_INVENTORY, 0, pt.x, pt.y);
			GCCreateItem gcCreateItem;
			gcCreateItem.setObjectID(pItem1->getObjectID());
			gcCreateItem.setItemClass(pItem1->getItemClass());
			gcCreateItem.setItemType(pItem1->getItemType());
			gcCreateItem.setOptionType(pItem1->getOptionTypeList());
			gcCreateItem.setDurability(pItem1->getDurability());
			gcCreateItem.setItemNum(pItem1->getNum());
			gcCreateItem.setInvenX(pt.x);
			gcCreateItem.setInvenY(pt.y);

			pPlayer->sendPacket(&gcCreateItem);


			gcCreateItem.setObjectID(pItem2->getObjectID());
			gcCreateItem.setItemClass(pItem2->getItemClass());
			gcCreateItem.setItemType(pItem2->getItemType());
			gcCreateItem.setOptionType(pItem2->getOptionTypeList());
			gcCreateItem.setDurability(pItem2->getDurability());
			gcCreateItem.setItemNum(pItem2->getNum());
			gcCreateItem.setInvenX(pt2.x);
			gcCreateItem.setInvenY(pt2.y);

			pPlayer->sendPacket(&gcCreateItem);

			//�౸���� ���δ�.
			pInventory->decreaseStar(star);
			cout << "�÷��̾��� �౸���� " << star.amount << " �� �ٿ����ϴ�." << endl;

			GCNPCResponse   gcNPCResponse;
			gcNPCResponse.setCode(NPC_RESPONSE_DECREASE_BALL);
			gcNPCResponse.setParameter(star.amount);
			pPlayer->sendPacket(&gcNPCResponse);

			GCSystemMessage gcSystemMessage;
			gcSystemMessage.setMessage(message);
			pPlayer->sendPacket(&gcSystemMessage);
	
		}
    	else
		{
			pInventory->deleteItem(pt.x, pt.y);
		    SAFE_DELETE(pItem1);
			SAFE_DELETE(pItem2);
//			StringStream buf;

//			buf << "�κ��丮�� ������ �����մϴ�";

			GCSystemMessage gcSystemMessage;
			gcSystemMessage.setMessage( g_pStringPool->getString( STRID_NOT_ENOUGH_INVENTORY_SPACE ) );
			pPlayer->sendPacket(&gcSystemMessage);
		}
	}
	else
	{
//		StringStream buf;
//		buf << "�κ��丮�� ������ �����մϴ�";

		GCSystemMessage gcSystemMessage;
		gcSystemMessage.setMessage( g_pStringPool->getString( STRID_NOT_ENOUGH_INVENTORY_SPACE ) );
		pPlayer->sendPacket(&gcSystemMessage);
	}

	GCNPCResponse response;
	response.setCode(NPC_RESPONSE_QUIT_DIALOGUE);
	pPlayer->sendPacket(&response);

	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string ActionTradeEventItem::toString () const 
	throw ()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "ActionTradeEventItem("
	    << ")";
	return msg.toString();

	__END_CATCH
}
