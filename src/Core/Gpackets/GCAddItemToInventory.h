//////////////////////////////////////////////////////////////////////////////
// Filename    : GCAddItemToInventory.h 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_ADD_ITEM_TO_INVENTORY_H__
#define __GC_ADD_ITEM_TO_INVENTORY_H__

#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"
#include <list>

//////////////////////////////////////////////////////////////////////////////
// class GCAddItemToInventory;
//////////////////////////////////////////////////////////////////////////////

class GCAddItemToInventory 
{
public:
	GCAddItemToInventory() ;
	~GCAddItemToInventory() ;
	
public:
    void read(SocketInputStream & iStream) ;
    void write(SocketOutputStream & oStream) ;
	PacketSize_t getPacketSize()  { return szObjectID + szCoord + szCoord + szBYTE + szItemType + szBYTE + m_OptionType.size() + szDurability; }
	string getPacketName()  { return "GCAddItemToInventory"; }
	string toString() ;

public:
	ObjectID_t getObjectID()  { return m_ObjectID; }
	void setObjectID(ObjectID_t ID)  { m_ObjectID = ID; }

	CoordInven_t getX()  { return m_X; }
	void setX(CoordInven_t x)  { m_X = x; }
	
	CoordInven_t getY()  { return m_Y; }
	void setY(CoordInven_t y)  { m_Y = y; }

	BYTE getItemClass()  { return m_ItemClass; }
	void setItemClass(BYTE Class)  { m_ItemClass = Class; }

	ItemType_t getItemType()  { return m_ItemType; }
	void setItemType(ItemType_t ItemType)  { m_ItemType = ItemType; }

	int getOptionTypeSize()  { return m_OptionType.size(); }
	const list<OptionType_t>& getOptionType()  { return m_OptionType; }
	OptionType_t popOptionType() 
	{
		if (m_OptionType.empty()) return 0;
		OptionType_t optionType = m_OptionType.front();
		m_OptionType.pop_front();
		return optionType;
	}
	void addOptionType(OptionType_t OptionType)  { m_OptionType.push_back( OptionType ); }
	void setOptionType(const list<OptionType_t>& OptionTypes)  { m_OptionType = OptionTypes; }

	Durability_t getDurability()  { return m_Durability; }
	void setDurability(Durability_t Durability)  { m_Durability = Durability; }

	ItemNum_t getItemNum()  { return m_ItemNum; }
	void setItemNum(ItemNum_t ItemNum)  { m_ItemNum = ItemNum; }

protected:
    ObjectID_t    		m_ObjectID;     // item object id
   	CoordInven_t  		m_X;            // inventory x coord
	CoordInven_t  		m_Y;            // inventory y coord
	BYTE          		m_ItemClass;    // item Class
	ItemType_t    		m_ItemType;     // item type
	list<OptionType_t>  m_OptionType;   // item option type
	Durability_t  		m_Durability;   // item durability
	ItemNum_t     		m_ItemNum;      // number of item
};

#endif
