//////////////////////////////////////////////////////////////////////////////
// Filename    : Serum.h
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __Serum_H__
#define __Serum_H__

#include "Item.h"
#include "ItemInfo.h"
#include "InfoClassManager.h"
#include "ItemFactory.h"
#include "ItemLoader.h"
#include "Mutex.h"

//////////////////////////////////////////////////////////////////////////////
// class Serum;
//////////////////////////////////////////////////////////////////////////////

class Serum : public Item 
{
public:
	Serum() throw();
	Serum(ItemType_t itemType, const list<OptionType_t>& optionType) throw();
	
public:
	virtual void create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID=0);
	virtual void save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y);
	void tinysave(const string & field) 	{ tinysave(field.c_str()); }
	void tinysave(const char* field) ;
	virtual string toString() ;

	static void initItemIDRegistry(void) throw();

public:
	virtual ItemClass getItemClass()  { return Item::ITEM_CLASS_SERUM; }
	virtual string getObjectTableName()  { return "SerumObject"; }

	virtual ItemType_t getItemType()  { return m_ItemType; }
	virtual void setItemType(ItemType_t itemType) throw() { m_ItemType = itemType; }

	virtual VolumeWidth_t getVolumeWidth() ;
	virtual VolumeHeight_t getVolumeHeight() ;
	virtual Weight_t getWeight() ;

	int getHPAmount(void) ;
	int getPeriod(void) ;
	int getCount(void) ;

	virtual ItemNum_t getNum()  { return m_Num; }
	virtual void setNum(ItemNum_t Num) throw() { m_Num = Num; }

	bool    isStackable()  { return true; }

private:
	ItemType_t m_ItemType; // 아이템 타입
	ItemNum_t  m_Num;      // 겹쳐있는 혈청의 갯수
	
	static Mutex    m_Mutex;          // 아이템 ID 관련 락
	static ItemID_t m_ItemIDRegistry; // 클래스별 고유 아이템 아이디 발급기
};


//////////////////////////////////////////////////////////////////////////////
// class SerumInfo
//////////////////////////////////////////////////////////////////////////////

class SerumInfo : public ItemInfo 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_SERUM; }

	int getHPAmount(void) const { return m_HPAmount; }
	void setHPAmount(int amount) { m_HPAmount = amount; }

	int getPeriod(void) const { return m_Period; }
	void setPeriod(int period) { m_Period = period; }

	int getCount(void) const { return m_Count; }
	void setCount(int count) { m_Count = count; }

	void parseEffect(const string& effect) throw();

	virtual string toString() ;

private:
	int m_HPAmount; // 단위 시간당 HP 회복량
	int m_Period;   // 단위 시간(초 단위)
	int m_Count;    // 단위 시간을 몇 번 반복할 것인가?



};


//////////////////////////////////////////////////////////////////////////////
// class SerumInfoManager;
//////////////////////////////////////////////////////////////////////////////

class SerumInfoManager : public InfoClassManager 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_SERUM; }
	virtual void load();
};

extern SerumInfoManager* g_pSerumInfoManager;


//////////////////////////////////////////////////////////////////////////////
// class SerumFactory
//////////////////////////////////////////////////////////////////////////////

class SerumFactory : public ItemFactory 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_SERUM; }
	virtual string getItemClassName()  { return "Serum"; }
	
public:
	virtual Item* createItem(ItemType_t ItemType, const list<OptionType_t>& OptionType) throw() { return new Serum(ItemType,OptionType); }
};


//////////////////////////////////////////////////////////////////////////////
// class SerumLoader;
//////////////////////////////////////////////////////////////////////////////

class SerumLoader : public ItemLoader 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_SERUM; }
	virtual string getItemClassName()  { return "Serum"; }

public:
	virtual void load(Creature* pCreature);
	virtual void load(Zone* pZone);
	virtual void load(StorageID_t storageID, Inventory* pInventory);

};

extern SerumLoader* g_pSerumLoader;

#endif
