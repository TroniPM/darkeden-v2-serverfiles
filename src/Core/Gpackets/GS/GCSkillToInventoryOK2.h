//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCSkillToInventoryOK2.h 
// Written By  : elca@ewestsoft.com
// Description : 기술이 성공했을때 보내는 패킷을 위한 클래스 정의
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_SKILL_TO_INVENTORY_OK_2_H__
#define __GC_SKILL_TO_INVENTORY_OK_2_H__


// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class GCSkillToInventoryOK2;
//
// 게임서버에서 클라이언트로 자신의 기술이 성공을 알려주기 위한 클래스
//
//////////////////////////////////////////////////////////////////////

class GCSkillToInventoryOK2 : public Packet {

public :
	
	// constructor
	GCSkillToInventoryOK2() throw();
	
	// destructor
	~GCSkillToInventoryOK2() throw();

	
public :
	
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) ;
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID()  { return PACKET_GC_SKILL_TO_INVENTORY_OK_2; }
	
	// get packet's body size
	// 최적화시, 미리 계산된 정수를 사용한다.
	PacketSize_t getPacketSize()  { return szSkillType + szObjectID + szDuration; }

	// get packet's name
	string getPacketName()  { return "GCSkillToInventoryOK2"; }
	
	// get packet's debug string
	string toString() ;

	// get / set ObjectID 
	CEffectID_t getObjectID()  { return m_ObjectID; }
	void setObjectID(ObjectID_t ObjectID) throw() { m_ObjectID = ObjectID; }

	// get / set SkillType
	SkillType_t getSkillType()  { return m_SkillType; }
	void setSkillType(SkillType_t SkillType) throw() { m_SkillType = SkillType; }

	// get / set Duration
	Duration_t getDuration()  { return m_Duration; }
	void setDuration(Duration_t Duration) throw() { m_Duration = Duration; }

private :
	
	// ObjectID
	ObjectID_t m_ObjectID;

	// SkillType
	SkillType_t m_SkillType;

	// Duration
	Duration_t m_Duration;

};


//////////////////////////////////////////////////////////////////////
//
// class GCSkillToInventoryOK2Factory;
//
// Factory for GCSkillToInventoryOK2
//
//////////////////////////////////////////////////////////////////////

class GCSkillToInventoryOK2Factory : public PacketFactory {

public :
	
	// constructor
	GCSkillToInventoryOK2Factory() throw() {}
	
	// destructor
	virtual ~GCSkillToInventoryOK2Factory() throw() {}

	
public :
	
	// create packet
	Packet* createPacket() throw() { return new GCSkillToInventoryOK2(); }

	// get packet name
	string getPacketName()  { return "GCSkillToInventoryOK2"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_GC_SKILL_TO_INVENTORY_OK_2; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize()  { return szSkillType + szObjectID + szDuration; }
};


//////////////////////////////////////////////////////////////////////
//
// class GCSkillToInventoryOK2Handler;
//
//////////////////////////////////////////////////////////////////////

class GCSkillToInventoryOK2Handler {

public :

	// execute packet's handler
	static void execute(GCSkillToInventoryOK2* pGCSkillToInventoryOK2, Player* pPlayer) throw(Error);

};

#endif
