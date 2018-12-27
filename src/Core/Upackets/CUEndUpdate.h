//--------------------------------------------------------------------------------
// 
// Filename    : CUEndUpdate.h 
// Written By  : Reiot
// 
//--------------------------------------------------------------------------------

#ifndef __CU_END_UPDATE_H__
#define __CU_END_UPDATE_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//--------------------------------------------------------------------------------
//
// class CUEndUpdate;
//
//
//--------------------------------------------------------------------------------

class CUEndUpdate : public Packet {

public :
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read ( SocketInputStream & iStream ) ;

	// �������κ��� ���� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read ( Socket * pSocket ) ;
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write ( SocketOutputStream & oStream ) ;

	// execute packet's handler
	void execute ( Player * pPlayer ) ;

	// get packet id
	PacketID_t getPacketID ()  { return PACKET_CU_END_UPDATE; }
	
	// get packet's body size
	PacketSize_t getPacketSize ()  { return 0; }

	//
	static PacketSize_t getPacketMaxSize ()  { return 0; }

	// get packet name
	string getPacketName ()  { return "CUEndUpdate"; }
	
	// get packet's debug string
	string toString () ;

};


//--------------------------------------------------------------------------------
//
// class CUEndUpdateFactory;
//
// Factory for CUEndUpdate
//
//--------------------------------------------------------------------------------

class CUEndUpdateFactory : public PacketFactory {

public :
	
	// create packet
	Packet * createPacket ()  { return new CUEndUpdate(); }

	// get packet name
	string getPacketName ()  { return "CUEndUpdate"; }
	
	// get packet id
	PacketID_t getPacketID ()  { return Packet::PACKET_CU_END_UPDATE; }

	// get packet's max body size
	PacketSize_t getPacketMaxSize ()  { return 0; }

};


//--------------------------------------------------------------------------------
//
// class CUEndUpdateHandler;
//
//--------------------------------------------------------------------------------

class CUEndUpdateHandler {

public :

	// execute packet's handler
	static void execute ( CUEndUpdate * pPacket , Player * pPlayer ) ;

};

#endif
