//////////////////////////////////////////////////////////////////////////////
// Filename    : Gun.h
// Written By  : sigi
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __GUN_H__
#define __GUN_H__

#include "Item.h"

//////////////////////////////////////////////////////////////////////////////
// class Gun;
//////////////////////////////////////////////////////////////////////////////

class Gun : public Item 
{
public:
	Gun() ;
	Gun(ItemType_t itemType, const list<OptionType_t>& optionType) ;
	virtual ~Gun() ;
	
public:
	virtual void saveBullet()  = 0;
	bool isGun()  { return true; }

public:
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


	virtual Durability_t getDurability()  { return m_Durability; }
	void setDurability(Durability_t durability)  { m_Durability = durability; }

	BYTE getBulletCount()  { return m_BulletCount; }
	void setBulletCount(BYTE bulletCount) throw() { m_BulletCount = bulletCount; }

	Damage_t getBonusDamage()  { return m_BonusDamage;}
	void setBonusDamage(Damage_t damage) throw() { m_BonusDamage = damage;}

	virtual Silver_t getSilver()  { return m_Silver; }
	virtual void setSilver(Silver_t amount) throw() { m_Silver = amount; }

	virtual EnchantLevel_t getEnchantLevel()  { return m_EnchantLevel; }
	virtual void setEnchantLevel(EnchantLevel_t level) throw() { m_EnchantLevel = level; }

	void makePCItemInfo(PCItemInfo& result) const;

protected:
	ItemType_t     m_ItemType;
	list<OptionType_t>   m_OptionType;
	Durability_t   m_Durability;
	BYTE           m_BulletCount;
	BYTE           m_BonusDamage;
	Silver_t       m_Silver;
	EnchantLevel_t m_EnchantLevel;
};

#endif
