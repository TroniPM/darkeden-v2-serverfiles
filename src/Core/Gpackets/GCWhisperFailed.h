//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCWhisperFailed.h 
// Written By  : elca@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_WHISPER_FAILED_H__
#define __GC_WHISPER_FAILED_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class GCWhisperFailed;
//
// 게임 서버에서 특정 사용자가 움직였다는 정보를 클라이언트로 보내줄 
// 때 사용하는 패킷 객체이다.(CreatureID,X,Y,DIR) 을 포함한다.
//
//////////////////////////////////////////////////////////////////////

class GCWhisperFailed : public Packet {

public :
	
	// constructor
	GCWhisperFailed() ;
	
	// destructor
	~GCWhisperFailed() ;

	
public :
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) ;
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID()  { return PACKET_GC_WHISPER_FAILED; }
	
	// get packet's body size
	// 최적화시, 미리 계산된 정수를 사용한다.
	PacketSize_t getPacketSize()  { return 0; }

	// get packet's name
	string getPacketName()  { return "GCWhisperFailed"; }
	
	// get packet's debug string
	string toString() ;

private :

};

//////////////////////////////////////////////////////////////////////
//
// class GCWhisperFailedFactory;
//
// Factory for GCWhisperFailed
//
//////////////////////////////////////////////////////////////////////

class GCWhisperFailedFactory : public PacketFactory {

public :
	
	// constructor
	GCWhisperFailedFactory()  {}
	
	// destructor
	virtual ~GCWhisperFailedFactory()  {}

	
public :
	
	// create packet
	Packet* createPacket()  { return new GCWhisperFailed(); }

	// get packet name
	string getPacketName()  { return "GCWhisperFailed"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_GC_WHISPER_FAILED; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize()  { return 0; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCWhisperFailedHandler;
//
//////////////////////////////////////////////////////////////////////

class GCWhisperFailedHandler {

public :

	// execute packet's handler
	static void execute(GCWhisperFailed* pGCWhisperFailed, Player* pPlayer);

};

#endif
