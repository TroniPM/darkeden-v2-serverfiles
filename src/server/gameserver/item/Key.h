//////////////////////////////////////////////////////////////////////////////
// Filename    : Key.h
// Written By  : Elca
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __KEY_H__
#define __KEY_H__

#include "Item.h"
#include "ItemInfo.h"
#include "InfoClassManager.h"
#include "ItemFactory.h"
#include "ItemLoader.h"
#include "Mutex.h"

class Slayer;

//////////////////////////////////////////////////////////////////////////////
// class Key;
//////////////////////////////////////////////////////////////////////////////

class Key : public Item 
{
public:
	Key() ;
	Key(ItemType_t itemType, const list<OptionType_t>& optionType) ;
	
public:
	virtual void create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID=0);
	virtual void save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y);
	void tinysave(const string & field) 	{ tinysave(field.c_str()); }
	void tinysave(const char* field) ;
	virtual string toString() ;

	static void initItemIDRegistry(void) ;

public:
	virtual ItemClass getItemClass()  { return Item::ITEM_CLASS_KEY; }
	virtual string getObjectTableName()  { return "KeyObject"; }

	virtual ItemType_t getItemType()  { return m_ItemType; }
	virtual void setItemType(ItemType_t itemType)  { m_ItemType = itemType; }

	virtual VolumeWidth_t getVolumeWidth() ;
	virtual VolumeHeight_t getVolumeHeight() ;
	virtual Weight_t getWeight() ;

public:
	ItemID_t getTarget()  { return m_Target; }
	void setTarget(ItemID_t target)  { m_Target = target; }

	ItemID_t setNewMotorcycle(Slayer* pSlayer);

private:
	ItemType_t			m_ItemType;			// ������ Ÿ��
	ItemID_t			m_Target;			// ������ �� ���ΰ�?	
	
	static Mutex		m_Mutex;			// ������ ID ���� ��
	static ItemID_t		m_ItemIDRegistry; 	// Ŭ������ ���� ������ ���̵� �߱ޱ�
};


//////////////////////////////////////////////////////////////////////////////
// class KeyInfo
//////////////////////////////////////////////////////////////////////////////

class KeyInfo : public ItemInfo 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_KEY; }
	virtual string toString() ;

	OptionType_t getOptionType()  { return m_OptionType; }
	void setOptionType( OptionType_t optionType ) { m_OptionType = optionType; }

	ItemType_t getTargetType()  { return m_TargetType; }
	void setTargetType( ItemType_t target ) { m_TargetType = target; }

private:
	OptionType_t m_OptionType;
	ItemType_t m_TargetType;
};


//////////////////////////////////////////////////////////////////////////////
// class KeyInfoManager;
//////////////////////////////////////////////////////////////////////////////

class KeyInfoManager : public InfoClassManager 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_KEY; }
	virtual void load();
};

// global variable declaration
extern KeyInfoManager* g_pKeyInfoManager;


//////////////////////////////////////////////////////////////////////////////
// class KeyFactory
//////////////////////////////////////////////////////////////////////////////

class KeyFactory : public ItemFactory 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_KEY; }
	virtual string getItemClassName()  { return "Key"; }
	
public:
	virtual Item* createItem(ItemType_t ItemType, const list<OptionType_t>& OptionType)  { return new Key(ItemType,OptionType); }
};


//////////////////////////////////////////////////////////////////////////////
// class KeyLoader;
//////////////////////////////////////////////////////////////////////////////

class KeyLoader : public ItemLoader 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_KEY; }
	virtual string getItemClassName()  { return "Key"; }

public:
	virtual void load(Creature* pCreature);
	virtual void load(Zone* pZone);
	virtual void load(StorageID_t storageID, Inventory* pInventory);
};

extern KeyLoader* g_pKeyLoader;


#endif
