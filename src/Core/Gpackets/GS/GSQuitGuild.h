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
    void read(SocketInputStream& iStream) throw(ProtocolException, Error);
		    
    // Datagram ��ü�� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream& oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_GS_QUIT_GUILD; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const throw() 
	{ 
		return szGuildID +				// Guild ID
			   szBYTE +					// name length
			   m_Name.size();			// name 
	}

	// get packet name
	string getPacketName() const throw() { return "GSQuitGuild"; }
	
	// get packet's debug string
	string toString() const throw();

public:

	// get/set Guild ID
	GuildID_t getGuildID() const throw() { return m_GuildID; }
	void setGuildID( GuildID_t guildID ) throw() { m_GuildID = guildID; }

	// get/set Name
	const string& getName() const throw() { return m_Name; }
	void setName( const string& name ) throw() { m_Name = name; }

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
	Packet* createPacket() throw() { return new GSQuitGuild(); }

	// get packet name
	string getPacketName() const throw() { return "GSQuitGuild"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GS_QUIT_GUILD; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static LGIncomingConnectionPacketMaxSize �� ����, �����϶�.
	PacketSize_t getPacketMaxSize() const throw() 
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
	static void execute(GSQuitGuild* pPacket, Player* pPlayer) throw(ProtocolException, Error);

};

#endif
