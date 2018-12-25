//////////////////////////////////////////////////////////////////////////////
// Filename    : VampireETC.h
// Written By  : Elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __OustersWingItem_H__
#define __OustersWingItem_H__

#include "Item.h"
#include "ItemInfo.h"
#include "InfoClassManager.h"
#include "ItemFactory.h"
#include "ItemLoader.h"
#include "Mutex.h"

//////////////////////////////////////////////////////////////////////////////
// class OustersETC;
//////////////////////////////////////////////////////////////////////////////

class OustersWingItem : public Item 
{
public:
	OustersWingItem() throw();
	OustersWingItem(ItemType_t itemType, const list<OptionType_t>& optionType) throw();
	
public:
	virtual void create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID=0);
	virtual void save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y);
	void tinysave(const string & field) 	{ tinysave(field.c_str()); }
	void tinysave(const char* field) ;
	virtual string toString() ;

	static void initItemIDRegistry(void) throw();

public:
	virtual ItemClass getItemClass()  { return Item::ITEM_CLASS_OUSTERSWING_ITEM; }
	virtual string getObjectTableName()  { return "OustersWingItemObject"; }

	virtual ItemType_t getItemType()  { return m_ItemType; }
	virtual void setItemType(ItemType_t itemType) throw() { m_ItemType = itemType; }

	virtual VolumeWidth_t getVolumeWidth() ;
	virtual VolumeHeight_t getVolumeHeight() ;
	virtual Weight_t getWeight() ;

	virtual Color_t getBodyColor()  { return m_BodyColor; }
	virtual void setBodyColor(Color_t BodyColor) throw() { m_BodyColor = BodyColor; }

	virtual Color_t getEffectColor()  { return m_EffectColor; }
	virtual void setEffectColor(Color_t EffectColor) throw() { m_EffectColor = EffectColor; }

	bool    isStackable()  { return true; }

private:
	ItemType_t m_ItemType; // ...
	Color_t  m_BodyColor;      //  기본 몸 코드
	Color_t  m_EffectColor;      //  기본 이펙트 코드

	static Mutex    m_Mutex;          // 아이템 ID 관련 락
	static ItemID_t m_ItemIDRegistry; // 클래스별 고유 아이템 아이디 발급기
};


//////////////////////////////////////////////////////////////////////////////
// class OustersWingItemInfo
//////////////////////////////////////////////////////////////////////////////

class OustersWingItemInfo : public ItemInfo 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_OUSTERSWING_ITEM; }
	virtual string toString() ;
};


//////////////////////////////////////////////////////////////////////////////
// class OustersWingItemInfoManager;
//////////////////////////////////////////////////////////////////////////////

class OustersWingItemInfoManager : public InfoClassManager 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_OUSTERSWING_ITEM; }
	virtual void load();
};

// global variable declaration
extern OustersWingItemInfoManager* g_pOustersWingItemInfoManager;


//////////////////////////////////////////////////////////////////////////////
// class OustersWingItemFactory
//////////////////////////////////////////////////////////////////////////////
class OustersWingItemFactory : public ItemFactory 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_OUSTERSWING_ITEM; }
	virtual string getItemClassName()  { return "OustersWingItem"; }
	
public:
	virtual Item* createItem(ItemType_t ItemType, const list<OptionType_t>& OptionType) throw() { return new OustersWingItem(ItemType,OptionType); }
};


//////////////////////////////////////////////////////////////////////////////
// class OustersWingItemLoader;
//////////////////////////////////////////////////////////////////////////////

class OustersWingItemLoader : public ItemLoader 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_OUSTERSWING_ITEM; }
	virtual string getItemClassName()  { return "OustersWingItem"; }

public:
	virtual void load(Creature* pCreature);
	virtual void load(Zone* pZone);
	virtual void load(StorageID_t storageID, Inventory* pInventory);
};

extern OustersWingItemLoader* g_pOustersWingItemLoader;

#endif
