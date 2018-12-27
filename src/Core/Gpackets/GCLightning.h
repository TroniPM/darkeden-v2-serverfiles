//--------------------------------------------------------------------------------
// 
// Filename    : GCLightning.h 
// Written By  : reiot
// 
//--------------------------------------------------------------------------------

#ifndef __GC_LIGHTNING_H__
#define __GC_LIGHTNING_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////
//
// class GCLightning;
//
// ������ ���� ���, �������� �� ���� ��� Ŭ���̾�Ʈ�鿡�� �����ϴ� ��Ŷ�̴�.
// 
//
//////////////////////////////////////////////////////////////////////

class GCLightning : public Packet {

public :
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) ;
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID()  { return PACKET_GC_LIGHTNING; }
	
	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static GCLightningPacketSize �� ����, �����϶�.
	PacketSize_t getPacketSize()  { return szBYTE; }

	// get packet's name
	string getPacketName()  { return "GCLightning"; }
	
	// get packet's debug string
	string toString() ;

public :

	// get/set delay
	BYTE getDelay()  { return m_Delay; }
	void setDelay(BYTE delay)  { m_Delay = delay; }


private :

	// ������ ģ ��, õ���� �� �������� �����̽ð�
	// 1 -> 0.1��
	BYTE m_Delay;

};


//////////////////////////////////////////////////////////////////////
//
// class GCLightningFactory;
//
// Factory for GCLightning
//
//////////////////////////////////////////////////////////////////////

class GCLightningFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket()  { return new GCLightning(); }

	// get packet name
	string getPacketName()  { return "GCLightning"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_GC_LIGHTNING; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCLightningPacketSize �� ����, �����϶�.
	PacketSize_t getPacketMaxSize()  { return szBYTE; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCLightningHandler;
//
//////////////////////////////////////////////////////////////////////

class GCLightningHandler {

public :

	// execute packet's handler
	static void execute(GCLightning* pPacket, Player* pPlayer) ;

};

#endif
