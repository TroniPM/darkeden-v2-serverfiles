////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionGiveNewbieItem.cpp
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "ActionGiveNewbieItem.h"
#include "Slayer.h"
#include "FlagSet.h"
#include "Item.h"
#include "Zone.h"
#include "ItemFactoryManager.h"
#include "item/Magazine.h"
#include "Gpackets/GCCreateItem.h"
#include "Gpackets/GCNPCResponse.h"
#include "Gpackets/GCModifyInformation.h"
#include "GamePlayer.h"

////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////
void ActionGiveNewbieItem::read (PropertyBuffer & propertyBuffer)
    throw (Error)
{
    __BEGIN_TRY

	try 
	{
		// read script type
		string ItemType = propertyBuffer.getProperty("Type");

		if      (ItemType == "SWORD") m_ItemClass = Item::ITEM_CLASS_SWORD;
		else if (ItemType == "BLADE") m_ItemClass = Item::ITEM_CLASS_BLADE;
		else if (ItemType == "AR")    m_ItemClass = Item::ITEM_CLASS_AR;
		else if (ItemType == "SR")    m_ItemClass = Item::ITEM_CLASS_SR;
		else if (ItemType == "SG")    m_ItemClass = Item::ITEM_CLASS_SG;
		else if (ItemType == "SMG")   m_ItemClass = Item::ITEM_CLASS_SMG;
		else if (ItemType == "CROSS") m_ItemClass = Item::ITEM_CLASS_CROSS;
		else if (ItemType == "MACE")  m_ItemClass = Item::ITEM_CLASS_MACE;
		else
		{
			cout << "ActionGiveNewbieItem::read() : Unknown item type" << endl;
			throw ("ActionGiveNewbieItem::read() : Unknown item type");
		}
	} 
	catch (NoSuchElementException & nsee)
	{
		cout << nsee.toString() << endl;
		throw Error(nsee.toString());
	}
	
    __END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// �׼��� �����Ѵ�.
////////////////////////////////////////////////////////////////////////////////
void ActionGiveNewbieItem::execute (Creature * pCreature1 , Creature * pCreature2) 
	throw (Error)
{
	__BEGIN_TRY

	Assert(pCreature1 != NULL);
	Assert(pCreature2 != NULL);
	Assert(pCreature1->isNPC());
	Assert(pCreature2->isPC());

	Player* pPlayer = pCreature2->getPlayer();
	Assert(pPlayer != NULL);

	// ���� Ŭ���̾�Ʈ�� ���� GCNPCResponse�� �����ش�.
	GCNPCResponse okpkt;
	pPlayer->sendPacket(&okpkt);

	// �ʺ��ڰ� �����̾ �ƴ� ���� ����.
	if (!pCreature2->isSlayer()) return;

	Slayer*    pSlayer    = dynamic_cast<Slayer*>(pCreature2);
	FlagSet*   pFlagSet   = pSlayer->getFlagSet();
	Inventory* pInventory = pSlayer->getInventory();
	Zone*      pZone      = pSlayer->getZone();

	////////////////////////////////////////////////////////////
	// ��¥ �ʺ������� �˻��Ѵ�.
	// 0���� �ʺ� ������ �޾Ҵ� �÷��׷� ���ߴ�.
	// �̰��� �������� ���� �ڵ��.
	////////////////////////////////////////////////////////////
	
	if (pFlagSet->isOn(0)) return;

	////////////////////////////////////////////////////////////
	// �� ������ Ŭ������ ���� �������� �����Ѵ�.
	////////////////////////////////////////////////////////////
	Item* pItem[10] = { NULL, };
	int   i         = 0;

	for (i=0; i<10; i++) pItem[i] = NULL;

	list<OptionType_t> nullList;

	if (m_ItemClass == Item::ITEM_CLASS_SWORD)
	{
		// ����
		pItem[0] = CREATE_ITEM(Item::ITEM_CLASS_SWORD, 0, nullList);
		// ����
		pItem[1] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 0, nullList);
		pItem[2] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 0, nullList);
		pItem[3] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 0, nullList);
		pItem[4] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 5, nullList);
	}
	else if (m_ItemClass == Item::ITEM_CLASS_BLADE)
	{
		// ����
		pItem[0] = CREATE_ITEM(Item::ITEM_CLASS_BLADE, 0, nullList);
		// ����
		pItem[1] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 0, nullList);
		pItem[2] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 0, nullList);
		pItem[3] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 0, nullList);
		pItem[4] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 5, nullList);
	}
	else if (m_ItemClass == Item::ITEM_CLASS_CROSS)
	{
		// ����
		pItem[0] = CREATE_ITEM(Item::ITEM_CLASS_CROSS, 0, nullList);
		// ����
		pItem[1] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 0, nullList);
		pItem[2] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 5, nullList);
		pItem[3] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 5, nullList);
		pItem[4] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 5, nullList);
	}
	else if (m_ItemClass == Item::ITEM_CLASS_MACE)
	{
		// ����
		pItem[0] = CREATE_ITEM(Item::ITEM_CLASS_MACE, 0, nullList);
		// ����
		pItem[1] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 0, nullList);
		pItem[2] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 5, nullList);
		pItem[3] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 5, nullList);
		pItem[4] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 5, nullList);
	}
	else if (m_ItemClass == Item::ITEM_CLASS_AR)
	{
		// ����
		pItem[0] = CREATE_ITEM(Item::ITEM_CLASS_AR, 0, nullList);
		// ����
		pItem[1] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 0, nullList);
		pItem[2] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 0, nullList);
		pItem[3] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 5, nullList);
		pItem[4] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 5, nullList);
		// źâ
		pItem[5] = CREATE_ITEM(Item::ITEM_CLASS_MAGAZINE, 2, nullList);
		Magazine* pMagazine = dynamic_cast<Magazine*>(pItem[5]);
		pMagazine->setNum(9);
	}
	else if (m_ItemClass == Item::ITEM_CLASS_SR)
	{
		// ����
		pItem[0] = CREATE_ITEM(Item::ITEM_CLASS_SR, 0, nullList);
		// ����
		pItem[1] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 0, nullList);
		pItem[2] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 0, nullList);
		pItem[3] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 5, nullList);
		pItem[4] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 5, nullList);
		// źâ
		pItem[5] = CREATE_ITEM(Item::ITEM_CLASS_MAGAZINE, 6, nullList);
		Magazine* pMagazine = dynamic_cast<Magazine*>(pItem[5]);
		pMagazine->setNum(9);
	}
	else if (m_ItemClass == Item::ITEM_CLASS_SG)
	{
		// ����
		pItem[0] = CREATE_ITEM(Item::ITEM_CLASS_SG, 0, nullList);
		// ����
		pItem[1] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 0, nullList);
		pItem[2] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 0, nullList);
		pItem[3] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 5, nullList);
		pItem[4] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 5, nullList);
		// źâ
		pItem[5] = CREATE_ITEM(Item::ITEM_CLASS_MAGAZINE, 0, nullList);
		Magazine* pMagazine = dynamic_cast<Magazine*>(pItem[5]);
		pMagazine->setNum(9);
	}
	else if (m_ItemClass == Item::ITEM_CLASS_SMG)
	{
		// ����
		pItem[0] = CREATE_ITEM(Item::ITEM_CLASS_SMG, 0, nullList);
		// ����
		pItem[1] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 0, nullList);
		pItem[2] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 0, nullList);
		pItem[3] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 5, nullList);
		pItem[4] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 5, nullList);
		// źâ
		pItem[5] = CREATE_ITEM(Item::ITEM_CLASS_MAGAZINE, 4, nullList);
		Magazine* pMagazine = dynamic_cast<Magazine*>(pItem[5]);
		pMagazine->setNum(9);
	}
	else
	{
		return;
	}

	////////////////////////////////////////////////////////////
	// ������ �������� ����ϰ�, DB�� �����ϰ�,
	// Ŭ���̾�Ʈ���� ������ �����ش�.
	////////////////////////////////////////////////////////////
	ObjectRegistry& OR = pZone->getObjectRegistry();
	TPOINT           pt;
	GCCreateItem     gcCreateItem;

	for (i=0; i<10; i++)
	{
		if (pItem[i] != NULL)
		{
			OR.registerObject(pItem[i]);

			if (pInventory->addItem(pItem[i], pt))
			{
				pItem[i]->create(pSlayer->getName(), STORAGE_INVENTORY, 0, pt.x, pt.y);

				gcCreateItem.setObjectID(pItem[i]->getObjectID());
				gcCreateItem.setItemClass(pItem[i]->getItemClass());
				gcCreateItem.setItemType(pItem[i]->getItemType());
				gcCreateItem.setOptionType(pItem[i]->getOptionTypeList());
				gcCreateItem.setDurability(pItem[i]->getDurability());
				gcCreateItem.setSilver(pItem[i]->getSilver());

				if (pItem[i]->getItemClass() == Item::ITEM_CLASS_MAGAZINE)
				{
					Magazine* pMag = dynamic_cast<Magazine*>(pItem[i]);
					gcCreateItem.setItemNum(pMag->getNum());
				}
				else
				{
					gcCreateItem.setItemNum(pItem[i]->getNum());
				}

				gcCreateItem.setInvenX(pt.x);
				gcCreateItem.setInvenY(pt.y);

				pPlayer->sendPacket(&gcCreateItem);
			}
			else
			{
				SAFE_DELETE(pItem[i]);
			}
		}
	}

	// ���� �شٳ�...
	//pSlayer->setGoldEx(pSlayer->getGold() + 500);
	// by sigi. 2002.9.18
	pSlayer->increaseGoldEx(500);
	GCModifyInformation gcModifyInformation;
	gcModifyInformation.addLongData(MODIFY_GOLD, pSlayer->getGold());
	pPlayer->sendPacket(&gcModifyInformation);

	////////////////////////////////////////////////////////////
	// �������� �޾�����, ���� FlagSet�� �����Ѵ�.
	// 0���� �ʺ� ������ �޾Ҵ� �÷��׷� ���ߴ�.
	// �̰��� �������� ���� �ڵ��.
	////////////////////////////////////////////////////////////
	pFlagSet->turnOn(FLAGSET_RECEIVE_NEWBIE_ITEM);

	if (m_ItemClass == Item::ITEM_CLASS_SWORD || m_ItemClass == Item::ITEM_CLASS_BLADE)
	{
		// ������ ��� 1
		pFlagSet->turnOn(FLAGSET_RECEIVE_NEWBIE_ITEM_FIGHTER);
	}
	else if (m_ItemClass == Item::ITEM_CLASS_CROSS || m_ItemClass == Item::ITEM_CLASS_MACE)
	{
		// �������� ��� 2
		pFlagSet->turnOn(FLAGSET_RECEIVE_NEWBIE_ITEM_CLERIC);
	}
	else
	{
		// ������ ��� 3
		pFlagSet->turnOn(FLAGSET_RECEIVE_NEWBIE_ITEM_GUNNER);
	}

	pFlagSet->save(pSlayer->getName());

	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string ActionGiveNewbieItem::toString () const 
	throw ()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "ActionGiveNewbieItem("
	    << ")";
	return msg.toString();

	__END_CATCH
}






