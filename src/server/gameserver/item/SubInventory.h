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
	SubInventory() throw();
	SubInventory(ItemType_t itemType, const list<OptionType_t>& optionType) throw(Error);
	~SubInventory() throw();
public:
	virtual void create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID=0) throw(Error);
	virtual bool destroy() throw(Error);
	virtual void save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y) throw(Error);
	void tinysave(const string & field) const throw (Error)	{ tinysave(field.c_str()); }
	void tinysave(const char* field) const throw (Error);
	virtual string toString() ;

	static void initItemIDRegistry(void) throw();

public:
/*
	virtual ItemClass getItemClass()  { return Item::ITEM_CLASS_SUB_INVENTORY; }
	virtual string getObjectTableName()  { return "SubInventoryObject"; }

	virtual ItemType_t getItemType()  { return m_ItemType; }
	virtual void setItemType(ItemType_t itemType) throw() { m_ItemType = itemType; }

	virtual VolumeWidth_t getVolumeWidth() const throw(Error);
	virtual VolumeHeight_t getVolumeHeight() const throw(Error);
	virtual Weight_t getWeight() const throw(Error);*/

	void setInventory(Inventory* pInventory) throw() { m_pInventory = pInventory; }
	Inventory* getInventory()  { return m_pInventory; }

	PocketNum_t getPocketWidthCount(void) ;
	PocketNum_t getPocketHeightCount(void) ;

	void makePCItemInfo(PCItemInfo& result) const;

private:
	//ItemType_t m_ItemType;
	Inventory*     m_pInventory;    // 인벤토리
	
	static Mutex    m_Mutex;          // 아이템 ID 관련 락
	static ItemID_t m_ItemIDRegistry; // 클래스별 고유 아이템 아이디 발급기
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
	Durability_t  m_Durability;      // 내구성
	uint          m_PocketCount;     // 포켓의 개수
	uint          m_PocketCount2;     // 포켓의 개수
	uint          m_ItemLevel;       // 아이템의 레벨

};


//////////////////////////////////////////////////////////////////////////////
// class SubInventoryInfoManager;
//////////////////////////////////////////////////////////////////////////////

class SubInventoryInfoManager : public InfoClassManager 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_SUB_INVENTORY; }
	virtual void load() throw(Error);
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
	virtual void load(Creature* pCreature) throw(Error);
	virtual void load(Zone* pZone) throw(Error);
	virtual void load(StorageID_t storageID, Inventory* pInventory) throw(Error);
};

extern SubInventoryLoader* g_pSubInventoryLoader;

#endif
