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
	HolyWater() throw();
	HolyWater(ItemType_t itemType, const list<OptionType_t>& optionType) throw();
	
public:
	virtual void create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID=0) throw(Error);
	virtual void save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y) throw(Error);
	void tinysave(const string & field) const throw (Error)	{ tinysave(field.c_str()); }
	void tinysave(const char* field) const throw (Error);

	virtual string toString() ;

	static void initItemIDRegistry(void) throw();

public:
	virtual ItemClass getItemClass()  { return Item::ITEM_CLASS_HOLYWATER; }
	virtual string getObjectTableName()  { return "HolyWaterObject"; }

	virtual ItemType_t getItemType()  { return m_ItemType; }
	virtual void setItemType(ItemType_t itemType) throw() { m_ItemType = itemType; }

	virtual VolumeWidth_t getVolumeWidth() const throw(Error);
	virtual VolumeHeight_t getVolumeHeight() const throw(Error);
	virtual Weight_t getWeight() const throw(Error);

	virtual Damage_t getMinDamage() const throw(Error);
	virtual Damage_t getMaxDamage() const throw(Error);

	virtual ItemNum_t getNum()  { return m_Num; }
	virtual void setNum(ItemNum_t Num) throw() { m_Num = Num; }

	bool    isStackable()  { return true; }

private:
	ItemType_t m_ItemType;  // ������ Ÿ��
	ItemNum_t  m_Num;
	
	static Mutex    m_Mutex;          // ������ ID ���� ��
	static ItemID_t m_ItemIDRegistry; // Ŭ������ ���� ������ ���̵� �߱ޱ�
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
	Damage_t m_MinDamage;     // �ּ� ������
	Damage_t m_MaxDamage;     // �ִ� ������
};

//////////////////////////////////////////////////////////////////////////////
// class HolyWaterInfoManager;
//////////////////////////////////////////////////////////////////////////////

class HolyWaterInfoManager : public InfoClassManager 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_HOLYWATER; }
	virtual void load() throw(Error);
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
	virtual void load(Creature* pCreature) throw(Error);
	virtual void load(Zone* pZone) throw(Error);
	virtual void load(StorageID_t storageID, Inventory* pInventory) throw(Error);
};

extern HolyWaterLoader* g_pHolyWaterLoader;

#endif
