//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGQuitUnion.h 
// Written By  :
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_QUIT_UNION_H__
#define __CG_QUIT_UNION_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class CGQuitUnion;
//
//////////////////////////////////////////////////////////////////////

class CGQuitUnion : public Packet
{
public:
	enum{
		QUIT_NORMAL = 0,		// 절차에 따라 신청
		QUIT_QUICK,				// 일방적으로 탈퇴
		QUIT_MAX
	};	

    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) ;
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID()  { return PACKET_CG_QUIT_UNION; }
	
	// get packet's body size
	PacketSize_t getPacketSize()  { return szGuildID+szBYTE; }

	// get packet name
	string getPacketName()  { return "CGQuitUnion"; }

	// get packet's debug string
	string toString() ;

    // get/set GuildID
    GuildID_t getGuildID()  { return m_GuildID; }
    void setGuildID( GuildID_t GuildID ) throw() { m_GuildID = GuildID; }

	// get/set Quit Method
	BYTE	getQuitMethod()	 { return m_Method; }
	void	setQuitMethod( BYTE Method ) throw() { m_Method = Method; }


private :

	// Guild ID
	GuildID_t	m_GuildID;
	BYTE		m_Method;


};


//////////////////////////////////////////////////////////////////////
//
// class CGQuitUnionFactory;
//
// Factory for CGQuitUnion
//
//////////////////////////////////////////////////////////////////////

class CGQuitUnionFactory : public PacketFactory {

public:
	
	// constructor
	CGQuitUnionFactory() throw() {}
	
	// destructor
	virtual ~CGQuitUnionFactory() throw() {}

	
public:
	
	// create packet
	Packet* createPacket() throw() { return new CGQuitUnion(); }

	// get packet name
	string getPacketName()  { return "CGQuitUnion"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_CG_QUIT_UNION; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize()  { return szGuildID + szBYTE; }
};


//////////////////////////////////////////////////////////////////////
//
// class CGQuitUnionHandler;
//
//////////////////////////////////////////////////////////////////////

class CGQuitUnionHandler {

public:

	// execute packet's handler
	static void execute(CGQuitUnion* pCGQuitUnion, Player* pPlayer);

};

#endif
