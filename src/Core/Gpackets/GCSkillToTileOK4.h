//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCSkillToTileOK4.h 
// Written By  : elca@ewestsoft.com
// Description : ����� ���� �ڰ� �޴� ��Ŷ
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_SKILL_TO_TILE_OK_4_H__
#define __GC_SKILL_TO_TILE_OK_4_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class GCSkillToTileOK4;
//
// ���Ӽ������� Ŭ���̾�Ʈ�� �ڽ��� ����� ������ �˷��ֱ� ���� Ŭ����
//
//////////////////////////////////////////////////////////////////////

class GCSkillToTileOK4 : public Packet {

public :
	
	// constructor
	GCSkillToTileOK4() throw();
	
	// destructor
	~GCSkillToTileOK4() throw();

	
public :
	
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID()  { return PACKET_GC_SKILL_TO_TILE_OK_4; }
	
	// get packet's body size
	// ����ȭ��, �̸� ���� ������ ����Ѵ�.
	PacketSize_t getPacketSize()  { return szSkillType + szCoord*2+ szRange + szDuration + 
			szBYTE + szObjectID* m_CListNum + szBYTE; }
         //CListNum, SListNum, ListEle* CListNum, ListEle* SListNum* 4 

	// get packet's name
	string getPacketName()  { return "GCSkillToTileOK4"; }
	
	// get packet's debug string
	string toString() ;

	// get / set ObjectID
//	ObjectID_t getObjectID()  { return m_ObjectID; }
//	void setObjectID(ObjectID_t ObjectID) throw() { m_ObjectID = ObjectID; }

	// get / set SkillType
	SkillType_t getSkillType()  { return m_SkillType; }
	void setSkillType(SkillType_t SkillType) throw() { m_SkillType = SkillType; }

	// get / set X
	Coord_t getX()  { return m_X; }
	void setX(Coord_t X) throw() { m_X = X; }

	// get / set Y
	Coord_t getY()  { return m_Y; }
	void setY(Coord_t Y) throw() { m_Y = Y; }
	
	// get / set Range
	Range_t getRange()  { return m_Range; }
	void setRange(Range_t r) throw() { m_Range = r; }

	// get / set Duration
	Duration_t getDuration()  { return m_Duration; }
	void setDuration(Duration_t Duration) throw() { m_Duration = Duration; }

    // get / set Creature List Number
    BYTE getCListNum()  { return m_CListNum; }
    void setCListNum(BYTE CListNum) throw() { m_CListNum = CListNum; }


    // add / delete  Creature List
    void addCListElement(ObjectID_t ObjectID) throw();

	// Clear Creature List
    void clearCList() throw() { m_CList.clear(); m_CListNum = 0; }

    // pop front Element in Status List
    ObjectID_t popCListElement() throw() { ObjectID_t CreatureList = m_CList.front(); m_CList.pop_front(); return CreatureList; }

	BYTE getGrade()  { return m_Grade; }
	void setGrade( BYTE grade ) throw() { m_Grade = grade; }

private :
	
	// ObjectID
//	ObjectID_t m_ObjectID;

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
// class GCSkillToTileOK4Factory;
//
// Factory for GCSkillToTileOK4
//
//////////////////////////////////////////////////////////////////////

class GCSkillToTileOK4Factory : public PacketFactory {

public :
	
	// constructor
	GCSkillToTileOK4Factory() throw() {}
	
	// destructor
	virtual ~GCSkillToTileOK4Factory() throw() {}

	
public :
	
	// create packet
	Packet* createPacket() throw() { return new GCSkillToTileOK4(); }

	// get packet name
	string getPacketName()  { return "GCSkillToTileOK4"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_GC_SKILL_TO_TILE_OK_4; }

	// get Pakcet Max Size
	PacketSize_t getPacketMaxSize()  { return szSkillType + szCoord*2 + szRange + szDuration + 
			szBYTE + szWORD + szObjectID + 255 + szBYTE; }
};


//////////////////////////////////////////////////////////////////////
//
// class GCSkillToTileOK4Handler;
//
//////////////////////////////////////////////////////////////////////

class GCSkillToTileOK4Handler {

public :

	// execute packet's handler
	static void execute(GCSkillToTileOK4* pGCSkillToTileOK4, Player* pPlayer) throw(Error);

};

#endif
