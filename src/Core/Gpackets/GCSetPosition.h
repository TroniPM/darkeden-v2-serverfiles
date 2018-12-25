//----------------------------------------------------------------------
// 
// Filename    : GCSetPosition.h 
// Written By  : Reiot
// Description : 
// 
//----------------------------------------------------------------------

#ifndef __GC_SET_POSITION_H__
#define __GC_SET_POSITION_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//----------------------------------------------------------------------
//
// class GCSetPosition;
//
// ���� �������� �÷��̾��� ��ġ�� �������ִ� ��Ŷ�̴�.
// ���߿� GCPatchPCInfo(��Ī) ��Ŷ�� ���յ� �����̴�.
//
//----------------------------------------------------------------------

class GCSetPosition : public Packet {

public :
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) ;
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID()  { return PACKET_GC_SET_POSITION; }
	
	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static GCSetPositionPacketSize �� �����ؼ� �����϶�.
	PacketSize_t getPacketSize()  { return szCoord + szCoord + szDir; }

	// get packet name
	string getPacketName()  { return "GCSetPosition"; }
	
	// get packet's debug string
	string toString() ;
	
	// get/set X Coordicate
	Coord_t getX()  { return m_X; }
	void setX(Coord_t x) throw() { m_X = x; }

	// get/set Y Coordicate
	Coord_t getY()  { return m_Y; }
	void setY(Coord_t y) throw() { m_Y = y; }

	// get/set Direction
	Dir_t getDir()  { return m_Dir; }
	void setDir(Dir_t dir) throw() { m_Dir = dir; }
	
private :
	
	Coord_t m_X;			// X ��ǥ
	Coord_t m_Y;			// Y ��ǥ
	Dir_t m_Dir;			// ����

};


//////////////////////////////////////////////////////////////////////
//
// class GCSetPositionFactory;
//
// Factory for GCSetPosition
//
//////////////////////////////////////////////////////////////////////

class GCSetPositionFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket() throw() { return new GCSetPosition(); }

	// get packet name
	string getPacketName()  { return "GCSetPosition"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_GC_SET_POSITION; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCSetPositionPacketSize �� �����ؼ� �����϶�.
	PacketSize_t getPacketMaxSize()  { return szCoord + szCoord + szDir; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCSetPositionHandler;
//
//////////////////////////////////////////////////////////////////////

class GCSetPositionHandler {
	
public :

	// execute packet's handler
	static void execute(GCSetPosition* pPacket, Player* player) ;
};

#endif
