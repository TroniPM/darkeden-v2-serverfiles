//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCGetOffMotorCycle.h 
// Written By  : elca@ewestsoft.com
// Description : ����� ���������� ������ ��Ŷ�� ���� Ŭ���� ����
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_GET_OFF_MOTORCYCLE_H__
#define __GC_GET_OFF_MOTORCYCLE_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class GCGetOffMotorCycle;
//
// ���Ӽ������� Ŭ���̾�Ʈ�� �ڽ��� ����� ������ �˷��ֱ� ���� Ŭ����
//
//////////////////////////////////////////////////////////////////////

class GCGetOffMotorCycle : public Packet {

public :
	
	// constructor
	GCGetOffMotorCycle() throw();
	
	// destructor
	~GCGetOffMotorCycle() throw();

	
public :
	
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) ;
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID()  { return PACKET_GC_GET_OFF_MOTORCYCLE; }
	
	// get packet's body size
	// ����ȭ��, �̸� ���� ������ ����Ѵ�.
	PacketSize_t getPacketSize()  { return szObjectID; }

	// get packet's name
	string getPacketName()  { return "GCGetOffMotorCycle"; }
	
	// get packet's debug string
	string toString() ;

	// get / set ObjectID
	ObjectID_t getObjectID()  { return m_ObjectID; }
	void setObjectID(ObjectID_t ObjectID) throw() { m_ObjectID = ObjectID; }

private :
	
	// ObjectID
	ObjectID_t m_ObjectID;

};


//////////////////////////////////////////////////////////////////////
//
// class GCGetOffMotorCycleFactory;
//
// Factory for GCGetOffMotorCycle
//
//////////////////////////////////////////////////////////////////////

class GCGetOffMotorCycleFactory : public PacketFactory {

public :
	
	// constructor
	GCGetOffMotorCycleFactory() throw() {}
	
	// destructor
	virtual ~GCGetOffMotorCycleFactory() throw() {}

	
public :
	
	// create packet
	Packet* createPacket() throw() { return new GCGetOffMotorCycle(); }

	// get packet name
	string getPacketName()  { return "GCGetOffMotorCycle"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_GC_GET_OFF_MOTORCYCLE; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize()  { return szObjectID; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCGetOffMotorCycleHandler;
//
//////////////////////////////////////////////////////////////////////

class GCGetOffMotorCycleHandler {

public :

	// execute packet's handler
	static void execute(GCGetOffMotorCycle* pGCGetOffMotorCycle, Player* pPlayer);

};

#endif
