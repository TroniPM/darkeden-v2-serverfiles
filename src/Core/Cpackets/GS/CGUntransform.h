//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGUntransform.h 
// Written By  : crazydog
// Description : ���㳪 ���뿡�� ����������� ���ƿ��������..
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_UNTRANSFORM_H__
#define __CG_UNTRANSFORM_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////
//
// class CGUntransform;
//
//////////////////////////////////////////////////////////////////////

class CGUntransform : public Packet {

public:
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) ;
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID()  { return PACKET_CG_UNTRANSFORM; }
	
	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static CGUntransformPacketSize �� �����ؼ� �����϶�.
	PacketSize_t getPacketSize()  { return 0; }

	// get packet name
	string getPacketName()  { return "CGUntransform"; }
	
	// get packet's debug string
	string toString() ;
};


//////////////////////////////////////////////////////////////////////
//
// class CGUntransformFactory;
//
// Factory for CGUntransform
//
//////////////////////////////////////////////////////////////////////

class CGUntransformFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket() throw() { return new CGUntransform(); }

	// get packet name
	string getPacketName()  { return "CGUntransform"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_CG_UNTRANSFORM; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static CGUntransformPacketSize �� �����ؼ� �����϶�.
	PacketSize_t getPacketMaxSize()  { return 0; }
	

};


//////////////////////////////////////////////////////////////////////
//
// class CGUntransformHandler;
//
//////////////////////////////////////////////////////////////////////

class CGUntransformHandler {
	
public:

	// execute packet's handler
	static void execute(CGUntransform* pPacket, Player* player) ;
};

#endif
