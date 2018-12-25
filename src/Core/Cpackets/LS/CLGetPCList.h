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
    void read(SocketInputStream & iStream) ;
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID()  { return PACKET_CL_GET_PC_LIST; }
	
	// get packet's body size
	PacketSize_t getPacketSize()  { return 0; }

	// get packet name
	string getPacketName()  { return "CLGetPCList"; }

	// get packet's debug string
	string toString()  { return "CLGetPCList"; }

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
	string getPacketName()  { return "CLGetPCList"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_CL_GET_PC_LIST; }

	// get packet's max body size
	PacketSize_t getPacketMaxSize()  { return 0; }

};


//////////////////////////////////////////////////////////////////////
//
// class CLGetPCListHandler;
//
//////////////////////////////////////////////////////////////////////

class CLGetPCListHandler {

public:

	// execute packet's handler
	static void execute(CLGetPCList* pPacket, Player* player) ;

};

#endif
