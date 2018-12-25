//////////////////////////////////////////////////////////////////////////////
// Filename    : ResurrectItem.h
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __RESURRECT_ITEM_H__
#define __RESURRECT_ITEM_H__

#include "Item.h"
#include "ItemInfo.h"
#include "InfoClassManager.h"
#include "ItemFactory.h"
#include "ItemLoader.h"
#include "Mutex.h"

//////////////////////////////////////////////////////////////////////////////
// class ResurrectItem;
//////////////////////////////////////////////////////////////////////////////

class ResurrectItem : public Item 
{
public:
	ResurrectItem() throw();
	ResurrectItem(ItemType_t itemType, const list<OptionType_t>& optionType, ItemNum_t Num) throw();
	
public:
	virtual void create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID=0) throw(Error);
	virtual void save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y) throw(Error);
	void tinysave(const string & field) const throw (Error)	{ tinysave(field.c_str()); }
	void tinysave(const char* field) ;
	virtual string toString() ;

	static void initItemIDRegistry(void) throw();

public:
	virtual ItemClass getItemClass()  { return Item::ITEM_CLASS_RESURRECT_ITEM; }
	virtual string getObjectTableName()  { return "ResurrectItemObject"; }

	virtual ItemType_t getItemType()  { return m_ItemType; }
	virtual void setItemType(ItemType_t itemType) throw() { m_ItemType = itemType; }

	virtual VolumeWidth_t getVolumeWidth() ;
	virtual VolumeHeight_t getVolumeHeight() ;
	virtual Weight_t getWeight() ;

public:
	virtual ItemNum_t getNum()  { return m_Num; }
	virtual void setNum(ItemNum_t Num) throw() { m_Num = Num; }

	bool	isStackable()  { return true; }

private:
	ItemType_t m_ItemType;
	ItemNum_t  m_Num;
	
	static Mutex    m_Mutex;          // 아이템 ID 관련 락
	static ItemID_t m_ItemIDRegistry; // 클래스별 고유 아이템 아이디 발급기
};

//////////////////////////////////////////////////////////////////////////////
// class ResurrectItemInfo
//////////////////////////////////////////////////////////////////////////////

class ResurrectItemInfo : public ItemInfo 
{
public:
	enum ResurrectType
	{
		HP_1,		// HP가 1인 상태로 부활
		HP_FULL		// HP가 꽉찬 상태로 부활
	};
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_RESURRECT_ITEM; }
	virtual string toString() ;

	ResurrectType	getResurrectType() const { return m_ResurrectType; }
	void			setResurrectType( ResurrectType type ) { m_ResurrectType = type; }

private:
	ResurrectType m_ResurrectType;
};

//////////////////////////////////////////////////////////////////////////////
// class ResurrectItemInfoManager;
//////////////////////////////////////////////////////////////////////////////

class ResurrectItemInfoManager : public InfoClassManager 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_RESURRECT_ITEM; }
	virtual void load() throw(Error);
};

extern ResurrectItemInfoManager* g_pResurrectItemInfoManager;

//////////////////////////////////////////////////////////////////////////////
// class ResurrectItemFactory
//////////////////////////////////////////////////////////////////////////////

class ResurrectItemFactory : public ItemFactory 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_RESURRECT_ITEM; }
	virtual string getItemClassName()  { return "ResurrectItem"; }
	
public:
	virtual Item* createItem(ItemType_t ItemType, const list<OptionType_t>& OptionType) throw() { return new ResurrectItem(ItemType,OptionType,1); }
};

//////////////////////////////////////////////////////////////////////////////
// class ResurrectItemLoader;
//////////////////////////////////////////////////////////////////////////////

class ResurrectItemLoader : public ItemLoader 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_RESURRECT_ITEM; }
	virtual string getItemClassName()  { return "ResurrectItem"; }

public:
	virtual void load(Creature* pCreature) throw(Error);
	virtual void load(Zone* pZone) throw(Error);
	virtual void load(StorageID_t storageID, Inventory* pInventory) throw(Error);
};

extern ResurrectItemLoader* g_pResurrectItemLoader;

#endif
