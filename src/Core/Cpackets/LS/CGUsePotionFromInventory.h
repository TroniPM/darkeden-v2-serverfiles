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
	CGUsePotionFromInventory() throw();

	// destructor
	~CGUsePotionFromInventory() throw();

public:
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_CG_USE_POTION_FROM_INVENTORY; }
	
	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static CGUsePotionFromInventoryPacketSize �� �����ؼ� �����϶�.
	PacketSize_t getPacketSize() const throw() { return szObjectID + szCoordInven + szCoordInven; }

	// get packet name
	string getPacketName() const throw() { return "CGUsePotionFromInventory"; }
	
	// get packet's debug string
	string toString() const throw();
	
public:

	// get / set ObjectID
	ObjectID_t getObjectID() const throw() { return m_ObjectID; }
	void setObjectID(ObjectID_t ObjectID) throw() { m_ObjectID = ObjectID; }

	// get / set Inventory X
	CoordInven_t getX() const throw() { return m_InvenX; }
	void setX(CoordInven_t InvenX) throw() { m_InvenX = InvenX; }

	// get / set Inventory Y
	CoordInven_t getY() const throw() { return m_InvenY; }
	void setY(CoordInven_t InvenY) throw() { m_InvenY = InvenY; }


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
	Packet* createPacket() throw() { return new CGUsePotionFromInventory(); }

	// get packet name
	string getPacketName() const throw() { return "CGUsePotionFromInventory"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_CG_USE_POTION_FROM_INVENTORY; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static CGUsePotionFromInventoryPacketSize �� �����ؼ� �����϶�.
	PacketSize_t getPacketMaxSize() const throw() { return szObjectID + szCoordInven + szCoordInven; }

};


//////////////////////////////////////////////////////////////////////
//
// class CGUsePotionFromInventoryHandler;
//
//////////////////////////////////////////////////////////////////////

class CGUsePotionFromInventoryHandler {
	
public:
	// execute packet's handler
	static void execute(CGUsePotionFromInventory* pPacket, Player* player) throw(ProtocolException, Error);
};

#endif
