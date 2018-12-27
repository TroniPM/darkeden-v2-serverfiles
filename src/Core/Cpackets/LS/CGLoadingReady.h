//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGReady.h 
// Written By  : Reiot
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_LOADING_READY_H__
#define __CG_LOADING_READY_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class CGReady;
//
//////////////////////////////////////////////////////////////////////

class CGLoadingReady : public Packet {

public:

    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) ;
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID()  { return PACKET_CG_LOADING_READY; }
	
	// get packet body size
	// *OPTIMIZATION HINT*
	// const static CGLoadingReadyPacketSize 를 정의, 리턴하라.
	PacketSize_t getPacketSize()  { return szBYTE; }
	
	// get packet's name
	string getPacketName()  { return "CGLoadingReady"; }
	
	// get packet's debug string
	string toString()  { return "CGLoadingReady"; }

public:
	BYTE getType()   { return m_Type; }
	void setType(BYTE Type)  { m_Type = Type; }

private:
	BYTE       m_Type;  // 기술의 종류	
};


//////////////////////////////////////////////////////////////////////
//
// class CGLoadingReadyFactory;
//
// Factory for CGLoadingReady
//
//////////////////////////////////////////////////////////////////////

class CGLoadingReadyFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket()  { return new CGLoadingReady(); }

	// get packet name
	string getPacketName()  { return "CGLoadingReady"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_CG_LOADING_READY; }

	// get packet's max body size
	PacketSize_t getPacketMaxSize()  { return szBYTE; }
	
};


//////////////////////////////////////////////////////////////////////
//
// class CGLoadingReadyHandler;
//
//////////////////////////////////////////////////////////////////////

class CGLoadingReadyHandler {

public:

	// execute packet's handler
	static void execute(CGLoadingReady* pPacket, Player* pPlayer) ;

};

#endif
