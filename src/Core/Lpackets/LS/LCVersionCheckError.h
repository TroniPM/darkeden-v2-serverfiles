//////////////////////////////////////////////////////////////////////
// 
// Filename    : LCVersionCheckError.h 
// Written By  : Reiot
// Description :
// 
//////////////////////////////////////////////////////////////////////

#ifndef __LC_VERSION_CHECK_ERROR_H__
#define __LC_VERSION_CHECK_ERROR_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class LCVersionCheckError;
//
//
//////////////////////////////////////////////////////////////////////

class LCVersionCheckError : public Packet {

public:
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID()  { return PACKET_LC_VERSION_CHECK_ERROR; }
	
	// get packet's body size
	PacketSize_t getPacketSize()  { return 0; }
	
	// get packet's name
	string getPacketName()  { return "LCVersionCheckError"; }
	
	// get packet's debug string
	string toString() ;
	
};


//////////////////////////////////////////////////////////////////////
//
// class LCVersionCheckErrorFactory;
//
// Factory for LCVersionCheckError
//
//////////////////////////////////////////////////////////////////////

class LCVersionCheckErrorFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket() throw() { return new LCVersionCheckError(); }

	// get packet name
	string getPacketName()  { return "LCVersionCheckError"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_LC_VERSION_CHECK_ERROR; }

	// get packet's max body size
	PacketSize_t getPacketMaxSize()  { return 0; }
	
};


//////////////////////////////////////////////////////////////////////
//
// class LCVersionCheckErrorHandler;
//
//////////////////////////////////////////////////////////////////////

class LCVersionCheckErrorHandler {

public:

	// execute packet's handler
	static void execute(LCVersionCheckError* pPacket, Player* pPlayer) throw(ProtocolException, Error);

};

#endif
