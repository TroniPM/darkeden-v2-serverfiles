//////////////////////////////////////////////////////////////////////////////
// Filename    : LCCreatePCError.h 
// Written By  : Reiot
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __LC_CREATE_PC_ERROR_H__
#define __LC_CREATE_PC_ERROR_H__

#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class LCCreatePCError;
//
// PC Creation 이 실패했을 경우, 로그인 서버는 클라이언트에게 이 패킷을
// 보낸다.
//////////////////////////////////////////////////////////////////////////////

class LCCreatePCError : public Packet 
{
public:
    void read(SocketInputStream & iStream) ;
    void write(SocketOutputStream & oStream) ;
	void execute(Player* pPlayer) ;
	PacketID_t getPacketID()  { return PACKET_LC_CREATE_PC_ERROR; }
	PacketSize_t getPacketSize()  { return szBYTE; }
	string getPacketName()  { return "LCCreatePCError"; }
	string toString() ;

public:
	BYTE getErrorID()  { return m_ErrorID; }
	void setErrorID(BYTE ErrorID) throw() { m_ErrorID = ErrorID; }

private: 
	BYTE m_ErrorID;
};

//////////////////////////////////////////////////////////////////////////////
// class LCCreatePCErrorFactory;
//////////////////////////////////////////////////////////////////////////////

class LCCreatePCErrorFactory : public PacketFactory 
{
public:
	
	// create packet
	Packet* createPacket() throw() { return new LCCreatePCError(); }

	// get packet name
	string getPacketName()  { return "LCCreatePCError"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_LC_CREATE_PC_ERROR; }

	// get packet's max body size
	PacketSize_t getPacketMaxSize()  { return szBYTE; }
	
};


//////////////////////////////////////////////////////////////////////
//
// class LCCreatePCErrorHandler;
//
//////////////////////////////////////////////////////////////////////

class LCCreatePCErrorHandler {

public:

	// execute packet's handler
	static void execute(LCCreatePCError* pPacket, Player* pPlayer) ;

};

#endif
