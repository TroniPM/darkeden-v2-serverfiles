//--------------------------------------------------------------------------------
// 
// Filename    : CURequest.h 
// Written By  : Reiot
// 
//--------------------------------------------------------------------------------

#ifndef __CU_REQUEST_H__
#define __CU_REQUEST_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"
#include "Resource.h"

//--------------------------------------------------------------------------------
//
// class CURequest;
//
// 
// 
//
//--------------------------------------------------------------------------------

class CURequest : public Packet {

public :
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read ( SocketInputStream & iStream ) throw ( ProtocolException , Error );
		    
	// �������κ��� ���� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read ( Socket * pSocket ) throw ( ProtocolException , Error );

    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write ( SocketOutputStream & oStream ) ;

	// execute packet's handler
	void execute ( Player * pPlayer ) throw ( ProtocolException , Error );

	// get packet id
	PacketID_t getPacketID ()  { return PACKET_CU_REQUEST; }
	
	// get packet's body size
	PacketSize_t getPacketSize ()  { return m_Resource.getSize(); }

	// �ӽ� �ڵ��. -_-;
	static PacketSize_t getPacketMaxSize () throw () { return Resource::getMaxSize(); }

	// get packet name
	string getPacketName ()  { return "CURequest"; }
	
	// get packet's debug string
	string toString () ;


public :

	// get/set resource
	const Resource & getResource ()  { return m_Resource; }
	void setResource ( const Resource & resource ) throw () { m_Resource = resource; }


private :

	// resource
	Resource m_Resource;	

};


//--------------------------------------------------------------------------------
//
// class CURequestFactory;
//
// Factory for CURequest
//
//--------------------------------------------------------------------------------

class CURequestFactory : public PacketFactory {

public :
	
	// create packet
	Packet * createPacket () throw () { return new CURequest(); }

	// get packet name
	string getPacketName ()  { return "CURequest"; }
	
	// get packet id
	PacketID_t getPacketID ()  { return Packet::PACKET_CU_REQUEST; }

	// get packet's max body size
	PacketSize_t getPacketMaxSize ()  
	{ 
		return Resource::getMaxSize(); 
	}

};


//--------------------------------------------------------------------------------
//
// class CURequestHandler;
//
//--------------------------------------------------------------------------------

class CURequestHandler {

public :

	// execute packet's handler
	static void execute ( CURequest * pPacket , Player * pPlayer ) throw ( ProtocolException , Error );

};

#endif
