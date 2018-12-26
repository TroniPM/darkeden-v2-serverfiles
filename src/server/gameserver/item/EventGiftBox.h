//////////////////////////////////////////////////////////////////////////////
// Filename    : EventGiftBox.h
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EVENT_GIFT_BOX_H__
#define __EVENT_GIFT_BOX_H__

#include "Item.h"
#include "ItemInfo.h"
#include "InfoClassManager.h"
#include "ItemFactory.h"
#include "ItemLoader.h"
#include "Mutex.h"

//////////////////////////////////////////////////////////////////////////////
// class EventGiftBox;
//////////////////////////////////////////////////////////////////////////////
class EventGiftBox : public Item 
{
public:
	EventGiftBox() ;
	EventGiftBox(ItemType_t itemType, const list<OptionType_t>& optionType) ;
	
public:
	virtual void create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID=0);
	virtual void save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y);
	void tinysave(const string & field) 	{ tinysave(field.c_str()); }
	void tinysave(const char* field) ;
	virtual string toString() ;

	static void initItemIDRegistry(void) ;

public:
	virtual ItemClass getItemClass()  { return Item::ITEM_CLASS_EVENT_GIFT_BOX; }
	virtual string getObjectTableName()  { return "EventGiftBoxObject"; }

	virtual ItemType_t getItemType()  { return m_ItemType; }
	virtual void setItemType(ItemType_t itemType) throw() { m_ItemType = itemType; }

	virtual VolumeWidth_t getVolumeWidth() ;
	virtual VolumeHeight_t getVolumeHeight() ;
	virtual Weight_t getWeight() ;

private:
	ItemType_t m_ItemType;
	
	static Mutex    m_Mutex;          // 아이템 ID 관련 락
	static ItemID_t m_ItemIDRegistry; // 클래스별 고유 아이템 아이디 발급기
};

//////////////////////////////////////////////////////////////////////////////
// class EventGiftBoxInfo
//////////////////////////////////////////////////////////////////////////////
class EventGiftBoxInfo : public ItemInfo 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_EVENT_GIFT_BOX; }
	virtual string toString() ;

private:
};

//////////////////////////////////////////////////////////////////////////////
// class EventGiftBoxInfoManager;
//////////////////////////////////////////////////////////////////////////////
class EventGiftBoxInfoManager : public InfoClassManager 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_EVENT_GIFT_BOX; }
	virtual void load();
};

extern EventGiftBoxInfoManager* g_pEventGiftBoxInfoManager;

//////////////////////////////////////////////////////////////////////////////
// class EventGiftBoxFactory
//////////////////////////////////////////////////////////////////////////////
class EventGiftBoxFactory : public ItemFactory 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_EVENT_GIFT_BOX; }
	virtual string getItemClassName()  { return "EventGiftBox"; }
	
public:
	virtual Item* createItem(ItemType_t ItemType, const list<OptionType_t>& OptionType) throw() { return new EventGiftBox(ItemType,OptionType); }
};


//////////////////////////////////////////////////////////////////////////////
// class EventGiftBoxLoader;
//////////////////////////////////////////////////////////////////////////////
class EventGiftBoxLoader : public ItemLoader 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_EVENT_GIFT_BOX; }
	virtual string getItemClassName()  { return "EventGiftBox"; }

public:
	virtual void load(Creature* pCreature);
	virtual void load(Zone* pZone);
	virtual void load(StorageID_t storageID, Inventory* pInventory);
};

extern EventGiftBoxLoader* g_pEventGiftBoxLoader;

#endif
