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
	
	static Mutex    m_Mutex;          // ������ ID ���� ��
	static ItemID_t m_ItemIDRegistry; // Ŭ������ ���� ������ ���̵� �߱ޱ�
};

//////////////////////////////////////////////////////////////////////////////
// class DyePotionInfo
//////////////////////////////////////////////////////////////////////////////

class DyePotionInfo : public ItemInfo 
{
public:
	enum ITEM_FUNCTION
	{
		FUNCTION_HAIR = 0,				// �Ӹ����� �ٲ۴�.
		FUNCTION_SKIN = 1,				// �Ǻλ��� �ٲ۴�.
		FUNCTION_SEX = 2,				// ������ �ٲ۴�.
		FUNCTION_BAT = 3,				// ���� ���� �ٲ۴�.
		FUNCTION_REGEN = 4,				// ȸ��~
		FUNCTION_MASTER_EFFECT = 5,		// ������ ����Ʈ ���� �ٲ۴�.
		FUNCTION_STATUSPOINT = 6,				// ȸ��~
		FUNCTION_CLEARRANK = 7,				// ȸ��~
		FUNCTION_ALLSTATUSPOINT = 8,				// ȸ��~
		FUNCTION_KILLPOINT = 9,				// ȸ��~
		FUNCTION_COLOR_PAINT = 10,				// ȸ��~
		FUNCTION_ADVANCE_COLOR = 11,				// ȸ��~
		FUNCTION_ITEM_BOX = 12,				// ȸ��~
	};

public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_DYE_POTION; }
	virtual string toString() ;

public :
	virtual BYTE getFunctionFlag()  { return m_fFunction; }
	virtual void setFunctionFlag(BYTE flag) throw() { m_fFunction = flag; }

	virtual int getFunctionValue()  { return m_FunctionValue; }
	virtual void setFunctionValue(int value) throw() { m_FunctionValue = value; }


	BYTE	   m_fFunction;		// ���
	int        m_FunctionValue;	// ��ɰ� ���õ� ��
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
