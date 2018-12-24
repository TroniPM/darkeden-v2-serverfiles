//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCThrowBombOK1.h 
// Written By  : elca@ewestsoft.com
// Description : ����� ���������� ������ ��Ŷ�� ���� Ŭ���� ����
// 				��� ����ڿ��� ������ ��Ŷ
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_THROW_BOMB_OK_1_H__
#define __GC_THROW_BOMB_OK_1_H__


// include files
#include "Types.h"
#include "Exception.h"
#include "ModifyInfo.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class GCThrowBombOK1;
//
// ���Ӽ������� Ŭ���̾�Ʈ�� �ڽ��� ����� ������ �˷��ֱ� ���� Ŭ����
//
//////////////////////////////////////////////////////////////////////

class GCThrowBombOK1 : public ModifyInfo {

public :
	
	// constructor
	GCThrowBombOK1() throw();
	
	// destructor
	~GCThrowBombOK1() throw();

	
public :
	
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_GC_THROW_BOMB_OK_1; }
	
	// get packet's body size
	// ����ȭ��, �̸� ���� ������ ����Ѵ�.
	PacketSize_t getPacketSize() const throw() { return szCoord* 2
			+ szBYTE + szDir + szItemType + szObjectID* m_CListNum + ModifyInfo::getPacketSize(); }

	// get packet's name
	string getPacketName() const throw() { return "GCThrowBombOK1"; }
	
	// get packet's debug string
	string toString() const throw();

	// get / set X, Y
	Coord_t getX() { return m_X; }
	void setX(Coord_t X) { m_X = X; }

	Coord_t getY() { return m_Y; }
	void setY(Coord_t Y) { m_Y = Y; }

	Dir_t getDir() { return m_Dir;}
	void setDir(Dir_t r) { m_Dir = r;}

	ItemType_t getItemType() const throw() { return m_ItemType;}
	void setItemType(ItemType_t i) throw() { m_ItemType = i;}
	

	void setXYDir(Coord_t X, Coord_t Y, Dir_t R) { m_X = X; m_Y = Y; m_Dir = R;}

	// get / set Creature List Number
	BYTE getCListNum() const throw() { return m_CListNum; }
	void setCListNum(BYTE CListNum) throw() { m_CListNum = CListNum; }

	// add / delete  Creature List
	void addCListElement(ObjectID_t ObjectID) throw();
	void clearCList() throw() { m_CList.clear(); m_CListNum = 0; }

	// pop front Element in Status List
	ObjectID_t popCListElement() throw() { ObjectID_t CreatureList = m_CList.front(); m_CList.pop_front(); return CreatureList; }

private :
	
	// Dir
	Dir_t m_Dir;
	ItemType_t m_ItemType;

	// X, Y Position
	Coord_t m_X;
	Coord_t m_Y;

	// CreatureList Element Number 
	BYTE m_CListNum;

	// Creature List
	list<ObjectID_t> m_CList;


};


//////////////////////////////////////////////////////////////////////
//
// class GCThrowBombOK1Factory;
//
// Factory for GCThrowBombOK1
//
//////////////////////////////////////////////////////////////////////

class GCThrowBombOK1Factory : public PacketFactory {

public :
	
	// constructor
	GCThrowBombOK1Factory() throw() {}
	
	// destructor
	virtual ~GCThrowBombOK1Factory() throw() {}

	
public :
	
	// create packet
	Packet* createPacket() throw() { return new GCThrowBombOK1(); }

	// get packet name
	string getPacketName() const throw() { return "GCThrowBombOK1"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_THROW_BOMB_OK_1; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize() const throw() { return szCoord* 2
			+ szBYTE + szBYTE + +szDir + szItemType + szWORD + szObjectID + ModifyInfo::getPacketMaxSize(); }

};



//////////////////////////////////////////////////////////////////////
//
// class GCThrowBombOK1Handler;
//
//////////////////////////////////////////////////////////////////////
class GCThrowBombOK1Handler {

public :

	// execute packet's handler
	static void execute(GCThrowBombOK1* pGCThrowBombOK1, Player* pPlayer) throw(Error);

};

#endif
