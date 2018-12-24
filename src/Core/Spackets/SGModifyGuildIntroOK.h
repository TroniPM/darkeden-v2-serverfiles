//----------------------------------------------------------------------
// 
// Filename    : SGModifyGuildIntroOK.h 
// Written By  : Reiot
// Description : 
// 
//----------------------------------------------------------------------

#ifndef __SG_MODIFY_GUILD_INTRO_OK_H__
#define __SG_MODIFY_GUILD_INTRO_OK_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//----------------------------------------------------------------------
//
// class SGModifyGuildIntroOK;
//
// ���� �߰� �Ǿ����� ���Ӽ����� �˸���.
//
// *CAUTION*
//
//----------------------------------------------------------------------

class SGModifyGuildIntroOK : public Packet {

public:
	
    // Datagram ��ü�������� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream& iStream) throw(ProtocolException, Error);
		    
    // Datagram ��ü�� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream& oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_SG_MODIFY_GUILD_INTRO_OK; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const throw() 
	{ 
		return szGuildID +			// guild ID
			   szBYTE +				// Guild Intro length
			   m_GuildIntro.size();	// Guild Intro
	}

	// get packet name
	string getPacketName() const throw() { return "SGModifyGuildIntroOK"; }
	
	// get packet's debug string
	string toString() const throw();

public:

	// get/set guildID
	GuildID_t getGuildID() const throw() { return m_GuildID; }
	void setGuildID( GuildID_t guildID ) throw() { m_GuildID = guildID; }

	// get/set guild intro
	const string& getGuildIntro() const throw() { return m_GuildIntro; }
	void setGuildIntro( const string& intro ) throw() { m_GuildIntro = intro; }

private :

	// GuildID
	GuildID_t m_GuildID;

	// Guild Intro
	string m_GuildIntro;

};


//////////////////////////////////////////////////////////////////////
//
// class SGModifyGuildIntroOKFactory;
//
// Factory for SGModifyGuildIntroOK
//
//////////////////////////////////////////////////////////////////////

class SGModifyGuildIntroOKFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket() throw() { return new SGModifyGuildIntroOK(); }

	// get packet name
	string getPacketName() const throw() { return "SGModifyGuildIntroOK"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_SG_MODIFY_GUILD_INTRO_OK; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static LGIncomingConnectionPacketMaxSize �� ����, �����϶�.
	PacketSize_t getPacketMaxSize() const throw() 
	{ 
		return szGuildID +				// guild ID
			   szBYTE +					// Guild Intro length
			   255;  					// Guild Intro max length
	}

};


//////////////////////////////////////////////////////////////////////
//
// class LGIncomingConnectionHandler;
//
//////////////////////////////////////////////////////////////////////

class SGModifyGuildIntroOKHandler {
	
public:

	// execute packet's handler
	static void execute(SGModifyGuildIntroOK* pPacket) throw(ProtocolException, Error);

};

#endif
