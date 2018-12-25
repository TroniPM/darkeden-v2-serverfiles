//////////////////////////////////////////////////////////////////////////////
// Filename    : ShoulderArmor.h
// Written By  : Elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SHOULDER_ARMOR_H__
#define __SHOULDER_ARMOR_H__

#include "Item.h"
#include "ConcreteItem.h"
#include "ItemPolicies.h"
#include "ItemInfo.h"
#include "InfoClassManager.h"
#include "ItemFactory.h"
#include "ItemLoader.h"
#include "Mutex.h"

//////////////////////////////////////////////////////////////////////////////
// class ShoulderArmor;
//////////////////////////////////////////////////////////////////////////////

class ShoulderArmor : public ConcreteItem<Item::ITEM_CLASS_SHOULDER_ARMOR, NoStack, HasDurability, HasOption, GroceryGrade, NoAttacking, NoEnchantLevel, HasOption2, HasHeroOption, HasHeroOptionAttr>
{
public:
	ShoulderArmor() throw();
	ShoulderArmor(ItemType_t itemType, const list<OptionType_t>& optionType) throw();
	
public:
	virtual void create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID=0);
	virtual void save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y);
	void tinysave(const string & field) 	{ tinysave(field.c_str()); }
	void tinysave(const char* field) ;
	virtual string toString() ;

	static void initItemIDRegistry(void) throw();

private:
	static Mutex    m_Mutex;          // 아이템 ID 관련 락
	static ItemID_t m_ItemIDRegistry; // 클래스별 고유 아이템 아이디 발급기
};


//////////////////////////////////////////////////////////////////////////////
// class ShoulderArmorInfo
//////////////////////////////////////////////////////////////////////////////

class ShoulderArmorInfo : public ItemInfo 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_SHOULDER_ARMOR; }

	virtual Durability_t getDurability()  { return m_Durability; }
	virtual void setDurability(Durability_t durability) throw() { m_Durability = durability; }

	Defense_t getDefenseBonus()  { return m_DefenseBonus; }
	void setDefenseBonus(Defense_t acBonus) throw() { m_DefenseBonus = acBonus; }

	Protection_t getProtectionBonus()  { return m_ProtectionBonus; }
	void setProtectionBonus(Protection_t acBonus) throw() { m_ProtectionBonus = acBonus; }

	virtual uint getItemLevel(void)  { return m_ItemLevel; }
	virtual void setItemLevel(uint level) throw() { m_ItemLevel = level; }

	virtual string toString() ;

private:
	Durability_t  m_Durability;
	Defense_t     m_DefenseBonus;
	Protection_t  m_ProtectionBonus;
	uint          m_ItemLevel;

};


//////////////////////////////////////////////////////////////////////////////
// class ShoulderArmorInfoManager;
//////////////////////////////////////////////////////////////////////////////

class ShoulderArmorInfoManager : public InfoClassManager 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_SHOULDER_ARMOR; }
	virtual void load();
};

extern ShoulderArmorInfoManager* g_pShoulderArmorInfoManager;


//////////////////////////////////////////////////////////////////////////////
// class ShoulderArmorFactory
//////////////////////////////////////////////////////////////////////////////

class ShoulderArmorFactory : public ItemFactory 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_SHOULDER_ARMOR; }
	virtual string getItemClassName()  { return "ShoulderArmor"; }
	
public:
	virtual Item* createItem(ItemType_t ItemType, const list<OptionType_t>& OptionType) throw() { return new ShoulderArmor(ItemType,OptionType); }

};


//////////////////////////////////////////////////////////////////////////////
// class ShoulderArmorLoader;
//////////////////////////////////////////////////////////////////////////////

class ShoulderArmorLoader : public ItemLoader 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_SHOULDER_ARMOR; }
	virtual string getItemClassName()  { return "ShoulderArmor"; }

public:
	virtual void load(Creature* pCreature);
	virtual void load(Zone* pZone);
	virtual void load(StorageID_t storageID, Inventory* pInventory);

};

extern ShoulderArmorLoader* g_pShoulderArmorLoader;

#endif
