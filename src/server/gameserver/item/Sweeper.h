//////////////////////////////////////////////////////////////////////////////
// Filename    : Sweeper.h
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SWEEPER_H__
#define __SWEEPER_H__

#include "Item.h"
#include "ItemInfo.h"
#include "InfoClassManager.h"
#include "ItemFactory.h"
#include "ItemLoader.h"
#include "Mutex.h"

//////////////////////////////////////////////////////////////////////////////
// class Sweeper;
//////////////////////////////////////////////////////////////////////////////

class Sweeper : public Item 
{
public:
	Sweeper() throw();
	Sweeper(ItemType_t itemType, const list<OptionType_t>& optionType) throw();
	
public:
	virtual void create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID=0);
	virtual void save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y);
	void tinysave(const string & field) 	{ tinysave(field.c_str()); }
	void tinysave(const char* field) ;
	virtual string toString() ;

	static void initItemIDRegistry(void) throw();

public:
	virtual ItemClass getItemClass()  { return Item::ITEM_CLASS_SWEEPER; }
	virtual string getObjectTableName()  { return "SweeperObject"; }

	virtual ItemType_t getItemType()  { return m_ItemType; }
	virtual void setItemType(ItemType_t itemType) throw() { m_ItemType = itemType; }

	virtual VolumeWidth_t getVolumeWidth() ;
	virtual VolumeHeight_t getVolumeHeight() ;
	virtual Weight_t getWeight() ;

public:
	virtual Durability_t getDurability()  { return m_Durability; }
	void setDurability(Durability_t durability) throw(Error) { m_Durability = durability; }

	virtual Defense_t getDefenseBonus() ;
	virtual Protection_t getProtectionBonus() ;

	virtual EnchantLevel_t getEnchantLevel()  { return m_EnchantLevel; }
	virtual void setEnchantLevel(EnchantLevel_t level) throw() { m_EnchantLevel = level; }

private:
	ItemType_t			m_ItemType;			// 아이템 타입
	Durability_t		m_Durability;		// 내구성
	EnchantLevel_t		m_EnchantLevel; 
	
	static Mutex    m_Mutex;          // 아이템 ID 관련 락
	static ItemID_t m_ItemIDRegistry; // 클래스별 고유 아이템 아이디 발급기
};

//////////////////////////////////////////////////////////////////////////////
// class SweeperInfo;
//////////////////////////////////////////////////////////////////////////////
class SweeperInfo : public ItemInfo 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_SWEEPER; }

	virtual Durability_t getDurability()  { return m_Durability; }
	virtual void setDurability(Durability_t durability) throw() { m_Durability = durability; }

	Defense_t getDefenseBonus()  { return m_DefenseBonus; }
	void setDefenseBonus(Defense_t acBonus) throw() { m_DefenseBonus = acBonus; }

	Protection_t getProtectionBonus()  { return m_ProtectionBonus; }
	void setProtectionBonus(Protection_t acBonus) throw() { m_ProtectionBonus = acBonus; }

	virtual uint getItemLevel(void)  { return m_ItemLevel; }
	virtual void setItemLevel(uint level) throw() { m_ItemLevel = level; }

	virtual string toString() ;

private:
	Durability_t		m_Durability;		// 내구성
	Defense_t			m_DefenseBonus;		// 명중률 보너스
	Protection_t		m_ProtectionBonus;
	uint				m_ItemLevel;

};


//////////////////////////////////////////////////////////////////////////////
// class SweeperInfoManager;
//////////////////////////////////////////////////////////////////////////////

class SweeperInfoManager : public InfoClassManager 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_SWEEPER; }
	virtual void load();
};

// global variable declaration
extern SweeperInfoManager* g_pSweeperInfoManager;


//////////////////////////////////////////////////////////////////////////////
// class SweeperFactory
//////////////////////////////////////////////////////////////////////////////

class SweeperFactory : public ItemFactory 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_SWEEPER; }
	virtual string getItemClassName()  { return "Sweeper"; }
	
public:
	virtual Item* createItem(ItemType_t ItemType, const list<OptionType_t>& OptionType) throw() { return new Sweeper(ItemType,OptionType); }
};


//////////////////////////////////////////////////////////////////////////////
// class SweeperLoader;
//////////////////////////////////////////////////////////////////////////////

class SweeperLoader : public ItemLoader 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_SWEEPER; }
	virtual string getItemClassName()  { return "Sweeper"; }

public:
	virtual void load(Creature* pCreature);
	virtual void load(Zone* pZone);
	virtual void load(StorageID_t storageID, Inventory* pInventory);
};

extern SweeperLoader* g_pSweeperLoader;
#endif
