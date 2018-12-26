//////////////////////////////////////////////////////////////////////////////
// Filename    : Belt.h
// Written By  : Elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SUB_INVENTORY_H__
#define __SUB_INVENTORY_H__

#include "Item.h"
#include "ConcreteItem.h"
#include "ItemPolicies.h"
#include "ItemInfo.h"
#include "InfoClassManager.h"
#include "ItemFactory.h"
#include "ItemLoader.h"
#include "Mutex.h"

//////////////////////////////////////////////////////////////////////////////
// class Belt;
//////////////////////////////////////////////////////////////////////////////

class SubInventory : public ConcreteItem <Item::ITEM_CLASS_SUB_INVENTORY, NoStack, HasDurability, NoOption, GroceryGrade, NoAttacking, HasEnchantLevel>
{
public:
	SubInventory() ;
	SubInventory(ItemType_t itemType, const list<OptionType_t>& optionType);
	~SubInventory() ;
public:
	virtual void create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID=0);
	virtual bool destroy();
	virtual void save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y);
	void tinysave(const string & field) 	{ tinysave(field.c_str()); }
	void tinysave(const char* field) ;
	virtual string toString() ;

	static void initItemIDRegistry(void) ;

public:
/*
	virtual ItemClass getItemClass()  { return Item::ITEM_CLASS_SUB_INVENTORY; }
	virtual string getObjectTableName()  { return "SubInventoryObject"; }

	virtual ItemType_t getItemType()  { return m_ItemType; }
	virtual void setItemType(ItemType_t itemType) throw() { m_ItemType = itemType; }

	virtual VolumeWidth_t getVolumeWidth() ;
	virtual VolumeHeight_t getVolumeHeight() ;
	virtual Weight_t getWeight() ;*/

	void setInventory(Inventory* pInventory) throw() { m_pInventory = pInventory; }
	Inventory* getInventory()  { return m_pInventory; }

	PocketNum_t getPocketWidthCount(void) ;
	PocketNum_t getPocketHeightCount(void) ;

	void makePCItemInfo(PCItemInfo& result) const;

private:
	//ItemType_t m_ItemType;
	Inventory*     m_pInventory;    // �κ��丮
	
	static Mutex    m_Mutex;          // ������ ID ���� ��
	static ItemID_t m_ItemIDRegistry; // Ŭ������ ���� ������ ���̵� �߱ޱ�
};


//////////////////////////////////////////////////////////////////////////////
// class SubInventoryInfo
//////////////////////////////////////////////////////////////////////////////

class SubInventoryInfo : public ItemInfo 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_SUB_INVENTORY; }

	uint getPocketWidthCount()  { return m_PocketCount; }
	void setPocketWidthCount(uint pocketCount) throw() { m_PocketCount = pocketCount; }

	uint getPocketHeightCount()  { return m_PocketCount2; }
	void setPocketHeightCount(uint pocketCount2) throw() { m_PocketCount2 = pocketCount2; }

	virtual uint getItemLevel(void)  { return m_ItemLevel; }
	virtual void setItemLevel(uint level) throw() { m_ItemLevel = level; }

	virtual string toString() ;

private:
	Durability_t  m_Durability;      // ������
	uint          m_PocketCount;     // ������ ����
	uint          m_PocketCount2;     // ������ ����
	uint          m_ItemLevel;       // �������� ����

};


//////////////////////////////////////////////////////////////////////////////
// class SubInventoryInfoManager;
//////////////////////////////////////////////////////////////////////////////

class SubInventoryInfoManager : public InfoClassManager 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_SUB_INVENTORY; }
	virtual void load();
};

extern SubInventoryInfoManager* g_pSubInventoryInfoManager;


//////////////////////////////////////////////////////////////////////////////
// class SubInventoryFactory
//////////////////////////////////////////////////////////////////////////////

class SubInventoryFactory : public ItemFactory 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_SUB_INVENTORY; }
	virtual string getItemClassName()  { return "SubInventory"; }
	
public:
	virtual Item* createItem(ItemType_t ItemType, const list<OptionType_t>& OptionType) throw() { return new SubInventory(ItemType,OptionType); }
};


//////////////////////////////////////////////////////////////////////////////
// class SubInventoryLoader;
//////////////////////////////////////////////////////////////////////////////

class SubInventoryLoader : public ItemLoader 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_SUB_INVENTORY; }
	virtual string getItemClassName()  { return "SubInventory"; }

public:
	virtual void load(Creature* pCreature);
	virtual void load(Zone* pZone);
	virtual void load(StorageID_t storageID, Inventory* pInventory);
};

extern SubInventoryLoader* g_pSubInventoryLoader;

#endif
