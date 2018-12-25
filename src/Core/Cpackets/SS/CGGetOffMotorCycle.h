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
	
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) ;
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID()  { return PACKET_CG_GET_OFF_MOTORCYCLE; }
	
	// get packet's body size
	PacketSize_t getPacketSize()  { return szObjectID; }

	// get packet name
	string getPacketName()  { return "CGGetOffMotorCycle"; }

	// get/set ObjectID
	ObjectID_t getObjectID()   { return m_ObjectID; }
	void setObjectID(ObjectID_t ObjectID) throw() { m_ObjectID = ObjectID; }

	// get packet's debug string
	string toString() ;

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
	string getPacketName()  { return "CGGetOffMotorCycle"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_CG_GET_OFF_MOTORCYCLE; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize()  { return szObjectID; }

};


//////////////////////////////////////////////////////////////////////
//
// class CGGetOffMotorCycleHandler;
//
//////////////////////////////////////////////////////////////////////

class CGGetOffMotorCycleHandler {

public:

	// execute packet's handler
	static void execute(CGGetOffMotorCycle* pCGGetOffMotorCycle, Player* pPlayer);

};

#endif
