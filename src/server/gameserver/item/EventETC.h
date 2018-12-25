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
	EventETC() throw();
	EventETC(ItemType_t itemType, const list<OptionType_t>& optionType, ItemNum_t Num) throw();
	
public:
	virtual void create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID=0) throw(Error);
	virtual void save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y) throw(Error);
	void tinysave(const string & field) const throw (Error)	{ tinysave(field.c_str()); }
	void tinysave(const char* field) const throw (Error);
	virtual string toString() ;

	static void initItemIDRegistry(void) throw();

public:
	virtual ItemClass getItemClass()  { return Item::ITEM_CLASS_EVENT_ETC; }
	virtual string getObjectTableName()  { return "EventETCObject"; }

	virtual ItemType_t getItemType()  { return m_ItemType; }
	virtual void setItemType(ItemType_t itemType) throw() { m_ItemType = itemType; }

	virtual VolumeWidth_t getVolumeWidth() const throw(Error);
	virtual VolumeHeight_t getVolumeHeight() const throw(Error);
	virtual Weight_t getWeight() const throw(Error);

public:
	virtual ItemNum_t getNum()  { return m_Num; }
	virtual void setNum(ItemNum_t Num) throw() { m_Num = Num; }

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
	virtual void load() throw(Error);
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
	virtual Item* createItem(ItemType_t ItemType, const list<OptionType_t>& OptionType) throw() { return new EventETC(ItemType,OptionType,1); }
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
	virtual void load(Creature* pCreature) throw(Error);
	virtual void load(Zone* pZone) throw(Error);
	virtual void load(StorageID_t storageID, Inventory* pInventory) throw(Error);
};

extern EventETCLoader* g_pEventETCLoader;

#endif
