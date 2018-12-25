//----------------------------------------------------------------------
// 
// Filename    : GSRequestGuildInfo.h 
// Written By  : 
// Description : 
// 
//----------------------------------------------------------------------

#ifndef __GS_REQUEST_GUILD_INFO_H__
#define __GS_REQUEST_GUILD_INFO_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//----------------------------------------------------------------------
//
// class GSRequestGuildInfo;
//
// ���� �߰��� ����� ������ ��û�Ѵ�.
//
// *CAUTION*
//
//----------------------------------------------------------------------

class GSRequestGuildInfo : public Packet {

public:
	
    // Stream ��ü�������� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // Stream ��ü�� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID()  { return PACKET_GS_REQUEST_GUILD_INFO; }
	
	// get packet's body size
	PacketSize_t getPacketSize()  
	{ 
		return 0;
	}

	// get packet name
	string getPacketName()  { return "GSRequestGuildInfo"; }
	
	// get packet's debug string
	string toString()  { return "GSRequestGuildInfo"; }
};


//////////////////////////////////////////////////////////////////////
//
// class GSRequestGuildInfoFactory;
//
// Factory for GSRequestGuildInfo
//
//////////////////////////////////////////////////////////////////////

class GSRequestGuildInfoFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket() throw() { return new GSRequestGuildInfo(); }

	// get packet name
	string getPacketName()  { return "GSRequestGuildInfo"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_GS_REQUEST_GUILD_INFO; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static LGIncomingConnectionPacketMaxSize �� ����, �����϶�.
	PacketSize_t getPacketMaxSize()  
	{ 
		return 0;
	}

};


//////////////////////////////////////////////////////////////////////
//
// class LGIncomingConnectionHandler;
//
//////////////////////////////////////////////////////////////////////

class GSRequestGuildInfoHandler {
	
public:

	// execute packet's handler
	static void execute(GSRequestGuildInfo* pPacket, Player* pPlayer) throw(ProtocolException, Error);

};

#endif
