//----------------------------------------------------------------------
// 
// Filename    : GCMorphVampire2.h 
// Written By  : crazydog
// 
//----------------------------------------------------------------------

#ifndef __GC_MORPH_VAMPIRE2_H__
#define __GC_MORPH_VAMPIRE2_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"
#include "PCSlayerInfo3.h"
#include "PCVampireInfo3.h"


//----------------------------------------------------------------------
//
// class GCMorphVampire2;
//
// slayer���� vampire�� �����ϴ� �� ���Ѻ��� �е鿡�� ������.
//----------------------------------------------------------------------

class GCMorphVampire2 : public Packet {

public :

	// constructor
	GCMorphVampire2() throw() {}
	GCMorphVampire2(PCVampireInfo3 info) throw() : m_VampireInfo3(info) {}
	
public :

    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID()  { return PACKET_GC_MORPH_VAMPIRE_2; }
	
	// get packet's body size
	PacketSize_t getPacketSize()  { return m_VampireInfo3.getSize(); }

	// get packet's name
	string getPacketName()  { return "GCMorphVampire2"; }
	
	// get packet's debug string
	string toString() ;


public :

	// get/set vampire info
	const PCVampireInfo3& getSlayerInfo() throw() { return m_VampireInfo3; }
	void setVampireInfo(PCVampireInfo3 info) throw() { m_VampireInfo3 = info; }


private :
	
	// �ܸ� ����
	PCVampireInfo3 m_VampireInfo3;
	
};


//--------------------------------------------------------------------------------
//
// class GCMorphVampire2Factory;
//
// Factory for GCMorphVampire2
//
//--------------------------------------------------------------------------------

class GCMorphVampire2Factory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket() throw() { return new GCMorphVampire2(); }

	// get packet name
	string getPacketName()  { return "GCMorphVampire2"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_GC_MORPH_VAMPIRE_2; }

	// get packet's body size
	PacketSize_t getPacketMaxSize() 
	{ 
		return PCVampireInfo3::getMaxSize();
	}

};


//--------------------------------------------------------------------------------
//
// class GCMorphVampire2Handler;
//
//--------------------------------------------------------------------------------

class GCMorphVampire2Handler {

public :

	// execute packet's handler
	static void execute(GCMorphVampire2* pPacket, Player* pPlayer) throw(Error);

};

#endif
