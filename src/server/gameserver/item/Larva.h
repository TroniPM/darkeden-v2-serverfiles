//////////////////////////////////////////////////////////////////////////////
// Filename    : Larva.h
// Written By  : Elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __LARVA_H__
#define __LARVA_H__

#include "Item.h"
#include "ItemInfo.h"
#include "InfoClassManager.h"
#include "ItemFactory.h"
#include "ItemLoader.h"
#include "Mutex.h"

//////////////////////////////////////////////////////////////////////////////
// class Larva;
//////////////////////////////////////////////////////////////////////////////

class Larva : public Item 
{
public:
	Larva() throw();
	Larva(ItemType_t itemType, const list<OptionType_t>& optionType, ItemNum_t Num) throw();
	
public:
	virtual void create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID=0) throw(Error);
	virtual void save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y) throw(Error);
	void tinysave(const string & field) const throw (Error)	{ tinysave(field.c_str()); }
	void tinysave(const char* field) const throw (Error);
	bool destroy() throw(Error);


	// get debug string
	virtual string toString() ;

	static void initItemIDRegistry(void) throw();

public:
	virtual ItemClass getItemClass()  { return Item::ITEM_CLASS_LARVA; }
	virtual string getObjectTableName()  { return "LarvaObject"; }

	virtual ItemType_t getItemType()  { return m_ItemType; }
	virtual void setItemType(ItemType_t itemType) throw() { m_ItemType = itemType; }

	virtual VolumeWidth_t getVolumeWidth() const throw(Error);
	virtual VolumeHeight_t getVolumeHeight() const throw(Error);
	virtual Weight_t getWeight() const throw(Error);

	virtual ItemNum_t getNum()  { return m_Num; }
	virtual void setNum(ItemNum_t Num) throw() { m_Num = Num; }

	bool    isStackable()  { return true; }

	// ȸ����
	int getHPAmount(void) ;
	int getMPAmount(void) ;

	int getHPDelay(void) ;
	int getMPDelay(void) ;

	int getHPQuantity(void) ;
	int getMPQuantity(void) ;

	int getHPRecoveryUnit(void) ;
	int getMPRecoveryUnit(void) ;

private:

	ItemType_t m_ItemType;			// ������ Ÿ��
	ItemNum_t m_Num;				// �����ִ� ������ ����
	
	static Mutex    m_Mutex;          // ������ ID ���� ��
	static ItemID_t m_ItemIDRegistry; // Ŭ������ ���� ������ ���̵� �߱ޱ�
};


//--------------------------------------------------------------------------------
// 
// class LarvaInfo
// 
//--------------------------------------------------------------------------------

class LarvaInfo : public ItemInfo 
{
public:

	// get item class
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_LARVA; }

	int getHPAmount(void)  { return m_HPAmount; }
	int getMPAmount(void)  { return m_MPAmount; }

	int getHPDelay(void)  { return m_HPDelay; }
	int getMPDelay(void)  { return m_MPDelay; }

	int getHPQuantity(void)  { return m_HPRecoveryUnit; }
	int getMPQuantity(void)  { return m_MPRecoveryUnit; }

	int getHPRecoveryUnit(void)  { return m_HPRecoveryUnit; }
	int getMPRecoveryUnit(void)  { return m_MPRecoveryUnit; }

	void parseEffect(const string& effect) throw();

	// toString
	virtual string toString() ;

private:
	int  m_HPAmount;
	int  m_MPAmount;
	int  m_HPDelay;
	int  m_MPDelay;
	int  m_HPRecoveryUnit;
	int  m_MPRecoveryUnit;

};


//--------------------------------------------------------------------------------
//
// class LarvaInfoManager;
//
//--------------------------------------------------------------------------------
class LarvaInfoManager : public InfoClassManager {

public:

	// get item class
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_LARVA; }
	
	// load from DB
	virtual void load() throw(Error);

};

// global variable declaration
extern LarvaInfoManager* g_pLarvaInfoManager;


//--------------------------------------------------------------------------------
//
// class LarvaFactory
//
//--------------------------------------------------------------------------------
class LarvaFactory : public ItemFactory {

public:
	
	// get item class
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_LARVA; }

	// get item classname
	virtual string getItemClassName()  { return "Larva"; }
	
public:

	// create item
	virtual Item* createItem(ItemType_t ItemType, const list<OptionType_t>& OptionType) throw() { return new Larva(ItemType,OptionType,1); }

};


//--------------------------------------------------------------------------------
//
// class LarvaLoader;
//
//--------------------------------------------------------------------------------

class LarvaLoader : public ItemLoader {

public:

	// get item class
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_LARVA; }

	// get item class name
	virtual string getItemClassName()  { return "Larva"; }

public:

	// load to creature
	virtual void load(Creature* pCreature) throw(Error);

	// load to zone
	virtual void load(Zone* pZone) throw(Error);

	// load to inventory
	virtual void load(StorageID_t storageID, Inventory* pInventory) throw(Error);

};

extern LarvaLoader* g_pLarvaLoader;
#endif
