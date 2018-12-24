//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCRideMotorCycleFailed.h 
// Written By  : elca@ewestsoft.com
// Description : ����� ���������� ������ ��Ŷ�� ���� Ŭ���� ����
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_RIDE_MOTORCYCLE_FAILED_H__
#define __GC_RIDE_MOTORCYCLE_FAILED_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class GCRideMotorCycleFailed;
//
// ���Ӽ������� Ŭ���̾�Ʈ�� �ڽ��� ����� ������ �˷��ֱ� ���� Ŭ����
//
//////////////////////////////////////////////////////////////////////
class GCRideMotorCycleFailed : public Packet {

public :
	
	// constructor
	GCRideMotorCycleFailed() throw();
	
	// destructor
	~GCRideMotorCycleFailed() throw();

	
public :
	
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_GC_RIDE_MOTORCYCLE_FAILED; }
	
	// get packet's body size
	// ����ȭ��, �̸� ���� ������ ����Ѵ�.
	PacketSize_t getPacketSize() const throw() { return szObjectID; }

	// get packet's name
	string getPacketName() const throw() { return "GCRideMotorCycleFailed"; }
	
	// get packet's debug string
	string toString() const throw();

	// get / set ObjectID
	ObjectID_t getObjectID() const throw() { return m_ObjectID; }
	void setObjectID(ObjectID_t ObjectID) throw() { m_ObjectID = ObjectID; }

private :
	
	// ObjectID
	ObjectID_t m_ObjectID;

};


//////////////////////////////////////////////////////////////////////
//
// class GCRideMotorCycleFailedFactory;
//
// Factory for GCRideMotorCycleFailed
//
//////////////////////////////////////////////////////////////////////
class GCRideMotorCycleFailedFactory : public PacketFactory {

public :
	
	// constructor
	GCRideMotorCycleFailedFactory() throw() {}
	
	// destructor
	virtual ~GCRideMotorCycleFailedFactory() throw() {}

	
public :
	
	// create packet
	Packet* createPacket() throw() { return new GCRideMotorCycleFailed(); }

	// get packet name
	string getPacketName() const throw() { return "GCRideMotorCycleFailed"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_RIDE_MOTORCYCLE_FAILED; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize() const throw() { return szObjectID; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCRideMotorCycleFailedHandler;
//
//////////////////////////////////////////////////////////////////////
class GCRideMotorCycleFailedHandler {

public :

	// execute packet's handler
	static void execute(GCRideMotorCycleFailed* pGCRideMotorCycleFailed, Player* pPlayer) throw(Error);

};

#endif
