//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGStoreClose.h 
// Written By  :
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_STORE_CLOSE_H__
#define __CG_STORE_CLOSE_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class CGStoreClose;
//
//////////////////////////////////////////////////////////////////////

class CGStoreClose : public Packet
{
public:
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID()  { return PACKET_CG_STORE_CLOSE; }
	
	// get packet's body size
	PacketSize_t getPacketSize()  { return 0; }

	// get packet name
	string getPacketName()  { return "CGStoreClose"; }

	// get packet's debug string
	string toString() ;

};


//////////////////////////////////////////////////////////////////////
//
// class CGStoreCloseFactory;
//
// Factory for CGStoreClose
//
//////////////////////////////////////////////////////////////////////

class CGStoreCloseFactory : public PacketFactory {

public:
	
	// constructor
	CGStoreCloseFactory() throw() {}
	
	// destructor
	virtual ~CGStoreCloseFactory() throw() {}

	
public:
	
	// create packet
	Packet* createPacket() throw() { return new CGStoreClose(); }

	// get packet name
	string getPacketName()  { return "CGStoreClose"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_CG_STORE_CLOSE; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize()  { return 0; }
};


//////////////////////////////////////////////////////////////////////
//
// class CGStoreCloseHandler;
//
//////////////////////////////////////////////////////////////////////

class CGStoreCloseHandler {

public:

	// execute packet's handler
	static void execute(CGStoreClose* pCGStoreClose, Player* pPlayer) throw(Error);

};

#endif
