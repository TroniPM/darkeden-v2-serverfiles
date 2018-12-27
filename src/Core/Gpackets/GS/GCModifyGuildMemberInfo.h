//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCModifyGuildMemberInfo.h 
// Written By  : Reiot
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_MODIFY_GUILD_MEMBER_INFO_H__
#define __GC_MODIFY_GUILD_MEMBER_INFO_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////
//
// class GCModifyGuildMemberInfo;
//
// ���� ������ Ư�� �÷��̾��� ModifyGuildMemberInfo �� �ٸ� �÷��̾�鿡�� ��ε�ĳ��Ʈ
// �� �� �����ϴ� ��Ŷ�̴�. ���ο� ĳ���͸�� ModifyGuildMemberInfo ��Ʈ���� ����Ÿ
// �ʵ�� ������ �ִ�.
//
//////////////////////////////////////////////////////////////////////

class GCModifyGuildMemberInfo : public Packet {

public :
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) ;
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID()  { return PACKET_GC_MODIFY_GUILD_MEMBER_INFO; }
	
	// get packet's body size
	PacketSize_t getPacketSize()  { return szGuildID + szBYTE + m_GuildName.size() + szGuildMemberRank; }

	// get packet name
	string getPacketName()  { return "GCModifyGuildMemberInfo"; }
	
	// get packet's debug string
	string toString() ;

	// get/set Guild ID
	GuildID_t getGuildID()  { return m_GuildID; }
	void setGuildID( GuildID_t guildID )  { m_GuildID = guildID; }

	// get/set Guild Name
	string getGuildName()  { return m_GuildName; }
	void setGuildName(const string& guildName)  { m_GuildName = guildName; }

	// get/set Guild ID
	GuildMemberRank_t getGuildMemberRank()  { return m_GuildMemberRank; }
	void setGuildMemberRank( GuildMemberRank_t guildMemberRank )  { m_GuildMemberRank = guildMemberRank; }

private :

	// Guild ID
	GuildID_t m_GuildID;

	// Guild Name
	string m_GuildName;

	// Guild Member Rank
	GuildMemberRank_t m_GuildMemberRank;
	
};


//////////////////////////////////////////////////////////////////////
//
// class GCModifyGuildMemberInfoFactory;
//
// Factory for GCModifyGuildMemberInfo
//
//////////////////////////////////////////////////////////////////////

class GCModifyGuildMemberInfoFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket()  { return new GCModifyGuildMemberInfo(); }

	// get packet name
	string getPacketName()  { return "GCModifyGuildMemberInfo"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_GC_MODIFY_GUILD_MEMBER_INFO; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCModifyGuildMemberInfoPacketMaxSize �� ����, �����϶�.
	PacketSize_t getPacketMaxSize()  { return szGuildID + szBYTE + 30 + szGuildMemberRank; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCModifyGuildMemberInfoHandler;
//
//////////////////////////////////////////////////////////////////////

class GCModifyGuildMemberInfoHandler {
	
public :
	
	// execute packet's handler
	static void execute(GCModifyGuildMemberInfo* pPacket, Player* pPlayer) ;

};

#endif
