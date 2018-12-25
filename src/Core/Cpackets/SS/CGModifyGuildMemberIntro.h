//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGModifyGuildMemberIntro.h 
// Written By  :
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_MODIFY_GUILD_MEMBER_INTRO_H__
#define __CG_MODIFY_GUILD_MEMBER_INTRO_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class CGModifyGuildMemberIntro;
//
//////////////////////////////////////////////////////////////////////

class CGModifyGuildMemberIntro : public Packet
{
public:
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID()  { return PACKET_CG_MODIFY_GUILDMEMBER_INTRO; }
	
	// get packet's body size
	PacketSize_t getPacketSize() 
	{ 
		return szGuildID + szBYTE + m_GuildMemberIntro.size();
	}

	// get packet name
	string getPacketName()  { return "CGModifyGuildMemberIntro"; }

	// get packet's debug string
	string toString() ;

	// get/set GuildID
	GuildID_t getGuildID()  { return m_GuildID; }
	void setGuildID( GuildID_t guildID ) throw() { m_GuildID = guildID; }

	// get/set intro
	const string& getGuildMemberIntro()  { return m_GuildMemberIntro; }
	void setGuildMemberIntro( const string& intro ) throw() { m_GuildMemberIntro = intro; }

private :

	// GuildID
	GuildID_t m_GuildID;

	// Guild Member Intro
	string m_GuildMemberIntro;

};


//////////////////////////////////////////////////////////////////////
//
// class CGModifyGuildMemberIntroFactory;
//
// Factory for CGModifyGuildMemberIntro
//
//////////////////////////////////////////////////////////////////////

class CGModifyGuildMemberIntroFactory : public PacketFactory {

public:
	
	// constructor
	CGModifyGuildMemberIntroFactory() throw() {}
	
	// destructor
	virtual ~CGModifyGuildMemberIntroFactory() throw() {}

	
public:
	
	// create packet
	Packet* createPacket() throw() { return new CGModifyGuildMemberIntro(); }

	// get packet name
	string getPacketName()  { return "CGModifyGuildMemberIntro"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_CG_MODIFY_GUILDMEMBER_INTRO; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize()  { return szGuildID + szBYTE + 255; }
};


//////////////////////////////////////////////////////////////////////
//
// class CGModifyGuildMemberIntroHandler;
//
//////////////////////////////////////////////////////////////////////

class CGModifyGuildMemberIntroHandler {

public:

	// execute packet's handler
	static void execute(CGModifyGuildMemberIntro* pCGModifyGuildMemberIntro, Player* pPlayer) throw(Error);

};

#endif
