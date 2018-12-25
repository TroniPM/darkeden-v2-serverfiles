//////////////////////////////////////////////////////////////////////////////
// Filename    : Magazine.h
// Written By  : Elca
//////////////////////////////////////////////////////////////////////////////

#ifndef __MAGAZINE_H__
#define __MAGAZINE_H__

#include "Item.h"
#include "ItemInfo.h"
#include "InfoClassManager.h"
#include "ItemFactory.h"
#include "ItemLoader.h"
#include "Mutex.h"

//////////////////////////////////////////////////////////////////////////////
// class Magazine;
//////////////////////////////////////////////////////////////////////////////

class Magazine : public Item 
{
public:
	Magazine() throw();
	Magazine(ItemType_t itemType, const list<OptionType_t>& optionType, ItemNum_t Num) throw();
	
public:
	virtual void create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID=0);
	virtual void save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y);
	void tinysave(const string & field) 	{ tinysave(field.c_str()); }
	void tinysave(const char* field) ;
	virtual string toString() ;

	static void initItemIDRegistry(void) throw();

public:
	virtual ItemClass getItemClass()  { return Item::ITEM_CLASS_MAGAZINE; }
	virtual string getObjectTableName()  { return "MagazineObject"; }

	virtual ItemType_t getItemType()  { return m_ItemType; }
	virtual void setItemType(ItemType_t itemType) throw() { m_ItemType = itemType; }

	virtual VolumeWidth_t getVolumeWidth() ;
	virtual VolumeHeight_t getVolumeHeight() ;
	virtual Weight_t getWeight() ;

public:
	ItemNum_t getNum()  { return m_Num; }
	void setNum(ItemNum_t Num) throw() { m_Num = Num; }

	bool    isStackable()  { return true; }

private:
	ItemType_t			m_ItemType;		// ������ Ÿ��
	ItemNum_t			m_Num;			// �����ִ� źâ�� ��
	
	static Mutex    m_Mutex;          // ������ ID ���� ��
	static ItemID_t m_ItemIDRegistry; // Ŭ������ ���� ������ ���̵� �߱ޱ�
};


//////////////////////////////////////////////////////////////////////////////
// class MagazineInfo
//////////////////////////////////////////////////////////////////////////////

class MagazineInfo : public ItemInfo 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_MAGAZINE; }
	virtual string toString() ;

	enum GunType
	{
		AR=0, SMG, SG, SR
	};

public:
	uint getMaxBullets()  { return m_MaxBullets; }
	void setMaxBullets(uint maxBullets) throw() { m_MaxBullets = maxBullets; }

	Silver_t getMaxSilver(void)  { return m_MaxSilver; }
	void setMaxSilver(Silver_t silver) throw() { m_MaxSilver = silver; }

	virtual uint getItemLevel(void)  { return m_ItemLevel; }
	virtual void setItemLevel(uint level) throw() { m_ItemLevel = level; }

	bool isVivid() const { return m_bVivid; }
	void setVivid( bool vivid=true ) { m_bVivid = vivid; }

	GunType getGunType() const { return m_GunType; }
	void setGunType( GunType type ) { m_GunType = type; }

private:
	uint     m_MaxBullets;
	Silver_t m_MaxSilver;
	uint     m_ItemLevel;
	bool	 m_bVivid;
	GunType	 m_GunType;
};


//////////////////////////////////////////////////////////////////////////////
// class MagazineInfoManager;
//////////////////////////////////////////////////////////////////////////////

class MagazineInfoManager : public InfoClassManager 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_MAGAZINE; }
	virtual void load();
};

// global variable declaration
extern MagazineInfoManager* g_pMagazineInfoManager;


//////////////////////////////////////////////////////////////////////////////
// class MagazineFactory
//////////////////////////////////////////////////////////////////////////////

class MagazineFactory : public ItemFactory 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_MAGAZINE; }
	virtual string getItemClassName()  { return "Magazine"; }
	
public:
	virtual Item* createItem(ItemType_t ItemType, const list<OptionType_t>& OptionType) throw() { return new Magazine(ItemType,OptionType,1); }
};


//////////////////////////////////////////////////////////////////////////////
// class MagazineLoader;
//////////////////////////////////////////////////////////////////////////////

class MagazineLoader : public ItemLoader 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_MAGAZINE; }
	virtual string getItemClassName()  { return "Magazine"; }

public:
	virtual void load(Creature* pCreature);
	virtual void load(Zone* pZone);
	virtual void load(StorageID_t storageID, Inventory* pInventory);
};

extern MagazineLoader* g_pMagazineLoader;

#endif
