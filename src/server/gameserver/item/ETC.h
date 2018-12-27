//////////////////////////////////////////////////////////////////////////////
// Filename    : ETC.h
// Written By  : Elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __ETC_H__
#define __ETC_H__

#include "Item.h"
#include "ItemInfo.h"
#include "InfoClassManager.h"
#include "ItemFactory.h"
#include "ItemLoader.h"
#include "Mutex.h"

//////////////////////////////////////////////////////////////////////////////
// class ETC;
//////////////////////////////////////////////////////////////////////////////

class ETC : public Item 
{
public:
	ETC() ;
	ETC(ItemType_t itemType, const list<OptionType_t>& optionType, ItemNum_t Num) ;
	
public:
	virtual void create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID=0);
	virtual void save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y);
	void tinysave(const string & field) 	{ tinysave(field.c_str()); }
	void tinysave(const char* field) ;
	virtual string toString() ;

	static void initItemIDRegistry(void) ;

public:
	virtual ItemClass getItemClass()  { return Item::ITEM_CLASS_ETC; }
	virtual string getObjectTableName()  { return "ETCObject"; }

	virtual ItemType_t getItemType()  { return m_ItemType; }
	virtual void setItemType(ItemType_t itemType)  { m_ItemType = itemType; }

	virtual VolumeWidth_t getVolumeWidth() ;
	virtual VolumeHeight_t getVolumeHeight() ;
	virtual Weight_t getWeight() ;

	virtual ItemNum_t getNum()  { return m_Num; }
	virtual void setNum(ItemNum_t Num)  { m_Num = Num; }

	bool    isStackable()  { return true; }


private:
	ItemType_t m_ItemType;
	ItemNum_t m_Num;				// �����ִ� ������ ����
	
	static Mutex    m_Mutex;          // ������ ID ���� ��
	static ItemID_t m_ItemIDRegistry; // Ŭ������ ���� ������ ���̵� �߱ޱ�
};


//////////////////////////////////////////////////////////////////////////////
// class ETCInfo
//////////////////////////////////////////////////////////////////////////////

class ETCInfo : public ItemInfo 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_ETC; }
	virtual string toString() ;

private:
	// bomb material 
	// required ability

};


//////////////////////////////////////////////////////////////////////////////
// class ETCInfoManager;
//////////////////////////////////////////////////////////////////////////////

class ETCInfoManager : public InfoClassManager 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_ETC; }
	
	virtual void load();

};

extern ETCInfoManager* g_pETCInfoManager;


//////////////////////////////////////////////////////////////////////////////
// class ETCFactory
//////////////////////////////////////////////////////////////////////////////
class ETCFactory : public ItemFactory {

public:
	
	// get item class
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_ETC; }

	// get item classname
	virtual string getItemClassName()  { return "ETC"; }
	
public:

	// create item
	virtual Item* createItem(ItemType_t ItemType, const list<OptionType_t>& OptionType)  { return new ETC(ItemType,OptionType,1); }

};


//////////////////////////////////////////////////////////////////////////////
// class ETCLoader;
//////////////////////////////////////////////////////////////////////////////

class ETCLoader : public ItemLoader 
{

public:

	// get item class
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_ETC; }

	// get item class name
	virtual string getItemClassName()  { return "ETC"; }

public:

	// load to creature
	virtual void load(Creature* pCreature);

	// load to zone
	virtual void load(Zone* pZone);

	// load to inventory
	virtual void load(StorageID_t storageID, Inventory* pInventory);

};

extern ETCLoader* g_pETCLoader;

#endif
