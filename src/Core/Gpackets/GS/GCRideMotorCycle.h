//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCRideMotorCycle.h 
// Written By  : elca@ewestsoft.com
// Description : ����� ���������� ������ ��Ŷ�� ���� Ŭ���� ����
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_RIDE_MOTORCYCLE_H__
#define __GC_RIDE_MOTORCYCLE_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class GCRideMotorCycle;
//
// ���Ӽ������� Ŭ���̾�Ʈ�� �ڽ��� ����� ������ �˷��ֱ� ���� Ŭ����
//
//////////////////////////////////////////////////////////////////////

class GCRideMotorCycle : public Packet {

public :
	
	// constructor
	GCRideMotorCycle() throw();
	
	// destructor
	~GCRideMotorCycle() throw();

	
public :
	
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_GC_RIDE_MOTORCYCLE; }
	
	// get packet's body size
	// ����ȭ��, �̸� ���� ������ ����Ѵ�.
	PacketSize_t getPacketSize() const throw() { return szObjectID + szObjectID; }

	// get packet's name
	string getPacketName() const throw() { return "GCRideMotorCycle"; }
	
	// get packet's debug string
	string toString() const throw();

	// get / set ObjectID
	ObjectID_t getObjectID() const throw() { return m_ObjectID; }
	void setObjectID(ObjectID_t ObjectID) throw() { m_ObjectID = ObjectID; }

	// get / set TargetObjectID
	ObjectID_t getTargetObjectID() const throw() { return m_TargetObjectID; }
	void setTargetObjectID(ObjectID_t TargetObjectID) throw() { m_TargetObjectID = TargetObjectID; }


private :
	
	// ObjectID
	ObjectID_t m_ObjectID;

	// TargetObjectID
	ObjectID_t m_TargetObjectID;

};


//////////////////////////////////////////////////////////////////////
//
// class GCRideMotorCycleFactory;
//
// Factory for GCRideMotorCycle
//
//////////////////////////////////////////////////////////////////////

class GCRideMotorCycleFactory : public PacketFactory {

public :
	
	// constructor
	GCRideMotorCycleFactory() throw() {}
	
	// destructor
	virtual ~GCRideMotorCycleFactory() throw() {}

	
public :
	
	// create packet
	Packet* createPacket() throw() { return new GCRideMotorCycle(); }

	// get packet name
	string getPacketName() const throw() { return "GCRideMotorCycle"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_RIDE_MOTORCYCLE; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize() const throw() { return szObjectID + szObjectID ; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCRideMotorCycleHandler;
//
//////////////////////////////////////////////////////////////////////

class GCRideMotorCycleHandler {

public :

	// execute packet's handler
	static void execute(GCRideMotorCycle* pGCRideMotorCycle, Player* pPlayer) throw(Error);

};

#endif
