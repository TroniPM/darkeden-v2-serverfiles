//////////////////////////////////////////////////////////////////////////////
// Filename    : CoreZap.h
// Written By  : Elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __HELMZAP_H__
#define __HELMZAP_H__

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

class HelmZap : public ConcreteItem<Item::ITEM_CLASS_HELMZAP, NoStack, NoDurability, HasOption, HasGrade, NoAttacking, HasEnchantLevel>
{
public:
	HelmZap() throw();
	HelmZap(ItemType_t itemType, const list<OptionType_t>& optionType) throw();
	
public:
	virtual void create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID=0) throw(Error);
	virtual void save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y) throw(Error);
	void tinysave(const string & field) const throw (Error)	{ tinysave(field.c_str()); }
	void tinysave(const char* field) const throw (Error);
	virtual string toString() ;

	static void initItemIDRegistry(void) throw();

private:
	
	static Mutex    m_Mutex;          // 아이템 ID 관련 락
	static ItemID_t m_ItemIDRegistry; // 클래스별 고유 아이템 아이디 발급기
};


//////////////////////////////////////////////////////////////////////////////
// class CoreZapInfo
//////////////////////////////////////////////////////////////////////////////

class HelmZapInfo : public ItemInfo 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_HELMZAP; }
	
	Defense_t getDefenseBonus()  { return m_DefenseBonus; }
	void setDefenseBonus(Defense_t acBonus) throw() { m_DefenseBonus = acBonus; }

	Protection_t getProtectionBonus()  { return m_ProtectionBonus; }
	void setProtectionBonus(Protection_t acBonus) throw() { m_ProtectionBonus = acBonus; }

	virtual string toString() ;

private:
	Defense_t     m_DefenseBonus;    // defense bonus
	Protection_t  m_ProtectionBonus; // protection bonus
};


//////////////////////////////////////////////////////////////////////////////
// class CoreZapInfoManager;
//////////////////////////////////////////////////////////////////////////////

class HelmZapInfoManager : public InfoClassManager 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_HELMZAP; }
	virtual void load() throw(Error);
};

// global variable declaration
extern HelmZapInfoManager* g_pHelmZapInfoManager;


//////////////////////////////////////////////////////////////////////////////
// class CoreZapFactory
//////////////////////////////////////////////////////////////////////////////

class HelmZapFactory : public ItemFactory 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_HELMZAP; }
	virtual string getItemClassName()  { return "HelmZap"; }
	
public:
	virtual Item* createItem(ItemType_t ItemType, const list<OptionType_t>& OptionType) throw() { return new HelmZap(ItemType,OptionType); }
};


//////////////////////////////////////////////////////////////////////////////
// class CoreZapLoader;
//////////////////////////////////////////////////////////////////////////////

class HelmZapLoader : public ItemLoader 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_HELMZAP; }
	virtual string getItemClassName()  { return "HelmZap"; }

public:
	virtual void load(Creature* pCreature) throw(Error);
	virtual void load(Zone* pZone) throw(Error);
	virtual void load(StorageID_t storageID, Inventory* pInventory) throw(Error);
};

extern HelmZapLoader* g_pHelmZapLoader;
#endif
