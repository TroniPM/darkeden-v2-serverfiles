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
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID()  { return PACKET_GC_CHANGE_DARK_LIGHT; }
	
	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static GCChangeDarkLightPacketSize �� ����, �����϶�.
	PacketSize_t getPacketSize()  { return szDarkLevel + szLightLevel; }

	// get packet's name
	string getPacketName()  { return "GCChangeDarkLight"; }
	
	// get packet's debug string
	string toString() ;

public :

	// get/set dark level
	DarkLevel_t getDarkLevel()  { return m_DarkLevel; }
	void setDarkLevel(DarkLevel_t darkLevel) throw() { m_DarkLevel = darkLevel; }

	// get/set light level
	LightLevel_t getLightLevel()  { return m_LightLevel; }
	void setLightLevel(LightLevel_t lightLevel) throw() { m_LightLevel = lightLevel; }


public :

	// ���� ��ӱ�(0 - 15)
	DarkLevel_t m_DarkLevel;

	// ���� ���� ũ��(1 - 13)
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
	Packet* createPacket() throw() { return new GCChangeDarkLight(); }

	// get packet name
	string getPacketName()  { return "GCChangeDarkLight"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_GC_CHANGE_DARK_LIGHT; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCChangeDarkLightPacketSize �� ����, �����϶�.
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
	static void execute(GCChangeDarkLight* pPacket, Player* pPlayer) throw(ProtocolException, Error);

};

#endif
