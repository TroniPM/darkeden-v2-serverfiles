//--------------------------------------------------------------------------------
// 
// Filename    : CUEndUpdate.h 
// Written By  : Reiot
// 
//--------------------------------------------------------------------------------

#ifndef __CU_END_UPDATE_H__
#define __CU_END_UPDATE_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//--------------------------------------------------------------------------------
//
// class CUEndUpdate;
//
//
//--------------------------------------------------------------------------------

class CUEndUpdate : public Packet {

public :
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read ( SocketInputStream & iStream ) ;

	// 소켓으로부터 직접 데이타를 읽어서 패킷을 초기화한다.
    void read ( Socket * pSocket ) ;
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write ( SocketOutputStream & oStream ) ;

	// execute packet's handler
	void execute ( Player * pPlayer ) ;

	// get packet id
	PacketID_t getPacketID ()  { return PACKET_CU_END_UPDATE; }
	
	// get packet's body size
	PacketSize_t getPacketSize ()  { return 0; }

	//
	static PacketSize_t getPacketMaxSize ()  { return 0; }

	// get packet name
	string getPacketName ()  { return "CUEndUpdate"; }
	
	// get packet's debug string
	string toString () ;

};


//--------------------------------------------------------------------------------
//
// class CUEndUpdateFactory;
//
// Factory for CUEndUpdate
//
//--------------------------------------------------------------------------------

class CUEndUpdateFactory : public PacketFactory {

public :
	
	// create packet
	Packet * createPacket ()  { return new CUEndUpdate(); }

	// get packet name
	string getPacketName ()  { return "CUEndUpdate"; }
	
	// get packet id
	PacketID_t getPacketID ()  { return Packet::PACKET_CU_END_UPDATE; }

	// get packet's max body size
	PacketSize_t getPacketMaxSize ()  { return 0; }

};


//--------------------------------------------------------------------------------
//
// class CUEndUpdateHandler;
//
//--------------------------------------------------------------------------------

class CUEndUpdateHandler {

public :

	// execute packet's handler
	static void execute ( CUEndUpdate * pPacket , Player * pPlayer ) ;

};

#endif
