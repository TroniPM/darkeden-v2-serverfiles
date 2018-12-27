//----------------------------------------------------------------------
// 
// Filename    : SGModifyGuildOK.h 
// Written By  : Reiot
// Description : 
// 
//----------------------------------------------------------------------

#ifndef __SG_MODIFY_GUILD_OK_H__
#define __SG_MODIFY_GUILD_OK_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//----------------------------------------------------------------------
//
// class SGModifyGuildOK;
//
// ���� �߰� �Ǿ����� ���Ӽ����� �˸���.
//
// *CAUTION*
//
//----------------------------------------------------------------------

class SGModifyGuildOK : public Packet {

public:
	
    // Datagram ��ü�������� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream& iStream) ;
		    
    // Datagram ��ü�� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream& oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID()  { return PACKET_SG_MODIFY_GUILD_OK; }
	
	// get packet's body size
	PacketSize_t getPacketSize()  
	{ 
		return szGuildID +  				// guild ID
			   szGuildState;				// guild state
	}

	// get packet name
	string getPacketName()  { return "SGModifyGuildOK"; }
	
	// get packet's debug string
	string toString() ;

public:

	// get/set guildID
	GuildID_t getGuildID()  { return m_GuildID; }
	void setGuildID( GuildID_t guildID )  { m_GuildID = guildID; }

	// get/set GuildState
	GuildState_t getGuildState()  { return m_GuildState; }
	void setGuildState( GuildState_t guildState )  { m_GuildState = guildState; }

private :

	// GuildID
	GuildID_t m_GuildID;

	// Guild State
	GuildState_t m_GuildState;

};


//////////////////////////////////////////////////////////////////////
//
// class SGModifyGuildOKFactory;
//
// Factory for SGModifyGuildOK
//
//////////////////////////////////////////////////////////////////////

class SGModifyGuildOKFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket()  { return new SGModifyGuildOK(); }

	// get packet name
	string getPacketName()  { return "SGModifyGuildOK"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_SG_MODIFY_GUILD_OK; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static LGIncomingConnectionPacketMaxSize �� ����, �����϶�.
	PacketSize_t getPacketMaxSize()  
	{ 
		return szGuildID +				// guild ID
			   szGuildState;
	}

};


//////////////////////////////////////////////////////////////////////
//
// class LGIncomingConnectionHandler;
//
//////////////////////////////////////////////////////////////////////

class SGModifyGuildOKHandler {
	
public:

	// execute packet's handler
	static void execute(SGModifyGuildOK* pPacket) ;

};

#endif
