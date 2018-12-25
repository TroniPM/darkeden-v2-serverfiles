//////////////////////////////////////////////////////////////////////////////
// Filename    : CoreZap.h
// Written By  : Elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SHOESZAP_H__
#define __SHOESZAP_H__

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

class ShoesZap : public ConcreteItem<Item::ITEM_CLASS_SHOESZAP, NoStack, NoDurability, HasOption, HasGrade, NoAttacking, HasEnchantLevel>
{
public:
	ShoesZap() throw();
	ShoesZap(ItemType_t itemType, const list<OptionType_t>& optionType) throw();
	
public:
	virtual void create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID=0) throw(Error);
	virtual void save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y) throw(Error);
	void tinysave(const string & field) const throw (Error)	{ tinysave(field.c_str()); }
	void tinysave(const char* field) const throw (Error);
	virtual string toString() ;

	static void initItemIDRegistry(void) throw();

private:
	
	static Mutex    m_Mutex;          // ������ ID ���� ��
	static ItemID_t m_ItemIDRegistry; // Ŭ������ ���� ������ ���̵� �߱ޱ�
};


//////////////////////////////////////////////////////////////////////////////
// class CoreZapInfo
//////////////////////////////////////////////////////////////////////////////

class ShoesZapInfo : public ItemInfo 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_SHOESZAP; }
	
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

class ShoesZapInfoManager : public InfoClassManager 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_SHOESZAP; }
	virtual void load() throw(Error);
};

// global variable declaration
extern ShoesZapInfoManager* g_pShoesZapInfoManager;


//////////////////////////////////////////////////////////////////////////////
// class CoreZapFactory
//////////////////////////////////////////////////////////////////////////////

class ShoesZapFactory : public ItemFactory 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_SHOESZAP; }
	virtual string getItemClassName()  { return "ShoesZap"; }
	
public:
	virtual Item* createItem(ItemType_t ItemType, const list<OptionType_t>& OptionType) throw() { return new ShoesZap(ItemType,OptionType); }
};


//////////////////////////////////////////////////////////////////////////////
// class CoreZapLoader;
//////////////////////////////////////////////////////////////////////////////

class ShoesZapLoader : public ItemLoader 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_SHOESZAP; }
	virtual string getItemClassName()  { return "ShoesZap"; }

public:
	virtual void load(Creature* pCreature) throw(Error);
	virtual void load(Zone* pZone) throw(Error);
	virtual void load(StorageID_t storageID, Inventory* pInventory) throw(Error);
};

extern ShoesZapLoader* g_pShoesZapLoader;
#endif
