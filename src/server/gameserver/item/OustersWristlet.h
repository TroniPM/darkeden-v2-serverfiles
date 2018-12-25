//////////////////////////////////////////////////////////////////////////////
// Filename    : OustersWristlet.h
// Written By  :
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __OUSTERS_WRISTLET_H__
#define __OUSTERS_WRISTLET_H__

#include "Item.h"
#include "ConcreteItem.h"
#include "ItemPolicies.h"
#include "ItemInfo.h"
#include "InfoClassManager.h"
#include "ItemFactory.h"
#include "ItemLoader.h"
#include "Mutex.h"

//////////////////////////////////////////////////////////////////////////////
// class OustersWristlet;
//////////////////////////////////////////////////////////////////////////////

class OustersWristlet : public ConcreteItem<Item::ITEM_CLASS_OUSTERS_WRISTLET, NoStack, HasDurability, HasOption, WeaponGrade, Weapon, NoEnchantLevel, HasOption2, HasHeroOption, HasHeroOptionAttr>
{
public:
	OustersWristlet() throw();
	OustersWristlet(ItemType_t itemType, const list<OptionType_t>& optionType) throw();
	
public:
	virtual void create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID=0) throw(Error);
	virtual void save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y) throw(Error);
	void tinysave(const string & field) const throw (Error)	{ tinysave(field.c_str()); }
	void tinysave(const char* field) const throw (Error);
	virtual string toString() ;

	static void initItemIDRegistry(void) throw();

public:
//	virtual ItemClass getItemClass()  { return Item::ITEM_CLASS_OUSTERS_WRISTLET; }
//	virtual string getObjectTableName()  { return "OustersWristletObject"; }

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

	virtual VolumeWidth_t getVolumeWidth() const throw(Error);
	virtual VolumeHeight_t getVolumeHeight() const throw(Error);
	virtual Weight_t getWeight() const throw(Error);

	virtual Durability_t getDurability() const throw(Error) { return m_Durability; }
	void setDurability(Durability_t durability) throw(Error) { m_Durability = durability; }

	virtual Damage_t getMinDamage() const throw(Error);
	virtual Damage_t getMaxDamage() const throw(Error);

	Damage_t getBonusDamage()  { return m_BonusDamage;}
	void setBonusDamage(Damage_t damage) throw() { m_BonusDamage = damage;}
*/
//	virtual int getCriticalBonus(void) ;

	virtual ElementalType getElementalType() const;
	virtual Elemental_t getElemental() const;

private:
//	ItemType_t     m_ItemType;
//	list<OptionType_t>   m_OptionType;
//	Durability_t   m_Durability;
//	BYTE           m_BonusDamage;

	static Mutex    m_Mutex;          // ������ ID ���� ��
	static ItemID_t m_ItemIDRegistry; // Ŭ������ ���� ������ ���̵� �߱ޱ�
};


//////////////////////////////////////////////////////////////////////////////
// class OustersWristletInfo
//////////////////////////////////////////////////////////////////////////////

class OustersWristletInfo : public ItemInfo 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_OUSTERS_WRISTLET; }

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

	virtual ElementalType getElementalType() const { return m_ElementalType; }
	void setElementalType( ElementalType elementalType ) { m_ElementalType = elementalType; }

	virtual Elemental_t getElemental() const { return m_Elemental; }
	void setElemental( Elemental_t elemental ) { m_Elemental = elemental; }

	virtual string toString() ;

private:
	Durability_t   m_Durability;
	Damage_t       m_MinDamage;
	Damage_t       m_MaxDamage;
	Range_t        m_Range;
//	ToHit_t        m_ToHitBonus;
	Speed_t        m_Speed;
	uint           m_ItemLevel;
	int            m_CriticalBonus; // �����۸��� �ٸ� ũ��Ƽ�� Ȯ��

	ElementalType m_ElementalType;
	Elemental_t   m_Elemental;
};


//////////////////////////////////////////////////////////////////////////////
// class OustersWristletInfoManager;
//////////////////////////////////////////////////////////////////////////////

class OustersWristletInfoManager : public InfoClassManager 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_OUSTERS_WRISTLET; }
	virtual void load() throw(Error);

};

extern OustersWristletInfoManager* g_pOustersWristletInfoManager;


//////////////////////////////////////////////////////////////////////////////
// class OustersWristletFactory
//////////////////////////////////////////////////////////////////////////////

class OustersWristletFactory : public ItemFactory 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_OUSTERS_WRISTLET; }
	virtual string getItemClassName()  { return "OustersWristlet"; }
	
public:
	virtual Item* createItem(ItemType_t ItemType, const list<OptionType_t>& OptionType) throw() { return new OustersWristlet(ItemType,OptionType); }
};


//////////////////////////////////////////////////////////////////////////////
// class OustersWristletLoader;
//////////////////////////////////////////////////////////////////////////////

class OustersWristletLoader : public ItemLoader 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_OUSTERS_WRISTLET; }
	virtual string getItemClassName()  { return "OustersWristlet"; }

public:
	virtual void load(Creature* pCreature) throw(Error);
	virtual void load(Zone* pZone) throw(Error);
	virtual void load(StorageID_t storageID, Inventory* pInventory) throw(Error);

};

extern OustersWristletLoader* g_pOustersWristletLoader;

#endif
