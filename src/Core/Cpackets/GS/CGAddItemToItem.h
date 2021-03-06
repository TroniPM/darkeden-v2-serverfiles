//////////////////////////////////////////////////////////////////////////////
// Filename    : CGAddItemToItem.h 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __CG_ADD_ITEM_TO_ITEM_H__
#define __CG_ADD_ITEM_TO_ITEM_H__

#include "Packet.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////////////
// class CGAddItemToItem;
//////////////////////////////////////////////////////////////////////////////

class CGAddItemToItem : public Packet 
{
public:
    void read(SocketInputStream & iStream) ;
    void write(SocketOutputStream & oStream) ;
	void execute(Player* pPlayer) ;
	PacketID_t getPacketID()  { return PACKET_CG_ADD_ITEM_TO_ITEM; }
	PacketSize_t getPacketSize()  { return szObjectID + szCoordInven + szCoordInven; }
	string getPacketName()  { return "CGAddItemToItem"; }
	string toString() ;

public:
	ObjectID_t getObjectID()  { return m_ObjectID; }
	void setObjectID(ObjectID_t ObjectID)  { m_ObjectID = ObjectID; }

	CoordInven_t getX()  { return m_X; }
	void setX(Coord_t X)  { m_X = X; }

	CoordInven_t getY()  { return m_Y; }
	void setY(Coord_t Y)  { m_Y = Y; }

private :
	ObjectID_t   m_ObjectID;	// ObjectID
	CoordInven_t m_X;			// Coord X
	CoordInven_t m_Y;			// Coord Y
};

//////////////////////////////////////////////////////////////////////////////
// class CGAddItemToItemFactory;
//////////////////////////////////////////////////////////////////////////////

class CGAddItemToItemFactory : public PacketFactory 
{
public:
	Packet* createPacket()  { return new CGAddItemToItem(); }
	string getPacketName()  { return "CGAddItemToItem"; }
	PacketID_t getPacketID()  { return Packet::PACKET_CG_ADD_ITEM_TO_ITEM; }
	PacketSize_t getPacketMaxSize()  { return szObjectID + szCoordInven + szCoordInven; }
};

//////////////////////////////////////////////////////////////////////////////
// class CGAddItemToItemHandler;
//////////////////////////////////////////////////////////////////////////////

class CGAddItemToItemHandler 
{
public:
	static void execute(CGAddItemToItem* pCGAddItemToItem, Player* pPlayer);

};

#endif
