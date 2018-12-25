//////////////////////////////////////////////////////////////////////////////
// Filename    : OustersBoots.h
// Written By  :
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __OUSTERS_BOOTS_H__
#define __OUSTERS_BOOTS_H__

#include "Item.h"
#include "ConcreteItem.h"
#include "ItemPolicies.h"
#include "ItemInfo.h"
#include "InfoClassManager.h"
#include "ItemFactory.h"
#include "ItemLoader.h"
#include "Mutex.h"

//////////////////////////////////////////////////////////////////////////////
// class OustersBoots;
//////////////////////////////////////////////////////////////////////////////

class OustersBoots : public ConcreteItem<Item::ITEM_CLASS_OUSTERS_BOOTS, NoStack, HasDurability, HasOption, ClothGrade, NoAttacking, NoEnchantLevel, HasOption2, HasHeroOption, HasHeroOptionAttr>
{
public:
	OustersBoots() throw();
	OustersBoots(ItemType_t itemType, const list<OptionType_t>& optionType) throw();
	
public:
	virtual void create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID=0);
	virtual void save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y);
	void tinysave(const string & field) 	{ tinysave(field.c_str()); }
	void tinysave(const char* field) ;
	virtual string toString() ;

	static void initItemIDRegistry(void) throw();

public:
//	virtual ItemClass getItemClass()  { return Item::ITEM_CLASS_OUSTERS_BOOTS; }
//	virtual string getObjectTableName()  { return "OustersBootsObject"; }

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

	virtual Defense_t getDefenseBonus() ;
	virtual Protection_t getProtectionBonus() ;
*/
private:
//	ItemType_t			m_ItemType;			// 아이템 타입
//	list<OptionType_t>		m_OptionType;		// 옵션 타입
//	Durability_t		m_Durability;		// 내구성
	
	static Mutex    m_Mutex;          // 아이템 ID 관련 락
	static ItemID_t m_ItemIDRegistry; // 클래스별 고유 아이템 아이디 발급기
};


//////////////////////////////////////////////////////////////////////////////
// class OustersBootsInfo
//////////////////////////////////////////////////////////////////////////////

class OustersBootsInfo : public ItemInfo 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_OUSTERS_BOOTS; }

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
	Durability_t	m_Durability;		// 내구성
	Defense_t		m_DefenseBonus;		// 디펜스 보너스
	Protection_t	m_ProtectionBonus;
	uint			m_ItemLevel;
};


//////////////////////////////////////////////////////////////////////////////
// class OustersBootsInfoManager;
//////////////////////////////////////////////////////////////////////////////

class OustersBootsInfoManager : public InfoClassManager 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_OUSTERS_BOOTS; }
	virtual void load();
};

// global variable declaration
extern OustersBootsInfoManager* g_pOustersBootsInfoManager;


//////////////////////////////////////////////////////////////////////////////
// class OustersBootsFactory
//////////////////////////////////////////////////////////////////////////////

class OustersBootsFactory : public ItemFactory 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_OUSTERS_BOOTS; }
	virtual string getItemClassName()  { return "OustersBoots"; }

public:
	virtual Item* createItem(ItemType_t ItemType, const list<OptionType_t>& OptionType) throw() { return new OustersBoots(ItemType,OptionType); }
};


//////////////////////////////////////////////////////////////////////////////
// class OustersBootsLoader;
//////////////////////////////////////////////////////////////////////////////

class OustersBootsLoader : public ItemLoader 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_OUSTERS_BOOTS; }
	virtual string getItemClassName()  { return "OustersBoots"; }

public:
	virtual void load(Creature* pCreature);
	virtual void load(Zone* pZone);
	virtual void load(StorageID_t storageID, Inventory* pInventory);
};

extern OustersBootsLoader* g_pOustersBootsLoader;

#endif
