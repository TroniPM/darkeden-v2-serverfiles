//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCFastMove.h 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_FAST_MOVE_H__
#define __GC_FAST_MOVE_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////
//
// class GCFastMove;
//
// ���� �������� Ư�� ����ڰ� �������ٴ� ������ Ŭ���̾�Ʈ�� ������ 
// �� ����ϴ� ��Ŷ ��ü�̴�.(ObjectID,X,Y,DIR) �� �����Ѵ�.
//
//////////////////////////////////////////////////////////////////////

class GCFastMove : public Packet {

public :

	// constructor
	GCFastMove() throw()
	{
	}

	GCFastMove(ObjectID_t objectID, Coord_t x, Coord_t y, Coord_t x2, Coord_t y2) throw()
		: m_ObjectID(objectID), m_FromX(x), m_FromY(y), m_ToX(x2), m_ToY(y2)
	{
	}


public :
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID()  { return PACKET_GC_FAST_MOVE; }
	
	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static GCFastMovePacketSize �� ����, �����϶�.
	PacketSize_t getPacketSize()  { return szObjectID + 4*szCoord + szSkillType; }

	// get packet's name
	string getPacketName()  { return "GCFastMove"; }
	
	// get packet's debug string
	string toString() ;


public :

	// get/set Creature ID 
	ObjectID_t getObjectID()  { return m_ObjectID; }
	void setObjectID(ObjectID_t objectID) throw() { m_ObjectID = objectID; }

	void setXY(Coord_t x, Coord_t y, Coord_t x2, Coord_t y2)
	{
		m_FromX = x; m_FromY = y; m_ToX = x2; m_ToY = y2;
	}

	// get
	Coord_t getFromX()  { return m_FromX; }
	Coord_t getFromY()  { return m_FromY; }
	Coord_t getToX()  { return m_ToX; }
	Coord_t getToY()  { return m_ToY; }
	
	SkillType_t getSkillType() const { return m_SkillType; }
	void setSkillType( SkillType_t skillType ) { m_SkillType = skillType; }


private :
	
	ObjectID_t m_ObjectID;		// ũ��ó ���̵�
	Coord_t m_FromX,m_FromY, m_ToX, m_ToY;				// �����ǥ, ������ǥ 
	SkillType_t m_SkillType;
};


//////////////////////////////////////////////////////////////////////
//
// class GCFastMoveFactory;
//
// Factory for GCFastMove
//
//////////////////////////////////////////////////////////////////////

class GCFastMoveFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket() throw() { return new GCFastMove(); }

	// get packet name
	string getPacketName()  { return "GCFastMove"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_GC_FAST_MOVE; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCFastMovePacketSize �� ����, �����϶�.
	PacketSize_t getPacketMaxSize()  { return szObjectID + 4*szCoord + szSkillType; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCFastMoveHandler;
//
//////////////////////////////////////////////////////////////////////

class GCFastMoveHandler {

public :

	// execute packet's handler
	static void execute(GCFastMove* pPacket, Player* pPlayer) throw(ProtocolException, Error);

};

#endif
