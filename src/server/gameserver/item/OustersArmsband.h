//////////////////////////////////////////////////////////////////////////////
// Filename    : OustersArmsband.h
// Written By  :
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __OUSTERS_ARMSBAND_H__
#define __OUSTERS_ARMSBAND_H__

#include "Item.h"
#include "ConcreteItem.h"
#include "ItemPolicies.h"
#include "ItemInfo.h"
#include "InfoClassManager.h"
#include "ItemFactory.h"
#include "ItemLoader.h"
#include "Mutex.h"

//////////////////////////////////////////////////////////////////////////////
// class OustersArmsband;
//////////////////////////////////////////////////////////////////////////////

class OustersArmsband : public ConcreteItem<Item::ITEM_CLASS_OUSTERS_ARMSBAND, NoStack, HasDurability, HasOption, GroceryGrade, NoAttacking, NoEnchantLevel, HasOption2, HasHeroOption, HasHeroOptionAttr> 
{
public:
	OustersArmsband() throw();
	OustersArmsband(ItemType_t itemType, const list<OptionType_t>& optionType) throw();
	~OustersArmsband() throw();
	
public:
	virtual void create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID=0);
	virtual bool destroy();
	virtual void save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y);
	void tinysave(const string & field) 	{ tinysave(field.c_str()); }
	void tinysave(const char* field) ;
	virtual string toString() ;

	static void initItemIDRegistry(void) throw();

public:
//	virtual ItemClass getItemClass()  { return Item::ITEM_CLASS_OUSTERS_ARMSBAND; }
//	virtual string getObjectTableName()  { return "OustersArmsbandObject"; }

/*	virtual ItemType_t getItemType()  { return m_ItemType; }
	virtual void setItemType(ItemType_t itemType) throw() { m_ItemType = itemType; }

	virtual bool hasOptionType()  { return !m_OptionType.empty(); }
	virtual int getOptionTypeSize()  { return m_OptionType.size(); }
	virtual int getRandomOptionType()  { if (m_OptionType.empty()) return 0; int pos = rand()%m_OptionType.size(); list<OptionType_t>::const_iterator itr = m_OptionType.begin(); for (int i=0; i<pos; i++) itr++; return *itr; }
	virtual const list<OptionType_t>& getOptionTypeList()  { return m_OptionType; }
	virtual OptionType_t getFirstOptionType()  { if (m_OptionType.empty()) return 0; return m_OptionType.front(); }
	virtual void removeOptionType(OptionType_t OptionType) throw() { list<OptionType_t>::iterator itr = find(m_OptionType.begin(), m_OptionType.end(), OptionType); if (itr!=m_OptionType.end()) m_OptionType.erase(itr); }
	virtual void changeOptionType(OptionType_t currentOptionType, OptionType_t newOptionType) throw() { list<OptionType_t>::iterator itr = find(m_OptionType.begin(), m_OptionType.end(), currentOptionType); if (itr!=m_OptionType.end()) *itr=newOptionType; }
	virtual void addOptionType(OptionType_t OptionType) throw() { m_OptionType.push_back(OptionType); }
	virtual void setOptionType(const list<OptionType_t>& OptionType) throw() { m_OptionType = OptionType; }

	virtual VolumeWidth_t getVolumeWidth() ;
	virtual VolumeHeight_t getVolumeHeight() ;
	virtual Weight_t getWeight() ;

public:
	virtual Durability_t getDurability()  { return m_Durability; }
	void setDurability(Durability_t durability) throw(Error) { m_Durability = durability; }
*/
	void setInventory(Inventory* pInventory) throw() { m_pInventory = pInventory; }
	Inventory* getInventory()  { return m_pInventory; }

	PocketNum_t getPocketCount(void) ;

/*	virtual Defense_t getDefenseBonus() ;
	virtual Protection_t getProtectionBonus() ;
*/
	void makePCItemInfo(PCItemInfo& result) const;

private:
//	ItemType_t			m_ItemType;			// 아이템 타입
//	list<OptionType_t>		m_OptionType;	// 옵션 타입
//	Durability_t		m_Durability;		// 내구성
	Inventory*			m_pInventory;		// 인벤토리
	
	static Mutex    m_Mutex;          // 아이템 ID 관련 락
	static ItemID_t m_ItemIDRegistry; // 클래스별 고유 아이템 아이디 발급기
};


//////////////////////////////////////////////////////////////////////////////
// class OustersArmsbandInfo
//////////////////////////////////////////////////////////////////////////////

class OustersArmsbandInfo : public ItemInfo 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_OUSTERS_ARMSBAND; }

	virtual Durability_t getDurability()  { return m_Durability; }
	virtual void setDurability(Durability_t durability) throw() { m_Durability = durability; }

	uint getPocketCount()  { return m_PocketCount; }
	void setPocketCount(uint pocketCount) throw() { m_PocketCount = pocketCount; }

	Defense_t getDefenseBonus()  { return m_DefenseBonus; }
	void setDefenseBonus(Defense_t acBonus) throw() { m_DefenseBonus = acBonus; }

	Protection_t getProtectionBonus()  { return m_ProtectionBonus; }
	void setProtectionBonus(Protection_t acBonus) throw() { m_ProtectionBonus = acBonus; }

	virtual uint getItemLevel(void)  { return m_ItemLevel; }
	virtual void setItemLevel(uint level) throw() { m_ItemLevel = level; }

	virtual string toString() ;

private:
	Durability_t	m_Durability;		// 내구성
	uint			m_PocketCount;		// 포켓의 개수
	Defense_t		m_DefenseBonus;
	Protection_t	m_ProtectionBonus;
	uint			m_ItemLevel;
};


//////////////////////////////////////////////////////////////////////////////
// class OustersArmsbandInfoManager;
//////////////////////////////////////////////////////////////////////////////

class OustersArmsbandInfoManager : public InfoClassManager 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_OUSTERS_ARMSBAND; }
	virtual void load();
};

// global variable declaration
extern OustersArmsbandInfoManager* g_pOustersArmsbandInfoManager;


//////////////////////////////////////////////////////////////////////////////
// class OustersArmsbandFactory
//////////////////////////////////////////////////////////////////////////////

class OustersArmsbandFactory : public ItemFactory 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_OUSTERS_ARMSBAND; }
	virtual string getItemClassName()  { return "OustersArmsband"; }

public:
	virtual Item* createItem(ItemType_t ItemType, const list<OptionType_t>& OptionType) throw() { return new OustersArmsband(ItemType,OptionType); }
};


//////////////////////////////////////////////////////////////////////////////
// class OustersArmsbandLoader;
//////////////////////////////////////////////////////////////////////////////

class OustersArmsbandLoader : public ItemLoader 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_OUSTERS_ARMSBAND; }
	virtual string getItemClassName()  { return "OustersArmsband"; }

public:
	virtual void load(Creature* pCreature);
	virtual void load(Zone* pZone);
	virtual void load(StorageID_t storageID, Inventory* pInventory);
};

extern OustersArmsbandLoader* g_pOustersArmsbandLoader;

#endif
