//////////////////////////////////////////////////////////////////////////////
// Filename    : OustersStone.h
// Written By  :
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __STONEABILITY_H__
#define __STONEABILITY_H__

#include "Item.h"
#include "ConcreteItem.h"
#include "ItemPolicies.h"
#include "ItemInfo.h"
#include "InfoClassManager.h"
#include "ItemFactory.h"
#include "ItemLoader.h"
#include "Mutex.h"

//////////////////////////////////////////////////////////////////////////////
// class OustersStone;
//////////////////////////////////////////////////////////////////////////////

class StoneAbility : public ConcreteItem<Item::ITEM_CLASS_STONE_ABILITY, NoStack, HasDurability, HasOption, ClothGrade, NoAttacking,  NoEnchantLevel, HasOption2, HasHeroOption, HasHeroOptionAttr>
{
public:
	StoneAbility() throw();
	StoneAbility(ItemType_t itemType, const list<OptionType_t>& optionType) throw();
	
public:
	virtual void create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID=0) throw(Error);
	virtual void save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y) throw(Error);
	void tinysave(const string & field) const throw (Error)	{ tinysave(field.c_str()); }
	void tinysave(const char* field) const throw (Error);
	virtual string toString() const throw();

	static void initItemIDRegistry(void) throw();

public:
	virtual ElementalType getElementalType() const;
	virtual Elemental_t getElemental() const;

private:	
	static Mutex    m_Mutex;          // 아이템 ID 관련 락
	static ItemID_t m_ItemIDRegistry; // 클래스별 고유 아이템 아이디 발급기
};


//////////////////////////////////////////////////////////////////////////////
// class StoneAbilityInfo
//////////////////////////////////////////////////////////////////////////////

class StoneAbilityInfo : public ItemInfo 
{
public:
	virtual Item::ItemClass getItemClass() const throw() { return Item::ITEM_CLASS_STONE_ABILITY; }

	virtual Durability_t getDurability() const throw() { return m_Durability; }
	virtual void setDurability(Durability_t durability) throw() { m_Durability = durability; }

	Defense_t getDefenseBonus() const throw() { return m_DefenseBonus; }
	void setDefenseBonus(Defense_t acBonus) throw() { m_DefenseBonus = acBonus; }

	Protection_t getProtectionBonus() const throw() { return m_ProtectionBonus; }
	void setProtectionBonus(Protection_t acBonus) throw() { m_ProtectionBonus = acBonus; }

	virtual uint getItemLevel(void) const throw() { return m_ItemLevel; }
	virtual void setItemLevel(uint level) throw() { m_ItemLevel = level; }

    virtual ElementalType getElementalType() const { return m_ElementalType; }
	void setElementalType( ElementalType elementalType ) { m_ElementalType = elementalType; }

	virtual Elemental_t getElemental() const { return m_Elemental; }
	void setElemental( Elemental_t elemental ) { m_Elemental = elemental; }

	virtual string toString() const throw();

private:
	Durability_t	m_Durability;		// 내구성
	Defense_t		m_DefenseBonus;
	Protection_t	m_ProtectionBonus;
	uint			m_ItemLevel;

	ElementalType m_ElementalType;
	Elemental_t   m_Elemental;
};


//////////////////////////////////////////////////////////////////////////////
// class StoneAbilityInfoManager;
//////////////////////////////////////////////////////////////////////////////

class StoneAbilityInfoManager : public InfoClassManager 
{
public:
	virtual Item::ItemClass getItemClass() const throw() { return Item::ITEM_CLASS_STONE_ABILITY; }
	virtual void load() throw(Error);
};

// global variable declaration
extern StoneAbilityInfoManager* g_pStoneAbilityInfoManager;


//////////////////////////////////////////////////////////////////////////////
// class StoneAbilityFactory
//////////////////////////////////////////////////////////////////////////////

class StoneAbilityFactory : public ItemFactory 
{
public:
	virtual Item::ItemClass getItemClass() const throw() { return Item::ITEM_CLASS_STONE_ABILITY; }
	virtual string getItemClassName() const throw() { return "StoneAbility"; }

public:
	virtual Item* createItem(ItemType_t ItemType, const list<OptionType_t>& OptionType) throw() { return new StoneAbility(ItemType,OptionType); }
};


//////////////////////////////////////////////////////////////////////////////
// class StoneAbilityLoader;
//////////////////////////////////////////////////////////////////////////////

class StoneAbilityLoader : public ItemLoader 
{
public:
	virtual Item::ItemClass getItemClass() const throw() { return Item::ITEM_CLASS_STONE_ABILITY; }
	virtual string getItemClassName() const throw() { return "StoneAbility"; }

public:
	virtual void load(Creature* pCreature) throw(Error);
	virtual void load(Zone* pZone) throw(Error);
	virtual void load(StorageID_t storageID, Inventory* pInventory) throw(Error);
};

extern StoneAbilityLoader* g_pStoneAbilityLoader;

#endif
