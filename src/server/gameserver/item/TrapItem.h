//////////////////////////////////////////////////////////////////////////////
// Filename    : TrapItem.h
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __TRAP_ITEM_H__
#define __TRAP_ITEM_H__

#include "Item.h"
#include "ItemInfo.h"
#include "InfoClassManager.h"
#include "ItemFactory.h"
#include "ItemLoader.h"
#include "Mutex.h"

//////////////////////////////////////////////////////////////////////////////
// class TrapItem;
//////////////////////////////////////////////////////////////////////////////

class TrapItem : public Item 
{
public:
	TrapItem() throw();
	TrapItem(ItemType_t itemType, const list<OptionType_t>& optionType) throw();
	
public:
	virtual void create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID=0);
	virtual void save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y);
	void tinysave(const string & field) 	{ tinysave(field.c_str()); }
	void tinysave(const char* field) ;
	virtual string toString() ;

	static void initItemIDRegistry(void) throw();

public:
	virtual ItemClass getItemClass()  { return Item::ITEM_CLASS_TRAP_ITEM; }
	virtual string getObjectTableName()  { return "TrapItemObject"; }

	virtual ItemType_t getItemType()  { return m_ItemType; }
	virtual void setItemType(ItemType_t itemType) throw() { m_ItemType = itemType; }

	virtual VolumeWidth_t getVolumeWidth() ;
	virtual VolumeHeight_t getVolumeHeight() ;
	virtual Weight_t getWeight() ;

private:
	ItemType_t m_ItemType;
	
	static Mutex    m_Mutex;          // 아이템 ID 관련 락
	static ItemID_t m_ItemIDRegistry; // 클래스별 고유 아이템 아이디 발급기
};

//////////////////////////////////////////////////////////////////////////////
// class TrapItemInfo
//////////////////////////////////////////////////////////////////////////////

class TrapItemInfo : public ItemInfo 
{
public:
	enum Function
	{
		SUMMON_MONSTER,
		MAKE_EFFECT,
		SUMMON_TRAP,
	};

	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_TRAP_ITEM; }
	virtual string toString() ;

	uint	getFunction() const { return m_Function; }
	void	setFunction(uint fun) { m_Function = fun; }

	uint	getParameter() const { return m_Parameter; }
	void	setParameter(uint param) { m_Parameter = param; }

private :
	uint	m_Function;
	uint	m_Parameter;
};

//////////////////////////////////////////////////////////////////////////////
// class TrapItemInfoManager;
//////////////////////////////////////////////////////////////////////////////

class TrapItemInfoManager : public InfoClassManager 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_TRAP_ITEM; }
	virtual void load();
};

extern TrapItemInfoManager* g_pTrapItemInfoManager;

//////////////////////////////////////////////////////////////////////////////
// class TrapItemFactory
//////////////////////////////////////////////////////////////////////////////

class TrapItemFactory : public ItemFactory 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_TRAP_ITEM; }
	virtual string getItemClassName()  { return "TrapItem"; }
	
public:
	virtual Item* createItem(ItemType_t ItemType, const list<OptionType_t>& OptionType) throw() { return new TrapItem(ItemType,OptionType); }
};

//////////////////////////////////////////////////////////////////////////////
// class TrapItemLoader;
//////////////////////////////////////////////////////////////////////////////

class TrapItemLoader : public ItemLoader 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_TRAP_ITEM; }
	virtual string getItemClassName()  { return "TrapItem"; }

public:
	virtual void load(Creature* pCreature);
	virtual void load(Zone* pZone);
	virtual void load(StorageID_t storageID, Inventory* pInventory);
};

extern TrapItemLoader* g_pTrapItemLoader;

#endif
