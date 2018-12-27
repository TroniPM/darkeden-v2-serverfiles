//////////////////////////////////////////////////////////////////////////////
// Filename    : CastleSymbol.h
// Written By  : Changaya
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __CASTLE_SYMBOL_H__
#define __CASTLE_SYMBOL_H__

#include "Item.h"
#include "ItemInfo.h"
#include "InfoClassManager.h"
#include "ItemFactory.h"
#include "ItemLoader.h"
#include "Mutex.h"

//////////////////////////////////////////////////////////////////////////////
// class CastleSymbol;
//////////////////////////////////////////////////////////////////////////////

class CastleSymbol : public Item 
{
public:
	CastleSymbol() ;
	CastleSymbol(ItemType_t itemType, const list<OptionType_t>& optionType) ;
	
public:
	virtual void create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID=0);
	virtual void save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y);
	void tinysave(const string & field) 	{ tinysave(field.c_str()); }
	void tinysave(const char* field) ;
	virtual string toString() ;

	static void initItemIDRegistry(void) ;

public:
	virtual ItemClass getItemClass()  { return Item::ITEM_CLASS_CASTLE_SYMBOL; }
	virtual string getObjectTableName()  { return "CastleSymbolObject"; }

	virtual ItemType_t getItemType()  { return m_ItemType; }
	virtual void setItemType(ItemType_t itemType)  { m_ItemType = itemType; }

	virtual VolumeWidth_t getVolumeWidth() ;
	virtual VolumeHeight_t getVolumeHeight() ;
	virtual Weight_t getWeight() ;

public:
	virtual Durability_t getDurability()  { return m_Durability; }
	void setDurability(Durability_t durability)  { m_Durability = durability; }

	virtual Defense_t getDefenseBonus() ;
	virtual Protection_t getProtectionBonus() ;

	virtual EnchantLevel_t getEnchantLevel()  { return m_EnchantLevel; }
	virtual void setEnchantLevel(EnchantLevel_t level)  { m_EnchantLevel = level; }

private:
	ItemType_t			m_ItemType;			// 아이템 타입
	Durability_t		m_Durability;		// 내구성
	EnchantLevel_t		m_EnchantLevel; 
	
	static Mutex    m_Mutex;          // 아이템 ID 관련 락
	static ItemID_t m_ItemIDRegistry; // 클래스별 고유 아이템 아이디 발급기
};

//////////////////////////////////////////////////////////////////////////////
// class CastleSymbolInfo;
//////////////////////////////////////////////////////////////////////////////
class CastleSymbolInfo : public ItemInfo 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_CASTLE_SYMBOL; }

	virtual Durability_t getDurability()  { return m_Durability; }
	virtual void setDurability(Durability_t durability)  { m_Durability = durability; }

	Defense_t getDefenseBonus()  { return m_DefenseBonus; }
	void setDefenseBonus(Defense_t acBonus)  { m_DefenseBonus = acBonus; }

	Protection_t getProtectionBonus()  { return m_ProtectionBonus; }
	void setProtectionBonus(Protection_t acBonus)  { m_ProtectionBonus = acBonus; }

	virtual uint getItemLevel(void)  { return m_ItemLevel; }
	virtual void setItemLevel(uint level)  { m_ItemLevel = level; }

	virtual string toString() ;

private:
	Durability_t		m_Durability;		// 내구성
	Defense_t			m_DefenseBonus;		// 명중률 보너스
	Protection_t		m_ProtectionBonus;
	uint				m_ItemLevel;

};


//////////////////////////////////////////////////////////////////////////////
// class CastleSymbolInfoManager;
//////////////////////////////////////////////////////////////////////////////

class CastleSymbolInfoManager : public InfoClassManager 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_CASTLE_SYMBOL; }
	virtual void load();
};

// global variable declaration
extern CastleSymbolInfoManager* g_pCastleSymbolInfoManager;


//////////////////////////////////////////////////////////////////////////////
// class CastleSymbolFactory
//////////////////////////////////////////////////////////////////////////////

class CastleSymbolFactory : public ItemFactory 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_CASTLE_SYMBOL; }
	virtual string getItemClassName()  { return "CastleSymbol"; }
	
public:
	virtual Item* createItem(ItemType_t ItemType, const list<OptionType_t>& OptionType)  { return new CastleSymbol(ItemType,OptionType); }
};


//////////////////////////////////////////////////////////////////////////////
// class CastleSymbolLoader;
//////////////////////////////////////////////////////////////////////////////

class CastleSymbolLoader : public ItemLoader 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_CASTLE_SYMBOL; }
	virtual string getItemClassName()  { return "CastleSymbol"; }

public:
	virtual void load(Creature* pCreature);
	virtual void load(Zone* pZone);
	virtual void load(StorageID_t storageID, Inventory* pInventory);
};

extern CastleSymbolLoader* g_pCastleSymbolLoader;
#endif
