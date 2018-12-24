//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCGetOffMotorCycleFailed.h 
// Written By  : elca@ewestsoft.com
// Description : ����� ���������� ������ ��Ŷ�� ���� Ŭ���� ����
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_GET_OFF_MOTORCYCLE_FAILED_H__
#define __GC_GET_OFF_MOTORCYCLE_FAILED_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class GCGetOffMotorCycleFailed;
//
// ���Ӽ������� Ŭ���̾�Ʈ�� �ڽ��� ����� ������ �˷��ֱ� ���� Ŭ����
//
//////////////////////////////////////////////////////////////////////
class GCGetOffMotorCycleFailed : public Packet {

public :
	
	// constructor
	GCGetOffMotorCycleFailed() throw();
	
	// destructor
	~GCGetOffMotorCycleFailed() throw();

	
public :
	
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_GC_GET_OFF_MOTORCYCLE_FAILED; }
	
	// get packet's body size
	// ����ȭ��, �̸� ���� ������ ����Ѵ�.
	PacketSize_t getPacketSize() const throw() { return 0; }

	// get packet's name
	string getPacketName() const throw() { return "GCGetOffMotorCycleFailed"; }
	
	// get packet's debug string
	string toString() const throw();

private :
	
};


//////////////////////////////////////////////////////////////////////
//
// class GCGetOffMotorCycleFailedFactory;
//
// Factory for GCGetOffMotorCycleFailed
//
//////////////////////////////////////////////////////////////////////
class GCGetOffMotorCycleFailedFactory : public PacketFactory {

public :
	
	// constructor
	GCGetOffMotorCycleFailedFactory() throw() {}
	
	// destructor
	virtual ~GCGetOffMotorCycleFailedFactory() throw() {}

	
public :
	
	// create packet
	Packet* createPacket() throw() { return new GCGetOffMotorCycleFailed(); }

	// get packet name
	string getPacketName() const throw() { return "GCGetOffMotorCycleFailed"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_GET_OFF_MOTORCYCLE_FAILED; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize() const throw() { return 0; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCGetOffMotorCycleFailedHandler;
//
//////////////////////////////////////////////////////////////////////
class GCGetOffMotorCycleFailedHandler {

public :

	// execute packet's handler
	static void execute(GCGetOffMotorCycleFailed* pGCGetOffMotorCycleFailed, Player* pPlayer) throw(Error);

};

#endif
