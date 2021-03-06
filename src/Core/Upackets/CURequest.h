//--------------------------------------------------------------------------------
// 
// Filename    : CURequest.h 
// Written By  : Reiot
// 
//--------------------------------------------------------------------------------

#ifndef __CU_REQUEST_H__
#define __CU_REQUEST_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"
#include "Resource.h"

//--------------------------------------------------------------------------------
//
// class CURequest;
//
// 
// 
//
//--------------------------------------------------------------------------------

class CURequest : public Packet {

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
	PacketID_t getPacketID ()  { return PACKET_CU_REQUEST; }
	
	// get packet's body size
	PacketSize_t getPacketSize ()  { return m_Resource.getSize(); }

	// 임시 코드당. -_-;
	static PacketSize_t getPacketMaxSize ()  { return Resource::getMaxSize(); }

	// get packet name
	string getPacketName ()  { return "CURequest"; }
	
	// get packet's debug string
	string toString () ;


public :

	// get/set resource
	const Resource & getResource ()  { return m_Resource; }
	void setResource ( const Resource & resource )  { m_Resource = resource; }


private :

	// resource
	Resource m_Resource;	

};


//--------------------------------------------------------------------------------
//
// class CURequestFactory;
//
// Factory for CURequest
//
//--------------------------------------------------------------------------------

class CURequestFactory : public PacketFactory {

public :
	
	// create packet
	Packet * createPacket ()  { return new CURequest(); }

	// get packet name
	string getPacketName ()  { return "CURequest"; }
	
	// get packet id
	PacketID_t getPacketID ()  { return Packet::PACKET_CU_REQUEST; }

	// get packet's max body size
	PacketSize_t getPacketMaxSize ()  
	{ 
		return Resource::getMaxSize(); 
	}

};


//--------------------------------------------------------------------------------
//
// class CURequestHandler;
//
//--------------------------------------------------------------------------------

class CURequestHandler {

public :

	// execute packet's handler
	static void execute ( CURequest * pPacket , Player * pPlayer ) ;

};

#endif
