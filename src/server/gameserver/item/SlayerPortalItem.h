//////////////////////////////////////////////////////////////////////////////
// Filename    : SlayerPortalItem.h
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SLAYER_PORTAL_ITEM_H__
#define __SLAYER_PORTAL_ITEM_H__

#include "Item.h"
#include "ItemInfo.h"
#include "InfoClassManager.h"
#include "ItemFactory.h"
#include "ItemLoader.h"
#include "Mutex.h"

//////////////////////////////////////////////////////////////////////////////
// class SlayerPortalItem;
//////////////////////////////////////////////////////////////////////////////

class SlayerPortalItem : public Item 
{
public:
	SlayerPortalItem() throw();
	SlayerPortalItem(ItemType_t itemType, const list<OptionType_t>& optionType) throw();
	
public:
	virtual void create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID=0);
	virtual void save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y);
	void tinysave(const string & field) 	{ tinysave(field.c_str()); }
	void tinysave(const char* field) ;

	static void initItemIDRegistry(void) throw();

public:
	virtual ItemClass getItemClass()  { return Item::ITEM_CLASS_SLAYER_PORTAL_ITEM; }
	virtual string getObjectTableName()  { return "SlayerPortalItemObject"; }

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
// class SlayerPortalItemInfo
//////////////////////////////////////////////////////////////////////////////

class SlayerPortalItemInfo : public ItemInfo 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_SLAYER_PORTAL_ITEM; }
	virtual string toString() ;

public:
	int getMaxCharge(void) const { return m_MaxCharge; }
	void setMaxCharge(int charge) { m_MaxCharge = charge; }

private:
	int m_MaxCharge;
};


//////////////////////////////////////////////////////////////////////////////
// class SlayerPortalItemInfoManager;
//////////////////////////////////////////////////////////////////////////////

class SlayerPortalItemInfoManager : public InfoClassManager 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_SLAYER_PORTAL_ITEM; }
	virtual void load();
};

extern SlayerPortalItemInfoManager* g_pSlayerPortalItemInfoManager;


//////////////////////////////////////////////////////////////////////////////
// class SlayerPortalItemFactory
//////////////////////////////////////////////////////////////////////////////

class SlayerPortalItemFactory : public ItemFactory 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_SLAYER_PORTAL_ITEM; }
	virtual string getItemClassName()  { return "SlayerPortalItem"; }
	
public:
	virtual Item* createItem(ItemType_t ItemType, const list<OptionType_t>& OptionType) throw() { return new SlayerPortalItem(ItemType,OptionType); }
};


//////////////////////////////////////////////////////////////////////////////
// class SlayerPortalItemLoader;
//////////////////////////////////////////////////////////////////////////////

class SlayerPortalItemLoader : public ItemLoader 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_SLAYER_PORTAL_ITEM; }
	virtual string getItemClassName()  { return "SlayerPortalItem"; }

public:
	virtual void load(Creature* pCreature);
	virtual void load(Zone* pZone);
	virtual void load(StorageID_t storageID, Inventory* pInventory);

};

extern SlayerPortalItemLoader* g_pSlayerPortalItemLoader;

#endif
