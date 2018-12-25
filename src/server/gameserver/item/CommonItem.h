//////////////////////////////////////////////////////////////////////////////
// Filename    : MoonCard.h
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __COMMON_ITEM_H__
#define __COMMON_ITEM_H__

#include "Item.h"
#include "ItemInfo.h"
#include "InfoClassManager.h"
#include "ItemFactory.h"
#include "ItemLoader.h"
#include "Mutex.h"

//////////////////////////////////////////////////////////////////////////////
// class MoonCard;
//////////////////////////////////////////////////////////////////////////////

class CommonItem : public Item 
{
public:
	CommonItem() throw();
	CommonItem(ItemType_t itemType, const list<OptionType_t>& optionType, ItemNum_t Num) throw();
	
public:
	virtual void create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID=0);
	virtual void save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y);
	void tinysave(const string & field) 	{ tinysave(field.c_str()); }
	void tinysave(const char* field) ;
	virtual string toString() ;

	static void initItemIDRegistry(void) throw();

public:
	virtual ItemClass getItemClass()  { return Item::ITEM_CLASS_COMMON_ITEM; }
	virtual string getObjectTableName()  { return "CommonItemObject"; }

	virtual ItemType_t getItemType()  { return m_ItemType; }
	virtual void setItemType(ItemType_t itemType) throw() { m_ItemType = itemType; }

	virtual VolumeWidth_t getVolumeWidth() ;
	virtual VolumeHeight_t getVolumeHeight() ;
	virtual Weight_t getWeight() ;

public:
	virtual ItemNum_t getNum()  { return m_Num; }
	virtual void setNum(ItemNum_t Num) throw() { m_Num = Num; }

	bool    isStackable()  { return true; }

private:
	ItemType_t m_ItemType;
	ItemNum_t  m_Num;
	
	static Mutex    m_Mutex;          // 아이템 ID 관련 락
	static ItemID_t m_ItemIDRegistry; // 클래스별 고유 아이템 아이디 발급기
};

//////////////////////////////////////////////////////////////////////////////
// class CommonItemInfo
//////////////////////////////////////////////////////////////////////////////

class CommonItemInfo : public ItemInfo 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_COMMON_ITEM; }
	virtual string toString() ;
};

//////////////////////////////////////////////////////////////////////////////
// class CommonItemInfoManager;
//////////////////////////////////////////////////////////////////////////////

class CommonItemInfoManager : public InfoClassManager 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_COMMON_ITEM; }
	virtual void load();
};

extern CommonItemInfoManager* g_pCommonItemInfoManager;

//////////////////////////////////////////////////////////////////////////////
// class CommonItemFactory
//////////////////////////////////////////////////////////////////////////////

class CommonItemFactory : public ItemFactory 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_COMMON_ITEM; }
	virtual string getItemClassName()  { return "CommonItem"; }
	
public:
	virtual Item* createItem(ItemType_t ItemType, const list<OptionType_t>& OptionType) throw() { return new CommonItem(ItemType,OptionType,1); }
};

//////////////////////////////////////////////////////////////////////////////
// class CommonItemLoader;
//////////////////////////////////////////////////////////////////////////////

class CommonItemLoader : public ItemLoader 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_COMMON_ITEM; }
	virtual string getItemClassName()  { return "CommonItem"; }

public:
	virtual void load(Creature* pCreature);
	virtual void load(Zone* pZone);
	virtual void load(StorageID_t storageID, Inventory* pInventory);
};

extern CommonItemLoader* g_pCommonItemLoader;

#endif
