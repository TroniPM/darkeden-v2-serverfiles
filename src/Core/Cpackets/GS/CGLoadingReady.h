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
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_CG_LOADING_READY; }
	
	// get packet body size
	// *OPTIMIZATION HINT*
	// const static CGLoadingReadyPacketSize �� ����, �����϶�.
	PacketSize_t getPacketSize() const throw() { return szBYTE; }
	
	// get packet's name
	string getPacketName() const throw() { return "CGLoadingReady"; }
	
	// get packet's debug string
	string toString() const throw() { return "CGLoadingReady"; }

public:
	BYTE getType() const throw()  { return m_Type; }
	void setType(BYTE Type) throw() { m_Type = Type; }

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
	Packet* createPacket() throw() { return new CGLoadingReady(); }

	// get packet name
	string getPacketName() const throw() { return "CGLoadingReady"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_CG_LOADING_READY; }

	// get packet's max body size
	PacketSize_t getPacketMaxSize() const throw() { return szBYTE; }
	
};


//////////////////////////////////////////////////////////////////////
//
// class CGLoadingReadyHandler;
//
//////////////////////////////////////////////////////////////////////

class CGLoadingReadyHandler {

public:

	// execute packet's handler
	static void execute(CGLoadingReady* pPacket, Player* pPlayer) throw(ProtocolException, Error);

};

#endif
