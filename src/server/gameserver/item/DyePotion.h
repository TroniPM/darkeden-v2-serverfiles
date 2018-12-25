//////////////////////////////////////////////////////////////////////////////
// Filename    : DyePotion.h
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __DYE_POTION_H__
#define __DYE_POTION_H__

#include "Item.h"
#include "ConcreteItem.h"
#include "ItemPolicies.h"
#include "ItemInfo.h"
#include "InfoClassManager.h"
#include "ItemFactory.h"
#include "ItemLoader.h"
#include "Mutex.h"

//////////////////////////////////////////////////////////////////////////////
// class DyePotion;
//////////////////////////////////////////////////////////////////////////////

class DyePotion : public ConcreteItem<Item::ITEM_CLASS_DYE_POTION, Stackable, NoDurability, NoOption, NoGrade, NoAttacking, NoEnchantLevel>
{
public:
	DyePotion() throw();
	DyePotion(ItemType_t itemType, const list<OptionType_t>& optionType, ItemNum_t Num) throw();
	
public:
	virtual void create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID=0);
	virtual void save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y);
	void tinysave(const string & field) 	{ tinysave(field.c_str()); }
	void tinysave(const char* field) ;
	virtual string toString() ;

	static void initItemIDRegistry(void) throw();

public:
//	virtual ItemClass getItemClass()  { return Item::ITEM_CLASS_DYE_POTION; }
//	virtual string getObjectTableName()  { return "DyePotionObject"; }

/*	virtual ItemType_t getItemType()  { return m_ItemType; }
	virtual void setItemType(ItemType_t itemType) throw() { m_ItemType = itemType; }

	virtual VolumeWidth_t getVolumeWidth() ;
	virtual VolumeHeight_t getVolumeHeight() ;
	virtual Weight_t getWeight() ;

public:
	virtual ItemNum_t getNum()  { return m_Num; }
	virtual void setNum(ItemNum_t Num) throw() { m_Num = Num; }

	bool    isStackable()  { return false; }
*/
private:
//	ItemType_t m_ItemType;
//	ItemNum_t  m_Num;
	
	static Mutex    m_Mutex;          // 아이템 ID 관련 락
	static ItemID_t m_ItemIDRegistry; // 클래스별 고유 아이템 아이디 발급기
};

//////////////////////////////////////////////////////////////////////////////
// class DyePotionInfo
//////////////////////////////////////////////////////////////////////////////

class DyePotionInfo : public ItemInfo 
{
public:
	enum ITEM_FUNCTION
	{
		FUNCTION_HAIR = 0,				// 머리색을 바꾼다.
		FUNCTION_SKIN = 1,				// 피부색을 바꾼다.
		FUNCTION_SEX = 2,				// 성별을 바꾼다.
		FUNCTION_BAT = 3,				// 박쥐 색을 바꾼다.
		FUNCTION_REGEN = 4,				// 회복~
		FUNCTION_MASTER_EFFECT = 5,		// 마스터 이펙트 색을 바꾼다.
		FUNCTION_STATUSPOINT = 6,				// 회복~
		FUNCTION_CLEARRANK = 7,				// 회복~
		FUNCTION_ALLSTATUSPOINT = 8,				// 회복~
		FUNCTION_KILLPOINT = 9,				// 회복~
		FUNCTION_COLOR_PAINT = 10,				// 회복~
		FUNCTION_ADVANCE_COLOR = 11,				// 회복~
		FUNCTION_ITEM_BOX = 12,				// 회복~
	};

public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_DYE_POTION; }
	virtual string toString() ;

public :
	virtual BYTE getFunctionFlag()  { return m_fFunction; }
	virtual void setFunctionFlag(BYTE flag) throw() { m_fFunction = flag; }

	virtual int getFunctionValue()  { return m_FunctionValue; }
	virtual void setFunctionValue(int value) throw() { m_FunctionValue = value; }


	BYTE	   m_fFunction;		// 기능
	int        m_FunctionValue;	// 기능과 관련된 값
};

//////////////////////////////////////////////////////////////////////////////
// class DyePotionInfoManager;
//////////////////////////////////////////////////////////////////////////////

class DyePotionInfoManager : public InfoClassManager 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_DYE_POTION; }
	virtual void load();
};

extern DyePotionInfoManager* g_pDyePotionInfoManager;

//////////////////////////////////////////////////////////////////////////////
// class DyePotionFactory
//////////////////////////////////////////////////////////////////////////////

class DyePotionFactory : public ItemFactory 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_DYE_POTION; }
	virtual string getItemClassName()  { return "DyePotion"; }
	
public:
	virtual Item* createItem(ItemType_t ItemType, const list<OptionType_t>& OptionType) throw() { return new DyePotion(ItemType,OptionType,1); }
};

//////////////////////////////////////////////////////////////////////////////
// class DyePotionLoader;
//////////////////////////////////////////////////////////////////////////////

class DyePotionLoader : public ItemLoader 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_DYE_POTION; }
	virtual string getItemClassName()  { return "DyePotion"; }

public:
	virtual void load(Creature* pCreature);
	virtual void load(Zone* pZone);
	virtual void load(StorageID_t storageID, Inventory* pInventory);
};

extern DyePotionLoader* g_pDyePotionLoader;

#endif
