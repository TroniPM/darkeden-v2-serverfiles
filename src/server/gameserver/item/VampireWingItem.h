//////////////////////////////////////////////////////////////////////////////
// Filename    : VampireETC.h
// Written By  : Elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __VampireWingItem_H__
#define __VampireWingItem_H__

#include "Item.h"
#include "ItemInfo.h"
#include "InfoClassManager.h"
#include "ItemFactory.h"
#include "ItemLoader.h"
#include "Mutex.h"

//////////////////////////////////////////////////////////////////////////////
// class VampireETC;
//////////////////////////////////////////////////////////////////////////////

class VampireWingItem : public Item 
{
public:
	VampireWingItem() ;
	VampireWingItem(ItemType_t itemType, const list<OptionType_t>& optionType) ;
	
public:
	virtual void create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID=0);
	virtual void save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y);
	void tinysave(const string & field) 	{ tinysave(field.c_str()); }
	void tinysave(const char* field) ;
	virtual string toString() ;

	static void initItemIDRegistry(void) ;

public:
	virtual ItemClass getItemClass()  { return Item::ITEM_CLASS_VAMPIREWING_ITEM; }
	virtual string getObjectTableName()  { return "VampireWingItemObject"; }

	virtual ItemType_t getItemType()  { return m_ItemType; }
	virtual void setItemType(ItemType_t itemType)  { m_ItemType = itemType; }

	virtual VolumeWidth_t getVolumeWidth() ;
	virtual VolumeHeight_t getVolumeHeight() ;
	virtual Weight_t getWeight() ;

	virtual Color_t getBodyColor()  { return m_BodyColor; }
	virtual void setBodyColor(Color_t BodyColor)  { m_BodyColor = BodyColor; }

	virtual Color_t getEffectColor()  { return m_EffectColor; }
	virtual void setEffectColor(Color_t EffectColor)  { m_EffectColor = EffectColor; }

	bool    isStackable()  { return true; }

private:
	ItemType_t m_ItemType; // ...
	Color_t  m_BodyColor;      //  기본 몸 코드
	Color_t  m_EffectColor;      //  기본 이펙트 코드

	static Mutex    m_Mutex;          // 아이템 ID 관련 락
	static ItemID_t m_ItemIDRegistry; // 클래스별 고유 아이템 아이디 발급기
};


//////////////////////////////////////////////////////////////////////////////
// class VampireWingItemInfo
//////////////////////////////////////////////////////////////////////////////

class VampireWingItemInfo : public ItemInfo 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_VAMPIREWING_ITEM; }
	virtual string toString() ;
};


//////////////////////////////////////////////////////////////////////////////
// class VampireWingItemInfoManager;
//////////////////////////////////////////////////////////////////////////////

class VampireWingItemInfoManager : public InfoClassManager 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_VAMPIREWING_ITEM; }
	virtual void load();
};

// global variable declaration
extern VampireWingItemInfoManager* g_pVampireWingItemInfoManager;


//////////////////////////////////////////////////////////////////////////////
// class VampireWingItemFactory
//////////////////////////////////////////////////////////////////////////////
class VampireWingItemFactory : public ItemFactory 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_VAMPIREWING_ITEM; }
	virtual string getItemClassName()  { return "VampireWingItem"; }
	
public:
	virtual Item* createItem(ItemType_t ItemType, const list<OptionType_t>& OptionType)  { return new VampireWingItem(ItemType,OptionType); }
};


//////////////////////////////////////////////////////////////////////////////
// class VampireWingItemLoader;
//////////////////////////////////////////////////////////////////////////////

class VampireWingItemLoader : public ItemLoader 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_VAMPIREWING_ITEM; }
	virtual string getItemClassName()  { return "VampireWingItem"; }

public:
	virtual void load(Creature* pCreature);
	virtual void load(Zone* pZone);
	virtual void load(StorageID_t storageID, Inventory* pInventory);
};

extern VampireWingItemLoader* g_pVampireWingItemLoader;

#endif
