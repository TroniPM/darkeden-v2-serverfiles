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
	GCRideMotorCycle() ;
	
	// destructor
	~GCRideMotorCycle() ;

	
public :
	
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) ;
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID()  { return PACKET_GC_RIDE_MOTORCYCLE; }
	
	// get packet's body size
	// ����ȭ��, �̸� ���� ������ ����Ѵ�.
	PacketSize_t getPacketSize()  { return szObjectID + szObjectID; }

	// get packet's name
	string getPacketName()  { return "GCRideMotorCycle"; }
	
	// get packet's debug string
	string toString() ;

	// get / set ObjectID
	ObjectID_t getObjectID()  { return m_ObjectID; }
	void setObjectID(ObjectID_t ObjectID)  { m_ObjectID = ObjectID; }

	// get / set TargetObjectID
	ObjectID_t getTargetObjectID()  { return m_TargetObjectID; }
	void setTargetObjectID(ObjectID_t TargetObjectID)  { m_TargetObjectID = TargetObjectID; }


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
	GCRideMotorCycleFactory()  {}
	
	// destructor
	virtual ~GCRideMotorCycleFactory()  {}

	
public :
	
	// create packet
	Packet* createPacket()  { return new GCRideMotorCycle(); }

	// get packet name
	string getPacketName()  { return "GCRideMotorCycle"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_GC_RIDE_MOTORCYCLE; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize()  { return szObjectID + szObjectID ; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCRideMotorCycleHandler;
//
//////////////////////////////////////////////////////////////////////

class GCRideMotorCycleHandler {

public :

	// execute packet's handler
	static void execute(GCRideMotorCycle* pGCRideMotorCycle, Player* pPlayer);

};

#endif
