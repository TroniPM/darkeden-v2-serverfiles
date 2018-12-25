//////////////////////////////////////////////////////////////////////////////
// Filename    : Persona.h
// Written By  : Elca
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __PERSONA_H__
#define __PERSONA_H__

#include "Item.h"
#include "ConcreteItem.h"
#include "ItemPolicies.h"
#include "ItemInfo.h"
#include "InfoClassManager.h"
#include "ItemFactory.h"
#include "ItemLoader.h"
#include "Mutex.h"

//////////////////////////////////////////////////////////////////////////////
// class Persona;
//////////////////////////////////////////////////////////////////////////////

class Persona : public ConcreteItem<Item::ITEM_CLASS_PERSONA, NoStack, HasDurability, HasOption, GroceryGrade, NoAttacking, NoEnchantLevel, HasOption2, HasHeroOption, HasHeroOptionAttr>
{
public:
	Persona() throw();
	Persona(ItemType_t itemType, const list<OptionType_t>& optionType) throw();
	
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
// class PersonaInfo
//////////////////////////////////////////////////////////////////////////////

class PersonaInfo : public ItemInfo 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_PERSONA; }

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
	Durability_t	m_Durability;		// ������
	Defense_t		m_DefenseBonus;		// ���߷� ���ʽ�
	Protection_t	m_ProtectionBonus;
	uint			m_ItemLevel;

};


//////////////////////////////////////////////////////////////////////////////
// class PersonaInfoManager;
//////////////////////////////////////////////////////////////////////////////

class PersonaInfoManager : public InfoClassManager 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_PERSONA; }
	virtual void load() throw(Error);
};

// global variable declaration
extern PersonaInfoManager* g_pPersonaInfoManager;


//////////////////////////////////////////////////////////////////////////////
// class PersonaFactory
//////////////////////////////////////////////////////////////////////////////

class PersonaFactory : public ItemFactory 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_PERSONA; }
	virtual string getItemClassName()  { return "Persona"; }
	
public:
	virtual Item* createItem(ItemType_t ItemType, const list<OptionType_t>& OptionType) throw() { return new Persona(ItemType,OptionType); }
};

//////////////////////////////////////////////////////////////////////////////
// class PersonaLoader;
//////////////////////////////////////////////////////////////////////////////

class PersonaLoader : public ItemLoader 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_PERSONA; }
	virtual string getItemClassName()  { return "Persona"; }

public:
	virtual void load(Creature* pCreature) throw(Error);
	virtual void load(Zone* pZone) throw(Error);
	virtual void load(StorageID_t storageID, Inventory* pInventory) throw(Error);
};

extern PersonaLoader* g_pPersonaLoader;

#endif
