//----------------------------------------------------------------------
// 
// Filename    : GSModifyGuildIntro.h 
// Written By  : 
// Description : 
// 
//----------------------------------------------------------------------

#ifndef __GS_MODIFY_GUILD_INTRO_H__
#define __GS_MODIFY_GUILD_INTRO_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//----------------------------------------------------------------------
//
// class GSModifyGuildIntro;
//
// ���� �߰��� ����� ������ ��û�Ѵ�.
//
// *CAUTION*
//
//----------------------------------------------------------------------

class GSModifyGuildIntro : public Packet {

public:
	
    // Datagram ��ü�������� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream& iStream) throw(ProtocolException, Error);
		    
    // Datagram ��ü�� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream& oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_GS_MODIFY_GUILD_INTRO; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const throw() 
	{ 
		return szGuildID +				// Guild ID
			   szBYTE +					// Guild Intro length
			   m_GuildIntro.size(); 	// Guild Intro
	}

	// get packet name
	string getPacketName() const throw() { return "GSModifyGuildIntro"; }
	
	// get packet's debug string
	string toString() const throw();

public:

	// get/set Guild ID
	GuildID_t getGuildID() const throw() { return m_GuildID; }
	void setGuildID( GuildID_t guildID ) throw() { m_GuildID = guildID; }

	// get/set Guild Intro
	const string& getGuildIntro() const throw() { return m_GuildIntro; }
	void setGuildIntro( const string& intro ) throw() { m_GuildIntro = intro; }

private :

	// Guild ID
	GuildID_t m_GuildID;

	// Guild Intro
	string m_GuildIntro;

};


//////////////////////////////////////////////////////////////////////
//
// class GSModifyGuildIntroFactory;
//
// Factory for GSModifyGuildIntro
//
//////////////////////////////////////////////////////////////////////

class GSModifyGuildIntroFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket() throw() { return new GSModifyGuildIntro(); }

	// get packet name
	string getPacketName() const throw() { return "GSModifyGuildIntro"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GS_MODIFY_GUILD_INTRO; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static LGIncomingConnectionPacketMaxSize �� ����, �����϶�.
	PacketSize_t getPacketMaxSize() const throw() 
	{ 
		return szGuildID +			// guild ID
			   szBYTE +				// Guild Intro length
			   255;					// Guild Intro max length
	}
};


//////////////////////////////////////////////////////////////////////
//
// class LGIncomingConnectionHandler;
//
//////////////////////////////////////////////////////////////////////

class GSModifyGuildIntroHandler {
	
public:

	// execute packet's handler
	static void execute(GSModifyGuildIntro* pPacket, Player* pPlayer) throw(ProtocolException, Error);

};

#endif
