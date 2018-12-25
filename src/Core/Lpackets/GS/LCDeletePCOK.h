//////////////////////////////////////////////////////////////////////
// 
// Filename    : LCDeletePCOK.h 
// Written By  : Reiot
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __LC_DELETE_PC_OK_H__
#define __LC_DELETE_PC_OK_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class LCDeletePCOK;
//
//////////////////////////////////////////////////////////////////////

class LCDeletePCOK : public Packet {

public:

    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) ;
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID()  { return PACKET_LC_DELETE_PC_OK; }
	
	// get packet body size
	// *OPTIMIZATION HINT*
	// const static LCDeletePCOKPacketSize �� ����, �����϶�.
	PacketSize_t getPacketSize()  { return 0; }
	
	// get packet's name
	string getPacketName()  { return "LCDeletePCOK"; }
	
	// get packet's debug string
	string toString()  { return "LCDeletePCOK"; }
	
};


//////////////////////////////////////////////////////////////////////
//
// class LCDeletePCOKFactory;
//
// Factory for LCDeletePCOK
//
//////////////////////////////////////////////////////////////////////

class LCDeletePCOKFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket() throw() { return new LCDeletePCOK(); }

	// get packet name
	string getPacketName()  { return "LCDeletePCOK"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_LC_DELETE_PC_OK; }

	// get packet's max body size
	PacketSize_t getPacketMaxSize()  { return 0; }
	
};


//////////////////////////////////////////////////////////////////////
//
// class LCDeletePCOKHandler;
//
//////////////////////////////////////////////////////////////////////

class LCDeletePCOKHandler {

public:

	// execute packet's handler
	static void execute(LCDeletePCOK* pPacket, Player* pPlayer) ;

};

#endif
