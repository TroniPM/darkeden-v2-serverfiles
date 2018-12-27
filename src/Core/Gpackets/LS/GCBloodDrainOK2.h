//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCBloodDrainOK2.h 
// Written By  : elca@ewestsoft.com
// Description : 기술이 성공했을때 보내는 패킷을 위한 클래스 정의
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_BLOOD_DRAIN_OK_2_H__
#define __GC_BLOOD_DRAIN_OK_2_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "ModifyInfo.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class GCBloodDrainOK2;
//
// 게임서버에서 클라이언트로 자신의 기술이 성공을 알려주기 위한 클래스
//
//////////////////////////////////////////////////////////////////////

class GCBloodDrainOK2 : public ModifyInfo {

public :
	
	// constructor
	GCBloodDrainOK2() ;
	
	// destructor
	~GCBloodDrainOK2() ;

	
public :
	
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) ;
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID()  { return PACKET_GC_BLOOD_DRAIN_OK_2; }
	
	// get packet's body size
	// 최적화시, 미리 계산된 정수를 사용한다.
	PacketSize_t getPacketSize()  { return szObjectID + ModifyInfo::getPacketSize(); }

	// get packet's name
	string getPacketName()  { return "GCBloodDrainOK2"; }
	
	// get packet's debug string
	string toString() ;

	// get / set CEffectID
	ObjectID_t getObjectID()  { return m_ObjectID; }
	void setObjectID(ObjectID_t ObjectID)  { m_ObjectID = ObjectID; }

private :
	
	// ObjectID
	ObjectID_t m_ObjectID;



};


//////////////////////////////////////////////////////////////////////
//
// class GCBloodDrainOK2Factory;
//
// Factory for GCBloodDrainOK2
//
//////////////////////////////////////////////////////////////////////

class GCBloodDrainOK2Factory : public PacketFactory {

public :
	
	// constructor
	GCBloodDrainOK2Factory()  {}
	
	// destructor
	virtual ~GCBloodDrainOK2Factory()  {}

	
public :
	
	// create packet
	Packet* createPacket()  { return new GCBloodDrainOK2(); }

	// get packet name
	string getPacketName()  { return "GCBloodDrainOK2"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_GC_BLOOD_DRAIN_OK_2; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize()  { return szObjectID + ModifyInfo::getPacketMaxSize(); }

};


//////////////////////////////////////////////////////////////////////
//
// class GCBloodDrainOK2Handler;
//
//////////////////////////////////////////////////////////////////////

class GCBloodDrainOK2Handler {

public :

	// execute packet's handler
	static void execute(GCBloodDrainOK2* pGCBloodDrainOK2, Player* pPlayer);

};

#endif
