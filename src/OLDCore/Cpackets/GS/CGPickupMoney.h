//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGPickupMoney.h 
// Written By  : 
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_PICKUP_MONEY_H__
#define __CG_PICKUP_MONEY_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////
//
// class CGPickupMoney;
//
//////////////////////////////////////////////////////////////////////

class CGPickupMoney : public Packet {
public:

	// constructor
	CGPickupMoney() throw();

	// destructor
	~CGPickupMoney() throw();

public:
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_CG_PICKUP_MONEY; }
	
	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static CGPickupMoneyPacketSize �� �����ؼ� �����϶�.
	PacketSize_t getPacketSize() const throw() { return szObjectID + szCoord + szCoord; }

	// get packet name
	string getPacketName() const throw() { return "CGPickupMoney"; }
	
	// get packet's debug string
	string toString() const throw();
	
public:

	// get / set ObjectID
	ObjectID_t getObjectID() throw() { return m_ObjectID; }
	void setObjectID(ObjectID_t ObjectID) throw() { m_ObjectID = ObjectID; }

	// get/set X Coordicate
	Coord_t getZoneX() const throw() { return m_ZoneX; }
	void setZoneX(Coord_t ZoneX) throw() { m_ZoneX = ZoneX; }

	// get/set Y Coordicate
	Coord_t getZoneY() const throw() { return m_ZoneY; }
	void setZoneY(Coord_t ZoneY) throw() { m_ZoneY = ZoneY; }

private :
	
	// ObjectID
	ObjectID_t m_ObjectID;

	// �������� �ִ� Zone��  X, Y ��ǥ.
	Coord_t m_ZoneX;
	Coord_t m_ZoneY;

};


//////////////////////////////////////////////////////////////////////
//
// class CGPickupMoneyFactory;
//
// Factory for CGPickupMoney
//
//////////////////////////////////////////////////////////////////////

class CGPickupMoneyFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket() throw() { return new CGPickupMoney(); }

	// get packet name
	string getPacketName() const throw() { return "CGPickupMoney"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_CG_PICKUP_MONEY; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static CGPickupMoneyPacketSize �� �����ؼ� �����϶�.
	PacketSize_t getPacketMaxSize() const throw() { return szObjectID + szCoord + szCoord; }

};


//////////////////////////////////////////////////////////////////////
//
// class CGPickupMoneyHandler;
//
//////////////////////////////////////////////////////////////////////

class CGPickupMoneyHandler {
	
public:

	// execute packet's handler
	static void execute(CGPickupMoney* pPacket, Player* player) throw(ProtocolException, Error);
};

#endif
