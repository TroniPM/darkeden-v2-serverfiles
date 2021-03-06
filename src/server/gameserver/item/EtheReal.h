//////////////////////////////////////////////////////////////////////////////
// Filename    : CoreZap.h
// Written By  : Elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __ETHEREAL_H__
#define __ETHEREAL_H__

#include "Item.h"
#include "ConcreteItem.h"
#include "ItemPolicies.h"
#include "ItemInfo.h"
#include "InfoClassManager.h"
#include "ItemFactory.h"
#include "ItemLoader.h"
#include "Mutex.h"
#include "OptionInfo.h"

//////////////////////////////////////////////////////////////////////////////
// class CoreZap;
//////////////////////////////////////////////////////////////////////////////

class EtheReal : public ConcreteItem<Item::ITEM_CLASS_ETHEREAL, NoStack, NoDurability, HasOption, HasGrade, NoAttacking, HasEnchantLevel>
{
public:
	EtheReal() ;
	EtheReal(ItemType_t itemType, const list<OptionType_t>& optionType) ;
	
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
// class CoreZapInfo
//////////////////////////////////////////////////////////////////////////////

class EtheRealInfo : public ItemInfo 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_ETHEREAL; }
	
	Defense_t getDefenseBonus()  { return m_DefenseBonus; }
	void setDefenseBonus(Defense_t acBonus)  { m_DefenseBonus = acBonus; }

	Protection_t getProtectionBonus()  { return m_ProtectionBonus; }
	void setProtectionBonus(Protection_t acBonus)  { m_ProtectionBonus = acBonus; }

	virtual string toString() ;

private:
	Defense_t     m_DefenseBonus;    // defense bonus
	Protection_t  m_ProtectionBonus; // protection bonus
};


//////////////////////////////////////////////////////////////////////////////
// class CoreZapInfoManager;
//////////////////////////////////////////////////////////////////////////////

class EtheRealInfoManager : public InfoClassManager 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_ETHEREAL; }
	virtual void load();
};

// global variable declaration
extern EtheRealInfoManager* g_pEtheRealInfoManager;


//////////////////////////////////////////////////////////////////////////////
// class CoreZapFactory
//////////////////////////////////////////////////////////////////////////////

class EtheRealFactory : public ItemFactory 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_ETHEREAL; }
	virtual string getItemClassName()  { return "EtheReal"; }
	
public:
	virtual Item* createItem(ItemType_t ItemType, const list<OptionType_t>& OptionType)  { return new EtheReal(ItemType,OptionType); }
};


//////////////////////////////////////////////////////////////////////////////
// class CoreZapLoader;
//////////////////////////////////////////////////////////////////////////////

class EtheRealLoader : public ItemLoader 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_ETHEREAL; }
	virtual string getItemClassName()  { return "EtheReal"; }

public:
	virtual void load(Creature* pCreature);
	virtual void load(Zone* pZone);
	virtual void load(StorageID_t storageID, Inventory* pInventory);
};

extern EtheRealLoader* g_pEtheRealLoader;
#endif
