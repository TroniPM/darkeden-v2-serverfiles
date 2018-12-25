//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCPhoneConnectionFailed.h 
// Written By  : elca@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_PHONE_CONNECTION_FAILED_H__
#define __GC_PHONE_CONNECTION_FAILED_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class GCPhoneConnectionFailed;
//
// ���� �������� Ư�� ����ڰ� �������ٴ� ������ Ŭ���̾�Ʈ�� ������ 
// �� ����ϴ� ��Ŷ ��ü�̴�.(CreatureID,X,Y,DIR) �� �����Ѵ�.
//
//////////////////////////////////////////////////////////////////////

class GCPhoneConnectionFailed : public Packet {

public :
	
	// constructor
	GCPhoneConnectionFailed() throw();
	
	// destructor
	~GCPhoneConnectionFailed() throw();

	
public :
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID()  { return PACKET_GC_PHONE_CONNECTION_FAILED; }
	
	// get packet's body size
	// ����ȭ��, �̸� ���� ������ ����Ѵ�.
	PacketSize_t getPacketSize()  { return 0; }

	// get packet's name
	string getPacketName()  { return "GCPhoneConnectionFailed"; }
	
	// get packet's debug string
	string toString() ;

private :

};

//////////////////////////////////////////////////////////////////////
//
// class GCPhoneConnectionFailedFactory;
//
// Factory for GCPhoneConnectionFailed
//
//////////////////////////////////////////////////////////////////////

class GCPhoneConnectionFailedFactory : public PacketFactory {

public :
	
	// constructor
	GCPhoneConnectionFailedFactory() throw() {}
	
	// destructor
	virtual ~GCPhoneConnectionFailedFactory() throw() {}

	
public :
	
	// create packet
	Packet* createPacket() throw() { return new GCPhoneConnectionFailed(); }

	// get packet name
	string getPacketName()  { return "GCPhoneConnectionFailed"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_GC_PHONE_CONNECTION_FAILED; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize()  { return 0; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCPhoneConnectionFailedHandler;
//
//////////////////////////////////////////////////////////////////////

class GCPhoneConnectionFailedHandler {

public :

	// execute packet's handler
	static void execute(GCPhoneConnectionFailed* pGCPhoneConnectionFailed, Player* pPlayer) throw(Error);

};

#endif
