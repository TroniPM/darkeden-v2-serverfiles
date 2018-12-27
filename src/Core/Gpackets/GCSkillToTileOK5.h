//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCSkillToTileOK5.h 
// Written By  : elca@ewestsoft.com
// Description : 기술에 당한 자가 받는 패킷
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_SKILL_TO_TILE_OK_5_H__
#define __GC_SKILL_TO_TILE_OK_5_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class GCSkillToTileOK5;
//
// 게임서버에서 클라이언트로 자신의 기술이 성공을 알려주기 위한 클래스
//
//////////////////////////////////////////////////////////////////////

class GCSkillToTileOK5 : public Packet {

public :
	
	// constructor
	GCSkillToTileOK5() ;
	
	// destructor
	~GCSkillToTileOK5() ;

	
public :
	
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) ;
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID()  { return PACKET_GC_SKILL_TO_TILE_OK_5; }
	
	// get packet's body size
	// 최적화시, 미리 계산된 정수를 사용한다.
	PacketSize_t getPacketSize()  { return szObjectID + szSkillType + szCoord*2+ szRange + szDuration + 
			szBYTE + szObjectID* m_CListNum + szBYTE; }
         //CListNum, SListNum, ListEle* CListNum, ListEle* SListNum* 5 

	// get packet's name
	string getPacketName()  { return "GCSkillToTileOK5"; }
	
	// get packet's debug string
	string toString() ;

	// get / set ObjectID
	ObjectID_t getObjectID()  { return m_ObjectID; }
	void setObjectID(ObjectID_t ObjectID)  { m_ObjectID = ObjectID; }

	// get / set SkillType
	SkillType_t getSkillType()  { return m_SkillType; }
	void setSkillType(SkillType_t SkillType)  { m_SkillType = SkillType; }

	// get / set X
	Coord_t getX()  { return m_X; }
	void setX(Coord_t X)  { m_X = X; }

	// get / set Y
	Coord_t getY()  { return m_Y; }
	void setY(Coord_t Y)  { m_Y = Y; }
	
	// get / set Range
	Range_t getRange()  { return m_Range; }
	void setRange(Range_t r)  { m_Range = r; }

	// get / set Duration
	Duration_t getDuration()  { return m_Duration; }
	void setDuration(Duration_t Duration)  { m_Duration = Duration; }

    // get / set Creature List Number
    BYTE getCListNum()  { return m_CListNum; }
    void setCListNum(BYTE CListNum)  { m_CListNum = CListNum; }


    // add / delete  Creature List
    void addCListElement(ObjectID_t ObjectID) ;

	// Clear Creature List
    void clearCList()  { m_CList.clear(); m_CListNum = 0; }

    // pop front Element in Status List
    ObjectID_t popCListElement()  { ObjectID_t CreatureList = m_CList.front(); m_CList.pop_front(); return CreatureList; }

	BYTE getGrade()  { return m_Grade; }
	void setGrade( BYTE grade )  { m_Grade = grade; }

private :
	
	// ObjectID
	ObjectID_t m_ObjectID;

	// SkillType
	SkillType_t m_SkillType;

	// X, Y
	Coord_t m_X;

	Coord_t m_Y;

	// Range
	Range_t m_Range;

	// Duration
	Duration_t m_Duration;

	// Creature List Num
	BYTE m_CListNum;

	// Creature List
	list<ObjectID_t> m_CList;

	BYTE m_Grade;
};


//////////////////////////////////////////////////////////////////////
//
// class GCSkillToTileOK5Factory;
//
// Factory for GCSkillToTileOK5
//
//////////////////////////////////////////////////////////////////////

class GCSkillToTileOK5Factory : public PacketFactory {

public :
	
	// constructor
	GCSkillToTileOK5Factory()  {}
	
	// destructor
	virtual ~GCSkillToTileOK5Factory()  {}

	
public :
	
	// create packet
	Packet* createPacket()  { return new GCSkillToTileOK5(); }

	// get packet name
	string getPacketName()  { return "GCSkillToTileOK5"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_GC_SKILL_TO_TILE_OK_5; }

	// get Pakcet Max Size
	PacketSize_t getPacketMaxSize()  { return szObjectID + szSkillType + szCoord*2 + szRange + szDuration + 
			szBYTE + szWORD + szObjectID + 255 + szBYTE; }
};


//////////////////////////////////////////////////////////////////////
//
// class GCSkillToTileOK5Handler;
//
//////////////////////////////////////////////////////////////////////

class GCSkillToTileOK5Handler {

public :

	// execute packet's handler
	static void execute(GCSkillToTileOK5* pGCSkillToTileOK5, Player* pPlayer);

};

#endif
