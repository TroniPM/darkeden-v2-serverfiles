//////////////////////////////////////////////////////////////////////////////
// Filename    : CodeSheet.h
// Written By  : Elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __CODE_SHEET_H__
#define __CODE_SHEET_H__

#include "Item.h"
#include "ItemInfo.h"
#include "InfoClassManager.h"
#include "ItemFactory.h"
#include "ItemLoader.h"
#include "Mutex.h"

//////////////////////////////////////////////////////////////////////////////
// class CodeSheet;
//////////////////////////////////////////////////////////////////////////////

class CodeSheet : public Item 
{
public:
	CodeSheet() throw();
	CodeSheet(ItemType_t itemType, const list<OptionType_t>& optionType) throw();
	
public:
	virtual void create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID=0);
	virtual void save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y);
	void tinysave(const string & field) 	{ tinysave(field.c_str()); }
	void tinysave(const char* field) ;
	virtual string toString() ;

	static void initItemIDRegistry(void) throw();

public:
	virtual ItemClass getItemClass()  { return Item::ITEM_CLASS_CODE_SHEET; }
	virtual string getObjectTableName()  { return "CodeSheetObject"; }

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

private:
	ItemType_t			m_ItemType;			// 아이템 타입
	list<OptionType_t>		m_OptionType;		// 옵션 타입
	
	static Mutex    m_Mutex;          // 아이템 ID 관련 락
	static ItemID_t m_ItemIDRegistry; // 클래스별 고유 아이템 아이디 발급기
};


//////////////////////////////////////////////////////////////////////////////
// class CodeSheetInfo
//////////////////////////////////////////////////////////////////////////////

class CodeSheetInfo : public ItemInfo 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_CODE_SHEET; }

	virtual string toString() ;

private:
};


//////////////////////////////////////////////////////////////////////////////
// class CodeSheetInfoManager;
//////////////////////////////////////////////////////////////////////////////

class CodeSheetInfoManager : public InfoClassManager 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_CODE_SHEET; }
	virtual void load();
};

// global variable declaration
extern CodeSheetInfoManager* g_pCodeSheetInfoManager;


//////////////////////////////////////////////////////////////////////////////
// class CodeSheetFactory
//////////////////////////////////////////////////////////////////////////////

class CodeSheetFactory : public ItemFactory 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_CODE_SHEET; }
	virtual string getItemClassName()  { return "CodeSheet"; }
	
public:
	virtual Item* createItem(ItemType_t ItemType, const list<OptionType_t>& OptionType) throw() { return new CodeSheet(ItemType,OptionType); }
};


//////////////////////////////////////////////////////////////////////////////
// class CodeSheetLoader;
//////////////////////////////////////////////////////////////////////////////

class CodeSheetLoader : public ItemLoader 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_CODE_SHEET; }
	virtual string getItemClassName()  { return "CodeSheet"; }

public:
	virtual void load(Creature* pCreature);
	virtual void load(Zone* pZone);
	virtual void load(StorageID_t storageID, Inventory* pInventory);
};

extern CodeSheetLoader* g_pCodeSheetLoader;
#endif
