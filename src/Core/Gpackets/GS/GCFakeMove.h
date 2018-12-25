//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCFakeMove.h 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_FAKE_MOVE_H__
#define __GC_FAKE_MOVE_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////
//
// class GCFakeMove;
//
// ���� �������� Ư�� ����ڰ� �������ٴ� ������ Ŭ���̾�Ʈ�� ������ 
// �� ����ϴ� ��Ŷ ��ü�̴�.(ObjectID,X,Y,DIR) �� �����Ѵ�.
//
//////////////////////////////////////////////////////////////////////

class GCFakeMove : public Packet {

public :

	// constructor
	GCFakeMove() throw()
	{
	}

	GCFakeMove(ObjectID_t objectID, Coord_t x, Coord_t y, Coord_t x2, Coord_t y2) throw()
		: m_ObjectID(objectID), m_ToX(x2), m_ToY(y2)
	{
	}


public :
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) ;
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID()  { return PACKET_GC_FAKE_MOVE; }
	
	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static GCFakeMovePacketSize �� ����, �����϶�.
	PacketSize_t getPacketSize()  { return szObjectID + 2*szCoord; }

	// get packet's name
	string getPacketName()  { return "GCFakeMove"; }
	
	// get packet's debug string
	string toString() ;


public :

	// get/set Creature ID 
	ObjectID_t getObjectID()  { return m_ObjectID; }
	void setObjectID(ObjectID_t objectID) throw() { m_ObjectID = objectID; }

	void setXY(Coord_t x2, Coord_t y2)
	{
		m_ToX = x2; 
		m_ToY = y2;
	}

	// get
	Coord_t getToX()  { return m_ToX; }
	Coord_t getToY()  { return m_ToY; }
	


private :
	
	ObjectID_t m_ObjectID;		// ũ��ó ���̵�
	Coord_t m_ToX, m_ToY;		// ������ǥ 
};


//////////////////////////////////////////////////////////////////////
//
// class GCFakeMoveFactory;
//
// Factory for GCFakeMove
//
//////////////////////////////////////////////////////////////////////

class GCFakeMoveFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket() throw() { return new GCFakeMove(); }

	// get packet name
	string getPacketName()  { return "GCFakeMove"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_GC_FAKE_MOVE; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCFakeMovePacketSize �� ����, �����϶�.
	PacketSize_t getPacketMaxSize()  { return szObjectID + 2*szCoord ; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCFakeMoveHandler;
//
//////////////////////////////////////////////////////////////////////

class GCFakeMoveHandler {

public :

	// execute packet's handler
	static void execute(GCFakeMove* pPacket, Player* pPlayer) ;

};

#endif
