//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGModifyGuildMember.h 
// Written By  :
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_MODIFY_GUILD_MEMBER_H__
#define __CG_MODIFY_GUILD_MEMBER_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class CGModifyGuildMember;
//
//////////////////////////////////////////////////////////////////////

class CGModifyGuildMember : public Packet
{
public:
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID()  { return PACKET_CG_MODIFY_GUILD_MEMBER; }
	
	// get packet's body size
	PacketSize_t getPacketSize()  { return szGuildID + szBYTE + m_Name.size() + szGuildMemberRank; }

	// get packet name
	string getPacketName()  { return "CGModifyGuildMember"; }

	// get packet's debug string
	string toString() ;

	// get/set GuildID
	GuildID_t getGuildID()  { return m_GuildID; }
	void setGuildID( GuildID_t guildID ) throw() { m_GuildID = guildID; }

	// get/set name
	const string& getName()  { return m_Name; }
	void setName( const string& name ) throw() { m_Name = name; }

	// get/set Guild Member Rank
	GuildMemberRank_t getGuildMemberRank()  { return m_GuildMemberRank; }
	void setGuildMemberRank( GuildMemberRank_t GuildMemberRank ) throw() { m_GuildMemberRank = GuildMemberRank; }

private :

	// GuildID
	GuildID_t m_GuildID;

	// name
	string m_Name;

	// Guild Member Rank
	GuildMemberRank_t m_GuildMemberRank;

};


//////////////////////////////////////////////////////////////////////
//
// class CGModifyGuildMemberFactory;
//
// Factory for CGModifyGuildMember
//
//////////////////////////////////////////////////////////////////////

class CGModifyGuildMemberFactory : public PacketFactory {

public:
	
	// constructor
	CGModifyGuildMemberFactory() throw() {}
	
	// destructor
	virtual ~CGModifyGuildMemberFactory() throw() {}

	
public:
	
	// create packet
	Packet* createPacket() throw() { return new CGModifyGuildMember(); }

	// get packet name
	string getPacketName()  { return "CGModifyGuildMember"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_CG_MODIFY_GUILD_MEMBER; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize()  { return szGuildID + szBYTE + 20 + szGuildMemberRank; }
};


//////////////////////////////////////////////////////////////////////
//
// class CGModifyGuildMemberHandler;
//
//////////////////////////////////////////////////////////////////////

class CGModifyGuildMemberHandler {

public:

	// execute packet's handler
	static void execute(CGModifyGuildMember* pCGModifyGuildMember, Player* pPlayer) throw(Error);

};

#endif
