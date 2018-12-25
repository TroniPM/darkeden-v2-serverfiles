//////////////////////////////////////////////////////////////////////////////
// Filename    : Mine.h
// Written By  : Elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __MINE_H__
#define __MINE_H__

#include "Item.h"
#include "ItemInfo.h"
#include "InfoClassManager.h"
#include "ItemFactory.h"
#include "ItemLoader.h"
#include "Mutex.h"

//////////////////////////////////////////////////////////////////////////////
// class Mine;
//////////////////////////////////////////////////////////////////////////////

class Mine : public Item 
{
public:
	Mine() throw();
	Mine(ItemType_t itemType, const list<OptionType_t>& optionType) throw();
	
public:
	virtual void create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID=0);
	virtual void save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y);
	void tinysave(const string & field) 	{ tinysave(field.c_str()); }
	void tinysave(const char* field) ;
	virtual string toString() ;

	static void initItemIDRegistry(void) throw();

public:
	virtual ItemClass getItemClass()  { return Item::ITEM_CLASS_MINE; }
	virtual string getObjectTableName()  { return "MineObject"; }

	virtual ItemType_t getItemType()  { return m_ItemType; }
	virtual void setItemType(ItemType_t itemType) throw() { m_ItemType = itemType; }

	virtual VolumeWidth_t getVolumeWidth() ;
	virtual VolumeHeight_t getVolumeHeight() ;
	virtual Weight_t getWeight() ;

	Damage_t getDamage()  { return m_Damage;}
	void setDamage(Damage_t D) throw(Error) { m_Damage = D;}

	Dir_t getDir()  { return m_Dir;}
	void setDir(Dir_t R) throw(Error) { m_Dir = R;}

	string getInstallerName()  { return m_InstallerName; }
	void setInstallerName( const string & InstallerName ) throw() { m_InstallerName = InstallerName; }

	int getInstallerPartyID()  { return m_InstallerPartyID; }
	void setInstallerPartyID( int InstallerPartyID ) throw() { m_InstallerPartyID = InstallerPartyID; }

	virtual Damage_t getMinDamage() ;
	virtual Damage_t getMaxDamage() ;

	virtual ItemNum_t getNum()  { return m_Num; }
	virtual void setNum(ItemNum_t Num) throw() { m_Num = Num; }

	bool    isStackable()  { return true; }

private:
	ItemType_t	m_ItemType; // 아이템 타입
	Damage_t	m_Damage;
	ItemNum_t	m_Num;
	Dir_t		m_Dir;
	string		m_InstallerName;
	int			m_InstallerPartyID;
	
	static Mutex    m_Mutex;          // 아이템 ID 관련 락
	static ItemID_t m_ItemIDRegistry; // 클래스별 고유 아이템 아이디 발급기
};


//////////////////////////////////////////////////////////////////////////////
// class MineInfo
//////////////////////////////////////////////////////////////////////////////

class MineInfo : public ItemInfo 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_MINE; }
	virtual string toString() ;

	virtual Damage_t getMinDamage()  { return m_MinDamage; }
	virtual void setMinDamage(Damage_t minDamage) throw() { m_MinDamage = minDamage; }

	virtual Damage_t getMaxDamage()  { return m_MaxDamage; }
	virtual void setMaxDamage(Damage_t maxDamage) throw() { m_MaxDamage = maxDamage; }

private:
	Damage_t m_MinDamage;     // 최소 데미지
	Damage_t m_MaxDamage;     // 최대 데미지
};


//////////////////////////////////////////////////////////////////////////////
// class MineInfoManager;
//////////////////////////////////////////////////////////////////////////////

class MineInfoManager : public InfoClassManager 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_MINE; }
	virtual void load();
};

extern MineInfoManager* g_pMineInfoManager;


//////////////////////////////////////////////////////////////////////////////
// class MineFactory
//////////////////////////////////////////////////////////////////////////////

class MineFactory : public ItemFactory 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_MINE; }
	virtual string getItemClassName()  { return "Mine"; }
	
public:
	virtual Item* createItem(ItemType_t ItemType, const list<OptionType_t>& OptionType) throw() { return new Mine(ItemType,OptionType); }
};


//////////////////////////////////////////////////////////////////////////////
// class MineLoader;
//////////////////////////////////////////////////////////////////////////////

class MineLoader : public ItemLoader 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_MINE; }
	virtual string getItemClassName()  { return "Mine"; }

public:
	virtual void load(Creature* pCreature);
	virtual void load(Zone* pZone);
	virtual void load(StorageID_t storageID, Inventory* pInventory);
};

extern MineLoader* g_pMineLoader;

#endif
