//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCUntransformFail.h 
// Written By  : crazydog
// Description :
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_UNTRANSFORM_FAIL_H__
#define __GC_UNTRANSFORM_FAIL_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class GCUntransformFail;
//
//////////////////////////////////////////////////////////////////////

class GCUntransformFail : public Packet {

public :

	// constructor
	GCUntransformFail() throw() {}
	

public :

    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_GC_UNTRANSFORM_FAIL; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const throw() { return 0; }
	
	// get packet's name
	string getPacketName() const throw() { return "GCUntransformFail"; }
	
	// get packet's debug string
	string toString() const throw();
	

public :


private : 


};


//////////////////////////////////////////////////////////////////////
//
// class  GCUntransformFailFactory;
//
// Factory for  GCUntransformFail
//
//////////////////////////////////////////////////////////////////////

class  GCUntransformFailFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket() throw() { return new GCUntransformFail(); }

	// get packet name
	string getPacketName() const throw() { return "GCUntransformFail"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_UNTRANSFORM_FAIL; }

	// get packet's max body size
	PacketSize_t getPacketMaxSize() const throw() { return 0; }
	
};


//////////////////////////////////////////////////////////////////////
//
// class  GCUntransformFailHandler;
//
//////////////////////////////////////////////////////////////////////

class  GCUntransformFailHandler {

public :

	// execute packet's handler
	static void execute(GCUntransformFail* pPacket, Player* pPlayer) throw(Error);

};

#endif
