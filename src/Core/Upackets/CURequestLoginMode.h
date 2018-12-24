//--------------------------------------------------------------------------------
// 
// Filename    : CURequestLoginMode.h 
// Written By  : Reiot
// 
//--------------------------------------------------------------------------------

#ifndef __CU_REQUEST_LOGIN_MODE_H__
#define __CU_REQUEST_LOGIN_MODE_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//--------------------------------------------------------------------------------
//
// class CURequestLoginMode;
//
// �α��� ��带 �˾Ƴ��� ���� ��Ŷ�̴�
// 
//
//--------------------------------------------------------------------------------

class CURequestLoginMode : public Packet {
public :
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read ( SocketInputStream & iStream ) throw ( ProtocolException , Error );

	// �������κ��� ���� �����͸� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
	void read ( Socket * pSocket ) throw ( ProtocolException , Error );
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write ( SocketOutputStream & oStream ) const throw ( ProtocolException , Error );

	// execute packet's handler
	void execute ( Player * pPlayer ) throw ( ProtocolException , Error );

	// get packet id
	PacketID_t getPacketID () const throw () { return PACKET_CU_REQUEST_LOGIN_MODE; }
	
	// get packet's body size
	PacketSize_t getPacketSize () const throw () { return 0; }
	//
	static PacketSize_t getPacketMaxSize () throw () { return 0; }

	// get packet name
	string getPacketName () const throw () { return "CURequestLoginMode"; }
	
	// get packet's debug string
	string toString () const throw ();
};


//--------------------------------------------------------------------------------
//
// class CURequestLoginModeFactory;
//
// Factory for CURequestLoginMode
//
//--------------------------------------------------------------------------------

class CURequestLoginModeFactory : public PacketFactory {

public :
	
	// create packet
	Packet * createPacket () throw () { return new CURequestLoginMode(); }

	// get packet name
	string getPacketName () const throw () { return "CURequestLoginMode"; }
	
	// get packet id
	PacketID_t getPacketID () const throw () { return Packet::PACKET_CU_REQUEST_LOGIN_MODE; }

	// get packet's max body size
	PacketSize_t getPacketMaxSize () const throw () { return 0; }

};


//--------------------------------------------------------------------------------
//
// class CURequestLoginModeHandler;
//
//--------------------------------------------------------------------------------

class CURequestLoginModeHandler {

public :

	// execute packet's handler
	static void execute ( CURequestLoginMode * pPacket , Player * pPlayer ) throw ( ProtocolException , Error );
};

#endif
