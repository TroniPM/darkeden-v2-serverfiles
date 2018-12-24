//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGReloadFromInventory.h 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_RELOAD_FROM_INVENTORY_H__
#define __CG_RELOAD_FROM_INVENTORY_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////
//
// class CGReloadFromInventory;
//
//////////////////////////////////////////////////////////////////////

class CGReloadFromInventory : public Packet {
public:

	// constructor
	CGReloadFromInventory() throw();

	// destructor
	~CGReloadFromInventory() throw();

public:
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_CG_RELOAD_FROM_INVENTORY; }
	
	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static CGReloadFromInventoryPacketSize �� �����ؼ� �����϶�.
	PacketSize_t getPacketSize() const throw() { return szObjectID + szCoordInven + szCoordInven; }

	// get packet name
	string getPacketName() const throw() { return "CGReloadFromInventory"; }
	
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
// class CGReloadFromInventoryFactory;
//
// Factory for CGReloadFromInventory
//
//////////////////////////////////////////////////////////////////////

class CGReloadFromInventoryFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket() throw() { return new CGReloadFromInventory(); }

	// get packet name
	string getPacketName() const throw() { return "CGReloadFromInventory"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_CG_RELOAD_FROM_INVENTORY; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static CGReloadFromInventoryPacketSize �� �����ؼ� �����϶�.
	PacketSize_t getPacketMaxSize() const throw() { return szObjectID + szCoordInven + szCoordInven; }

};


//////////////////////////////////////////////////////////////////////
//
// class CGReloadFromInventoryHandler;
//
//////////////////////////////////////////////////////////////////////

class CGReloadFromInventoryHandler {
	
public:

	// execute packet's handler
	static void execute(CGReloadFromInventory* pPacket, Player* player) throw(ProtocolException, Error);
};

#endif
