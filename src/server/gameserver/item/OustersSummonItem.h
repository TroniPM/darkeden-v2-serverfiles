//////////////////////////////////////////////////////////////////////////////
// Filename    : OustersSummonItem.h
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __OUSTERS_SUMMON_ITEM_H__
#define __OUSTERS_SUMMON_ITEM_H__

#include "Item.h"
#include "ItemInfo.h"
#include "InfoClassManager.h"
#include "ItemFactory.h"
#include "ItemLoader.h"
#include "Mutex.h"

//////////////////////////////////////////////////////////////////////////////
// class OustersSummonItem;
//////////////////////////////////////////////////////////////////////////////

class OustersSummonItem : public Item 
{
public:
	OustersSummonItem() throw();
	OustersSummonItem(ItemType_t itemType, const list<OptionType_t>& optionType) throw();
	
public:
	virtual void create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID=0);
	virtual void save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y);
	void tinysave(const string & field) 	{ tinysave(field.c_str()); }
	void tinysave(const char* field) ;

	static void initItemIDRegistry(void) throw();

public:
	virtual ItemClass getItemClass()  { return Item::ITEM_CLASS_OUSTERS_SUMMON_ITEM; }
	virtual string getObjectTableName()  { return "OustersSummonItemObject"; }

	virtual ItemType_t getItemType()  { return m_ItemType; }
	virtual void setItemType(ItemType_t itemType) throw() { m_ItemType = itemType; }

	virtual VolumeWidth_t getVolumeWidth() ;
	virtual VolumeHeight_t getVolumeHeight() ;
	virtual Weight_t getWeight() ;

	virtual string toString() ;

public:
	int getCharge(void) const { return m_Charge; }
	void setCharge(int charge) { m_Charge = charge; }

	int getMaxCharge(void) ;

public:
	virtual EnchantLevel_t getEnchantLevel()  { return m_Charge; }

private:
	ItemType_t m_ItemType; // ������ Ÿ��
	int        m_Charge;   // ��Ż�� �� �� �ִ� Ƚ��
	
	static Mutex    m_Mutex;          // ������ ID ���� ��
	static ItemID_t m_ItemIDRegistry; // Ŭ������ ���� ������ ���̵� �߱ޱ�
};


//////////////////////////////////////////////////////////////////////////////
// class OustersSummonItemInfo
//////////////////////////////////////////////////////////////////////////////

class OustersSummonItemInfo : public ItemInfo 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_OUSTERS_SUMMON_ITEM; }
	virtual string toString() ;

public:
	int getMaxCharge(void) const { return m_MaxCharge; }
	void setMaxCharge(int charge) { m_MaxCharge = charge; }

	EffectID_t getEffectID(void) const { return m_EffectID; }
	void setEffectID(int effectID) { m_EffectID = effectID; }

private:
	int m_MaxCharge;
	EffectID_t m_EffectID;
};


//////////////////////////////////////////////////////////////////////////////
// class OustersSummonItemInfoManager;
//////////////////////////////////////////////////////////////////////////////

class OustersSummonItemInfoManager : public InfoClassManager 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_OUSTERS_SUMMON_ITEM; }
	virtual void load();
};

extern OustersSummonItemInfoManager* g_pOustersSummonItemInfoManager;


//////////////////////////////////////////////////////////////////////////////
// class OustersSummonItemFactory
//////////////////////////////////////////////////////////////////////////////

class OustersSummonItemFactory : public ItemFactory 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_OUSTERS_SUMMON_ITEM; }
	virtual string getItemClassName()  { return "OustersSummonItem"; }
	
public:
	virtual Item* createItem(ItemType_t ItemType, const list<OptionType_t>& OptionType) throw() { return new OustersSummonItem(ItemType,OptionType); }
};


//////////////////////////////////////////////////////////////////////////////
// class OustersSummonItemLoader;
//////////////////////////////////////////////////////////////////////////////

class OustersSummonItemLoader : public ItemLoader 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_OUSTERS_SUMMON_ITEM; }
	virtual string getItemClassName()  { return "OustersSummonItem"; }

public:
	virtual void load(Creature* pCreature);
	virtual void load(Zone* pZone);
	virtual void load(StorageID_t storageID, Inventory* pInventory);

};

extern OustersSummonItemLoader* g_pOustersSummonItemLoader;

#endif
