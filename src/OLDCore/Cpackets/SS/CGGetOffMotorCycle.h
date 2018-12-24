//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGGetOffMotorCycle.h 
// Written By  : elca@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_GET_OFF_MOTORCYCLE_H__
#define __CG_GET_OFF_MOTORCYCLE_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class CGGetOffMotorCycle;
//
//////////////////////////////////////////////////////////////////////

class CGGetOffMotorCycle : public Packet {

public:
	
	// constructor
	CGGetOffMotorCycle() throw();
	
	// destructor
	~CGGetOffMotorCycle() throw();

	
public:
	
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_CG_GET_OFF_MOTORCYCLE; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const throw() { return szObjectID; }

	// get packet name
	string getPacketName() const throw() { return "CGGetOffMotorCycle"; }

	// get/set ObjectID
	ObjectID_t getObjectID() const throw()  { return m_ObjectID; }
	void setObjectID(ObjectID_t ObjectID) throw() { m_ObjectID = ObjectID; }

	// get packet's debug string
	string toString() const throw();

private :

	// ObjectID
	ObjectID_t m_ObjectID;
};


//////////////////////////////////////////////////////////////////////
//
// class CGGetOffMotorCycleFactory;
//
// Factory for CGGetOffMotorCycle
//
//////////////////////////////////////////////////////////////////////

class CGGetOffMotorCycleFactory : public PacketFactory {

public:
	
	// constructor
	CGGetOffMotorCycleFactory() throw() {}
	
	// destructor
	virtual ~CGGetOffMotorCycleFactory() throw() {}

	
public:
	
	// create packet
	Packet* createPacket() throw() { return new CGGetOffMotorCycle(); }

	// get packet name
	string getPacketName() const throw() { return "CGGetOffMotorCycle"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_CG_GET_OFF_MOTORCYCLE; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize() const throw() { return szObjectID; }

};


//////////////////////////////////////////////////////////////////////
//
// class CGGetOffMotorCycleHandler;
//
//////////////////////////////////////////////////////////////////////

class CGGetOffMotorCycleHandler {

public:

	// execute packet's handler
	static void execute(CGGetOffMotorCycle* pCGGetOffMotorCycle, Player* pPlayer) throw(Error);

};

#endif
