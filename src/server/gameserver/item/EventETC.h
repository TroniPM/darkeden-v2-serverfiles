//////////////////////////////////////////////////////////////////////////////
// Filename    : EventETC.h
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EVENT_ETC_H__
#define __EVENT_ETC_H__

#include "Item.h"
#include "ItemInfo.h"
#include "InfoClassManager.h"
#include "ItemFactory.h"
#include "ItemLoader.h"
#include "Mutex.h"

//////////////////////////////////////////////////////////////////////////////
// class EventETC;
//////////////////////////////////////////////////////////////////////////////

class EventETC : public Item 
{
public:
	EventETC() ;
	EventETC(ItemType_t itemType, const list<OptionType_t>& optionType, ItemNum_t Num) ;
	
public:
	virtual void create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID=0);
	virtual void save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y);
	void tinysave(const string & field) 	{ tinysave(field.c_str()); }
	void tinysave(const char* field) ;
	virtual string toString() ;

	static void initItemIDRegistry(void) ;

public:
	virtual ItemClass getItemClass()  { return Item::ITEM_CLASS_EVENT_ETC; }
	virtual string getObjectTableName()  { return "EventETCObject"; }

	virtual ItemType_t getItemType()  { return m_ItemType; }
	virtual void setItemType(ItemType_t itemType)  { m_ItemType = itemType; }

	virtual VolumeWidth_t getVolumeWidth() ;
	virtual VolumeHeight_t getVolumeHeight() ;
	virtual Weight_t getWeight() ;

public:
	virtual ItemNum_t getNum()  { return m_Num; }
	virtual void setNum(ItemNum_t Num)  { m_Num = Num; }

	bool	isStackable()  { return true; }

private:
	ItemType_t m_ItemType;
	ItemNum_t  m_Num;
	
	static Mutex    m_Mutex;          // ������ ID ���� ��
	static ItemID_t m_ItemIDRegistry; // Ŭ������ ���� ������ ���̵� �߱ޱ�
};

//////////////////////////////////////////////////////////////////////////////
// class EventETCInfo
//////////////////////////////////////////////////////////////////////////////

class EventETCInfo : public ItemInfo 
{
public:
/*	enum ITEM_FUNCTION
	{
		FUNCTION_NULL = 0,
		FUNCTION_ENCHANT_OPTION = 0x01,	// �ɼ��� �� ���� �ٲ۴�.
		FUNCTION_ADD_OPTION = 0x02,		// �ɼ��� �߰��Ѵ�.
		FUNCTION_ENCHANT_RARE_OPTION = 0x04,	// ���� �������� �ɼ��� ��~�Ѵ�.
	};*/

public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_EVENT_ETC; }
	virtual string toString() ;

	uint getFunction() const { return m_Function; }
	void setFunction( uint func ) { m_Function = func; }

private:
	uint m_Function;
};

//////////////////////////////////////////////////////////////////////////////
// class EventETCInfoManager;
//////////////////////////////////////////////////////////////////////////////

class EventETCInfoManager : public InfoClassManager 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_EVENT_ETC; }
	virtual void load();
};

extern EventETCInfoManager* g_pEventETCInfoManager;

//////////////////////////////////////////////////////////////////////////////
// class EventETCFactory
//////////////////////////////////////////////////////////////////////////////

class EventETCFactory : public ItemFactory 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_EVENT_ETC; }
	virtual string getItemClassName()  { return "EventETC"; }
	
public:
	virtual Item* createItem(ItemType_t ItemType, const list<OptionType_t>& OptionType)  { return new EventETC(ItemType,OptionType,1); }
};

//////////////////////////////////////////////////////////////////////////////
// class EventETCLoader;
//////////////////////////////////////////////////////////////////////////////

class EventETCLoader : public ItemLoader 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_EVENT_ETC; }
	virtual string getItemClassName()  { return "EventETC"; }

public:
	virtual void load(Creature* pCreature);
	virtual void load(Zone* pZone);
	virtual void load(StorageID_t storageID, Inventory* pInventory);
};

extern EventETCLoader* g_pEventETCLoader;

#endif
