//////////////////////////////////////////////////////////////////////////////
// Filename    : PetFood.h
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __OUSTERS_TUNING_H__
#define __OUSTERS_TUNING_H__

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

class OustersTuningItem : public Item 
{
public:
	OustersTuningItem() ;
	OustersTuningItem(ItemType_t itemType, const list<OptionType_t>& optionType, ItemNum_t Num) ;
	
public:
	virtual void create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID=0);
	virtual void save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y);
	void tinysave(const string & field) 	{ tinysave(field.c_str()); }
	void tinysave(const char* field) ;
	virtual string toString() ;

	static void initItemIDRegistry(void) ;

public:
	virtual ItemClass getItemClass()  { return Item::ITEM_CLASS_OUSTERS_TUNING_ITEM; }
	virtual string getObjectTableName()  { return "OustersTuningItemObject"; }

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
	
	static Mutex    m_Mutex;          // ������ ID ���� ��
	static ItemID_t m_ItemIDRegistry; // Ŭ������ ���� ������ ���̵� �߱ޱ�
};

//////////////////////////////////////////////////////////////////////////////
// class OustersTuningItemInfo
//////////////////////////////////////////////////////////////////////////////

class OustersTuningItemInfo : public ItemInfo 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_OUSTERS_TUNING_ITEM; }
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
// class OustersTuningItemInfoManager;
//////////////////////////////////////////////////////////////////////////////

class OustersTuningItemInfoManager : public InfoClassManager 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_OUSTERS_TUNING_ITEM; }
	virtual void load();
};

extern OustersTuningItemInfoManager* g_pOustersTuningItemInfoManager;

//////////////////////////////////////////////////////////////////////////////
// class OustersTuningItemFactory
//////////////////////////////////////////////////////////////////////////////

class OustersTuningItemFactory : public ItemFactory 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_OUSTERS_TUNING_ITEM; }
	virtual string getItemClassName()  { return "OustersTuningItem"; }
	
public:
	virtual Item* createItem(ItemType_t ItemType, const list<OptionType_t>& OptionType) throw() { return new OustersTuningItem(ItemType,OptionType,1); }
};

//////////////////////////////////////////////////////////////////////////////
// class OustersTuningItemLoader;
//////////////////////////////////////////////////////////////////////////////

class OustersTuningItemLoader : public ItemLoader 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_OUSTERS_TUNING_ITEM; }
	virtual string getItemClassName()  { return "OustersTuningItem"; }

public:
	virtual void load(Creature* pCreature);
	virtual void load(Zone* pZone);
	virtual void load(StorageID_t storageID, Inventory* pInventory);
};

extern OustersTuningItemLoader* g_pOustersTuningItemLoader;

#endif
