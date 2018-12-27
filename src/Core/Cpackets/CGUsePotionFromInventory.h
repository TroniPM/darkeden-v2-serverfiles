//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGUsePotionFromInventory.h 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_USE_POTION_FROM_INVENTORY_H__
#define __CG_USE_POTION_FROM_INVENTORY_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////
//
// class CGUsePotionFromInventory;
//
//////////////////////////////////////////////////////////////////////

class CGUsePotionFromInventory : public Packet {
public:

	// constructor
	CGUsePotionFromInventory() ;

	// destructor
	~CGUsePotionFromInventory() ;

public:
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) ;
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID()  { return PACKET_CG_USE_POTION_FROM_INVENTORY; }
	
	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static CGUsePotionFromInventoryPacketSize �� �����ؼ� �����϶�.
	PacketSize_t getPacketSize()  { return szObjectID + szCoordInven + szCoordInven; }

	// get packet name
	string getPacketName()  { return "CGUsePotionFromInventory"; }
	
	// get packet's debug string
	string toString() ;
	
public:

	// get / set ObjectID
	ObjectID_t getObjectID()  { return m_ObjectID; }
	void setObjectID(ObjectID_t ObjectID)  { m_ObjectID = ObjectID; }

	// get / set Inventory X
	CoordInven_t getX()  { return m_InvenX; }
	void setX(CoordInven_t InvenX)  { m_InvenX = InvenX; }

	// get / set Inventory Y
	CoordInven_t getY()  { return m_InvenY; }
	void setY(CoordInven_t InvenY)  { m_InvenY = InvenY; }


private :
	
	// ObjectID
	ObjectID_t m_ObjectID;

	// Inventory�� X, Y ��ǥ
	CoordInven_t m_InvenX;
	CoordInven_t m_InvenY;

};


//////////////////////////////////////////////////////////////////////
//
// class CGUsePotionFromInventoryFactory;
//
// Factory for CGUsePotionFromInventory
//
//////////////////////////////////////////////////////////////////////

class CGUsePotionFromInventoryFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket()  { return new CGUsePotionFromInventory(); }

	// get packet name
	string getPacketName()  { return "CGUsePotionFromInventory"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_CG_USE_POTION_FROM_INVENTORY; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static CGUsePotionFromInventoryPacketSize �� �����ؼ� �����϶�.
	PacketSize_t getPacketMaxSize()  { return szObjectID + szCoordInven + szCoordInven; }

};


//////////////////////////////////////////////////////////////////////
//
// class CGUsePotionFromInventoryHandler;
//
//////////////////////////////////////////////////////////////////////

class CGUsePotionFromInventoryHandler {
	
public:
	// execute packet's handler
	static void execute(CGUsePotionFromInventory* pPacket, Player* player) ;
};

#endif
