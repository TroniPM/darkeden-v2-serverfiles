//////////////////////////////////////////////////////////////////////////////
// Filename    : Motorcycle.h
// Written By  : Elca
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __MOTORCYCLE_H__
#define __MOTORCYCLE_H__

#include "Item.h"
#include "ItemInfo.h"
#include "InfoClassManager.h"
#include "ItemFactory.h"
#include "ItemLoader.h"
#include "Mutex.h"

//////////////////////////////////////////////////////////////////////////////
// class Motorcycle;
//////////////////////////////////////////////////////////////////////////////

class Motorcycle : public Item 
{
public:
	Motorcycle() throw();
	Motorcycle(ItemType_t itemType, const list<OptionType_t>& optionType) throw(Error);
	~Motorcycle() throw();
	
public:
	virtual void create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID=0) throw(Error);
	virtual void save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y) throw(Error);
	void tinysave(const string & field) const throw (Error)	{ tinysave(field.c_str()); }
	void tinysave(const char* field) ;
	virtual string toString() ;

	static void initItemIDRegistry(void) throw();

public:
	virtual ItemClass getItemClass()  { return Item::ITEM_CLASS_MOTORCYCLE; }
	virtual string getObjectTableName()  { return "MotorcycleObject"; }

	virtual ItemType_t getItemType()  { return m_ItemType; }
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
	virtual Durability_t getDurability() const throw(Error) { return m_Durability; }
	void setDurability(Durability_t durability) throw(Error) { m_Durability = durability; }

	Inventory* getInventory() throw() { return m_pInventory; }

private:
	ItemType_t			m_ItemType;			// ������ Ÿ��
	list<OptionType_t>		m_OptionType;		// �ɼ� Ÿ��
	Durability_t		m_Durability;		// ������
	Inventory*			m_pInventory;		// �κ��丮
	
	static Mutex    m_Mutex;          // ������ ID ���� ��
	static ItemID_t m_ItemIDRegistry; // Ŭ������ ���� ������ ���̵� �߱ޱ�
};


//////////////////////////////////////////////////////////////////////////////
// class MotorcycleInfo
//////////////////////////////////////////////////////////////////////////////

class MotorcycleInfo : public ItemInfo 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_MOTORCYCLE; }

	virtual Durability_t getDurability()  { return m_Durability; }
	virtual void setDurability(Durability_t durability) throw() { m_Durability = durability; }

	virtual string toString() ;

private:
	Durability_t m_Durability;	// ������
};


//////////////////////////////////////////////////////////////////////////////
// class MotorcycleInfoManager;
//////////////////////////////////////////////////////////////////////////////

class MotorcycleInfoManager : public InfoClassManager 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_MOTORCYCLE; }
	virtual void load() throw(Error);
};

// global variable declaration
extern MotorcycleInfoManager* g_pMotorcycleInfoManager;


//////////////////////////////////////////////////////////////////////////////
// class MotorcycleFactory
//////////////////////////////////////////////////////////////////////////////

class MotorcycleFactory : public ItemFactory 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_MOTORCYCLE; }
	virtual string getItemClassName()  { return "Motorcycle"; }
	
public:
	virtual Item* createItem(ItemType_t ItemType, const list<OptionType_t>& OptionType) throw() { return new Motorcycle(ItemType,OptionType); }
};


//////////////////////////////////////////////////////////////////////////////
// class MotorcycleLoader;
//////////////////////////////////////////////////////////////////////////////

class MotorcycleLoader : public ItemLoader 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_MOTORCYCLE; }
	virtual string getItemClassName()  { return "Motorcycle"; }

public:
	virtual void load(Creature* pCreature) throw(Error);
	virtual void load(Zone* pZone) throw(Error);
	virtual void load(StorageID_t storageID, Inventory* pInventory) throw(Error);
};

extern MotorcycleLoader* g_pMotorcycleLoader;

#endif
