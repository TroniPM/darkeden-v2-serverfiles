//////////////////////////////////////////////////////////////////////////////
// Filename    : CoreZap.h
// Written By  : Elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __BOOTZAP_H__
#define __BOOTZAP_H__

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

class BootZap : public ConcreteItem<Item::ITEM_CLASS_BOOTZAP, NoStack, NoDurability, HasOption, HasGrade, NoAttacking, HasEnchantLevel>
{
public:
	BootZap() throw();
	BootZap(ItemType_t itemType, const list<OptionType_t>& optionType) throw();
	
public:
	virtual void create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID=0) throw(Error);
	virtual void save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y) throw(Error);
	void tinysave(const string & field) const throw (Error)	{ tinysave(field.c_str()); }
	void tinysave(const char* field) const throw (Error);
	virtual string toString() const throw();

	static void initItemIDRegistry(void) throw();

private:
	
	static Mutex    m_Mutex;          // 아이템 ID 관련 락
	static ItemID_t m_ItemIDRegistry; // 클래스별 고유 아이템 아이디 발급기
};


//////////////////////////////////////////////////////////////////////////////
// class CoreZapInfo
//////////////////////////////////////////////////////////////////////////////

class BootZapInfo : public ItemInfo 
{
public:
	virtual Item::ItemClass getItemClass() const throw() { return Item::ITEM_CLASS_BOOTZAP; }
	
	Defense_t getDefenseBonus() const throw() { return m_DefenseBonus; }
	void setDefenseBonus(Defense_t acBonus) throw() { m_DefenseBonus = acBonus; }

	Protection_t getProtectionBonus() const throw() { return m_ProtectionBonus; }
	void setProtectionBonus(Protection_t acBonus) throw() { m_ProtectionBonus = acBonus; }

	virtual string toString() const throw();

private:
	Defense_t     m_DefenseBonus;    // defense bonus
	Protection_t  m_ProtectionBonus; // protection bonus
};


//////////////////////////////////////////////////////////////////////////////
// class CoreZapInfoManager;
//////////////////////////////////////////////////////////////////////////////

class BootZapInfoManager : public InfoClassManager 
{
public:
	virtual Item::ItemClass getItemClass() const throw() { return Item::ITEM_CLASS_BOOTZAP; }
	virtual void load() throw(Error);
};

// global variable declaration
extern BootZapInfoManager* g_pBootZapInfoManager;


//////////////////////////////////////////////////////////////////////////////
// class CoreZapFactory
//////////////////////////////////////////////////////////////////////////////

class BootZapFactory : public ItemFactory 
{
public:
	virtual Item::ItemClass getItemClass() const throw() { return Item::ITEM_CLASS_BOOTZAP; }
	virtual string getItemClassName() const throw() { return "BootZap"; }
	
public:
	virtual Item* createItem(ItemType_t ItemType, const list<OptionType_t>& OptionType) throw() { return new BootZap(ItemType,OptionType); }
};


//////////////////////////////////////////////////////////////////////////////
// class CoreZapLoader;
//////////////////////////////////////////////////////////////////////////////

class BootZapLoader : public ItemLoader 
{
public:
	virtual Item::ItemClass getItemClass() const throw() { return Item::ITEM_CLASS_BOOTZAP; }
	virtual string getItemClassName() const throw() { return "BootZap"; }

public:
	virtual void load(Creature* pCreature) throw(Error);
	virtual void load(Zone* pZone) throw(Error);
	virtual void load(StorageID_t storageID, Inventory* pInventory) throw(Error);
};

extern BootZapLoader* g_pBootZapLoader;
#endif
