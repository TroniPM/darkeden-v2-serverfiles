//////////////////////////////////////////////////////////////////////////////
// Filename    : GCAddItemToZone.h 
// Written By  : elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_ADD_ITEM_TO_ZONE_H__
#define __GC_ADD_ITEM_TO_ZONE_H__

#include "Packet.h"
#include "PacketFactory.h"
#include "SubItemInfo.h"
#include <list>

//////////////////////////////////////////////////////////////////////////////
// class GCAddItemToZone;
//////////////////////////////////////////////////////////////////////////////

class GCAddItemToZone : public Packet 
{
public:
	GCAddItemToZone() ;
	~GCAddItemToZone() ;

public:
    void read(SocketInputStream & iStream) ;
    void write(SocketOutputStream & oStream) ;
	PacketSize_t getPacketSize()  
	{ 
		PacketSize_t rValue = 0;

		rValue += szObjectID;                       // item object id
		rValue += szCoord*2;                        // item coord in inventory
		rValue += szBYTE;                           // item class
		rValue += szItemType;                       // item type
		rValue += szBYTE + m_OptionType.size();     // item option type
		rValue += szBYTE + m_OptionType2.size();     // item option type
		rValue += szSilver;                         // silver
		rValue += szGrade;                         // silver
		rValue += szDurability;                     // item durability
		rValue += szEnchantLevel;                   // enchant level
		rValue += szEnchantLevel;                   // enchant level
		rValue += szEnchantLevel;                   // enchant level
		rValue += szItemNum;                        // number of item
		rValue += szBYTE;                           // number of sub item
		rValue += SubItemInfo::getSize()*m_ListNum; // actual sub item info

		return rValue;
	}

public :

	// get/set creature ID 
	ObjectID_t getObjectID()  { return m_ObjectID; }
	void setObjectID(ObjectID_t creatureID)  { m_ObjectID = creatureID; }

	// get/set X
	Coord_t getX()  { return m_X; }
	void setX(Coord_t x)  { m_X = x; }
	
	// get/set Y
	Coord_t getY()  { return m_Y; }
	void setY(Coord_t y)  { m_Y = y; }

	// get / set ItemClass
	BYTE getItemClass()  { return m_ItemClass; }
	void setItemClass(BYTE Class)  { m_ItemClass = Class; }

	// get / set ItemType
	ItemType_t getItemType()  { return m_ItemType; }
	void setItemType(ItemType_t ItemType)  { m_ItemType = ItemType; }

	// get / set OptionType
	OptionType_t popOptionType() 
	{
		if (m_OptionType.empty()) return 0;
		OptionType_t optionType = m_OptionType.front();
		m_OptionType.pop_front();
		return optionType;
	}
	int getOptionTypeSize()  { return m_OptionType.size(); }
	void addOptionType(OptionType_t OptionType)  { m_OptionType.push_back( OptionType ); }
	void setOptionType(const list<OptionType_t>& OptionTypes)  { m_OptionType = OptionTypes; }
	const list<OptionType_t>& getOptionType()  { return m_OptionType; }

	// get / set OptionType
	OptionType_t popOptionType2() 
	{
		if (m_OptionType2.empty()) return 0;
		OptionType_t optionType2 = m_OptionType2.front();
		m_OptionType2.pop_front();
		return optionType2;
	}
	int getOptionTypeSize2()  { return m_OptionType2.size(); }
	void addOptionType2(OptionType_t OptionType)  { m_OptionType2.push_back( OptionType ); }
	void setOptionType2(const list<OptionType_t>& OptionTypes)  { m_OptionType2 = OptionTypes; }
	const list<OptionType_t>& getOptionType2()  { return m_OptionType2; }

	// get / set Silver
	Silver_t getSilver()  { return m_Silver; }
	void setSilver(Silver_t Silver)  { m_Silver = Silver; }

	// get / set Grade
	Grade_t getGrade()  { return m_Grade; }
	void setGrade(Grade_t Grade)  { m_Grade = Grade; }

	// get / set enchant level
	EnchantLevel_t getEnchantLevel()  { return m_EnchantLevel; }
	void setEnchantLevel(EnchantLevel_t level)  { m_EnchantLevel = level; }

	EnchantLevel_t getHeroOption()  { return m_HeroOption; }
	void setHeroOption(EnchantLevel_t level)  { m_HeroOption= level; }

	EnchantLevel_t getHeroOptionAttr()  { return m_HeroOptionAttr; }
	void setHeroOptionAttr(EnchantLevel_t level)  { m_HeroOptionAttr = level; }

	// get / set Durability
	Durability_t getDurability()  { return m_Durability; }
	void setDurability(Durability_t Durability)  { m_Durability = Durability; }

	// get / set ItemNum
	ItemNum_t getItemNum()  { return m_ItemNum; }
	void setItemNum(ItemNum_t ItemNum)  { m_ItemNum = ItemNum; }

	// get / set ListNumber
	BYTE getListNum()  { return m_ListNum; }
	void setListNum(BYTE ListNum)  { m_ListNum = ListNum; }

	// add / delete / clear S List
	void addListElement(SubItemInfo* pSubItemInfo)  { m_SubItemInfoList.push_back(pSubItemInfo); }

	// ClearList
	void clearList()  { m_SubItemInfoList.clear(); m_ListNum = 0; }

	// pop front Element in Status List
	SubItemInfo* popFrontListElement()  
	{ 
		SubItemInfo* TempSubItemInfo = m_SubItemInfoList.front(); m_SubItemInfoList.pop_front(); return TempSubItemInfo; 
	}

protected :
	
    // Item¿« ObjectID
    ObjectID_t m_ObjectID;

	// Zone¿« X, Y ¡¬«•
   	Coord_t m_X;
	Coord_t m_Y;

	// Item Class
	BYTE m_ItemClass;

	// ItemType
	ItemType_t m_ItemType;

	// ItemOptionType
	list<OptionType_t> m_OptionType;
	list<OptionType_t> m_OptionType2;

	// Silvering
	Silver_t m_Silver;

	Grade_t m_Grade;

	// Durability
	Durability_t m_Durability;

	// Enchant level
	EnchantLevel_t m_EnchantLevel;
	EnchantLevel_t m_HeroOption;
	EnchantLevel_t m_HeroOptionAttr;

	// ItemNum
	ItemNum_t m_ItemNum;

	//	// SubItemInfo List Total Number
	BYTE m_ListNum;
	
	// SubItemInfo List
	list<SubItemInfo*> m_SubItemInfoList;

};

#endif
