//----------------------------------------------------------------------
// 
// Filename    : SGExpelGuildMemberOK.h 
// Written By  : Reiot
// Description : 
// 
//----------------------------------------------------------------------

#ifndef __SG_EXPEL_GUILD_MEMBER_OK_H__
#define __SG_EXPEL_GUILD_MEMBER_OK_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//----------------------------------------------------------------------
//
// class SGExpelGuildMemberOK;
//
// ���� �߰� �Ǿ����� ���Ӽ����� �˸���.
//
// *CAUTION*
//
//----------------------------------------------------------------------

class SGExpelGuildMemberOK : public Packet {

public:
	
    // Datagram ��ü�������� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream& iStream) throw(ProtocolException, Error);
		    
    // Datagram ��ü�� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream& oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID()  { return PACKET_SG_EXPEL_GUILD_MEMBER_OK; }
	
	// get packet's body size
	PacketSize_t getPacketSize()  
	{ 
		return szGuildID +			// guild ID
			   szBYTE +				// name length
			   m_Name.size() +		// name size
			   szBYTE +				// sender length
			   m_Sender.size();		// sender size
	}

	// get packet name
	string getPacketName()  { return "SGExpelGuildMemberOK"; }
	
	// get packet's debug string
	string toString() ;

public:

	// get/set guildID
	GuildID_t getGuildID()  { return m_GuildID; }
	void setGuildID( GuildID_t guildID ) throw() { m_GuildID = guildID; }

	// get/set guild name
	const string& getName()  { return m_Name; }
	void setName( const string& name ) throw() { m_Name = name; }

	// get/set sender
	const string& getSender()  { return m_Sender; }
	void setSender( const string& sender ) throw() { m_Sender = sender; }

private :

	// GuildID
	GuildID_t m_GuildID;

	// name
	string m_Name;

	// sender
	string m_Sender;

};


//////////////////////////////////////////////////////////////////////
//
// class SGExpelGuildMemberOKFactory;
//
// Factory for SGExpelGuildMemberOK
//
//////////////////////////////////////////////////////////////////////

class SGExpelGuildMemberOKFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket() throw() { return new SGExpelGuildMemberOK(); }

	// get packet name
	string getPacketName()  { return "SGExpelGuildMemberOK"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_SG_EXPEL_GUILD_MEMBER_OK; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static LGIncomingConnectionPacketMaxSize �� ����, �����϶�.
	PacketSize_t getPacketMaxSize()  
	{ 
		return szGuildID +				// guild ID
			   szBYTE +					// name length
			   20 + 					// name max size
			   szBYTE +					// sender length
			   20;						// sender max size
	}

};


//////////////////////////////////////////////////////////////////////
//
// class LGIncomingConnectionHandler;
//
//////////////////////////////////////////////////////////////////////

class SGExpelGuildMemberOKHandler {
	
public:

	// execute packet's handler
	static void execute(SGExpelGuildMemberOK* pPacket) throw(ProtocolException, Error);

};

#endif
