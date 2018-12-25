//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCSkillToObjectOK6.h 
// Written By  : elca@ewestsoft.com
// Description : 기술이 성공했을때 보내는 패킷을 위한 클래스 정의
// 				기술에 당한 분들이 받으실 패킷
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_SKILL_TO_OBJECT_OK_6_H__
#define __GC_SKILL_TO_OBJECT_OK_6_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "ModifyInfo.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class GCSkillToObjectOK6;
//
// 게임서버에서 클라이언트로 자신의 기술이 성공을 알려주기 위한 클래스
//
//////////////////////////////////////////////////////////////////////

class GCSkillToObjectOK6 : public ModifyInfo {

public :
	
	// constructor
	GCSkillToObjectOK6() throw();
	
	// destructor
	~GCSkillToObjectOK6() throw();

	
public :
	
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) ;
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID()  { return PACKET_GC_SKILL_TO_OBJECT_OK_6; }
	
	// get packet's body size
	// 최적화시, 미리 계산된 정수를 사용한다.
	PacketSize_t getPacketSize()  { return szCoord*2 + szSkillType + szDuration + szBYTE + ModifyInfo::getPacketSize(); }

	// get packet's name
	string getPacketName()  { return "GCSkillToObjectOK6"; }
	
	// get packet's debug string
	string toString() ;

	// get / set ObjectID
	Coord_t getX()  { return m_X;}
	Coord_t getY()  { return m_Y;}
	void setXY(Coord_t X, Coord_t Y) throw() { m_X = X; m_Y = Y;}
		

	// get / set SkillType
	SkillType_t getSkillType()  { return m_SkillType; }
	void setSkillType(SkillType_t SkillType) throw() { m_SkillType = SkillType; }

	// get / set Duration
	Duration_t getDuration()  { return m_Duration; }
	void setDuration(Duration_t Duration) throw() { m_Duration = Duration; }
	
	// get / set CEffectID 
//	CEffectID_t getCEffectID()  { return m_CEffectID; }
//	void setCEffectID(CEffectID_t e) throw() { m_CEffectID = e; }

	BYTE getGrade()  { return m_Grade; } 
	void setGrade( BYTE grade ) throw() { m_Grade = grade; }

private :

	// origin X, Y	
	Coord_t m_X, m_Y;

	// SkillType
	SkillType_t m_SkillType;

	// Duration
	Duration_t m_Duration;

	// CEffectID
//	CEffectID_t m_CEffectID;

	BYTE m_Grade;
};


//////////////////////////////////////////////////////////////////////
//
// class GCSkillToObjectOK6Factory;
//
// Factory for GCSkillToObjectOK6
//
//////////////////////////////////////////////////////////////////////

class GCSkillToObjectOK6Factory : public PacketFactory {

public :
	
	// constructor
	GCSkillToObjectOK6Factory() throw() {}
	
	// destructor
	virtual ~GCSkillToObjectOK6Factory() throw() {}

	
public :
	
	// create packet
	Packet* createPacket() throw() { return new GCSkillToObjectOK6(); }

	// get packet name
	string getPacketName()  { return "GCSkillToObjectOK6"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_GC_SKILL_TO_OBJECT_OK_6; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize()  { return szCoord*2+ szSkillType + szDuration + szBYTE + ModifyInfo::getPacketMaxSize(); }

};


//////////////////////////////////////////////////////////////////////
//
// class GCSkillToObjectOK6Handler;
//
//////////////////////////////////////////////////////////////////////

class GCSkillToObjectOK6Handler {

public :

	// execute packet's handler
	static void execute(GCSkillToObjectOK6* pGCSkillToObjectOK6, Player* pPlayer);

};

#endif
