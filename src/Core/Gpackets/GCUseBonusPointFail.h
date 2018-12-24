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

    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_GC_USE_BONUS_POINT_FAIL; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const throw() { return 0; }
	
	// get packet's name
	string getPacketName() const throw() { return "GCUseBonusPointFail"; }
	
	// get packet's debug string
	string toString() const throw();
	

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
	string getPacketName() const throw() { return "GCUseBonusPointFail"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_USE_BONUS_POINT_FAIL; }

	// get packet's max body size
	PacketSize_t getPacketMaxSize() const throw() { return 0; }
	
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
