//////////////////////////////////////////////////////////////////////////////
// Filename    : PetFood.h
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __VAMPIRE_TUNING_H__
#define __VAMPIRE_TUNING_H__

#include "Item.h"
#include "ItemInfo.h"
#include "InfoClassManager.h"
#include "ItemFactory.h"
#include "ItemLoader.h"
#include "Mutex.h"
#include "types/PetTypes.h"

//////////////////////////////////////////////////////////////////////////////
// class PetFood;
//////////////////////////////////////////////////////////////////////////////

class VampireTuningItem : public Item 
{
public:
	VampireTuningItem() throw();
	VampireTuningItem(ItemType_t itemType, const list<OptionType_t>& optionType, ItemNum_t Num) throw();
	
public:
	virtual void create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID=0);
	virtual void save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y);
	void tinysave(const string & field) 	{ tinysave(field.c_str()); }
	void tinysave(const char* field) ;
	virtual string toString() ;

	static void initItemIDRegistry(void) throw();

public:
	virtual ItemClass getItemClass()  { return Item::ITEM_CLASS_VAMPIRE_TUNING_ITEM; }
	virtual string getObjectTableName()  { return "VampireTuningItemObject"; }

	virtual ItemType_t getItemType()  { return m_ItemType; }
	virtual void setItemType(ItemType_t itemType) throw() { m_ItemType = itemType; }

	virtual ItemNum_t getNum()  { return m_Num; }
	virtual void setNum(ItemNum_t Num) throw() { m_Num = Num; }

	bool    isStackable()  { return true; }

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
// class VampireTuningItemInfo
//////////////////////////////////////////////////////////////////////////////

class VampireTuningItemInfo : public ItemInfo 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_VAMPIRE_TUNING_ITEM; }
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
// class VampireTuningItemInfoManager;
//////////////////////////////////////////////////////////////////////////////

class VampireTuningItemInfoManager : public InfoClassManager 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_VAMPIRE_TUNING_ITEM; }
	virtual void load();
};

extern VampireTuningItemInfoManager* g_pVampireTuningItemInfoManager;

//////////////////////////////////////////////////////////////////////////////
// class VampireTuningItemFactory
//////////////////////////////////////////////////////////////////////////////

class VampireTuningItemFactory : public ItemFactory 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_VAMPIRE_TUNING_ITEM; }
	virtual string getItemClassName()  { return "VampireTuningItem"; }
	
public:
	virtual Item* createItem(ItemType_t ItemType, const list<OptionType_t>& OptionType) throw() { return new VampireTuningItem(ItemType,OptionType,1); }
};

//////////////////////////////////////////////////////////////////////////////
// class VampireTuningItemLoader;
//////////////////////////////////////////////////////////////////////////////

class VampireTuningItemLoader : public ItemLoader 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_VAMPIRE_TUNING_ITEM; }
	virtual string getItemClassName()  { return "VampireTuningItem"; }

public:
	virtual void load(Creature* pCreature);
	virtual void load(Zone* pZone);
	virtual void load(StorageID_t storageID, Inventory* pInventory);
};

extern VampireTuningItemLoader* g_pVampireTuningItemLoader;

#endif
