//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGModifyGuildIntro.h 
// Written By  :
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_MODIFY_GUILD_INTRO_H__
#define __CG_MODIFY_GUILD_INTRO_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class CGModifyGuildIntro;
//
//////////////////////////////////////////////////////////////////////

class CGModifyGuildIntro : public Packet
{
public:
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) ;
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID()  { return PACKET_CG_MODIFY_GUILD_INTRO; }
	
	// get packet's body size
	PacketSize_t getPacketSize() 
	{ 
		return szGuildID + szBYTE + m_GuildIntro.size();
	}

	// get packet name
	string getPacketName()  { return "CGModifyGuildIntro"; }

	// get packet's debug string
	string toString() ;

	// get/set GuildID
	GuildID_t getGuildID()  { return m_GuildID; }
	void setGuildID( GuildID_t guildID ) throw() { m_GuildID = guildID; }

	// get/set intro
	const string& getGuildIntro()  { return m_GuildIntro; }
	void setGuildIntro( const string& intro ) throw() { m_GuildIntro = intro; }

private :

	// GuildID
	GuildID_t m_GuildID;

	// Guild Intro
	string m_GuildIntro;

};


//////////////////////////////////////////////////////////////////////
//
// class CGModifyGuildIntroFactory;
//
// Factory for CGModifyGuildIntro
//
//////////////////////////////////////////////////////////////////////

class CGModifyGuildIntroFactory : public PacketFactory {

public:
	
	// constructor
	CGModifyGuildIntroFactory() throw() {}
	
	// destructor
	virtual ~CGModifyGuildIntroFactory() throw() {}

	
public:
	
	// create packet
	Packet* createPacket() throw() { return new CGModifyGuildIntro(); }

	// get packet name
	string getPacketName()  { return "CGModifyGuildIntro"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_CG_MODIFY_GUILD_INTRO; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize()  { return szGuildID + szBYTE + 255; }
};


//////////////////////////////////////////////////////////////////////
//
// class CGModifyGuildIntroHandler;
//
//////////////////////////////////////////////////////////////////////

class CGModifyGuildIntroHandler {

public:

	// execute packet's handler
	static void execute(CGModifyGuildIntro* pCGModifyGuildIntro, Player* pPlayer);

};

#endif
