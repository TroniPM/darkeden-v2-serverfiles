//////////////////////////////////////////////////////////////////////////////
// Filename    : BloodBible.h
// Written By  : Changaya
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __BLOOD_BIBLE_H__
#define __BLOOD_BIBLE_H__

#include "Item.h"
#include "ItemInfo.h"
#include "InfoClassManager.h"
#include "ItemFactory.h"
#include "ItemLoader.h"
#include "Mutex.h"

//////////////////////////////////////////////////////////////////////////////
// class BloodBible;
//////////////////////////////////////////////////////////////////////////////

class BloodBible : public Item 
{
public:
	BloodBible() throw();
	BloodBible(ItemType_t itemType, const list<OptionType_t>& optionType) throw();
	
public:
	virtual void create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID=0) throw(Error);
	virtual void save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y) throw(Error);
	void tinysave(const string & field) const throw (Error)	{ tinysave(field.c_str()); }
	void tinysave(const char* field) ;
	virtual string toString() ;

	static void initItemIDRegistry(void) throw();

public:
	virtual ItemClass getItemClass()  { return Item::ITEM_CLASS_BLOOD_BIBLE; }
	virtual string getObjectTableName()  { return "BloodBibleObject"; }

	virtual ItemType_t getItemType()  { return m_ItemType; }
	virtual void setItemType(ItemType_t itemType) throw() { m_ItemType = itemType; }

	virtual VolumeWidth_t getVolumeWidth() ;
	virtual VolumeHeight_t getVolumeHeight() ;
	virtual Weight_t getWeight() ;

public:
	virtual Durability_t getDurability()  { return m_Durability; }
	void setDurability(Durability_t durability) throw(Error) { m_Durability = durability; }

	virtual Defense_t getDefenseBonus() ;
	virtual Protection_t getProtectionBonus() ;

	virtual EnchantLevel_t getEnchantLevel()  { return m_EnchantLevel; }
	virtual void setEnchantLevel(EnchantLevel_t level) throw() { m_EnchantLevel = level; }

private:
	ItemType_t			m_ItemType;			// ������ Ÿ��
	Durability_t		m_Durability;		// ������
	EnchantLevel_t		m_EnchantLevel; 
	
	static Mutex    m_Mutex;          // ������ ID ���� ��
	static ItemID_t m_ItemIDRegistry; // Ŭ������ ���� ������ ���̵� �߱ޱ�
};

//////////////////////////////////////////////////////////////////////////////
// class BloodBibleInfo;
//////////////////////////////////////////////////////////////////////////////
class BloodBibleInfo : public ItemInfo 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_BLOOD_BIBLE; }

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
	Durability_t		m_Durability;		// ������
	Defense_t			m_DefenseBonus;		// ���߷� ���ʽ�
	Protection_t		m_ProtectionBonus;
	uint				m_ItemLevel;

};


//////////////////////////////////////////////////////////////////////////////
// class BloodBibleInfoManager;
//////////////////////////////////////////////////////////////////////////////

class BloodBibleInfoManager : public InfoClassManager 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_BLOOD_BIBLE; }
	virtual void load() throw(Error);
};

// global variable declaration
extern BloodBibleInfoManager* g_pBloodBibleInfoManager;


//////////////////////////////////////////////////////////////////////////////
// class BloodBibleFactory
//////////////////////////////////////////////////////////////////////////////

class BloodBibleFactory : public ItemFactory 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_BLOOD_BIBLE; }
	virtual string getItemClassName()  { return "BloodBible"; }
	
public:
	virtual Item* createItem(ItemType_t ItemType, const list<OptionType_t>& OptionType) throw() { return new BloodBible(ItemType,OptionType); }
};


//////////////////////////////////////////////////////////////////////////////
// class BloodBibleLoader;
//////////////////////////////////////////////////////////////////////////////

class BloodBibleLoader : public ItemLoader 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_BLOOD_BIBLE; }
	virtual string getItemClassName()  { return "BloodBible"; }

public:
	virtual void load(Creature* pCreature) throw(Error);
	virtual void load(Zone* pZone) throw(Error);
	virtual void load(StorageID_t storageID, Inventory* pInventory) throw(Error);
};

extern BloodBibleLoader* g_pBloodBibleLoader;
#endif
