//----------------------------------------------------------------------
// 
// Filename    : GCAddSlayerCorpse.h 
// Written By  : Reiot
// 
//----------------------------------------------------------------------

#ifndef __GC_ADD_SLAYER_CORPSE_H__
#define __GC_ADD_SLAYER_CORPSE_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"
#include "PCSlayerInfo3.h"

//----------------------------------------------------------------------
//
// class GCAddSlayerCorpse;
//
// 슬레이어의 시체 정보를 담아서 클라이언트에 전송한다.
//
//----------------------------------------------------------------------

class GCAddSlayerCorpse : public Packet {

public :

	// constructor
	GCAddSlayerCorpse() throw() { m_TreasureCount = 0; }
	GCAddSlayerCorpse(const PCSlayerInfo3 & slayerInfo) throw() : m_SlayerInfo(slayerInfo) {}


public :

    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) ;
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID()  { return PACKET_GC_ADD_SLAYER_CORPSE; }
	
	// get packet's body size
	PacketSize_t getPacketSize()  { return m_SlayerInfo.getSize() + szBYTE; }

	// get packet's name
	string getPacketName()  { return "GCAddSlayerCorpse"; }
	
	// get packet's debug string
	string toString() ;


public :

	// get slayer info
	PCSlayerInfo3 & getSlayerInfo() throw() { return m_SlayerInfo; }
	const PCSlayerInfo3 & getSlayerInfo()  { return m_SlayerInfo; }
	void setSlayerInfo(const PCSlayerInfo3 & slayerInfo) throw() { m_SlayerInfo = slayerInfo; }

	// get/set Treasure Count
	BYTE getTreasureCount()  { return m_TreasureCount; }
	void setTreasureCount(BYTE Count) throw() { m_TreasureCount = Count; }

private :
	
	// 슬레이어의 외모 정보
	PCSlayerInfo3 m_SlayerInfo;

	// 보물 숫자
	BYTE m_TreasureCount;

};


//--------------------------------------------------------------------------------
//
// class GCAddSlayerCorpseFactory;
//
// Factory for GCAddSlayerCorpse
//
//--------------------------------------------------------------------------------

class GCAddSlayerCorpseFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket() throw() { return new GCAddSlayerCorpse(); }

	// get packet name
	string getPacketName()  { return "GCAddSlayerCorpse"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_GC_ADD_SLAYER_CORPSE; }

	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static GCAddSlayerCorpsePacketSize 를 정의, 리턴하라.
	PacketSize_t getPacketMaxSize() 
	{ 
		return PCSlayerInfo3::getMaxSize() + szBYTE;
	}

};


//--------------------------------------------------------------------------------
//
// class GCAddSlayerCorpseHandler;
//
//--------------------------------------------------------------------------------

class GCAddSlayerCorpseHandler {

public :

	// execute packet's handler
	static void execute(GCAddSlayerCorpse* pPacket, Player* pPlayer);

};

#endif
