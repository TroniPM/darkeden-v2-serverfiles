//----------------------------------------------------------------------
// 
// Filename    : GSExpelGuildMember.h 
// Written By  : 
// Description : 
// 
//----------------------------------------------------------------------

#ifndef __GS_EXPEL_GUILD_MEMBER_H__
#define __GS_EXPEL_GUILD_MEMBER__H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//----------------------------------------------------------------------
//
// class GSExpelGuildMember;
//
// ���� �߰��� ����� ������ ��û�Ѵ�.
//
// *CAUTION*
//
//----------------------------------------------------------------------

class GSExpelGuildMember : public Packet {

public:
	
    // Datagram ��ü�������� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream& iStream) ;
		    
    // Datagram ��ü�� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream& oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID()  { return PACKET_GS_EXPEL_GUILD_MEMBER; }
	
	// get packet's body size
	PacketSize_t getPacketSize()  
	{ 
		return szGuildID +				// Guild ID
			   szBYTE +					// name length
			   m_Name.size() +			// name 
			   szBYTE +					// sender length
			   m_Sender.size();			// sender
	}

	// get packet name
	string getPacketName()  { return "GSExpelGuildMember"; }
	
	// get packet's debug string
	string toString() ;

public:

	// get/set Guild ID
	GuildID_t getGuildID()  { return m_GuildID; }
	void setGuildID( GuildID_t guildID )  { m_GuildID = guildID; }

	// get/set Name
	const string& getName()  { return m_Name; }
	void setName( const string& name )  { m_Name = name; }

	// get/set sender
	const string& getSender()  { return m_Sender; }
	void setSender( const string& sender )  { m_Sender = sender; }

private :

	// Guild ID
	GuildID_t m_GuildID;

	// name
	string m_Name;

	// sender
	string m_Sender;

};


//////////////////////////////////////////////////////////////////////
//
// class GSExpelGuildMemberFactory;
//
// Factory for GSExpelGuildMember
//
//////////////////////////////////////////////////////////////////////

class GSExpelGuildMemberFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket()  { return new GSExpelGuildMember(); }

	// get packet name
	string getPacketName()  { return "GSExpelGuildMember"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_GS_EXPEL_GUILD_MEMBER; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static LGIncomingConnectionPacketMaxSize �� ����, �����϶�.
	PacketSize_t getPacketMaxSize()  
	{ 
		return szGuildID +			// guild ID
			   szBYTE +				// name length
			   20 +					// name max length
			   szBYTE +				// sender length
			   20;					// sender max length
	}
};


//////////////////////////////////////////////////////////////////////
//
// class LGIncomingConnectionHandler;
//
//////////////////////////////////////////////////////////////////////

class GSExpelGuildMemberHandler {
	
public:

	// execute packet's handler
	static void execute(GSExpelGuildMember* pPacket, Player* pPlayer) ;

};

#endif
