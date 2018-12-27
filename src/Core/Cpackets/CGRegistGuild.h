//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGRegistGuild.h 
// Written By  :
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_REGIST_GUILD_H__
#define __CG_REGIST_GUILD_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class CGRegistGuild;
//
//////////////////////////////////////////////////////////////////////

class CGRegistGuild : public Packet
{
public:
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) ;
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID()  { return PACKET_CG_REGIST_GUILD; }
	
	// get packet's body size
	PacketSize_t getPacketSize()  { return szBYTE + m_GuildName.size() + szBYTE + m_GuildIntro.size(); }

	// get packet name
	string getPacketName()  { return "CGRegistGuild"; }

	// get packet's debug string
	string toString() ;

	// get/set GuildName
	string getGuildName()  { return m_GuildName; }
	void setGuildName( const string& guildName )  { m_GuildName = guildName; }

	// get/set GuildIntro
	string getGuildIntro()  { return m_GuildIntro; }
	void setGuildIntro( const string& guildIntro )  { m_GuildIntro = guildIntro; }


private :

	// Guild Name
	string m_GuildName;

	// Guild Intro
	string m_GuildIntro;
	
};


//////////////////////////////////////////////////////////////////////
//
// class CGRegistGuildFactory;
//
// Factory for CGRegistGuild
//
//////////////////////////////////////////////////////////////////////

class CGRegistGuildFactory : public PacketFactory {

public:
	
	// constructor
	CGRegistGuildFactory()  {}
	
	// destructor
	virtual ~CGRegistGuildFactory()  {}

	
public:
	
	// create packet
	Packet* createPacket()  { return new CGRegistGuild(); }

	// get packet name
	string getPacketName()  { return "CGRegistGuild"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_CG_REGIST_GUILD; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize()  { return szBYTE + 30 + szBYTE + 256; }
};


//////////////////////////////////////////////////////////////////////
//
// class CGRegistGuildHandler;
//
//////////////////////////////////////////////////////////////////////

class CGRegistGuildHandler {

public:

	// execute packet's handler
	static void execute(CGRegistGuild* pCGRegistGuild, Player* pPlayer);

};

#endif
