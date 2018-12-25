//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCDisconnect.h 
// Written By  : Reiot
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_DISCONNECT_H__
#define __GC_DISCONNECT_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class GCDisconnect;
//
//////////////////////////////////////////////////////////////////////

class GCDisconnect : public Packet {

public :
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) ;
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID()  { return PACKET_GC_DISCONNECT; }
	
	// get packet's body size
	PacketSize_t getPacketSize()  { return szBYTE + m_Message.size(); }

	// get packet name
	string getPacketName()  { return "GCDisconnect"; }
	
	// get packet's debug string
	string toString() ;

	// get/set chatting message
	string getMessage()  { return m_Message; }
	void setMessage(const string & msg) throw() { m_Message = msg; }

private :
	
	// chatting message
	string m_Message;
	
};


//////////////////////////////////////////////////////////////////////
//
// class GCDisconnectFactory;
//
// Factory for GCDisconnect
//
//////////////////////////////////////////////////////////////////////

class GCDisconnectFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket() throw() { return new GCDisconnect(); }

	// get packet name
	string getPacketName()  { return "GCDisconnect"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_GC_DISCONNECT; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCDisconnectPacketMaxSize �� ����, �����϶�.
	PacketSize_t getPacketMaxSize()  { return szBYTE + 128 ; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCDisconnectHandler;
//
//////////////////////////////////////////////////////////////////////

class GCDisconnectHandler {
	
public :
	
	// execute packet's handler
	static void execute(GCDisconnect* pPacket, Player* pPlayer) ;

};

#endif
