//////////////////////////////////////////////////////////////////////////////
// Filename    : WarItem.h
// Written By  : bezz
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __WAR_ITEM_H__
#define __WAR_ITEM_H__

#include "Item.h"
#include "ItemInfo.h"
#include "InfoClassManager.h"
#include "ItemFactory.h"
#include "ItemLoader.h"
#include "Mutex.h"

//////////////////////////////////////////////////////////////////////////////
// class WarItem;
//////////////////////////////////////////////////////////////////////////////

class WarItem : public Item 
{
public:
	WarItem() ;
	WarItem(ItemType_t itemType, const list<OptionType_t>& optionType) ;
	
public:
	virtual void create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID=0);
	virtual void save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y);
	void tinysave(const string & field) 	{ tinysave(field.c_str()); }
	void tinysave(const char* field) ;
	virtual string toString() ;

	static void initItemIDRegistry(void) ;

public:
	virtual ItemClass getItemClass()  { return Item::ITEM_CLASS_WAR_ITEM; }
	virtual string getObjectTableName()  { return "WarItemObject"; }

	virtual ItemType_t getItemType()  { return m_ItemType; }
	virtual void setItemType(ItemType_t itemType) throw() { m_ItemType = itemType; }

	virtual VolumeWidth_t getVolumeWidth() ;
	virtual VolumeHeight_t getVolumeHeight() ;
	virtual Weight_t getWeight() ;

public:
	// get/set index
	int getIndex() const { return m_Index; }
	void setIndex( int index ) { m_Index = index; }

private:
	ItemType_t			m_ItemType;			// 아이템 타입
	int				m_Index;			// War Item index
	
	static Mutex    m_Mutex;          // 아이템 ID 관련 락
	static ItemID_t m_ItemIDRegistry; // 클래스별 고유 아이템 아이디 발급기
};

//////////////////////////////////////////////////////////////////////////////
// class WarItemInfo;
//////////////////////////////////////////////////////////////////////////////
class WarItemInfo : public ItemInfo 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_WAR_ITEM; }

	virtual string toString() ;

private:
};


//////////////////////////////////////////////////////////////////////////////
// class WarItemInfoManager;
//////////////////////////////////////////////////////////////////////////////

class WarItemInfoManager : public InfoClassManager 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_WAR_ITEM; }
	virtual void load();
};

// global variable declaration
extern WarItemInfoManager* g_pWarItemInfoManager;


//////////////////////////////////////////////////////////////////////////////
// class WarItemFactory
//////////////////////////////////////////////////////////////////////////////

class WarItemFactory : public ItemFactory 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_WAR_ITEM; }
	virtual string getItemClassName()  { return "WarItem"; }
	
public:
	virtual Item* createItem(ItemType_t ItemType, const list<OptionType_t>& OptionType) throw() { return new WarItem(ItemType,OptionType); }
};


//////////////////////////////////////////////////////////////////////////////
// class WarItemLoader;
//////////////////////////////////////////////////////////////////////////////

class WarItemLoader : public ItemLoader 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_WAR_ITEM; }
	virtual string getItemClassName()  { return "WarItem"; }

public:
	virtual void load(Creature* pCreature);
	virtual void load(Zone* pZone);
	virtual void load(StorageID_t storageID, Inventory* pInventory);
};

extern WarItemLoader* g_pWarItemLoader;

#endif

