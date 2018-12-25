//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCHPRecoveryEndToSelf.h 
// Written By  : Reiot
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_HP_RECOVERY_END_TO_SELF_H__
#define __GC_HP_RECOVERY_END_TO_SELF_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"
#include "EffectInfo.h"


//////////////////////////////////////////////////////////////////////
//
// class GCHPRecoveryEndToSelf;
//
////////////////////////////////////////////////////////////////////

class GCHPRecoveryEndToSelf : public Packet {

public :

	GCHPRecoveryEndToSelf() throw(Error);

	virtual ~GCHPRecoveryEndToSelf() throw(Error);
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) ;
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID()  { return PACKET_GC_HP_RECOVERY_END_TO_SELF; }
	
	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static GCHPRecoveryEndToSelfPacketSize 를 정의, 리턴하라.
	PacketSize_t getPacketSize()  
	{ 
		return szHP; 
	}

	// get packet's name
	string getPacketName()  { return "GCHPRecoveryEndToSelf"; }
	
	// get packet's debug string
	string toString() ;

public :

	// get /set CurrentHP
	HP_t getCurrentHP()  { return m_CurrentHP; }
	void setCurrentHP(HP_t CurrentHP) throw() { m_CurrentHP = CurrentHP; }

private :
	
	// 현재 체력
	HP_t m_CurrentHP;

};


//////////////////////////////////////////////////////////////////////
//
// class GCHPRecoveryEndToSelfFactory;
//
// Factory for GCHPRecoveryEndToSelf
//
//////////////////////////////////////////////////////////////////////

class GCHPRecoveryEndToSelfFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket() throw() { return new GCHPRecoveryEndToSelf(); }

	// get packet name
	string getPacketName()  { return "GCHPRecoveryEndToSelf"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_GC_HP_RECOVERY_END_TO_SELF; }

	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static GCHPRecoveryEndToSelfPacketSize 를 정의, 리턴하라.
	PacketSize_t getPacketMaxSize()  
	{ 
		return szHP; 
	}

};


//////////////////////////////////////////////////////////////////////
//
// class GCHPRecoveryEndToSelfHandler;
//
//////////////////////////////////////////////////////////////////////

class GCHPRecoveryEndToSelfHandler {

public :

	// execute packet's handler
	static void execute(GCHPRecoveryEndToSelf* pPacket, Player* pPlayer) throw(Error);

};

#endif
