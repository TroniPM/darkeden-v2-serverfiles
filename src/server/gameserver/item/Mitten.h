//////////////////////////////////////////////////////////////////////////////
// Filename    : Mitten.h
// Written By  :
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __MITTEN_H__
#define __MITTEN_H__

#include "Item.h"
#include "ConcreteItem.h"
#include "ItemPolicies.h"
#include "ItemInfo.h"
#include "InfoClassManager.h"
#include "ItemFactory.h"
#include "ItemLoader.h"
#include "Mutex.h"

//////////////////////////////////////////////////////////////////////////////
// class Mitten;
//////////////////////////////////////////////////////////////////////////////

class Mitten : public ConcreteItem<Item::ITEM_CLASS_MITTEN, NoStack, HasDurability, HasOption, GroceryGrade, NoAttacking, NoEnchantLevel, HasOption2, HasHeroOption, HasHeroOptionAttr>
{
public:
	Mitten() ;
	Mitten(ItemType_t itemType, const list<OptionType_t>& optionType) ;
	
public:
	virtual void create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID=0);
	virtual void save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y);
	void tinysave(const string & field) 	{ tinysave(field.c_str()); }
	void tinysave(const char* field) ;
	virtual string toString() ;

	static void initItemIDRegistry(void) ;

private:
	static Mutex    m_Mutex;          // 아이템 ID 관련 락
	static ItemID_t m_ItemIDRegistry; // 클래스별 고유 아이템 아이디 발급기
};


//////////////////////////////////////////////////////////////////////////////
// class MittenInfo
//////////////////////////////////////////////////////////////////////////////

class MittenInfo : public ItemInfo 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_MITTEN; }

	virtual Durability_t getDurability()  { return m_Durability; }
	virtual void setDurability(Durability_t durability)  { m_Durability = durability; }

	Defense_t getDefenseBonus()  { return m_DefenseBonus; }
	void setDefenseBonus(Defense_t acBonus)  { m_DefenseBonus = acBonus; }

	Protection_t getProtectionBonus()  { return m_ProtectionBonus; }
	void setProtectionBonus(Protection_t acBonus)  { m_ProtectionBonus = acBonus; }

	virtual uint getItemLevel(void)  { return m_ItemLevel; }
	virtual void setItemLevel(uint level)  { m_ItemLevel = level; }

	virtual string toString() ;

private:
	Durability_t	m_Durability;		// 내구성
	Defense_t		m_DefenseBonus;
	Protection_t	m_ProtectionBonus;
	uint			m_ItemLevel;
};


//////////////////////////////////////////////////////////////////////////////
// class MittenInfoManager;
//////////////////////////////////////////////////////////////////////////////

class MittenInfoManager : public InfoClassManager 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_MITTEN; }
	virtual void load();
};

// global variable declaration
extern MittenInfoManager* g_pMittenInfoManager;


//////////////////////////////////////////////////////////////////////////////
// class MittenFactory
//////////////////////////////////////////////////////////////////////////////

class MittenFactory : public ItemFactory 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_MITTEN; }
	virtual string getItemClassName()  { return "Mitten"; }

public:
	virtual Item* createItem(ItemType_t ItemType, const list<OptionType_t>& OptionType)  { return new Mitten(ItemType,OptionType); }
};


//////////////////////////////////////////////////////////////////////////////
// class MittenLoader;
//////////////////////////////////////////////////////////////////////////////

class MittenLoader : public ItemLoader 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_MITTEN; }
	virtual string getItemClassName()  { return "Mitten"; }

public:
	virtual void load(Creature* pCreature);
	virtual void load(Zone* pZone);
	virtual void load(StorageID_t storageID, Inventory* pInventory);
};

extern MittenLoader* g_pMittenLoader;

#endif
