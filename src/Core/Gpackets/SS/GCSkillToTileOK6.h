//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCSkillToTileOK6.h 
// Written By  : elca@ewestsoft.com
// Description : ����� ���ߴµ� ����ڴ� �� �� ���� �ڰ� �޴� packet 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_SKILL_TO_TILE_OK_6_H__
#define __GC_SKILL_TO_TILE_OK_6_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "ModifyInfo.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class GCSkillToTileOK6;
//
//
//////////////////////////////////////////////////////////////////////

class GCSkillToTileOK6 : public ModifyInfo {

public :
	
	// constructor
	GCSkillToTileOK6() ;
	
	// destructor
	~GCSkillToTileOK6() ;

	
public :
	
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) ;
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID()  { return PACKET_GC_SKILL_TO_TILE_OK_6; }
	
	// get packet's body size
	// ����ȭ��, �̸� ���� ������ ����Ѵ�.
	PacketSize_t getPacketSize()  { return szCoord*2 + szSkillType + szCoord*2 + szRange + szDuration + 
			szBYTE + szObjectID* m_CListNum + szBYTE + ModifyInfo::getPacketSize(); }
         //CListNum, SListNum, ListEle* CListNum, ListEle* SListNum* 2 

	// get packet's name
	string getPacketName()  { return "GCSkillToTileOK6"; }
	
	// get packet's debug string
	string toString() ;

	// get orign x, y
	Coord_t getOrgX()  { return m_OrgX;}
	Coord_t getOrgY()  { return m_OrgY;}
	// set origin x, y
	void setOrgXY(Coord_t X, Coord_t Y) throw() { m_OrgX = X; m_OrgY = Y;}
	

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
    void addCListElement(ObjectID_t ObjectID) ;

	// Clear Creature List
    void clearCList() throw() { m_CList.clear(); m_CListNum = 0; }

    // pop front Element in Status List
    ObjectID_t popCListElement() throw() { ObjectID_t CreatureList = m_CList.front(); m_CList.pop_front(); return CreatureList; }

	BYTE getGrade()  { return m_Grade; }
	void setGrade( BYTE grade ) throw() { m_Grade = grade; }


private :
	
	// ObjectID
	Coord_t m_OrgX, m_OrgY;	// ��� ������� ��ġ.

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
// class GCSkillToTileOK6Factory;
//
// Factory for GCSkillToTileOK6
//
//////////////////////////////////////////////////////////////////////

class GCSkillToTileOK6Factory : public PacketFactory {

public :
	
	// constructor
	GCSkillToTileOK6Factory() throw() {}
	
	// destructor
	virtual ~GCSkillToTileOK6Factory() throw() {}

	
public :
	
	// create packet
	Packet* createPacket() throw() { return new GCSkillToTileOK6(); }

	// get packet name
	string getPacketName()  { return "GCSkillToTileOK6"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_GC_SKILL_TO_TILE_OK_6; }

	// get Pakcet Max Size
	PacketSize_t getPacketMaxSize()  { return szCoord*2 + szSkillType + szCoord*2 + szRange + szDuration + 
			szBYTE + szWORD + szObjectID + szBYTE + ModifyInfo::getPacketMaxSize(); }
};


//////////////////////////////////////////////////////////////////////
//
// class GCSkillToTileOK6Handler;
//
//////////////////////////////////////////////////////////////////////

class GCSkillToTileOK6Handler {

public :

	// execute packet's handler
	static void execute(GCSkillToTileOK6* pGCSkillToTileOK6, Player* pPlayer);

};

#endif
