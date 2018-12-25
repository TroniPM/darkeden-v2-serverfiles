//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGRequestUnion.h 
// Written By  :
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_REQUEST_UNION_H__
#define __CG_REQUEST_UNION_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class CGRequestUnion;
//
//////////////////////////////////////////////////////////////////////

class CGRequestUnion : public Packet
{
public:
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID()  { return PACKET_CG_REQUEST_UNION; }
	
	// get packet's body size
	PacketSize_t getPacketSize()  { return szGuildID; }

	// get packet name
	string getPacketName()  { return "CGRequestUnion"; }

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
// class CGRequestUnionFactory;
//
// Factory for CGRequestUnion
//
//////////////////////////////////////////////////////////////////////

class CGRequestUnionFactory : public PacketFactory {

public:
	
	// constructor
	CGRequestUnionFactory() throw() {}
	
	// destructor
	virtual ~CGRequestUnionFactory() throw() {}

	
public:
	
	// create packet
	Packet* createPacket() throw() { return new CGRequestUnion(); }

	// get packet name
	string getPacketName()  { return "CGRequestUnion"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_CG_REQUEST_UNION; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize()  { return szGuildID; }
};


//////////////////////////////////////////////////////////////////////
//
// class CGRequestUnionHandler;
//
//////////////////////////////////////////////////////////////////////

class CGRequestUnionHandler {

public:

	// execute packet's handler
	static void execute(CGRequestUnion* pCGRequestUnion, Player* pPlayer) throw(Error);

};

#endif
