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
	OustersTuningItem() throw();
	OustersTuningItem(ItemType_t itemType, const list<OptionType_t>& optionType, ItemNum_t Num) throw();
	
public:
	virtual void create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID=0) throw(Error);
	virtual void save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y) throw(Error);
	void tinysave(const string & field) const throw (Error)	{ tinysave(field.c_str()); }
	void tinysave(const char* field) const throw (Error);
	virtual string toString() ;

	static void initItemIDRegistry(void) throw();

public:
	virtual ItemClass getItemClass()  { return Item::ITEM_CLASS_OUSTERS_TUNING_ITEM; }
	virtual string getObjectTableName()  { return "OustersTuningItemObject"; }

	virtual ItemType_t getItemType()  { return m_ItemType; }
	virtual void setItemType(ItemType_t itemType) throw() { m_ItemType = itemType; }

	virtual ItemNum_t getNum()  { return m_Num; }
	virtual void setNum(ItemNum_t Num) throw() { m_Num = Num; }

	bool    isStackable()  { return true; }

	virtual VolumeWidth_t getVolumeWidth() const throw(Error);
	virtual VolumeHeight_t getVolumeHeight() const throw(Error);
	virtual Weight_t getWeight() const throw(Error);

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
	virtual void load() throw(Error);
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
	virtual void load(Creature* pCreature) throw(Error);
	virtual void load(Zone* pZone) throw(Error);
	virtual void load(StorageID_t storageID, Inventory* pInventory) throw(Error);
};

extern OustersTuningItemLoader* g_pOustersTuningItemLoader;

#endif
