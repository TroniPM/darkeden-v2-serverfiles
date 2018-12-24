//////////////////////////////////////////////////////////////////////////////
// Filename    : PetEnchantItem.h
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __PET_ENCHANT_ITEM_H__
#define __PET_ENCHANT_ITEM_H__

#include "Item.h"
#include "ItemInfo.h"
#include "InfoClassManager.h"
#include "ItemFactory.h"
#include "ItemLoader.h"
#include "Mutex.h"
#include "ConcreteItem.h"
#include "ItemPolicies.h"
#include "types/PetTypes.h"
#include "Types.h"
#include <list>

//////////////////////////////////////////////////////////////////////////////
// class PetEnchantItem;
//////////////////////////////////////////////////////////////////////////////

class PetEnchantItem : public ConcreteItem<Item::ITEM_CLASS_PET_ENCHANT_ITEM, Stackable, NoDurability, HasOption, NoGrade, NoAttacking, NoEnchantLevel>
{
public:
	PetEnchantItem() throw();
	PetEnchantItem(ItemType_t itemType, const list<OptionType_t>& optionType, ItemNum_t Num) throw();
	
public:
	virtual void create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID=0) throw(Error);
	virtual void save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y) throw(Error);
	void tinysave(const string & field) const throw (Error)	{ tinysave(field.c_str()); }
	void tinysave(const char* field) const throw (Error);
	virtual string toString() const throw();

	static void initItemIDRegistry(void) throw();

public:
	virtual ItemClass getItemClass() const throw() { return Item::ITEM_CLASS_PET_ENCHANT_ITEM; }
	virtual string getObjectTableName() const throw() { return "PetEnchantItemObject"; }

	virtual ItemType_t getItemType() const throw() { return m_ItemType; }
	virtual void setItemType(ItemType_t itemType) throw() { m_ItemType = itemType; }

	virtual VolumeWidth_t getVolumeWidth() const throw(Error);
	virtual VolumeHeight_t getVolumeHeight() const throw(Error);
	virtual Weight_t getWeight() const throw(Error);

	virtual ItemNum_t getNum() const throw() { return m_Num; }
	virtual void setNum(ItemNum_t Num) throw() { m_Num = Num; }

	void makePCItemInfo(PCItemInfo& result) const;

	bool    isStackable() const throw() { return true; }

private:
	ItemType_t m_ItemType;
	ItemNum_t m_Num;
	
	static Mutex    m_Mutex;          // ������ ID ���� ��
	static ItemID_t m_ItemIDRegistry; // Ŭ������ ���� ������ ���̵� �߱ޱ�
};

//////////////////////////////////////////////////////////////////////////////
// class PetEnchantItemInfo
//////////////////////////////////////////////////////////////////////////////

class PetEnchantItemInfo : public ItemInfo 
{
public:
	enum PetEnchantFunctions
	{
		ENCHANT_FUNCTION = 0,
		SPEC_OPTION_FUNCTION = 1,
		PET_AMPUL_FUNCTION = 2,
		REVIVAL_FUNCTION = 13,
		RARE_FUNCTION = 14,
		MUTANT_FUNCTION = 15,
		PET_ATTRCLEAR_FUNCTION = 22,
		PET_MAGIC_FUNCTION = 23,
		PET_EXPERT_FUNCTION = 24,
		PET_RED_FUNCTION = 25,
		PET_SHOCK_FUNCTION = 26,
		PET_ICE_FUNCTION = 27,
		PET_DIET_FUNCTION = 28,
		PET_MIXING_CLEANER_FUNCTION = 29,
	};

	virtual Item::ItemClass getItemClass() const throw() { return Item::ITEM_CLASS_PET_ENCHANT_ITEM; }
	virtual string toString() const throw();

	BYTE getFunction() const { return m_Function; }
	void setFunction( BYTE Function ) { m_Function = Function; }

	int getFunctionGrade() const { return m_FunctionGrade; }
	void setFunctionGrade( int Grade ) { m_FunctionGrade = Grade; }


private :
	BYTE m_Function;
	int m_FunctionGrade;
};

//////////////////////////////////////////////////////////////////////////////
// class PetEnchantItemInfoManager;
//////////////////////////////////////////////////////////////////////////////

class PetEnchantItemInfoManager : public InfoClassManager 
{
public:
	virtual Item::ItemClass getItemClass() const throw() { return Item::ITEM_CLASS_PET_ENCHANT_ITEM; }
	virtual void load() throw(Error);
};

extern PetEnchantItemInfoManager* g_pPetEnchantItemInfoManager;

//////////////////////////////////////////////////////////////////////////////
// class PetEnchantItemFactory
//////////////////////////////////////////////////////////////////////////////

class PetEnchantItemFactory : public ItemFactory 
{
public:
	virtual Item::ItemClass getItemClass() const throw() { return Item::ITEM_CLASS_PET_ENCHANT_ITEM; }
	virtual string getItemClassName() const throw() { return "PetEnchantItem"; }
	
public:
	virtual Item* createItem(ItemType_t ItemType, const list<OptionType_t>& OptionType) throw() { return new PetEnchantItem(ItemType,OptionType,1); }
};

//////////////////////////////////////////////////////////////////////////////
// class PetEnchantItemLoader;
//////////////////////////////////////////////////////////////////////////////

class PetEnchantItemLoader : public ItemLoader 
{
public:
	virtual Item::ItemClass getItemClass() const throw() { return Item::ITEM_CLASS_PET_ENCHANT_ITEM; }
	virtual string getItemClassName() const throw() { return "PetEnchantItem"; }

public:
	virtual void load(Creature* pCreature) throw(Error);
	virtual void load(Zone* pZone) throw(Error);
	virtual void load(StorageID_t storageID, Inventory* pInventory) throw(Error);
};

extern PetEnchantItemLoader* g_pPetEnchantItemLoader;

#endif
