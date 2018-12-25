//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGReady.h 
// Written By  : Reiot
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_READY_H__
#define __CG_READY_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class CGReady;
//
//////////////////////////////////////////////////////////////////////

class CGReady : public Packet {

public:

    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID()  { return PACKET_CG_READY; }
	
	// get packet body size
	// *OPTIMIZATION HINT*
	// const static CGReadyPacketSize �� ����, �����϶�.
	PacketSize_t getPacketSize()  { return 0; }
	
	// get packet's name
	string getPacketName()  { return "CGReady"; }
	
	// get packet's debug string
	string toString()  { return "CGReady"; }
	
};


//////////////////////////////////////////////////////////////////////
//
// class CGReadyFactory;
//
// Factory for CGReady
//
//////////////////////////////////////////////////////////////////////

class CGReadyFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket() throw() { return new CGReady(); }

	// get packet name
	string getPacketName()  { return "CGReady"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_CG_READY; }

	// get packet's max body size
	PacketSize_t getPacketMaxSize()  { return 0; }
	
};


//////////////////////////////////////////////////////////////////////
//
// class CGReadyHandler;
//
//////////////////////////////////////////////////////////////////////

class CGReadyHandler {

public:

	// execute packet's handler
	static void execute(CGReady* pPacket, Player* pPlayer) throw(ProtocolException, Error);

};

#endif
