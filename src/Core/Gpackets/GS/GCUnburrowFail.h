//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCUnburrowFail.h 
// Written By  : crazydog
// Description :
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_UNBURROW_FAIL_H__
#define __GC_UNBURROW_FAIL_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class GCUnburrowFail;
//
//////////////////////////////////////////////////////////////////////

class GCUnburrowFail : public Packet {

public :

	// constructor
	GCUnburrowFail() throw() {}
	

public :

    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID()  { return PACKET_GC_UNBURROW_FAIL; }
	
	// get packet's body size
	PacketSize_t getPacketSize()  { return 0; }
	
	// get packet's name
	string getPacketName()  { return "GCUnburrowFail"; }
	
	// get packet's debug string
	string toString() ;
	

public :


private : 


};


//////////////////////////////////////////////////////////////////////
//
// class  GCUnburrowFailFactory;
//
// Factory for  GCUnburrowFail
//
//////////////////////////////////////////////////////////////////////

class  GCUnburrowFailFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket() throw() { return new GCUnburrowFail(); }

	// get packet name
	string getPacketName()  { return "GCUnburrowFail"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_GC_UNBURROW_FAIL; }

	// get packet's max body size
	PacketSize_t getPacketMaxSize()  { return 0; }
	
};


//////////////////////////////////////////////////////////////////////
//
// class  GCUnburrowFailHandler;
//
//////////////////////////////////////////////////////////////////////

class  GCUnburrowFailHandler {

public :

	// execute packet's handler
	static void execute(GCUnburrowFail* pPacket, Player* pPlayer) throw(Error);

};

#endif
