//////////////////////////////////////////////////////////////////////////////
// Filename    : VampireWeapon.h
// Written By  : Elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __VAMPIRE_WEAPON_H__
#define __VAMPIRE_WEAPON_H__

#include "Item.h"
#include "ConcreteItem.h"
#include "ItemPolicies.h"
#include "ItemInfo.h"
#include "InfoClassManager.h"
#include "ItemFactory.h"
#include "ItemLoader.h"
#include "Mutex.h"


//////////////////////////////////////////////////////////////////////////////
// class VampireWeapon;
//////////////////////////////////////////////////////////////////////////////

class VampireWeapon : public ConcreteItem<Item::ITEM_CLASS_VAMPIRE_WEAPON, NoStack, HasDurability, HasOption, WeaponGrade, Weapon,   NoEnchantLevel, HasOption2, HasHeroOption, HasHeroOptionAttr>
{
public:
	VampireWeapon() throw();
	VampireWeapon(ItemType_t itemType, const list<OptionType_t>& optionType) throw();
	
public:
	virtual void create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID=0);
	virtual void save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y);
	void tinysave(const string & field) 	{ tinysave(field.c_str()); }
	void tinysave(const char* field) ;
	virtual string toString() ;

	static void initItemIDRegistry(void) throw();

public:
//	virtual ItemClass getItemClass()  { return Item::ITEM_CLASS_VAMPIRE_WEAPON; }
//	virtual string getObjectTableName()  { return "VampireWeaponObject"; }

/*	virtual ItemType_t getItemType()  { return m_ItemType; }
	virtual void setItemType(ItemType_t itemType) throw() { m_ItemType = itemType; }

	virtual bool hasOptionType()  { return !m_OptionType.empty(); }
	virtual int getOptionTypeSize()  { return m_OptionType.size(); }
	virtual int getRandomOptionType()  { if (m_OptionType.empty()) return 0; int pos = rand()%m_OptionType.size(); list<OptionType_t>::const_iterator itr = m_OptionType.begin(); for (int i=0; i<pos; i++) itr++; return *itr; }
	virtual const list<OptionType_t>& getOptionTypeList()  { return m_OptionType; }
	virtual OptionType_t getFirstOptionType()  { if (m_OptionType.empty()) return 0; return m_OptionType.front(); }
	virtual void removeOptionType(OptionType_t OptionType) throw() { list<OptionType_t>::iterator itr = find(m_OptionType.begin(), m_OptionType.end(), OptionType); if (itr!=m_OptionType.end()) m_OptionType.erase(itr); }
	virtual void changeOptionType(OptionType_t currentOptionType, OptionType_t newOptionType) throw() { list<OptionType_t>::iterator itr = find(m_OptionType.begin(), m_OptionType.end(), currentOptionType); if (itr!=m_OptionType.end()) *itr=newOptionType; }
	virtual void addOptionType(OptionType_t OptionType) throw() { m_OptionType.push_back(OptionType); }
	virtual void setOptionType(const list<OptionType_t>& OptionType) throw() { m_OptionType = OptionType; }

	virtual VolumeWidth_t getVolumeWidth() ;
	virtual VolumeHeight_t getVolumeHeight() ;
	virtual Weight_t getWeight() ;

	virtual Durability_t getDurability()  { return m_Durability; }
	void setDurability(Durability_t durability) throw(Error) { m_Durability = durability; }

	virtual Damage_t getMinDamage() ;
	virtual Damage_t getMaxDamage() ;

	Damage_t getBonusDamage()  { return m_BonusDamage;}
	void setBonusDamage(Damage_t damage) throw() { m_BonusDamage = damage;}
*/
//	virtual int getCriticalBonus(void) ;

private:
//	ItemType_t     m_ItemType;
//	list<OptionType_t>   m_OptionType;
//	Durability_t   m_Durability;
//	BYTE           m_BonusDamage;
	
	static Mutex    m_Mutex;          // 아이템 ID 관련 락
	static ItemID_t m_ItemIDRegistry; // 클래스별 고유 아이템 아이디 발급기
};


//////////////////////////////////////////////////////////////////////////////
// class VampireWeaponInfo
//////////////////////////////////////////////////////////////////////////////

class VampireWeaponInfo : public ItemInfo 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_VAMPIRE_WEAPON; }

	virtual Durability_t getDurability()  { return m_Durability; }
	virtual void setDurability(Durability_t durability) throw() { m_Durability = durability; }

	virtual Damage_t getMinDamage()  { return m_MinDamage; }
	virtual void setMinDamage(Damage_t minDamage) throw() { m_MinDamage = minDamage; }

	virtual Damage_t getMaxDamage()  { return m_MaxDamage; }
	virtual void setMaxDamage(Damage_t maxDamage) throw() { m_MaxDamage = maxDamage; }

	Range_t getRange()  { return m_Range; }
	void setRange(Range_t range) throw() { m_Range = range; }

//	ToHit_t getToHitBonus()  { return m_ToHitBonus; }
//	void setToHitBonus(ToHit_t tohit) throw() { m_ToHitBonus = tohit; }

	virtual Speed_t getSpeed(void)  { return m_Speed; }
	virtual void setSpeed(Speed_t speed) throw() { m_Speed = speed; }

	virtual uint getItemLevel(void)  { return m_ItemLevel; }
	virtual void setItemLevel(uint level) throw() { m_ItemLevel = level; }

	virtual int getCriticalBonus(void)  { return m_CriticalBonus; }
	virtual void setCriticalBonus(int bonus) throw() { m_CriticalBonus = bonus; }

	virtual string toString() ;

private:
	Durability_t   m_Durability;
	Damage_t       m_MinDamage;
	Damage_t       m_MaxDamage;
	Range_t        m_Range;
//	ToHit_t        m_ToHitBonus;
	Speed_t        m_Speed;
	uint           m_ItemLevel;
	int            m_CriticalBonus; // 아이템마다 다른 크리티컬 확률

};


//////////////////////////////////////////////////////////////////////////////
// class VampireWeaponInfoManager;
//////////////////////////////////////////////////////////////////////////////

class VampireWeaponInfoManager : public InfoClassManager 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_VAMPIRE_WEAPON; }
	virtual void load();

};

extern VampireWeaponInfoManager* g_pVampireWeaponInfoManager;


//////////////////////////////////////////////////////////////////////////////
// class VampireWeaponFactory
//////////////////////////////////////////////////////////////////////////////

class VampireWeaponFactory : public ItemFactory 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_VAMPIRE_WEAPON; }
	virtual string getItemClassName()  { return "VampireWeapon"; }
	
public:
	virtual Item* createItem(ItemType_t ItemType, const list<OptionType_t>& OptionType) throw() { return new VampireWeapon(ItemType,OptionType); }
};


//////////////////////////////////////////////////////////////////////////////
// class VampireWeaponLoader;
//////////////////////////////////////////////////////////////////////////////

class VampireWeaponLoader : public ItemLoader 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_VAMPIRE_WEAPON; }
	virtual string getItemClassName()  { return "VampireWeapon"; }

public:
	virtual void load(Creature* pCreature);
	virtual void load(Zone* pZone);
	virtual void load(StorageID_t storageID, Inventory* pInventory);

};

extern VampireWeaponLoader* g_pVampireWeaponLoader;

#endif
