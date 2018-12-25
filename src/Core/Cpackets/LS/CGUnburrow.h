//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGUnburrow.h 
// Written By  : crazydog
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_UNBURROW_H__
#define __CG_UNBURROW_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////
//
// class CGUnburrow;
//
//////////////////////////////////////////////////////////////////////

class CGUnburrow : public Packet {

public:
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID()  { return PACKET_CG_UNBURROW; }
	
	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static CGUnburrowPacketSize �� �����ؼ� �����϶�.
	PacketSize_t getPacketSize()  { return szCoord + szCoord + szDir; }

	// get packet name
	string getPacketName()  { return "CGUnburrow"; }
	
	// get packet's debug string
	string toString() ;
	
public:

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
// class CGUnburrowFactory;
//
// Factory for CGUnburrow
//
//////////////////////////////////////////////////////////////////////

class CGUnburrowFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket() throw() { return new CGUnburrow(); }

	// get packet name
	string getPacketName()  { return "CGUnburrow"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_CG_UNBURROW; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static CGUnburrowPacketSize �� �����ؼ� �����϶�.
	PacketSize_t getPacketMaxSize()  { return szCoord + szCoord + szDir; }

};


//////////////////////////////////////////////////////////////////////
//
// class CGUnburrowHandler;
//
//////////////////////////////////////////////////////////////////////

class CGUnburrowHandler {
	
public:

	// execute packet's handler
	static void execute(CGUnburrow* pPacket, Player* player) throw(ProtocolException, Error);
};

#endif
