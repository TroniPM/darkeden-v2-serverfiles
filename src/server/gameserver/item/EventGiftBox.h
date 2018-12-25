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
	EventGiftBox() throw();
	EventGiftBox(ItemType_t itemType, const list<OptionType_t>& optionType) throw();
	
public:
	virtual void create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID=0) throw(Error);
	virtual void save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y) throw(Error);
	void tinysave(const string & field) const throw (Error)	{ tinysave(field.c_str()); }
	void tinysave(const char* field) const throw (Error);
	virtual string toString() ;

	static void initItemIDRegistry(void) throw();

public:
	virtual ItemClass getItemClass()  { return Item::ITEM_CLASS_EVENT_GIFT_BOX; }
	virtual string getObjectTableName()  { return "EventGiftBoxObject"; }

	virtual ItemType_t getItemType()  { return m_ItemType; }
	virtual void setItemType(ItemType_t itemType) throw() { m_ItemType = itemType; }

	virtual VolumeWidth_t getVolumeWidth() const throw(Error);
	virtual VolumeHeight_t getVolumeHeight() const throw(Error);
	virtual Weight_t getWeight() const throw(Error);

private:
	ItemType_t m_ItemType;
	
	static Mutex    m_Mutex;          // ������ ID ���� ��
	static ItemID_t m_ItemIDRegistry; // Ŭ������ ���� ������ ���̵� �߱ޱ�
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
	virtual void load() throw(Error);
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
	virtual void load(Creature* pCreature) throw(Error);
	virtual void load(Zone* pZone) throw(Error);
	virtual void load(StorageID_t storageID, Inventory* pInventory) throw(Error);
};

extern EventGiftBoxLoader* g_pEventGiftBoxLoader;

#endif
