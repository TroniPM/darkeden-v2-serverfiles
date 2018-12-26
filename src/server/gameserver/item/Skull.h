//////////////////////////////////////////////////////////////////////////////
// Filename    : Skull.h
// Written By  : Elca
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKULL_H__
#define __SKULL_H__

#include "Item.h"
#include "ItemInfo.h"
#include "InfoClassManager.h"
#include "ItemFactory.h"
#include "ItemLoader.h"
#include "Mutex.h"

//////////////////////////////////////////////////////////////////////////////
// class Skull;
//////////////////////////////////////////////////////////////////////////////

class Skull : public Item 
{
public:
	Skull() ;
	Skull(ItemType_t itemType, const list<OptionType_t>& optionType) ;
	
public:
	virtual void create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID=0);
	virtual void save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y);
	void tinysave(const string & field) 	{ tinysave(field.c_str()); }
	void tinysave(const char* field) ;

	static void initItemIDRegistry(void) ;

public:
	virtual ItemClass getItemClass()  { return Item::ITEM_CLASS_SKULL; }
	virtual string getObjectTableName()  { return "SkullObject"; }

	virtual ItemType_t getItemType()  { return m_ItemType; }
	virtual void setItemType(ItemType_t itemType) throw() { m_ItemType = itemType; }

	virtual VolumeWidth_t getVolumeWidth() ;
	virtual VolumeHeight_t getVolumeHeight() ;
	virtual Weight_t getWeight() ;

	virtual string toString() ;

public:
	virtual ItemNum_t getNum()  { return m_Num; }
	virtual void setNum(ItemNum_t Num) throw() { m_Num = Num; }

	bool    isStackable()  { return true; }
	
private:
	ItemType_t m_ItemType; // 아이템 타입
	ItemNum_t  m_Num;      // 겹쳐있는 해골의 갯수
	
	static Mutex    m_Mutex;          // 아이템 ID 관련 락
	static ItemID_t m_ItemIDRegistry; // 클래스별 고유 아이템 아이디 발급기
};


//--------------------------------------------------------------------------------
// 
// class SkullInfo
// 
//--------------------------------------------------------------------------------

class SkullInfo : public ItemInfo 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_SKULL; }

	virtual uint getItemLevel(void)  { return m_ItemLevel; }
	virtual void setItemLevel(uint level) throw() { m_ItemLevel = level; }

	virtual string toString() ;

private:
	uint m_ItemLevel;

};


//--------------------------------------------------------------------------------
//
// class SkullInfoManager;
//
//--------------------------------------------------------------------------------
class SkullInfoManager : public InfoClassManager 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_SKULL; }
	virtual void load();

};

// global variable declaration
extern SkullInfoManager* g_pSkullInfoManager;


//--------------------------------------------------------------------------------
//
// class SkullFactory
//
//--------------------------------------------------------------------------------
class SkullFactory : public ItemFactory {

public:
	
	// get item class
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_SKULL; }

	// get item classname
	virtual string getItemClassName()  { return "Skull"; }
	
public:

	// create item
	virtual Item* createItem(ItemType_t ItemType, const list<OptionType_t>& OptionType) throw() { return new Skull(ItemType,OptionType); }

};


//--------------------------------------------------------------------------------
//
// class SkullLoader;
//
//--------------------------------------------------------------------------------

class SkullLoader : public ItemLoader {

public:

	// get item class
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_SKULL; }

	// get item class name
	virtual string getItemClassName()  { return "Skull"; }

public:

	// load to creature
	virtual void load(Creature* pCreature);

	// load to zone
	virtual void load(Zone* pZone);

	// load to inventory
	virtual void load(StorageID_t storageID, Inventory* pInventory);

};

extern SkullLoader* g_pSkullLoader;
#endif
