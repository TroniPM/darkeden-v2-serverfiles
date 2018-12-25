//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCUseBonusPointFail.h 
// Written By  : crazydog
// Description :
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_USE_BONUS_POINT_FAIL_H__
#define __GC_USE_BONUS_POINT_FAIL_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class GCUseBonusPointFail;
//
//////////////////////////////////////////////////////////////////////

class GCUseBonusPointFail : public Packet {

public :

	// constructor
	GCUseBonusPointFail() throw() {}
	

public :

    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) ;
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID()  { return PACKET_GC_USE_BONUS_POINT_FAIL; }
	
	// get packet's body size
	PacketSize_t getPacketSize()  { return 0; }
	
	// get packet's name
	string getPacketName()  { return "GCUseBonusPointFail"; }
	
	// get packet's debug string
	string toString() ;
	

public :


private : 


};


//////////////////////////////////////////////////////////////////////
//
// class  GCUseBonusPointFailFactory;
//
// Factory for  GCUseBonusPointFail
//
//////////////////////////////////////////////////////////////////////

class  GCUseBonusPointFailFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket() throw() { return new GCUseBonusPointFail(); }

	// get packet name
	string getPacketName()  { return "GCUseBonusPointFail"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_GC_USE_BONUS_POINT_FAIL; }

	// get packet's max body size
	PacketSize_t getPacketMaxSize()  { return 0; }
	
};


//////////////////////////////////////////////////////////////////////
//
// class  GCUseBonusPointFailHandler;
//
//////////////////////////////////////////////////////////////////////

class  GCUseBonusPointFailHandler {

public :

	// execute packet's handler
	static void execute(GCUseBonusPointFail* pPacket, Player* pPlayer) throw(Error);

};

#endif
