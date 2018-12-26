//////////////////////////////////////////////////////////////////////////////
// Filename    : HolyWater.h
// Written By  : Elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __HOLYWATER_H__
#define __HOLYWATER_H__

#include "Item.h"
#include "ItemInfo.h"
#include "InfoClassManager.h"
#include "ItemFactory.h"
#include "ItemLoader.h"
#include "Mutex.h"

//////////////////////////////////////////////////////////////////////////////
// class HolyWater;
//////////////////////////////////////////////////////////////////////////////

class HolyWater : public Item 
{
public:
	HolyWater() ;
	HolyWater(ItemType_t itemType, const list<OptionType_t>& optionType) ;
	
public:
	virtual void create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID=0);
	virtual void save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y);
	void tinysave(const string & field) 	{ tinysave(field.c_str()); }
	void tinysave(const char* field) ;

	virtual string toString() ;

	static void initItemIDRegistry(void) ;

public:
	virtual ItemClass getItemClass()  { return Item::ITEM_CLASS_HOLYWATER; }
	virtual string getObjectTableName()  { return "HolyWaterObject"; }

	virtual ItemType_t getItemType()  { return m_ItemType; }
	virtual void setItemType(ItemType_t itemType) throw() { m_ItemType = itemType; }

	virtual VolumeWidth_t getVolumeWidth() ;
	virtual VolumeHeight_t getVolumeHeight() ;
	virtual Weight_t getWeight() ;

	virtual Damage_t getMinDamage() ;
	virtual Damage_t getMaxDamage() ;

	virtual ItemNum_t getNum()  { return m_Num; }
	virtual void setNum(ItemNum_t Num) throw() { m_Num = Num; }

	bool    isStackable()  { return true; }

private:
	ItemType_t m_ItemType;  // 아이템 타입
	ItemNum_t  m_Num;
	
	static Mutex    m_Mutex;          // 아이템 ID 관련 락
	static ItemID_t m_ItemIDRegistry; // 클래스별 고유 아이템 아이디 발급기
};

//////////////////////////////////////////////////////////////////////////////
// class HolyWaterInfo
//////////////////////////////////////////////////////////////////////////////

class HolyWaterInfo : public ItemInfo 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_HOLYWATER; }
	virtual string toString() ;

	virtual Damage_t getMinDamage()  { return m_MinDamage; }
	virtual void setMinDamage(Damage_t minDamage) throw() { m_MinDamage = minDamage; }

	virtual Damage_t getMaxDamage()  { return m_MaxDamage; }
	virtual void setMaxDamage(Damage_t maxDamage) throw() { m_MaxDamage = maxDamage; }

private:
	Damage_t m_MinDamage;     // 최소 데미지
	Damage_t m_MaxDamage;     // 최대 데미지
};

//////////////////////////////////////////////////////////////////////////////
// class HolyWaterInfoManager;
//////////////////////////////////////////////////////////////////////////////

class HolyWaterInfoManager : public InfoClassManager 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_HOLYWATER; }
	virtual void load();
};

// global variable declaration
extern HolyWaterInfoManager* g_pHolyWaterInfoManager;

//////////////////////////////////////////////////////////////////////////////
// class HolyWaterFactory
//////////////////////////////////////////////////////////////////////////////

class HolyWaterFactory : public ItemFactory 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_HOLYWATER; }
	virtual string getItemClassName()  { return "HolyWater"; }
	
public:
	virtual Item* createItem(ItemType_t ItemType, const list<OptionType_t>& OptionType) throw() { return new HolyWater(ItemType,OptionType); }
};

//////////////////////////////////////////////////////////////////////////////
// class HolyWaterLoader;
//////////////////////////////////////////////////////////////////////////////

class HolyWaterLoader : public ItemLoader 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_HOLYWATER; }
	virtual string getItemClassName()  { return "HolyWater"; }

public:
	virtual void load(Creature* pCreature);
	virtual void load(Zone* pZone);
	virtual void load(StorageID_t storageID, Inventory* pInventory);
};

extern HolyWaterLoader* g_pHolyWaterLoader;

#endif
