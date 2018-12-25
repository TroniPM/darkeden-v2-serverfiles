//////////////////////////////////////////////////////////////////////////////
// Filename    : Bomb.h
// Written By  : Elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __BOMB_H__
#define __BOMB_H__

#include "Item.h"
#include "ItemInfo.h"
#include "InfoClassManager.h"
#include "ItemFactory.h"
#include "ItemLoader.h"
#include "Mutex.h"

//////////////////////////////////////////////////////////////////////////////
// class Bomb;
//////////////////////////////////////////////////////////////////////////////

class Bomb : public Item 
{
public:
	Bomb() throw();
	Bomb(ItemType_t itemType, const list<OptionType_t>& optionType) throw();
	
public:
	virtual void create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID=0);
	virtual void save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y);
	void tinysave(const string & field) 	{ tinysave(field.c_str()); }
	void tinysave(const char* field) ;
	virtual string toString() ;

	static void initItemIDRegistry(void) throw();

public:
	virtual ItemClass getItemClass()  { return Item::ITEM_CLASS_BOMB; }
	virtual string getObjectTableName()  { return "BombObject"; }

	virtual ItemType_t getItemType()  { return m_ItemType; }
	virtual void setItemType(ItemType_t itemType) throw() { m_ItemType = itemType; }

	virtual VolumeWidth_t getVolumeWidth() ;
	virtual VolumeHeight_t getVolumeHeight() ;
	virtual Weight_t getWeight() ;

	Damage_t getDamage()  { return m_Damage;}
	void setDamage(Damage_t D) throw(Error) { m_Damage = D;}

	//Dir_t getDir()  { return m_Dir;}
	//void setDir(Dir_t R) throw(Error) { m_Dir = R;}

	virtual Damage_t getMinDamage() ;
	virtual Damage_t getMaxDamage() ;

	virtual ItemNum_t getNum()  { return m_Num; }
	virtual void setNum(ItemNum_t Num) throw() { m_Num = Num; }

	bool    isStackable()  { return true; }

private:
	ItemType_t m_ItemType;			// ������ Ÿ��
	Damage_t   m_Damage;
	ItemNum_t  m_Num;
	//	Dir_t m_Dir;
	
	static Mutex    m_Mutex;          // ������ ID ���� ��
	static ItemID_t m_ItemIDRegistry; // Ŭ������ ���� ������ ���̵� �߱ޱ�
};


//////////////////////////////////////////////////////////////////////////////
// class BombInfo
//////////////////////////////////////////////////////////////////////////////

class BombInfo : public ItemInfo 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_BOMB; }
	virtual string toString() ;

	virtual Damage_t getMinDamage()  { return m_MinDamage; }
	virtual void setMinDamage(Damage_t minDamage) throw() { m_MinDamage = minDamage; }

	virtual Damage_t getMaxDamage()  { return m_MaxDamage; }
	virtual void setMaxDamage(Damage_t maxDamage) throw() { m_MaxDamage = maxDamage; }

private:
	Damage_t m_MinDamage;     // �ּ� ������
	Damage_t m_MaxDamage;     // �ִ� ������
};


//////////////////////////////////////////////////////////////////////////////
// class BombInfoManager;
//////////////////////////////////////////////////////////////////////////////

class BombInfoManager : public InfoClassManager 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_BOMB; }
	virtual void load();
};

extern BombInfoManager* g_pBombInfoManager;


//////////////////////////////////////////////////////////////////////////////
// class BombFactory
//////////////////////////////////////////////////////////////////////////////

class BombFactory : public ItemFactory 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_BOMB; }
	virtual string getItemClassName()  { return "Bomb"; }
	
public:
	virtual Item* createItem(ItemType_t ItemType, const list<OptionType_t>& OptionType) throw() { return new Bomb(ItemType,OptionType); }
};


//////////////////////////////////////////////////////////////////////////////
// class BombLoader;
//////////////////////////////////////////////////////////////////////////////

class BombLoader : public ItemLoader 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_BOMB; }
	virtual string getItemClassName()  { return "Bomb"; }

public:
	virtual void load(Creature* pCreature);
	virtual void load(Zone* pZone);
	virtual void load(StorageID_t storageID, Inventory* pInventory);
};

extern BombLoader* g_pBombLoader;

#endif
