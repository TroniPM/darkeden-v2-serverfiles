//////////////////////////////////////////////////////////////////////
// 
// Filename    :  GCUnburrowOK.h 
// Written By  :  Elca
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_UNBURROW_OK_H__
#define __GC_UNBURROW_OK_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class  GCUnburrowOK;
//
// ���� �������� Ư�� ����ڰ� �������ٴ� ������ Ŭ���̾�Ʈ�� ������ 
// �� ����ϴ� ��Ŷ ��ü�̴�.(CreatureID,X,Y,DIR) �� �����Ѵ�.
//
//////////////////////////////////////////////////////////////////////

class GCUnburrowOK : public Packet {

public :

	// constructor
	GCUnburrowOK() throw() {}
	GCUnburrowOK(Coord_t x, Coord_t y, Dir_t dir) throw() : m_X(x), m_Y(y), m_Dir(dir) {}


public :
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) ;
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID()  { return PACKET_GC_UNBURROW_OK; }
	
	// get packet body size
	// *OPTIMIZATION HINT*
	// const static GCUnburrowOKPacketSize �� ����, �����϶�.
	PacketSize_t getPacketSize()  { return szCoord + szCoord + szDir; }
	
	// get packet's name
	string getPacketName()  { return "GCUnburrowOK"; }
	
	// get packet's debug string
	string toString() ;
	

public :

	// get/set X
	Coord_t getX()  { return m_X; }
	void setX(Coord_t x) throw() { m_X = x; }
	
	// get/set Y
	Coord_t getY()  { return m_Y; }
	void setY(Coord_t y) throw() { m_Y = y ; }

	// get/set Dir
	Dir_t getDir()  { return m_Dir; }
	void setDir(Dir_t dir) throw() { m_Dir = dir; }
	

private : 

	Coord_t m_X;   // ��ǥ X ��ǥ
	Coord_t m_Y;   // ��ǥ Y ��ǥ
	Dir_t m_Dir;   // ��ǥ ����

};


//////////////////////////////////////////////////////////////////////
//
// class GCUnburrowOKFactory;
//
// Factory for GCUnburrowOK
//
//////////////////////////////////////////////////////////////////////

class  GCUnburrowOKFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket() throw() { return new GCUnburrowOK(); }

	// get packet name
	string getPacketName()  { return "GCUnburrowOK"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_GC_UNBURROW_OK; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCUnburrowOKPacketSize �� ����, �����϶�.
	PacketSize_t getPacketMaxSize()  { return szCoord + szCoord + szDir; }
	
};


//////////////////////////////////////////////////////////////////////
//
// class  GCUnburrowOKHandler;
//
//////////////////////////////////////////////////////////////////////

class  GCUnburrowOKHandler {

public :

	// execute packet's handler
	static void execute( GCUnburrowOK* pPacket, Player* pPlayer) ;

};

#endif
