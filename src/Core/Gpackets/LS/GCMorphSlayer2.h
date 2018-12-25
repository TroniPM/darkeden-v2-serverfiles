//----------------------------------------------------------------------
// 
// Filename    : GCMorphSlayer2.h 
// Written By  : crazydog
// 
//----------------------------------------------------------------------

#ifndef __GC_MORPH_SLAYER2_H__
#define __GC_MORPH_SLAYER2_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"
#include "PCSlayerInfo3.h"
#include "PCVampireInfo3.h"


//----------------------------------------------------------------------
//
// class GCMorphSlayer2;
//
// slayer���� vampire�� �����ϴ� �� ���Ѻ��� �е鿡�� ������.
//----------------------------------------------------------------------

class GCMorphSlayer2 : public Packet {

public :

	// constructor
	GCMorphSlayer2() throw() {}
	GCMorphSlayer2(PCSlayerInfo3 info) throw() : m_SlayerInfo3(info) {}
	
public :

    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID()  { return PACKET_GC_MORPH_SLAYER_2; }
	
	// get packet's body size
	PacketSize_t getPacketSize()  { return m_SlayerInfo3.getSize(); }

	// get packet's name
	string getPacketName()  { return "GCMorphSlayer2"; }
	
	// get packet's debug string
	string toString() ;


public :

	// get/set vampire info
	const PCSlayerInfo3& getSlayerInfo() throw() { return m_SlayerInfo3; }
	void setSlayerInfo(PCSlayerInfo3  info) throw() { m_SlayerInfo3 = info; }


private :
	
	// �ܸ� ����
	PCSlayerInfo3 m_SlayerInfo3;
	
};


//--------------------------------------------------------------------------------
//
// class GCMorphSlayer2Factory;
//
// Factory for GCMorphSlayer2
//
//--------------------------------------------------------------------------------

class GCMorphSlayer2Factory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket() throw() { return new GCMorphSlayer2(); }

	// get packet name
	string getPacketName()  { return "GCMorphSlayer2"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_GC_MORPH_SLAYER_2; }

	// get packet's body size
	PacketSize_t getPacketMaxSize() 
	{ 
		return PCSlayerInfo3::getMaxSize();
	}

};


//--------------------------------------------------------------------------------
//
// class GCMorphSlayer2Handler;
//
//--------------------------------------------------------------------------------

class GCMorphSlayer2Handler {

public :

	// execute packet's handler
	static void execute(GCMorphSlayer2* pPacket, Player* pPlayer) throw(Error);

};

#endif
