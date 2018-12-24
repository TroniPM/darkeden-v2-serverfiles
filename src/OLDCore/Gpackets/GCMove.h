//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCMove.h 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_MOVE_H__
#define __GC_MOVE_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////
//
// class GCMove;
//
// ���� �������� Ư�� ����ڰ� �������ٴ� ������ Ŭ���̾�Ʈ�� ������ 
// �� ����ϴ� ��Ŷ ��ü�̴�.(ObjectID,X,Y,DIR) �� �����Ѵ�.
//
//////////////////////////////////////////////////////////////////////

class GCMove : public Packet {

public :

	// constructor
	GCMove() throw()
	{
	}

	GCMove(ObjectID_t objectID, Coord_t x, Coord_t y, Dir_t dir) throw()
		: m_ObjectID(objectID), m_X(x), m_Y(y), m_Dir(dir)
	{
	}


public :
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_GC_MOVE; }
	
	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static GCMovePacketSize �� ����, �����϶�.
	PacketSize_t getPacketSize() const throw() { return szObjectID + szCoord + szCoord + szDir ; }

	// get packet's name
	string getPacketName() const throw() { return "GCMove"; }
	
	// get packet's debug string
	string toString() const throw();


public :

	// get/set Creature ID 
	ObjectID_t getObjectID() const throw() { return m_ObjectID; }
	void setObjectID(ObjectID_t objectID) throw() { m_ObjectID = objectID; }

	// get/set X
	Coord_t getX() const throw() { return m_X; }
	void setX(Coord_t x) throw() { m_X = x; }
	
	// get/set Y
	Coord_t getY() const throw() { return m_Y; }
	void setY(Coord_t y) throw() { m_Y = y; }

	// get/set Dir
	Dir_t getDir() const throw() { return m_Dir; }
	void setDir(Dir_t dir) throw() { m_Dir = dir; }


private :
	
	ObjectID_t m_ObjectID;		// ũ��ó ���̵�
	Coord_t m_X;				// X ��ǥ
	Coord_t m_Y;				// Y ��ǥ
	Dir_t m_Dir;				// ����

};


//////////////////////////////////////////////////////////////////////
//
// class GCMoveFactory;
//
// Factory for GCMove
//
//////////////////////////////////////////////////////////////////////

class GCMoveFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket() throw() { return new GCMove(); }

	// get packet name
	string getPacketName() const throw() { return "GCMove"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_MOVE; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCMovePacketSize �� ����, �����϶�.
	PacketSize_t getPacketMaxSize() const throw() { return szObjectID + szCoord + szCoord + szDir ; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCMoveHandler;
//
//////////////////////////////////////////////////////////////////////

class GCMoveHandler {

public :

	// execute packet's handler
	static void execute(GCMove* pPacket, Player* pPlayer) throw(ProtocolException, Error);

};

#endif
