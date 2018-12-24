//////////////////////////////////////////////////////////////////////
// 
// Filename    : CLGetPCList.h 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CL_GET_PC_LIST_H__
#define __CL_GET_PC_LIST_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class CLGetPCList;
//
//////////////////////////////////////////////////////////////////////

class CLGetPCList : public Packet {

public:
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_CL_GET_PC_LIST; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const throw() { return 0; }

	// get packet name
	string getPacketName() const throw() { return "CLGetPCList"; }

	// get packet's debug string
	string toString() const throw() { return "CLGetPCList"; }

private :

};


//////////////////////////////////////////////////////////////////////
//
// class CLGetPCListFactory;
//
// Factory for CLGetPCList
//
//////////////////////////////////////////////////////////////////////

class CLGetPCListFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket() throw() { return new CLGetPCList(); }

	// get packet name
	string getPacketName() const throw() { return "CLGetPCList"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_CL_GET_PC_LIST; }

	// get packet's max body size
	PacketSize_t getPacketMaxSize() const throw() { return 0; }

};


//////////////////////////////////////////////////////////////////////
//
// class CLGetPCListHandler;
//
//////////////////////////////////////////////////////////////////////

class CLGetPCListHandler {

public:

	// execute packet's handler
	static void execute(CLGetPCList* pPacket, Player* player) throw(ProtocolException, Error);

};

#endif
