//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGStoreOpen.h 
// Written By  :
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_STORE_OPEN_H__
#define __CG_STORE_OPEN_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class CGStoreOpen;
//
//////////////////////////////////////////////////////////////////////

class CGStoreOpen : public Packet
{
public:
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_CG_STORE_OPEN; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const throw() { return 0; }

	// get packet name
	string getPacketName() const throw() { return "CGStoreOpen"; }

	// get packet's debug string
	string toString() const throw();

};


//////////////////////////////////////////////////////////////////////
//
// class CGStoreOpenFactory;
//
// Factory for CGStoreOpen
//
//////////////////////////////////////////////////////////////////////

class CGStoreOpenFactory : public PacketFactory {

public:
	
	// constructor
	CGStoreOpenFactory() throw() {}
	
	// destructor
	virtual ~CGStoreOpenFactory() throw() {}

	
public:
	
	// create packet
	Packet* createPacket() throw() { return new CGStoreOpen(); }

	// get packet name
	string getPacketName() const throw() { return "CGStoreOpen"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_CG_STORE_OPEN; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize() const throw() { return 0; }
};


//////////////////////////////////////////////////////////////////////
//
// class CGStoreOpenHandler;
//
//////////////////////////////////////////////////////////////////////

class CGStoreOpenHandler {

public:

	// execute packet's handler
	static void execute(CGStoreOpen* pCGStoreOpen, Player* pPlayer) throw(Error);

};

#endif
