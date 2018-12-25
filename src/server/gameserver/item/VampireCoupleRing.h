//////////////////////////////////////////////////////////////////////////////
// Filename    : VampireCoupleRing.h
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __VAMPIRE_COUPLE_RING_H__
#define __VAMPIRE_COUPLE_RING_H__

#include "CoupleRingBase.h"
#include "ItemInfo.h"
#include "InfoClassManager.h"
#include "ItemFactory.h"
#include "ItemLoader.h"
#include "Mutex.h"

//////////////////////////////////////////////////////////////////////////////
// class VampireCoupleRing;
//////////////////////////////////////////////////////////////////////////////
class VampireCoupleRing : public CoupleRingBase 
{
public:
	VampireCoupleRing() throw();
	VampireCoupleRing(ItemType_t itemType, const list<OptionType_t>& optionType) throw();
	
public:
	virtual void create(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y, ItemID_t itemID=0);
	virtual void save(const string & ownerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y);
	void tinysave(const string & field) 	{ tinysave(field.c_str()); }
	void tinysave(const char* field) ;
	virtual string toString() ;

	static void initItemIDRegistry(void) throw();

public:
	virtual ItemClass getItemClass()  { return Item::ITEM_CLASS_VAMPIRE_COUPLE_RING; }
	virtual string getObjectTableName()  { return "VampireCoupleRingObject"; }

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

	Defense_t getDefenseBonus()  { return 8; }
	Protection_t getProtectionBonus()  { return 3; }

	virtual VolumeWidth_t getVolumeWidth() ;
	virtual VolumeHeight_t getVolumeHeight() ;
	virtual Weight_t getWeight() ;

public:
	bool	hasPartnerItem();

private:
	ItemType_t 			m_ItemType;
	list<OptionType_t>	m_OptionType;
	
	static Mutex    	m_Mutex;          // 아이템 ID 관련 락
	static ItemID_t 	m_ItemIDRegistry; // 클래스별 고유 아이템 아이디 발급기
};

//////////////////////////////////////////////////////////////////////////////
// class VampireCoupleRingInfo
//////////////////////////////////////////////////////////////////////////////
class VampireCoupleRingInfo : public ItemInfo 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_VAMPIRE_COUPLE_RING; }
	virtual string toString() ;

private:
};

//////////////////////////////////////////////////////////////////////////////
// class VampireCoupleRingInfoManager;
//////////////////////////////////////////////////////////////////////////////
class VampireCoupleRingInfoManager : public InfoClassManager 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_VAMPIRE_COUPLE_RING; }
	virtual void load();
};

extern VampireCoupleRingInfoManager* g_pVampireCoupleRingInfoManager;

//////////////////////////////////////////////////////////////////////////////
// class VampireCoupleRingFactory
//////////////////////////////////////////////////////////////////////////////
class VampireCoupleRingFactory : public ItemFactory 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_VAMPIRE_COUPLE_RING; }
	virtual string getItemClassName()  { return "VampireCoupleRing"; }
	
public:
	virtual Item* createItem(ItemType_t ItemType, const list<OptionType_t>& OptionType) throw() { return new VampireCoupleRing(ItemType,OptionType); }
};


//////////////////////////////////////////////////////////////////////////////
// class VampireCoupleRingLoader;
//////////////////////////////////////////////////////////////////////////////
class VampireCoupleRingLoader : public ItemLoader 
{
public:
	virtual Item::ItemClass getItemClass()  { return Item::ITEM_CLASS_VAMPIRE_COUPLE_RING; }
	virtual string getItemClassName()  { return "VampireCoupleRing"; }

public:
	virtual void load(Creature* pCreature);
	virtual void load(Zone* pZone);
	virtual void load(StorageID_t storageID, Inventory* pInventory);
};

extern VampireCoupleRingLoader* g_pVampireCoupleRingLoader;

#endif
