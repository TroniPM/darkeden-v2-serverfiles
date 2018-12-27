//--------------------------------------------------------------------------------
// 
// Filename    : UCUpdate.h 
// Written By  : Reiot
// 
//--------------------------------------------------------------------------------

#ifndef __UC_UPDATE_H__
#define __UC_UPDATE_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"
#include "Resource.h"

//--------------------------------------------------------------------------------
//
// class UCUpdate;
//
//--------------------------------------------------------------------------------

class UCUpdate : public Packet {

public :

	// �Է½�Ʈ��(����)���κ��� �����͸� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
	void read ( SocketInputStream & iStream )  { throw UnsupportedError(__PRETTY_FUNCTION__); }

    // �������κ��� ���� �����͸� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read ( Socket * pSocket ) ;
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write ( SocketOutputStream & oStream )  { throw UnsupportedError(__PRETTY_FUNCTION__); }

    // �������� ���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write ( Socket * pSocket ) ;

	// execute packet's handler
	void execute ( Player * pPlayer ) ;

	// get packet id
	PacketID_t getPacketID ()  { return PACKET_UC_UPDATE; }
	
	// get packet body size
	// *OPTIMIZATION HINT*
	// const static UCUpdatePacketSize �� ����, �����϶�.
	PacketSize_t getPacketSize ()  
	{ 
		return m_Resource.getSize();
	}
	
	// �ƹ��� Ŀ�� ��ް��� ���� ���Ѵ�.
	static PacketSize_t getPacketMaxSize ()  
	{ 
		return Resource::getMaxSize();
	}

	// get packet's name
	string getPacketName ()  { return "UCUpdate"; }
	
	// get packet's debug string
	string toString () ;


public :

	// get/set resource
	const Resource & getResource ()  { return m_Resource; }
	void setResource ( const Resource & resource )  { m_Resource = resource; }

private :

	Resource m_Resource;
	
};


//--------------------------------------------------------------------------------
//
// class UCUpdateFactory;
//
// Factory for UCUpdate
//
//--------------------------------------------------------------------------------

class UCUpdateFactory : public PacketFactory {

public :
	
	// create packet
	Packet * createPacket ()  { return new UCUpdate(); }

	// get packet name
	string getPacketName ()  { return "UCUpdate"; }
	
	// get packet id
	PacketID_t getPacketID ()  { return Packet::PACKET_UC_UPDATE; }

	// get packet's max body size
	PacketSize_t getPacketMaxSize ()  { return Resource::getMaxSize(); }
	
};


//--------------------------------------------------------------------------------
//
// class UCUpdateHandler;
//
//--------------------------------------------------------------------------------

class UCUpdateHandler {

public :

	// execute packet's handler
	static void execute ( UCUpdate * pPacket , Player * pPlayer ) ;

};

#endif
