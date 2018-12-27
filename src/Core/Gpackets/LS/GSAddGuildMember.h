//----------------------------------------------------------------------
// 
// Filename    : GSAddGuildMember.h 
// Written By  : 
// Description : 
// 
//----------------------------------------------------------------------

#ifndef __GS_ADD_GUILD_MEMBER_H__
#define __GS_ADD_GUILD_MEMBER_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//----------------------------------------------------------------------
//
// class GSAddGuildMember;
//
// ��� ��� �߰��� ����� ������ ��û�Ѵ�.
//
// *CAUTION*
//
//----------------------------------------------------------------------

class GSAddGuildMember : public Packet {

public:
	
    // Datagram ��ü�������� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream& iStream) ;
		    
    // Datagram ��ü�� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream& oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID()  { return PACKET_GS_ADD_GUILD_MEMBER; }
	
	// get packet's body size
	PacketSize_t getPacketSize()  
	{ 
		return szGuildID +					// guild id
			   szBYTE +						// member name length
			   m_Name.size() +				// member name
			   szGuildMemberRank +			// Guild Member Rank
			   szBYTE +						// Guild Member Intro length
			   m_GuildMemberIntro.size() +	// Guild Member Intro
			   szServerGroupID;				// server group ID
	}

	// get packet name
	string getPacketName()  { return "GSAddGuildMember"; }
	
	// get packet's debug string
	string toString() ;

public:

	// get/set guild ID
	GuildID_t getGuildID()  { return m_GuildID; }
	void setGuildID( GuildID_t id )  { m_GuildID = id; }

	// get/set name
	const string& getName()  { return m_Name; }
	void setName( const string& name )  { m_Name = name; }

	// get/set Guild Member Rank
	GuildMemberRank_t getGuildMemberRank()  { return m_GuildMemberRank; }
	void setGuildMemberRank( GuildMemberRank_t GuildMemberRank )  { m_GuildMemberRank = GuildMemberRank; }

	// get/set Guild Member Intro
	const string& getGuildMemberIntro()  { return m_GuildMemberIntro; }
	void setGuildMemberIntro( const string& GuildMemberIntro )  { m_GuildMemberIntro = GuildMemberIntro; }

	// get/set server group ID
	ServerGroupID_t getServerGroupID()  { return m_ServerGroupID; }
	void setServerGroupID( ServerGroupID_t serverGroupID )  { m_ServerGroupID = serverGroupID; }

private :

	// Guild ID
	GuildID_t m_GuildID;

	// ��� �̸�
	string m_Name;

	// Guild Member Rank
	GuildMemberRank_t m_GuildMemberRank;

	// Guild Member Intro
	string m_GuildMemberIntro;

	// Server Group ID
	ServerGroupID_t m_ServerGroupID;

};


//////////////////////////////////////////////////////////////////////
//
// class GSAddGuildFactory;
//
// Factory for GSAddGuild
//
//////////////////////////////////////////////////////////////////////

class GSAddGuildMemberFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket()  { return new GSAddGuildMember(); }

	// get packet name
	string getPacketName()  { return "GSAddGuildMember"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_GS_ADD_GUILD_MEMBER; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static LGIncomingConnectionPacketMaxSize �� ����, �����϶�.
	PacketSize_t getPacketMaxSize()  
	{ 
		return szGuildID +					// guild id
			   szBYTE +						// member name length
			   20 +							// member name max size
			   szGuildMemberRank +			// Guild Member Rank
			   szBYTE +						// Guild Member Intro length
			   256 +						// Guild Member Intro max size
			   szServerGroupID;				// server group ID
	}

};


//////////////////////////////////////////////////////////////////////
//
// class LGIncomingConnectionHandler;
//
//////////////////////////////////////////////////////////////////////

class GSAddGuildMemberHandler {
	
public:

	// execute packet's handler
	static void execute(GSAddGuildMember* pPacket, Player* pPlayer) ;

};

#endif
