//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCThrowBombOK3.h 
// Written By  : elca@ewestsoft.com
// Description : ����� ���� �ڰ� �޴� ��Ŷ
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_THROW_BOMB_OK_3_H__
#define __GC_THROW_BOMB_OK_3_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class GCThrowBombOK3;
//
// ���Ӽ������� Ŭ���̾�Ʈ�� �ڽ��� ����� ������ �˷��ֱ� ���� Ŭ����
//
//////////////////////////////////////////////////////////////////////

class GCThrowBombOK3 : public Packet {

public :
	
	// constructor
	GCThrowBombOK3() ;
	
	// destructor
	~GCThrowBombOK3() ;

	
public :
	
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) ;
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID()  { return PACKET_GC_THROW_BOMB_OK_3; }
	
	// get packet's body size
	// ����ȭ��, �̸� ���� ������ ����Ѵ�.
	PacketSize_t getPacketSize()  { return szObjectID + szCoord*2+ szDir + szItemType 
			+ szBYTE + szObjectID* m_CListNum; }
         //CListNum, SListNum, ListEle* CListNum, ListEle* SListNum* 5 

	// get packet's name
	string getPacketName()  { return "GCThrowBombOK3"; }
	
	// get packet's debug string
	string toString() ;

	// get / set ObjectID
	ObjectID_t getObjectID()  { return m_ObjectID; }
	void setObjectID(ObjectID_t ObjectID)  { m_ObjectID = ObjectID; }

	// get / set X
	Coord_t getX()  { return m_X; }
	void setX(Coord_t X)  { m_X = X; }

	// get / set Y
	Coord_t getY()  { return m_Y; }
	void setY(Coord_t Y)  { m_Y = Y; }

	void setXYDir(Coord_t X, Coord_t Y, Dir_t R)  { m_X = X; m_Y = Y; m_Dir = R;}
	
	// get / set Dir
	Dir_t getDir()  { return m_Dir; }
	void setDir(Dir_t r)  { m_Dir = r; }
	
	// get / set ItemType
	ItemType_t getItemType()  { return m_ItemType; }
	void setItemType(ItemType_t r)  { m_ItemType = r; }

    // get / set Creature List Number
    BYTE getCListNum()  { return m_CListNum; }
    void setCListNum(BYTE CListNum)  { m_CListNum = CListNum; }


    // add / delete  Creature List
    void addCListElement(ObjectID_t ObjectID) ;

	// Clear Creature List
    void clearCList()  { m_CList.clear(); m_CListNum = 0; }

    // pop front Element in Status List
    ObjectID_t popCListElement()  { ObjectID_t CreatureList = m_CList.front(); m_CList.pop_front(); return CreatureList; }


private :
	
	// ObjectID
	ObjectID_t m_ObjectID;


	// X, Y
	Coord_t m_X;

	Coord_t m_Y;

	// Dir
	Dir_t m_Dir;

	ItemType_t m_ItemType;

	// Creature List Num
	BYTE m_CListNum;

	// Creature List
	list<ObjectID_t> m_CList;

};


//////////////////////////////////////////////////////////////////////
//
// class GCThrowBombOK3Factory;
//
// Factory for GCThrowBombOK3
//
//////////////////////////////////////////////////////////////////////

class GCThrowBombOK3Factory : public PacketFactory {

public :
	
	// constructor
	GCThrowBombOK3Factory()  {}
	
	// destructor
	virtual ~GCThrowBombOK3Factory()  {}

	
public :
	
	// create packet
	Packet* createPacket()  { return new GCThrowBombOK3(); }

	// get packet name
	string getPacketName()  { return "GCThrowBombOK3"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_GC_THROW_BOMB_OK_3; }

	// get Pakcet Max Size
	PacketSize_t getPacketMaxSize()  { return szObjectID + szCoord*2 + szDir + szItemType 
	   + szBYTE + szWORD + szObjectID + 255; }
};


//////////////////////////////////////////////////////////////////////
//
// class GCThrowBombOK3Handler;
//
//////////////////////////////////////////////////////////////////////

class GCThrowBombOK3Handler {

public :

	// execute packet's handler
	static void execute(GCThrowBombOK3* pGCThrowBombOK3, Player* pPlayer);

};

#endif
