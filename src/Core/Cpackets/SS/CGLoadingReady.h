//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGReady.h 
// Written By  : Reiot
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_LOADING_READY_H__
#define __CG_LOADING_READY_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class CGReady;
//
//////////////////////////////////////////////////////////////////////

class CGLoadingReady : public Packet {

public:

    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) ;
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID()  { return PACKET_CG_LOADING_READY; }
	
	// get packet body size
	// *OPTIMIZATION HINT*
	// const static CGLoadingReadyPacketSize �� ����, �����϶�.
	PacketSize_t getPacketSize()  { return szBYTE; }
	
	// get packet's name
	string getPacketName()  { return "CGLoadingReady"; }
	
	// get packet's debug string
	string toString()  { return "CGLoadingReady"; }

public:
	BYTE getType()   { return m_Type; }
	void setType(BYTE Type)  { m_Type = Type; }

private:
	BYTE       m_Type;  // ����� ����	
};


//////////////////////////////////////////////////////////////////////
//
// class CGLoadingReadyFactory;
//
// Factory for CGLoadingReady
//
//////////////////////////////////////////////////////////////////////

class CGLoadingReadyFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket()  { return new CGLoadingReady(); }

	// get packet name
	string getPacketName()  { return "CGLoadingReady"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_CG_LOADING_READY; }

	// get packet's max body size
	PacketSize_t getPacketMaxSize()  { return szBYTE; }
	
};


//////////////////////////////////////////////////////////////////////
//
// class CGLoadingReadyHandler;
//
//////////////////////////////////////////////////////////////////////

class CGLoadingReadyHandler {

public:

	// execute packet's handler
	static void execute(CGLoadingReady* pPacket, Player* pPlayer) ;

};

#endif
