//////////////////////////////////////////////////////////////////////////////
// Filename    : Mace.h
// Written By  : Elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __MACE_H__
#define __MACE_H__

#include "Item.h"
#include "ConcreteItem.h"
#include "ItemPolicies.h"
#include "ItemInfo.h"
#include "InfoClassManager.h"
#include "ItemFactory.h"
#include "ItemLoader.h"
#include "Mutex.h"

//////////////////////////////////////////////////////////////////////////////
// class Mace;
//////////////////////////////////////////////////////////////////////////////

class Mace : public ConcreteItem<Item::ITEM_CLASS_MACE, NoStack, HasDurability, HasOption, WeaponGrade, SlayerWeapon, NoEnchantLevel, HasOption2, HasHeroOption, HasHeroOptionAttr>
{
public:
	Mace() throw();
	Mace(ItemType_t itemType, const list<OptionType_t>& optionType) throw();
	
public:
	virtual void create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID=0);
	virtual void save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y);
	void tinysave(const string & field) 	{ tinysave(field.c_str()); }
	void tinysave(const char* field) ;
	virtual string toString() ;

	static void initItemIDRegistry(void) throw();

public:
//	virtual ItemClass getItemClass()  { return Item::ITEM_CLASS_MACE; }
//	virtual string getObjectTableName()  { return "MaceObject"; }

/*	virtual ItemType_t getItemType()  { return m_ItemType; }
	virtual void setItemType(ItemType_t itemType) throw() { m_ItemType = itemType; }

	bool isSilverWeapon()  { return true; }

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
	MP_t getMPBonus() ;
/*
	virtual Silver_t getSilver()  { return m_Silver; }
	virtual void setSilver(Silver_t amount) throw() { m_Silver = amount; }
*/
//	virtual int getCriticalBonus(void) ;
	
private:
//	ItemType_t     m_ItemType;
//	list<OptionType_t>   m_OptionType;
//	Durability_t   m_Durability;
//	BYTE           m_BonusDamage;
//	Silver_t       m_Silver;
	
	static Mutex    m_Mutex;          // ������ ID ���� ��
	static ItemID_t m_ItemIDRegistry; // Ŭ������ ���� ������ ���̵� �߱ޱ�
};


//////////////////////////////////////////////////////////////////////////////
// class MaceInfo
//////////////////////////////////////////////////////////////////////////////

class MaceInfo : public ItemInfo 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_MACE; }

	virtual Durability_t getDurability()  { return m_Durability; }
	virtual void setDurability(Durability_t durability) throw() { m_Durability = durability; }

	virtual Damage_t getMinDamage()  { return m_MinDamage; }
	virtual void setMinDamage(Damage_t minDamage) throw() { m_MinDamage = minDamage; }

	virtual Damage_t getMaxDamage()  { return m_MaxDamage; }
	virtual void setMaxDamage(Damage_t maxDamage) throw() { m_MaxDamage = maxDamage; }

	virtual MP_t getMPBonus()  { return m_MPBonus; }
	void setMPBonus(MP_t mpBonus) throw() { m_MPBonus = mpBonus; }

	virtual Silver_t getMaxSilver()  { return m_MaxSilver; }
	virtual void setMaxSilver(Silver_t amount) throw() { m_MaxSilver = amount; }

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
	MP_t           m_MPBonus;
	Silver_t       m_MaxSilver;
	Speed_t        m_Speed;
	uint           m_ItemLevel;
	int            m_CriticalBonus; // �����۸��� �ٸ� ũ��Ƽ�� Ȯ��

};


//////////////////////////////////////////////////////////////////////////////
// class MaceInfoManager;
//////////////////////////////////////////////////////////////////////////////

class MaceInfoManager : public InfoClassManager 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_MACE; }
	virtual void load();

};

extern MaceInfoManager* g_pMaceInfoManager;


//////////////////////////////////////////////////////////////////////////////
// class MaceFactory
//////////////////////////////////////////////////////////////////////////////

class MaceFactory : public ItemFactory 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_MACE; }
	virtual string getItemClassName()  { return "Mace"; }
	
public:
	virtual Item* createItem(ItemType_t ItemType, const list<OptionType_t>& OptionType) throw() { return new Mace(ItemType,OptionType); }

};


//////////////////////////////////////////////////////////////////////////////
// class MaceLoader;
//////////////////////////////////////////////////////////////////////////////

class MaceLoader : public ItemLoader 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_MACE; }
	virtual string getItemClassName()  { return "Mace"; }

public:
	virtual void load(Creature* pCreature);
	virtual void load(Zone* pZone);
	virtual void load(StorageID_t storageID, Inventory* pInventory);

};

extern MaceLoader* g_pMaceLoader;

#endif
