//////////////////////////////////////////////////////////////////////////////
// Filename    : Fascia.h
// Written By  :
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __FASCIA_H__
#define __FASCIA_H__

#include "Item.h"
#include "ConcreteItem.h"
#include "ItemPolicies.h"
#include "ItemInfo.h"
#include "InfoClassManager.h"
#include "ItemFactory.h"
#include "ItemLoader.h"
#include "Mutex.h"

//////////////////////////////////////////////////////////////////////////////
// class Fascia;
//////////////////////////////////////////////////////////////////////////////

class Fascia : public ConcreteItem<Item::ITEM_CLASS_FASCIA, NoStack, NoDurability, HasOption, GroceryGrade, NoAttacking, NoEnchantLevel, HasOption2, HasHeroOption, HasHeroOptionAttr>
{
public:
	Fascia() throw();
	Fascia(ItemType_t itemType, const list<OptionType_t>& optionType) throw();
	
public:
	virtual void create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID=0) throw(Error);
	virtual void save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y) throw(Error);
	void tinysave(const string & field) const throw (Error)	{ tinysave(field.c_str()); }
	void tinysave(const char* field) ;
	virtual string toString() ;

	static void initItemIDRegistry(void) throw();

private:
	static Mutex    m_Mutex;          // ������ ID ���� ��
	static ItemID_t m_ItemIDRegistry; // Ŭ������ ���� ������ ���̵� �߱ޱ�
};


//////////////////////////////////////////////////////////////////////////////
// class FasciaInfo
//////////////////////////////////////////////////////////////////////////////

class FasciaInfo : public ItemInfo 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_FASCIA; }

	Defense_t getDefenseBonus()  { return m_DefenseBonus; }
	void setDefenseBonus(Defense_t acBonus) throw() { m_DefenseBonus = acBonus; }

	Protection_t getProtectionBonus()  { return m_ProtectionBonus; }
	void setProtectionBonus(Protection_t acBonus) throw() { m_ProtectionBonus = acBonus; }

	virtual uint getItemLevel(void)  { return m_ItemLevel; }
	virtual void setItemLevel(uint level) throw() { m_ItemLevel = level; }

	virtual string toString() ;

private:
	Defense_t		m_DefenseBonus;
	Protection_t	m_ProtectionBonus;
	uint			m_ItemLevel;
};


//////////////////////////////////////////////////////////////////////////////
// class FasciaInfoManager;
//////////////////////////////////////////////////////////////////////////////

class FasciaInfoManager : public InfoClassManager 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_FASCIA; }
	virtual void load() throw(Error);
};

// global variable declaration
extern FasciaInfoManager* g_pFasciaInfoManager;


//////////////////////////////////////////////////////////////////////////////
// class FasciaFactory
//////////////////////////////////////////////////////////////////////////////

class FasciaFactory : public ItemFactory 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_FASCIA; }
	virtual string getItemClassName()  { return "Fascia"; }

public:
	virtual Item* createItem(ItemType_t ItemType, const list<OptionType_t>& OptionType) throw() { return new Fascia(ItemType,OptionType); }
};


//////////////////////////////////////////////////////////////////////////////
// class FasciaLoader;
//////////////////////////////////////////////////////////////////////////////

class FasciaLoader : public ItemLoader 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_FASCIA; }
	virtual string getItemClassName()  { return "Fascia"; }

public:
	virtual void load(Creature* pCreature) throw(Error);
	virtual void load(Zone* pZone) throw(Error);
	virtual void load(StorageID_t storageID, Inventory* pInventory) throw(Error);
};

extern FasciaLoader* g_pFasciaLoader;

#endif
