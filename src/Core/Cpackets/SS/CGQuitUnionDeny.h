//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGQuitUnionDeny.h 
// Written By  :
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_QUIT_UNION_DENY_H__
#define __CG_QUIT_UNION_DENY_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class CGQuitUnionDeny;
//
//////////////////////////////////////////////////////////////////////

class CGQuitUnionDeny : public Packet
{
public:
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) ;
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID()  { return PACKET_CG_QUIT_UNION_DENY; }
	
	// get packet's body size
	PacketSize_t getPacketSize()  { return szGuildID; }

	// get packet name
	string getPacketName()  { return "CGQuitUnionDeny"; }

	// get packet's debug string
	string toString() ;

	// get/set GuildID
	GuildID_t getGuildID()  { return m_GuildID; }
	void setGuildID( GuildID_t GuildID ) throw() { m_GuildID = GuildID; }


private :

	// Guild ID
	GuildID_t m_GuildID;
	
};


//////////////////////////////////////////////////////////////////////
//
// class CGQuitUnionDenyFactory;
//
// Factory for CGQuitUnionDeny
//
//////////////////////////////////////////////////////////////////////

class CGQuitUnionDenyFactory : public PacketFactory {

public:
	
	// constructor
	CGQuitUnionDenyFactory() throw() {}
	
	// destructor
	virtual ~CGQuitUnionDenyFactory() throw() {}

	
public:
	
	// create packet
	Packet* createPacket() throw() { return new CGQuitUnionDeny(); }

	// get packet name
	string getPacketName()  { return "CGQuitUnionDeny"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_CG_QUIT_UNION_DENY; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize()  { return szGuildID; }
};


//////////////////////////////////////////////////////////////////////
//
// class CGQuitUnionDenyHandler;
//
//////////////////////////////////////////////////////////////////////

class CGQuitUnionDenyHandler {

public:

	// execute packet's handler
	static void execute(CGQuitUnionDeny* pCGQuitUnionDeny, Player* pPlayer);

};

#endif
