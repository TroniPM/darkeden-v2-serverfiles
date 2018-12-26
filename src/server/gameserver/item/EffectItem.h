//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectItem.h
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_ITEM_H__
#define __EFFECT_ITEM_H__

#include "Item.h"
#include "ConcreteItem.h"
#include "ItemPolicies.h"
#include "ItemInfo.h"
#include "InfoClassManager.h"
#include "ItemFactory.h"
#include "ItemLoader.h"
#include "Mutex.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectItem;
//////////////////////////////////////////////////////////////////////////////

class EffectItem : public ConcreteItem<Item::ITEM_CLASS_EFFECT_ITEM, Stackable, NoDurability, NoOption, NoGrade, NoAttacking, NoEnchantLevel, NoOption2, HasHeroOption, NoHeroOptionAttr>
{
public:
	EffectItem() ;
	EffectItem(ItemType_t itemType, const list<OptionType_t>& optionType, ItemNum_t Num) ;
	
public:
	virtual void create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID=0);
	virtual void save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y);
	void tinysave(const string & field) 	{ tinysave(field.c_str()); }
	void tinysave(const char* field) ;
	virtual string toString() ;

	static void initItemIDRegistry(void) ;

public:
private:
	
	static Mutex    m_Mutex;          // 아이템 ID 관련 락
	static ItemID_t m_ItemIDRegistry; // 클래스별 고유 아이템 아이디 발급기
};

//////////////////////////////////////////////////////////////////////////////
// class EffectItemInfo
//////////////////////////////////////////////////////////////////////////////

class EffectItemInfo : public ItemInfo 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_EFFECT_ITEM; }
	virtual string toString() ;

	Effect::EffectClass	getEffectClass() const { return m_EffectClass; }
	void				setEffectClass( Effect::EffectClass eClass ) { m_EffectClass = eClass; }

	int		getDuration() const { return m_Duration; }
	void	setDuration( int Duration ) { m_Duration = Duration; }

	const string& getNotEffectClass()  { return m_Name; }
	void setNotEffectClass(const string & name) throw() { m_Name = name;}

private:
	Effect::EffectClass m_EffectClass;
	int					m_Duration;
	string m_Name;

};

//////////////////////////////////////////////////////////////////////////////
// class EffectItemInfoManager;
//////////////////////////////////////////////////////////////////////////////

class EffectItemInfoManager : public InfoClassManager 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_EFFECT_ITEM; }
	virtual void load();
};

extern EffectItemInfoManager* g_pEffectItemInfoManager;

//////////////////////////////////////////////////////////////////////////////
// class EffectItemFactory
//////////////////////////////////////////////////////////////////////////////

class EffectItemFactory : public ItemFactory 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_EFFECT_ITEM; }
	virtual string getItemClassName()  { return "EffectItem"; }
	
public:
	virtual Item* createItem(ItemType_t ItemType, const list<OptionType_t>& OptionType) throw() { return new EffectItem(ItemType,OptionType,1); }
};

//////////////////////////////////////////////////////////////////////////////
// class EffectItemLoader;
//////////////////////////////////////////////////////////////////////////////

class EffectItemLoader : public ItemLoader 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_EFFECT_ITEM; }
	virtual string getItemClassName()  { return "EffectItem"; }

public:
	virtual void load(Creature* pCreature);
	virtual void load(Zone* pZone);
	virtual void load(StorageID_t storageID, Inventory* pInventory);
};

extern EffectItemLoader* g_pEffectItemLoader;

#endif
