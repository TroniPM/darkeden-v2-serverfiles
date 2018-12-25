//////////////////////////////////////////////////////////////////////////////
// Filename    : EventStar.h
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EVENT_STAR_H__
#define __EVENT_STAR_H__

#include "Item.h"
#include "ItemInfo.h"
#include "InfoClassManager.h"
#include "ItemFactory.h"
#include "ItemLoader.h"
#include "Mutex.h"
#include "ConcreteItem.h"
#include "ItemPolicies.h"

//////////////////////////////////////////////////////////////////////////////
// class EventStar;
//////////////////////////////////////////////////////////////////////////////

class EventStar : public ConcreteItem<Item::ITEM_CLASS_EVENT_STAR, Stackable, NoDurability, NoOption, NoGrade, NoAttacking, HasEnchantLevel, NoOption2, HasHeroOption, HasHeroOptionAttr>
{
public:
	EventStar() throw();
	EventStar(ItemType_t itemType, const list<OptionType_t>& optionType, ItemNum_t Num) throw();
	
public:
	virtual void create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID=0) throw(Error);
	virtual void save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y) throw(Error);
	void tinysave(const string & field) const throw (Error)	{ tinysave(field.c_str()); }
	void tinysave(const char* field) const throw (Error);
	virtual string toString() ;

	static void initItemIDRegistry(void) throw();

public:
	virtual ItemClass getItemClass()  { return Item::ITEM_CLASS_EVENT_STAR; }
	virtual string getObjectTableName()  { return "EventStarObject"; }

	virtual ItemType_t getItemType()  { return m_ItemType; }
	virtual void setItemType(ItemType_t itemType) throw() { m_ItemType = itemType; }

	virtual VolumeWidth_t getVolumeWidth() const throw(Error);
	virtual VolumeHeight_t getVolumeHeight() const throw(Error);
	virtual Weight_t getWeight() const throw(Error);

public:
	virtual ItemNum_t getNum()  { return m_Num; }
	virtual void setNum(ItemNum_t Num) throw() { m_Num = Num; }

	bool    isStackable()  { return true; }
	//bool isSilverWeapon()  { return true; }

	void makePCItemInfo(PCItemInfo& result) const;

private:
	ItemType_t m_ItemType;
	ItemNum_t  m_Num;

	static Mutex    m_Mutex;          // ������ ID ���� ��
	static ItemID_t m_ItemIDRegistry; // Ŭ������ ���� ������ ���̵� �߱ޱ�
};

//////////////////////////////////////////////////////////////////////////////
// class EventStarInfo
//////////////////////////////////////////////////////////////////////////////

class EventStarInfo : public ItemInfo 
{
public:
	enum ITEM_FUNCTION
	{
		FUNCTION_NULL = 0,
		FUNCTION_ENCHANT_OPTION = 1,	// �ɼ��� �� ���� �ٲ۴�.
		FUNCTION_ADD_OPTION = 2,		// �ɼ��� �߰��Ѵ�.
		FUNCTION_ENCHANT_RARE_OPTION = 4,	// ���� �������� �ɼ��� ��~�Ѵ�.
		FUNCTION_TRANS_KIT = 8,		// ���� ������ �ٲ۴�.
		FUNCTION_CORAL = 11,		// ������ �޼��� �ø���.
		FUNCTION_TYPE_GRADE = 12,		// ������ Ÿ�Ը� �ø���.
		FUNCTION_ENCHANT_SETOPTION = 13,		// ������ Ÿ�Ը� �ø���.
		FUNCTION_ENCHANT_SET_RARE_OPTION = 14,	// ���� �������� �ɼ��� ��~�Ѵ�.
		FUNCTION_ENCHANT_SET_THREE_OPTION = 15,	// ���� �������� �ɼ��� ��~�Ѵ�.
		FUNCTION_UP_GRADE = 16,		// ������ �޼��� �ø���.
		FUNCTION_ENCHANT_ADDSETOPTION = 17,		// ������ Ÿ�Ը� �ø���.
		FUNCTION_ENCHANT_SET_ADDRARE_OPTION = 18,	// ���� �������� �ɼ��� ��~�Ѵ�.
		FUNCTION_ENCHANT_SET_ADDTHREE_OPTION = 19,	// ���� �������� �ɼ��� ��~�Ѵ�.
		FUNCTION_ENCHANT_REDSUNCORE = 20,	// ���� �������� �ɼ��� ��~�Ѵ�.
		FUNCTION_ENCHANT_PET_ENCHANT = 21,	// �� ������ ���׷��̵�
	};

public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_EVENT_STAR; }
	virtual string toString() ;

public :
	virtual BYTE getFunctionFlag()  { return m_fFunction; }
	virtual BYTE isFunctionEnchantOption() const { return m_fFunction & FUNCTION_ENCHANT_OPTION; }	// �ɼ��� �� ���� �ٲ۴�.
	virtual BYTE isFunctionAddOption() const { return m_fFunction & FUNCTION_ADD_OPTION; }	// �ɼ��� �߰��Ѵ�.
	virtual BYTE isFunctionEnchantRareOption() const { return m_fFunction & FUNCTION_ENCHANT_RARE_OPTION; }	// �ɼ��� �� ���� �ٲ۴�.
	virtual BYTE isFunctionTransKit() const { return m_fFunction & FUNCTION_TRANS_KIT; }
	virtual void setFunctionFlag(BYTE flag) throw() { m_fFunction = flag; }

	virtual int getFunctionValue()  { return m_FunctionValue; }
	virtual void setFunctionValue(int value) throw() { m_FunctionValue = value; }


	BYTE	   m_fFunction;		// ���
	int        m_FunctionValue;	// ��ɰ� ���õ� ��
};

//////////////////////////////////////////////////////////////////////////////
// class EventStarInfoManager;
//////////////////////////////////////////////////////////////////////////////

class EventStarInfoManager : public InfoClassManager 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_EVENT_STAR; }
	virtual void load() throw(Error);
};

extern EventStarInfoManager* g_pEventStarInfoManager;

//////////////////////////////////////////////////////////////////////////////
// class EventStarFactory
//////////////////////////////////////////////////////////////////////////////

class EventStarFactory : public ItemFactory 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_EVENT_STAR; }
	virtual string getItemClassName()  { return "EventStar"; }
	
public:
	virtual Item* createItem(ItemType_t ItemType, const list<OptionType_t>& OptionType) throw() { return new EventStar(ItemType,OptionType,1); }
};

//////////////////////////////////////////////////////////////////////////////
// class EventStarLoader;
//////////////////////////////////////////////////////////////////////////////

class EventStarLoader : public ItemLoader 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_EVENT_STAR; }
	virtual string getItemClassName()  { return "EventStar"; }

public:
	virtual void load(Creature* pCreature) throw(Error);
	virtual void load(Zone* pZone) throw(Error);
	virtual void load(StorageID_t storageID, Inventory* pInventory) throw(Error);
};

extern EventStarLoader* g_pEventStarLoader;

#endif
