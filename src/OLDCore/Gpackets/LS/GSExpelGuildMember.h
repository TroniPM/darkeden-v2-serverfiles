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
    void read(SocketInputStream& iStream) throw(ProtocolException, Error);
		    
    // Datagram ��ü�� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream& oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_GS_EXPEL_GUILD_MEMBER; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const throw() 
	{ 
		return szGuildID +				// Guild ID
			   szBYTE +					// name length
			   m_Name.size() +			// name 
			   szBYTE +					// sender length
			   m_Sender.size();			// sender
	}

	// get packet name
	string getPacketName() const throw() { return "GSExpelGuildMember"; }
	
	// get packet's debug string
	string toString() const throw();

public:

	// get/set Guild ID
	GuildID_t getGuildID() const throw() { return m_GuildID; }
	void setGuildID( GuildID_t guildID ) throw() { m_GuildID = guildID; }

	// get/set Name
	const string& getName() const throw() { return m_Name; }
	void setName( const string& name ) throw() { m_Name = name; }

	// get/set sender
	const string& getSender() const throw() { return m_Sender; }
	void setSender( const string& sender ) throw() { m_Sender = sender; }

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
	Packet* createPacket() throw() { return new GSExpelGuildMember(); }

	// get packet name
	string getPacketName() const throw() { return "GSExpelGuildMember"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GS_EXPEL_GUILD_MEMBER; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static LGIncomingConnectionPacketMaxSize �� ����, �����϶�.
	PacketSize_t getPacketMaxSize() const throw() 
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
	static void execute(GSExpelGuildMember* pPacket, Player* pPlayer) throw(ProtocolException, Error);

};

#endif
