//--------------------------------------------------------------------------------
// 
// Filename    : UCUpdate.h 
// Written By  : Reiot
// 
//--------------------------------------------------------------------------------

#ifndef __UC_UPDATE_H__
#define __UC_UPDATE_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"
#include "Resource.h"

//--------------------------------------------------------------------------------
//
// class UCUpdate;
//
//--------------------------------------------------------------------------------

class UCUpdate : public Packet {

public :

	// 입력스트림(버퍼)으로부터 데이터를 읽어서 패킷을 초기화한다.
	void read ( SocketInputStream & iStream )  { throw UnsupportedError(__PRETTY_FUNCTION__); }

    // 소켓으로부터 직접 데이터를 읽어서 패킷을 초기화한다.
    void read ( Socket * pSocket ) ;
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write ( SocketOutputStream & oStream )  { throw UnsupportedError(__PRETTY_FUNCTION__); }

    // 소켓으로 직접 패킷의 바이너리 이미지를 보낸다.
    void write ( Socket * pSocket ) ;

	// execute packet's handler
	void execute ( Player * pPlayer ) ;

	// get packet id
	PacketID_t getPacketID ()  { return PACKET_UC_UPDATE; }
	
	// get packet body size
	// *OPTIMIZATION HINT*
	// const static UCUpdatePacketSize 를 정의, 리턴하라.
	PacketSize_t getPacketSize ()  
	{ 
		return m_Resource.getSize();
	}
	
	// 아무리 커도 백메가는 받지 못한다.
	static PacketSize_t getPacketMaxSize ()  
	{ 
		return Resource::getMaxSize();
	}

	// get packet's name
	string getPacketName ()  { return "UCUpdate"; }
	
	// get packet's debug string
	string toString () ;


public :

	// get/set resource
	const Resource & getResource ()  { return m_Resource; }
	void setResource ( const Resource & resource )  { m_Resource = resource; }

private :

	Resource m_Resource;
	
};


//--------------------------------------------------------------------------------
//
// class UCUpdateFactory;
//
// Factory for UCUpdate
//
//--------------------------------------------------------------------------------

class UCUpdateFactory : public PacketFactory {

public :
	
	// create packet
	Packet * createPacket ()  { return new UCUpdate(); }

	// get packet name
	string getPacketName ()  { return "UCUpdate"; }
	
	// get packet id
	PacketID_t getPacketID ()  { return Packet::PACKET_UC_UPDATE; }

	// get packet's max body size
	PacketSize_t getPacketMaxSize ()  { return Resource::getMaxSize(); }
	
};


//--------------------------------------------------------------------------------
//
// class UCUpdateHandler;
//
//--------------------------------------------------------------------------------

class UCUpdateHandler {

public :

	// execute packet's handler
	static void execute ( UCUpdate * pPacket , Player * pPlayer ) ;

};

#endif
