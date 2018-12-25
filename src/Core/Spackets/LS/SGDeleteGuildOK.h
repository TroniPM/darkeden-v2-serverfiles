//----------------------------------------------------------------------
// 
// Filename    : SGDeleteGuildOK.h 
// Written By  : Reiot
// Description : 
// 
//----------------------------------------------------------------------

#ifndef __SG_DELETE_GUILD_OK_H__
#define __SG_DELETE_GUILD_OK_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//----------------------------------------------------------------------
//
// class SGDeleteGuildOK;
//
// ���� �߰� �Ǿ����� ���Ӽ����� �˸���.
//
// *CAUTION*
//
//----------------------------------------------------------------------

class SGDeleteGuildOK : public Packet {

public:
	
    // Datagram ��ü�������� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream& iStream) throw(ProtocolException, Error);
		    
    // Datagram ��ü�� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream& oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID()  { return PACKET_SG_DELETE_GUILD_OK; }
	
	// get packet's body size
	PacketSize_t getPacketSize()  
	{ 
		return szGuildID; 				// guild ID
	}

	// get packet name
	string getPacketName()  { return "SGDeleteGuildOK"; }
	
	// get packet's debug string
	string toString() ;

public:

	// get/set guildID
	GuildID_t getGuildID()  { return m_GuildID; }
	void setGuildID( GuildID_t guildID ) throw() { m_GuildID = guildID; }

private :

	// GuildID
	GuildID_t m_GuildID;

};


//////////////////////////////////////////////////////////////////////
//
// class SGDeleteGuildOKFactory;
//
// Factory for SGDeleteGuildOK
//
//////////////////////////////////////////////////////////////////////

class SGDeleteGuildOKFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket() throw() { return new SGDeleteGuildOK(); }

	// get packet name
	string getPacketName()  { return "SGDeleteGuildOK"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_SG_DELETE_GUILD_OK; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static LGIncomingConnectionPacketMaxSize �� ����, �����϶�.
	PacketSize_t getPacketMaxSize()  
	{ 
		return szGuildID;				// guild ID
	}

};


//////////////////////////////////////////////////////////////////////
//
// class LGIncomingConnectionHandler;
//
//////////////////////////////////////////////////////////////////////

class SGDeleteGuildOKHandler {
	
public:

	// execute packet's handler
	static void execute(SGDeleteGuildOK* pPacket) throw(ProtocolException, Error);

};

#endif
