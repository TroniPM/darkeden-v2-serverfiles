//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGPhoneDisconnect.h 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_PHONE_DISCONNECT_H__
#define __CG_PHONE_DISCONNECT_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////
//
// class CGPhoneDisconnect;
//
//////////////////////////////////////////////////////////////////////

class CGPhoneDisconnect : public Packet {
public:

	// constructor
	CGPhoneDisconnect() throw();

	// destructor
	~CGPhoneDisconnect() throw();

public:
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID()  { return PACKET_CG_PHONE_DISCONNECT; }
	
	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static CGPhoneDisconnectPacketSize �� �����ؼ� �����϶�.
	PacketSize_t getPacketSize()  { return szSlotID; }

	// get packet name
	string getPacketName()  { return "CGPhoneDisconnect"; }
	
	// get packet's debug string
	string toString() ;
	
public:

	// get / set phoneNumber
	SlotID_t getSlotID()  { return m_SlotID; }
	void setSlotID(SlotID_t SlotID) throw() { m_SlotID = SlotID; }

private :
	
	// SlotID
	SlotID_t m_SlotID;

};


//////////////////////////////////////////////////////////////////////
//
// class CGPhoneDisconnectFactory;
//
// Factory for CGPhoneDisconnect
//
//////////////////////////////////////////////////////////////////////

class CGPhoneDisconnectFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket() throw() { return new CGPhoneDisconnect(); }

	// get packet name
	string getPacketName()  { return "CGPhoneDisconnect"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_CG_PHONE_DISCONNECT; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static CGPhoneDisconnectPacketSize �� �����ؼ� �����϶�.
	PacketSize_t getPacketMaxSize()  { return szSlotID; }

};


//////////////////////////////////////////////////////////////////////
//
// class CGPhoneDisconnectHandler;
//
//////////////////////////////////////////////////////////////////////

class CGPhoneDisconnectHandler {
	
public:

	// execute packet's handler
	static void execute(CGPhoneDisconnect* pPacket, Player* player) throw(ProtocolException, Error);
};

#endif
