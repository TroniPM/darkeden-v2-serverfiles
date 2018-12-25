//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGJoinGuild.h 
// Written By  :
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_JOIN_GUILD_H__
#define __CG_JOIN_GUILD_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class CGJoinGuild;
//
//////////////////////////////////////////////////////////////////////

class CGJoinGuild : public Packet
{
public:
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) ;
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID()  { return PACKET_CG_JOIN_GUILD; }
	
	// get packet's body size
	PacketSize_t getPacketSize()  { return szGuildID + szGuildMemberRank + szBYTE + m_GuildMemberIntro.size(); }

	// get packet name
	string getPacketName()  { return "CGJoinGuild"; }

	// get packet's debug string
	string toString() ;

	// get/set Guild ID
	GuildID_t getGuildID()  { return m_GuildID; }
	void setGuildID( GuildID_t GuildID ) throw() { m_GuildID = GuildID; }

	// get/set Guild Member Rank
	GuildMemberRank_t getGuildMemberRank()  { return m_GuildMemberRank; }
	void setGuildMemberRank( GuildMemberRank_t GuildMemberRank ) throw() { m_GuildMemberRank = GuildMemberRank; }

	// get/set Guild Member Intro
	string getGuildMemberIntro()  { return m_GuildMemberIntro; }
	void setGuildMemberIntro( const string& GuildMemberIntro ) throw() { m_GuildMemberIntro = GuildMemberIntro; }


private :

	// Guild ID
	GuildID_t m_GuildID;

	// Guild Member Rank
	GuildMemberRank_t m_GuildMemberRank;

	// Guild Member Intro
	string m_GuildMemberIntro;
	
};


//////////////////////////////////////////////////////////////////////
//
// class CGJoinGuildFactory;
//
// Factory for CGJoinGuild
//
//////////////////////////////////////////////////////////////////////

class CGJoinGuildFactory : public PacketFactory {

public:
	
	// constructor
	CGJoinGuildFactory() throw() {}
	
	// destructor
	virtual ~CGJoinGuildFactory() throw() {}

	
public:
	
	// create packet
	Packet* createPacket() throw() { return new CGJoinGuild(); }

	// get packet name
	string getPacketName()  { return "CGJoinGuild"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_CG_JOIN_GUILD; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize()  { return szGuildID + szGuildMemberRank + szBYTE + 256; }
};


//////////////////////////////////////////////////////////////////////
//
// class CGJoinGuildHandler;
//
//////////////////////////////////////////////////////////////////////

class CGJoinGuildHandler {

public:

	// execute packet's handler
	static void execute(CGJoinGuild* pCGJoinGuild, Player* pPlayer);

};

#endif
