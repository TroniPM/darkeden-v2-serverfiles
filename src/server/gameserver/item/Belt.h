//////////////////////////////////////////////////////////////////////////////
// Filename    : Belt.h
// Written By  : Elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __BELT_H__
#define __BELT_H__

#include "Item.h"
#include "ConcreteItem.h"
#include "ItemPolicies.h"
#include "ItemInfo.h"
#include "InfoClassManager.h"
#include "ItemFactory.h"
#include "ItemLoader.h"
#include "Mutex.h"

//////////////////////////////////////////////////////////////////////////////
// class Belt;
//////////////////////////////////////////////////////////////////////////////

class Belt : public ConcreteItem <Item::ITEM_CLASS_BELT, NoStack, HasDurability, HasOption, GroceryGrade, NoAttacking, HasEnchantLevel,HasOption2, HasHeroOption, HasHeroOptionAttr>
{
public:
	Belt() throw();
	Belt(ItemType_t itemType, const list<OptionType_t>& optionType) throw(Error);
	~Belt() throw();

public:
	virtual void create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID=0) throw(Error);
	virtual bool destroy() throw(Error);
	virtual void save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y) throw(Error);
	void tinysave(const string & field) const throw (Error)	{ tinysave(field.c_str()); }
	void tinysave(const char* field) const throw (Error);
	virtual string toString() ;

	static void initItemIDRegistry(void) throw();

public:
//	virtual ItemClass getItemClass()  { return Item::ITEM_CLASS_BELT; }
//	virtual string getObjectTableName()  { return "BeltObject"; }

//	virtual ItemType_t getItemType()  { return m_ItemType; }
//	virtual void setItemType(ItemType_t itemType) throw() { m_ItemType = itemType; }

/*	virtual bool hasOptionType()  { return !m_OptionType.empty(); }
	virtual int getOptionTypeSize()  { return m_OptionType.size(); }
	virtual int getRandomOptionType()  { if (m_OptionType.empty()) return 0; int pos = rand()%m_OptionType.size(); list<OptionType_t>::const_iterator itr = m_OptionType.begin(); for (int i=0; i<pos; i++) itr++; return *itr; }
	virtual const list<OptionType_t>& getOptionTypeList()  { return m_OptionType; }
	virtual OptionType_t getFirstOptionType()  { if (m_OptionType.empty()) return 0; return m_OptionType.front(); }
	virtual void removeOptionType(OptionType_t OptionType) throw() { list<OptionType_t>::iterator itr = find(m_OptionType.begin(), m_OptionType.end(), OptionType); if (itr!=m_OptionType.end()) m_OptionType.erase(itr); }
	virtual void changeOptionType(OptionType_t currentOptionType, OptionType_t newOptionType) throw() { list<OptionType_t>::iterator itr = find(m_OptionType.begin(), m_OptionType.end(), currentOptionType); if (itr!=m_OptionType.end()) *itr=newOptionType; }
	virtual void addOptionType(OptionType_t OptionType) throw() { m_OptionType.push_back(OptionType); }
	virtual void setOptionType(const list<OptionType_t>& OptionType) throw() { m_OptionType = OptionType; }


	virtual VolumeWidth_t getVolumeWidth() const throw(Error);
	virtual VolumeHeight_t getVolumeHeight() const throw(Error);
	virtual Weight_t getWeight() const throw(Error);

	virtual Durability_t getDurability() const throw(Error) { return m_Durability; }
	void setDurability(Durability_t durability) throw(Error) { m_Durability = durability; }
*/
	void setInventory(Inventory* pInventory) throw() { m_pInventory = pInventory; }
	Inventory* getInventory()  { return m_pInventory; }

	PocketNum_t getPocketCount(void) ;

/*	virtual Defense_t getDefenseBonus() const throw(Error);
	virtual Protection_t getProtectionBonus() const throw(Error);*/

	void makePCItemInfo(PCItemInfo& result) const;

private:
//	ItemType_t     m_ItemType;      // ������ Ÿ��
//	list<OptionType_t>   m_OptionType;    // �ɼ� Ÿ��
//	Durability_t   m_Durability;    // ������
	Inventory*     m_pInventory;    // �κ��丮
	
	static Mutex    m_Mutex;          // ������ ID ���� ��
	static ItemID_t m_ItemIDRegistry; // Ŭ������ ���� ������ ���̵� �߱ޱ�
};


//////////////////////////////////////////////////////////////////////////////
// class BeltInfo
//////////////////////////////////////////////////////////////////////////////

class BeltInfo : public ItemInfo 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_BELT; }

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
	Durability_t  m_Durability;      // ������
	uint          m_PocketCount;     // ������ ����
	Defense_t     m_DefenseBonus;    // defense bonus
	Protection_t  m_ProtectionBonus; // protection bonus
	uint          m_ItemLevel;       // �������� ����

};


//////////////////////////////////////////////////////////////////////////////
// class BeltInfoManager;
//////////////////////////////////////////////////////////////////////////////

class BeltInfoManager : public InfoClassManager 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_BELT; }
	virtual void load() throw(Error);
};

extern BeltInfoManager* g_pBeltInfoManager;


//////////////////////////////////////////////////////////////////////////////
// class BeltFactory
//////////////////////////////////////////////////////////////////////////////

class BeltFactory : public ItemFactory 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_BELT; }
	virtual string getItemClassName()  { return "Belt"; }
	
public:
	virtual Item* createItem(ItemType_t ItemType, const list<OptionType_t>& OptionType) throw() { return new Belt(ItemType,OptionType); }
};


//////////////////////////////////////////////////////////////////////////////
// class BeltLoader;
//////////////////////////////////////////////////////////////////////////////

class BeltLoader : public ItemLoader 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_BELT; }
	virtual string getItemClassName()  { return "Belt"; }

public:
	virtual void load(Creature* pCreature) throw(Error);
	virtual void load(Zone* pZone) throw(Error);
	virtual void load(StorageID_t storageID, Inventory* pInventory) throw(Error);
};

extern BeltLoader* g_pBeltLoader;

#endif
