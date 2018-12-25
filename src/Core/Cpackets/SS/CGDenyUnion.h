//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGDenyUnion.h 
// Written By  :
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_DENY_UNION_H__
#define __CG_DENY_UNION_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class CGDenyUnion;
//
//////////////////////////////////////////////////////////////////////

class CGDenyUnion : public Packet
{
public:
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) ;
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID()  { return PACKET_CG_DENY_UNION; }
	
	// get packet's body size
	PacketSize_t getPacketSize()  { return szGuildID; }

	// get packet name
	string getPacketName()  { return "CGDenyUnion"; }

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
// class CGDenyUnionFactory;
//
// Factory for CGDenyUnion
//
//////////////////////////////////////////////////////////////////////

class CGDenyUnionFactory : public PacketFactory {

public:
	
	// constructor
	CGDenyUnionFactory() throw() {}
	
	// destructor
	virtual ~CGDenyUnionFactory() throw() {}

	
public:
	
	// create packet
	Packet* createPacket() throw() { return new CGDenyUnion(); }

	// get packet name
	string getPacketName()  { return "CGDenyUnion"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_CG_DENY_UNION; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize()  { return szGuildID; }
};


//////////////////////////////////////////////////////////////////////
//
// class CGDenyUnionHandler;
//
//////////////////////////////////////////////////////////////////////

class CGDenyUnionHandler {

public:

	// execute packet's handler
	static void execute(CGDenyUnion* pCGDenyUnion, Player* pPlayer);

};

#endif
