//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCShowGuildJoin.h 
// Written By  : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_SHOW_GUILD_JOIN_H__
#define __GC_SHOW_GUILD_JOIN_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////
//
// class GCShowGuildJoin;
//
// Ŭ���̾�Ʈ�� ��� ��� â�� ��쵵�� �Ѵ�.
//
//////////////////////////////////////////////////////////////////////

class GCShowGuildJoin : public Packet {

public :
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID()  { return PACKET_GC_SHOW_GUILD_JOIN; }
	
	// get packet's body size
	PacketSize_t getPacketSize() 
	{
		return szGuildID +
			   szBYTE +
			   m_GuildName.size() +
			   szGuildMemberRank +
			   szGold;
	}

	// get packet name
	string getPacketName()  { return "GCShowGuildJoin"; }
	
	// get packet's debug string
	string toString() ;

	// get/set Guild ID
	GuildID_t getGuildID()  { return m_GuildID; }
	void setGuildID( GuildID_t GuildID ) throw() { m_GuildID = GuildID; }

	// get/set Guild Name
	const string& getGuildName()  { return m_GuildName; }
	void setGuildName( const string& GuildName ) throw() { m_GuildName = GuildName; }

	// get/set Guild Member Rak
	GuildMemberRank_t getGuildMemberRank()  { return m_GuildMemberRank; }
	void setGuildMemberRank( GuildMemberRank_t GuildMemberRank ) throw() { m_GuildMemberRank = GuildMemberRank; }

	// get/set Join Fee
	Gold_t getJoinFee()  { return m_JoinFee; }
	void setJoinFee( Gold_t JoinFee ) throw() { m_JoinFee = JoinFee; }

private :
	// Guild ID
	GuildID_t m_GuildID;

	// Guild Name
	string m_GuildName;
	
	// Guild Member Rank
	GuildMemberRank_t m_GuildMemberRank;

	// Join Fee
	Gold_t m_JoinFee;
};


//////////////////////////////////////////////////////////////////////
//
// class GCShowGuildJoinFactory;
//
// Factory for GCShowGuildJoin
//
//////////////////////////////////////////////////////////////////////

class GCShowGuildJoinFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket() throw() { return new GCShowGuildJoin(); }

	// get packet name
	string getPacketName()  { return "GCShowGuildJoin"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_GC_SHOW_GUILD_JOIN; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCSystemMessagePacketMaxSize �� ����, �����϶�.
	PacketSize_t getPacketMaxSize() 
	{
		return szGuildID +
			   szBYTE +
			   30 +
			   szGuildMemberRank +
			   szGold;
	}
};


//////////////////////////////////////////////////////////////////////
//
// class GCShowGuildJoin;
//
//////////////////////////////////////////////////////////////////////

class GCShowGuildJoinHandler {
	
public :
	
	// execute packet's handler
	static void execute(GCShowGuildJoin* pPacket, Player* pPlayer) throw(ProtocolException, Error);

};

#endif
