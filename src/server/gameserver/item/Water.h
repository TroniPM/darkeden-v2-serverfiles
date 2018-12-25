//////////////////////////////////////////////////////////////////////////////
// Filename    : Water.h
// Written By  : Elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __WATER_H__
#define __WATER_H__

#include "Item.h"
#include "ItemInfo.h"
#include "InfoClassManager.h"
#include "ItemFactory.h"
#include "ItemLoader.h"
#include "Mutex.h"

//////////////////////////////////////////////////////////////////////////////
// class Water;
//////////////////////////////////////////////////////////////////////////////

class Water : public Item 
{
public:
	Water() throw();
	Water(ItemType_t itemType, const list<OptionType_t>& optionType) throw();
	
public:
	virtual void create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID=0);
	virtual void save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y);
	void tinysave(const string & field) 	{ tinysave(field.c_str()); }
	void tinysave(const char* field) ;

	virtual string toString() ;

	static void initItemIDRegistry(void) throw();

public:
	virtual ItemClass getItemClass()  { return Item::ITEM_CLASS_WATER; }
	virtual string getObjectTableName()  { return "WaterObject"; }

	virtual ItemType_t getItemType()  { return m_ItemType; }
	virtual void setItemType(ItemType_t itemType) throw() { m_ItemType = itemType; }

	virtual VolumeWidth_t getVolumeWidth() ;
	virtual VolumeHeight_t getVolumeHeight() ;
	virtual Weight_t getWeight() ;

	virtual ItemNum_t getNum()  { return m_Num; }
	virtual void setNum(ItemNum_t Num) throw() { m_Num = Num; }

	bool    isStackable()  { return true; }

private:
	ItemType_t m_ItemType;			// ������ Ÿ��
	ItemNum_t m_Num; 
	
	static Mutex    m_Mutex;          // ������ ID ���� ��
	static ItemID_t m_ItemIDRegistry; // Ŭ������ ���� ������ ���̵� �߱ޱ�
};

//////////////////////////////////////////////////////////////////////////////
// class WaterInfo
//////////////////////////////////////////////////////////////////////////////

class WaterInfo : public ItemInfo 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_WATER; }
	virtual string toString() ;
};

//////////////////////////////////////////////////////////////////////////////
// class WaterInfoManager;
//////////////////////////////////////////////////////////////////////////////

class WaterInfoManager : public InfoClassManager 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_WATER; }
	virtual void load();
};

// global variable declaration
extern WaterInfoManager* g_pWaterInfoManager;

//////////////////////////////////////////////////////////////////////////////
// class WaterFactory
//////////////////////////////////////////////////////////////////////////////

class WaterFactory : public ItemFactory 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_WATER; }
	virtual string getItemClassName()  { return "Water"; }

public:
	virtual Item* createItem(ItemType_t ItemType, const list<OptionType_t>& OptionType) throw() { return new Water(ItemType,OptionType); }
};

//////////////////////////////////////////////////////////////////////////////
// class WaterLoader;
//////////////////////////////////////////////////////////////////////////////

class WaterLoader : public ItemLoader 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_WATER; }
	virtual string getItemClassName()  { return "Water"; }

public:
	virtual void load(Creature* pCreature);
	virtual void load(Zone* pZone);
	virtual void load(StorageID_t storageID, Inventory* pInventory);
};

extern WaterLoader* g_pWaterLoader;

#endif
