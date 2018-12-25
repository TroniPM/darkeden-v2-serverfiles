//////////////////////////////////////////////////////////////////////////////
// Filename    : EventBall.h
// Written By  : changaya
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EVENT_BALL_H__
#define __EVENT_BALL_H__

#include "Item.h"
#include "ItemInfo.h"
#include "InfoClassManager.h"
#include "ItemFactory.h"
#include "ItemLoader.h"
#include "Mutex.h"

//////////////////////////////////////////////////////////////////////////////
// class EventBall;
//////////////////////////////////////////////////////////////////////////////

class EventBall : public Item 
{
public:
	EventBall() throw();
	EventBall(ItemType_t itemType, OptionType_t optionType, ItemNum_t Num) throw();
	
public:
	virtual void create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID=0);
	virtual void save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y);
	void tinysave(const string & field) 	{ tinysave(field.c_str()); }
	void tinysave(const char* field) ;
	virtual string toString() ;

	static void initItemIDRegistry(void) throw();

public:
	virtual ItemClass getItemClass()  { return Item::ITEM_CLASS_EVENT_BALL; }
	virtual string getObjectTableName()  { return "EventBallObject"; }

	virtual ItemType_t getItemType()  { return m_ItemType; }
	virtual void setItemType(ItemType_t itemType) throw() { m_ItemType = itemType; }

	virtual VolumeWidth_t getVolumeWidth() ;
	virtual VolumeHeight_t getVolumeHeight() ;
	virtual Weight_t getWeight() ;

public:
	virtual ItemNum_t getNum()  { return m_Num; }
	virtual void setNum(ItemNum_t Num) throw() { m_Num = Num; }

	bool    isStackable()  { return true; }

private:
	ItemType_t m_ItemType;
	ItemNum_t  m_Num;
	
	static Mutex    m_Mutex;          // ������ ID ���� ��
	static ItemID_t m_ItemIDRegistry; // Ŭ������ ���� ������ ���̵� �߱ޱ�
};

//////////////////////////////////////////////////////////////////////////////
// class EventBallInfo
//////////////////////////////////////////////////////////////////////////////

class EventBallInfo : public ItemInfo 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_EVENT_BALL; }
	virtual string toString() ;
};

//////////////////////////////////////////////////////////////////////////////
// class EventBallInfoManager;
//////////////////////////////////////////////////////////////////////////////

class EventBallInfoManager : public InfoClassManager 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_EVENT_BALL; }
	virtual void load();
};

extern EventBallInfoManager* g_pEventBallInfoManager;

//////////////////////////////////////////////////////////////////////////////
// class EventBallFactory
//////////////////////////////////////////////////////////////////////////////

class EventBallFactory : public ItemFactory 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_EVENT_BALL; }
	virtual string getItemClassName()  { return "EventBall"; }
	
public:
	virtual Item* createItem(ItemType_t ItemType, OptionType_t OptionType) throw() { return new EventBall(ItemType,OptionType,1); }
};

//////////////////////////////////////////////////////////////////////////////
// class EventBallLoader;
//////////////////////////////////////////////////////////////////////////////

class EventBallLoader : public ItemLoader 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_EVENT_BALL; }
	virtual string getItemClassName()  { return "EventBall"; }

public:
	virtual void load(Creature* pCreature);
	virtual void load(Zone* pZone);
	virtual void load(StorageID_t storageID, Inventory* pInventory);
};

extern EventBallLoader* g_pEventBallLoader;

#endif
