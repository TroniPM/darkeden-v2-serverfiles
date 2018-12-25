//////////////////////////////////////////////////////////////////////////////
// Filename    : PetFood.h
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SLAYER_TUNING_ITEM_H__
#define __SLAYER_TUNING_ITEM_H__

#include "Item.h"
#include "ConcreteItem.h"
#include "ItemPolicies.h"
#include "ItemInfo.h"
#include "InfoClassManager.h"
#include "ItemFactory.h"
#include "ItemLoader.h"
#include "Mutex.h"

//////////////////////////////////////////////////////////////////////////////
// class PetFood;
//////////////////////////////////////////////////////////////////////////////

class SlayerTuningItem : public Item 
{
public:
	SlayerTuningItem() throw();
	SlayerTuningItem(ItemType_t itemType, const list<OptionType_t>& optionType, ItemNum_t Num) throw();
	
public:
	virtual void create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID=0);
	virtual void save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y);
	void tinysave(const string & field) 	{ tinysave(field.c_str()); }
	void tinysave(const char* field) ;
	virtual string toString() ;

	static void initItemIDRegistry(void) throw();

public:
	virtual ItemClass getItemClass()  { return Item::ITEM_CLASS_SLAYER_TUNING_ITEM; }
	virtual string getObjectTableName()  { return "SlayerTuningItemObject"; }

	virtual ItemType_t getItemType()  { return m_ItemType; }
	virtual void setItemType(ItemType_t itemType) throw() { m_ItemType = itemType; }

	virtual ItemNum_t getNum()  { return m_Num; }
	virtual void setNum(ItemNum_t Num) throw() { m_Num = Num; }

	virtual VolumeWidth_t getVolumeWidth() ;
	virtual VolumeHeight_t getVolumeHeight() ;
	virtual Weight_t getWeight() ;

private:
	ItemType_t m_ItemType;
	ItemNum_t m_Num;
	
	static Mutex    m_Mutex;          // 아이템 ID 관련 락
	static ItemID_t m_ItemIDRegistry; // 클래스별 고유 아이템 아이디 발급기
};

//////////////////////////////////////////////////////////////////////////////
// class CreateItemInfo
//////////////////////////////////////////////////////////////////////////////

class SlayerTuningItemInfo : public ItemInfo 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_SLAYER_TUNING_ITEM; }
	virtual string toString() ;

	int		getTunningItemClass() const { return m_TunningItemClass; }
	void	setTunningItemClass( int TunningItemClass) { m_TunningItemClass = TunningItemClass; }

	int		getTunningItemType() const { return m_TunningItemType; }
	void	setTunningItemType( int TunningItemType) { m_TunningItemType = TunningItemType; }

private :
	int					m_TunningItemClass;
	int					m_TunningItemType;
};

//////////////////////////////////////////////////////////////////////////////
// class CreateItemInfoManager;
//////////////////////////////////////////////////////////////////////////////

class SlayerTuningItemInfoManager : public InfoClassManager 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_SLAYER_TUNING_ITEM; }
	virtual void load();
};

extern SlayerTuningItemInfoManager* g_pSlayerTuningItemInfoManager;

//////////////////////////////////////////////////////////////////////////////
// class CreateItemFactory
//////////////////////////////////////////////////////////////////////////////

class SlayerTuningItemFactory : public ItemFactory 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_SLAYER_TUNING_ITEM; }
	virtual string getItemClassName()  { return "SlayerTuningItem"; }
	
public:
	virtual Item* createItem(ItemType_t ItemType, const list<OptionType_t>& OptionType) throw() { return new SlayerTuningItem(ItemType,OptionType,1); }
};

//////////////////////////////////////////////////////////////////////////////
// class CreateItemLoader;
//////////////////////////////////////////////////////////////////////////////

class SlayerTuningItemLoader : public ItemLoader 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_SLAYER_TUNING_ITEM; }
	virtual string getItemClassName()  { return "SlayerTuningItem"; }

public:
	virtual void load(Creature* pCreature);
	virtual void load(Zone* pZone);
	virtual void load(StorageID_t storageID, Inventory* pInventory);
};

extern SlayerTuningItemLoader* g_pSlayerTuningItemLoader;

#endif
