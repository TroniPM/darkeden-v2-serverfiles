//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCSkillToTileOK3.h 
// Written By  : elca@ewestsoft.com
// Description : 기술 사용자는 볼수 있고, 당한자는 볼 수 없는 패킷
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_SKILL_TO_TILE_OK_3_H__
#define __GC_SKILL_TO_TILE_OK_3_H__


// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class GCSkillToTileOK3;
//
// 게임서버에서 클라이언트로 자신의 기술이 성공을 알려주기 위한 클래스
//
//////////////////////////////////////////////////////////////////////

class GCSkillToTileOK3 : public Packet {

public :
	
	// constructor
	GCSkillToTileOK3() ;
	
	// destructor
	~GCSkillToTileOK3() ;

	
public :
	
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) ;
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID()  { return PACKET_GC_SKILL_TO_TILE_OK_3; }
	
	// get packet's body size
	// 최적화시, 미리 계산된 정수를 사용한다.
//	PacketSize_t getPacketSize()  { return szSkillType + szObjectID +(szCoord* 2)
//			+ szDuration + szBYTE + szObjectID* m_CListNum; }
	PacketSize_t getPacketSize()  { return szSkillType + szObjectID +(szCoord* 2) + szBYTE;}

	// get packet's name
	string getPacketName()  { return "GCSkillToTileOK3"; }
	
	// get packet's debug string
	string toString() ;

	// get / set ObjectID 
	CEffectID_t getObjectID()  { return m_ObjectID; }
	void setObjectID(ObjectID_t ObjectID)  { m_ObjectID = ObjectID; }

	// get / set SkillType
	SkillType_t getSkillType()  { return m_SkillType; }
	void setSkillType(SkillType_t SkillType)  { m_SkillType = SkillType; }

	// get / set Duration
//	Duration_t getDuration()  { return m_Duration; }
//	void setDuration(Duration_t Duration)  { m_Duration = Duration; }

	// get / set X, Y
	Coord_t getX() { return m_X; }
	void setX(Coord_t X) { m_X = X; }

	Coord_t getY() { return m_Y; }
	void setY(Coord_t Y) { m_Y = Y; }

	// get / set Creature List Number
//	BYTE getCListNum()  { return m_CListNum; }

//	void setCListNum(BYTE CListNum)  { m_CListNum = CListNum; }

	// add / delete  Creature List
//	void addCListElement(ObjectID_t ObjectID) ;

	// Clear CreatureList
//	void clearCList()  { m_CList.clear(); m_CListNum = 0; }

	// pop front Element in Status List
//	ObjectID_t popCListElement()  { ObjectID_t CreatureList = m_CList.front(); m_CList.pop_front(); return CreatureList; }

	BYTE getGrade() const { return m_Grade; }
	void setGrade( BYTE grade ) { m_Grade = grade; }

private :
	
	// CEffectID
	ObjectID_t m_ObjectID;

	// SkillType
	SkillType_t m_SkillType;

	// Duration
//	Duration_t m_Duration;

	// X, Y Position
	Coord_t m_X;

	Coord_t m_Y;

	// CreatureList Element Number 
//	BYTE m_CListNum;

	// Creature List
//	list<ObjectID_t> m_CList;

	BYTE m_Grade;
};


//////////////////////////////////////////////////////////////////////
//
// class GCSkillToTileOK3Factory;
//
// Factory for GCSkillToTileOK3
//
//////////////////////////////////////////////////////////////////////

class GCSkillToTileOK3Factory : public PacketFactory {

public :
	
	// constructor
	GCSkillToTileOK3Factory()  {}
	
	// destructor
	virtual ~GCSkillToTileOK3Factory()  {}

	
public :
	
	// create packet
	Packet* createPacket()  { return new GCSkillToTileOK3(); }

	// get packet name
	string getPacketName()  { return "GCSkillToTileOK3"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_GC_SKILL_TO_TILE_OK_3; }

	// get Packet Max Size
//	PacketSize_t getPacketMaxSize()  { return szSkillType + szObjectID +(szCoord* 2) 
//			+ szDuration + szBYTE + szObjectID + 255; }
	// get Packet Max Size
	PacketSize_t getPacketMaxSize()  { return szSkillType + szObjectID +(szCoord* 2) + szBYTE; }
};


//////////////////////////////////////////////////////////////////////
//
// class GCSkillToTileOK3Handler;
//
//////////////////////////////////////////////////////////////////////

class GCSkillToTileOK3Handler {

public :

	// execute packet's handler
	static void execute(GCSkillToTileOK3* pGCSkillToTileOK3, Player* pPlayer);

};

#endif
