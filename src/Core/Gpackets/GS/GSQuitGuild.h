//----------------------------------------------------------------------
// 
// Filename    : GSQuitGuild.h 
// Written By  : 
// Description : 
// 
//----------------------------------------------------------------------

#ifndef __GS_QUIT_GUILD_H__
#define __GS_QUIT_GUILD_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//----------------------------------------------------------------------
//
// class GSQuitGuild;
//
// ���� �߰��� ����� ������ ��û�Ѵ�.
//
// *CAUTION*
//
//----------------------------------------------------------------------

class GSQuitGuild : public Packet {

public:
	
    // Datagram ��ü�������� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream& iStream) ;
		    
    // Datagram ��ü�� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream& oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID()  { return PACKET_GS_QUIT_GUILD; }
	
	// get packet's body size
	PacketSize_t getPacketSize()  
	{ 
		return szGuildID +				// Guild ID
			   szBYTE +					// name length
			   m_Name.size();			// name 
	}

	// get packet name
	string getPacketName()  { return "GSQuitGuild"; }
	
	// get packet's debug string
	string toString() ;

public:

	// get/set Guild ID
	GuildID_t getGuildID()  { return m_GuildID; }
	void setGuildID( GuildID_t guildID )  { m_GuildID = guildID; }

	// get/set Name
	const string& getName()  { return m_Name; }
	void setName( const string& name )  { m_Name = name; }

private :

	// Guild ID
	GuildID_t m_GuildID;

	// name
	string m_Name;

};


//////////////////////////////////////////////////////////////////////
//
// class GSQuitGuildFactory;
//
// Factory for GSQuitGuild
//
//////////////////////////////////////////////////////////////////////

class GSQuitGuildFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket()  { return new GSQuitGuild(); }

	// get packet name
	string getPacketName()  { return "GSQuitGuild"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_GS_QUIT_GUILD; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static LGIncomingConnectionPacketMaxSize �� ����, �����϶�.
	PacketSize_t getPacketMaxSize()  
	{ 
		return szGuildID +			// guild ID
			   szBYTE +				// name length
			   20;					// name max length
	}

};


//////////////////////////////////////////////////////////////////////
//
// class LGIncomingConnectionHandler;
//
//////////////////////////////////////////////////////////////////////

class GSQuitGuildHandler {
	
public:

	// execute packet's handler
	static void execute(GSQuitGuild* pPacket, Player* pPlayer) ;

};

#endif
