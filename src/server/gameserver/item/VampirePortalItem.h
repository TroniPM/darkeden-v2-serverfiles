//////////////////////////////////////////////////////////////////////////////
// Filename    : VampirePortalItem.h
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __VAMPIRE_PORTAL_ITEM_H__
#define __VAMPIRE_PORTAL_ITEM_H__

#include "Item.h"
#include "ItemInfo.h"
#include "InfoClassManager.h"
#include "ItemFactory.h"
#include "ItemLoader.h"
#include "Mutex.h"

//////////////////////////////////////////////////////////////////////////////
// class VampirePortalItem;
//////////////////////////////////////////////////////////////////////////////

class EffectVampirePortal;

class VampirePortalItem : public Item 
{
public:
	VampirePortalItem() ;
	VampirePortalItem(ItemType_t itemType, const list<OptionType_t>& optionType) ;
	~VampirePortalItem() ;
	
public:
	virtual void create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID=0);
	virtual void save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y);
	void tinysave(const string& field) 	{ tinysave(field.c_str()); }
	void tinysave(const char*field) ;

	static void initItemIDRegistry(void) ;

public:
	virtual ItemClass getItemClass()  { return Item::ITEM_CLASS_VAMPIRE_PORTAL_ITEM; }
	virtual string getObjectTableName()  { return "VampirePortalItemObject"; }

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

	ZoneID_t getZoneID(void) const { return m_ZoneID; }
	void setZoneID(ZoneID_t id) { m_ZoneID = id; }

	ZoneCoord_t getX(void) const { return m_X; }
	void setX(ZoneCoord_t X) { m_X = X; }

	ZoneCoord_t getY(void) const { return m_Y; }
	void setY(ZoneCoord_t Y) { m_Y = Y; }

public:
	virtual Durability_t getDurability() ;
	virtual Silver_t getSilver() ;
	virtual EnchantLevel_t getEnchantLevel() ;

private:
	ItemType_t  m_ItemType; // ������ Ÿ��
	int         m_Charge;   // ��Ż�� �� �� �ִ� Ƚ��
	ZoneID_t    m_ZoneID;   // ��ǥ �� ID
	ZoneCoord_t m_X;        // ��ǥ �� ��ǥ 
	ZoneCoord_t m_Y;        // ��ǥ �� ��ǥ 
	
	static Mutex    m_Mutex;          // ������ ID ���� ��
	static ItemID_t m_ItemIDRegistry; // Ŭ������ ���� ������ ���̵� �߱ޱ�
};


//////////////////////////////////////////////////////////////////////////////
// class VampirePortalItemInfo
//////////////////////////////////////////////////////////////////////////////

class VampirePortalItemInfo : public ItemInfo 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_VAMPIRE_PORTAL_ITEM; }
	virtual string toString() ;

public:
	int getMaxCharge(void) const { return m_MaxCharge; }
	void setMaxCharge(int charge) { m_MaxCharge = charge; }

private:
	int m_MaxCharge;
};


//////////////////////////////////////////////////////////////////////////////
// class VampirePortalItemInfoManager;
//////////////////////////////////////////////////////////////////////////////

class VampirePortalItemInfoManager : public InfoClassManager 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_VAMPIRE_PORTAL_ITEM; }
	virtual void load();
};

extern VampirePortalItemInfoManager* g_pVampirePortalItemInfoManager;


//////////////////////////////////////////////////////////////////////////////
// class VampirePortalItemFactory
//////////////////////////////////////////////////////////////////////////////

class VampirePortalItemFactory : public ItemFactory 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_VAMPIRE_PORTAL_ITEM; }
	virtual string getItemClassName()  { return "VampirePortalItem"; }
	
public:
	virtual Item* createItem(ItemType_t ItemType, const list<OptionType_t>& OptionType) throw() { return new VampirePortalItem(ItemType,OptionType); }
};


//////////////////////////////////////////////////////////////////////////////
// class VampirePortalItemLoader;
//////////////////////////////////////////////////////////////////////////////

class VampirePortalItemLoader : public ItemLoader 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_VAMPIRE_PORTAL_ITEM; }
	virtual string getItemClassName()  { return "VampirePortalItem"; }

public:
	virtual void load(Creature* pCreature);
	virtual void load(Zone* pZone);
	virtual void load(StorageID_t storageID, Inventory* pInventory);

};

extern VampirePortalItemLoader* g_pVampirePortalItemLoader;

#endif
