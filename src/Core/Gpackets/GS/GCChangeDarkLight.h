//--------------------------------------------------------------------------------
// 
// Filename    : GCChangeDarkLight.h 
// Written By  : reiot
// 
//--------------------------------------------------------------------------------

#ifndef __GC_CHANGE_DARK_LIGHT_H__
#define __GC_CHANGE_DARK_LIGHT_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//--------------------------------------------------------------------------------
//
// class GCChangeDarkLight;
//
//--------------------------------------------------------------------------------

class GCChangeDarkLight : public Packet {

public :
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) ;
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID()  { return PACKET_GC_CHANGE_DARK_LIGHT; }
	
	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static GCChangeDarkLightPacketSize 를 정의, 리턴하라.
	PacketSize_t getPacketSize()  { return szDarkLevel + szLightLevel; }

	// get packet's name
	string getPacketName()  { return "GCChangeDarkLight"; }
	
	// get packet's debug string
	string toString() ;

public :

	// get/set dark level
	DarkLevel_t getDarkLevel()  { return m_DarkLevel; }
	void setDarkLevel(DarkLevel_t darkLevel)  { m_DarkLevel = darkLevel; }

	// get/set light level
	LightLevel_t getLightLevel()  { return m_LightLevel; }
	void setLightLevel(LightLevel_t lightLevel)  { m_LightLevel = lightLevel; }


public :

	// 존의 어둡기(0 - 15)
	DarkLevel_t m_DarkLevel;

	// 존의 빛의 크기(1 - 13)
	LightLevel_t m_LightLevel;

};


//--------------------------------------------------------------------------------
//
// class GCChangeDarkLightFactory;
//
// Factory for GCChangeDarkLight
//
//--------------------------------------------------------------------------------

class GCChangeDarkLightFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket()  { return new GCChangeDarkLight(); }

	// get packet name
	string getPacketName()  { return "GCChangeDarkLight"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_GC_CHANGE_DARK_LIGHT; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCChangeDarkLightPacketSize 를 정의, 리턴하라.
	PacketSize_t getPacketMaxSize()  { return szDarkLevel + szLightLevel; }

};


//--------------------------------------------------------------------------------
//
// class GCChangeDarkLightHandler;
//
//--------------------------------------------------------------------------------

class GCChangeDarkLightHandler {

public :

	// execute packet's handler
	static void execute(GCChangeDarkLight* pPacket, Player* pPlayer) ;

};

#endif
