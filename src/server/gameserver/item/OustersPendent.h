//////////////////////////////////////////////////////////////////////////////
// Filename    : OustersPendent.h
// Written By  :
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __OUSTERS_PENDENT_H__
#define __OUSTERS_PENDENT_H__

#include "Item.h"
#include "ConcreteItem.h"
#include "ItemPolicies.h"
#include "ItemInfo.h"
#include "InfoClassManager.h"
#include "ItemFactory.h"
#include "ItemLoader.h"
#include "Mutex.h"

//////////////////////////////////////////////////////////////////////////////
// class OustersPendent;
//////////////////////////////////////////////////////////////////////////////

class OustersPendent : public ConcreteItem<Item::ITEM_CLASS_OUSTERS_PENDENT, NoStack, HasDurability, HasOption, AccessoryGrade, NoAttacking, NoEnchantLevel, HasOption2, HasHeroOption, HasHeroOptionAttr>
{
public:
	OustersPendent() throw();
	OustersPendent(ItemType_t itemType, const list<OptionType_t>& optionType) throw();
	
public:
	virtual void create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID=0);
	virtual void save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y);
	void tinysave(const string & field) 	{ tinysave(field.c_str()); }
	void tinysave(const char* field) ;
	virtual string toString() ;

	static void initItemIDRegistry(void) throw();

public:
//	virtual ItemClass getItemClass()  { return Item::ITEM_CLASS_OUSTERS_PENDENT; }
//	virtual string getObjectTableName()  { return "OustersPendentObject"; }

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
//	ItemType_t			m_ItemType;			// ������ Ÿ��
//	list<OptionType_t>		m_OptionType;		// �ɼ� Ÿ��
//	Durability_t		m_Durability;		// ������
	
	static Mutex    m_Mutex;          // ������ ID ���� ��
	static ItemID_t m_ItemIDRegistry; // Ŭ������ ���� ������ ���̵� �߱ޱ�
};


//////////////////////////////////////////////////////////////////////////////
// class OustersPendentInfo
//////////////////////////////////////////////////////////////////////////////

class OustersPendentInfo : public ItemInfo 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_OUSTERS_PENDENT; }

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
	Durability_t	m_Durability;		// ������
	Defense_t		m_DefenseBonus;
	Protection_t	m_ProtectionBonus;
	uint			m_ItemLevel;
};


//////////////////////////////////////////////////////////////////////////////
// class OustersPendentInfoManager;
//////////////////////////////////////////////////////////////////////////////

class OustersPendentInfoManager : public InfoClassManager 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_OUSTERS_PENDENT; }
	virtual void load();
};

// global variable declaration
extern OustersPendentInfoManager* g_pOustersPendentInfoManager;


//////////////////////////////////////////////////////////////////////////////
// class OustersPendentFactory
//////////////////////////////////////////////////////////////////////////////

class OustersPendentFactory : public ItemFactory 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_OUSTERS_PENDENT; }
	virtual string getItemClassName()  { return "OustersPendent"; }

public:
	virtual Item* createItem(ItemType_t ItemType, const list<OptionType_t>& OptionType) throw() { return new OustersPendent(ItemType,OptionType); }
};


//////////////////////////////////////////////////////////////////////////////
// class OustersPendentLoader;
//////////////////////////////////////////////////////////////////////////////

class OustersPendentLoader : public ItemLoader 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_OUSTERS_PENDENT; }
	virtual string getItemClassName()  { return "OustersPendent"; }

public:
	virtual void load(Creature* pCreature);
	virtual void load(Zone* pZone);
	virtual void load(StorageID_t storageID, Inventory* pInventory);
};

extern OustersPendentLoader* g_pOustersPendentLoader;

#endif
