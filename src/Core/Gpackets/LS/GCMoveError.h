//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCMoveError.h 
// Written By  : Elca
// Description :
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_MOVEError_H__
#define __GC_MOVEError_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class GCMoveError;
//
//////////////////////////////////////////////////////////////////////

class GCMoveError : public Packet {

public :

	// constructor
	GCMoveError() throw() {}
	GCMoveError(Coord_t x, Coord_t y) throw() : m_X(x), m_Y(y) {}
	

public :

    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID()  { return PACKET_GC_MOVE_ERROR; }
	
	// get packet's body size
	PacketSize_t getPacketSize()  { return szCoord + szCoord; }
	
	// get packet's name
	string getPacketName()  { return "GCMoveError"; }
	
	// get packet's debug string
	string toString() ;
	

public :

	// get/set X
	Coord_t getX()  { return m_X; }
	void setX(Coord_t x) throw() { m_X = x; }
	
	// get/set Y
	Coord_t getY()  { return m_Y; }
	void setY(Coord_t y) throw() { m_Y = y ; }

	void setXY(Coord_t x, Coord_t y) throw() { m_X = x; m_Y = y ; }

private : 

	Coord_t m_X;   // ���� X ��ǥ
	Coord_t m_Y;   // ���� Y ��ǥ

};


//////////////////////////////////////////////////////////////////////
//
// class  GCMoveErrorFactory;
//
// Factory for  GCMoveError
//
//////////////////////////////////////////////////////////////////////

class  GCMoveErrorFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket() throw() { return new GCMoveError(); }

	// get packet name
	string getPacketName()  { return "GCMoveError"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_GC_MOVE_ERROR; }

	// get packet's max body size
	PacketSize_t getPacketMaxSize()  { return szCoord + szCoord; }
	
};


//////////////////////////////////////////////////////////////////////
//
// class  GCMoveErrorHandler;
//
//////////////////////////////////////////////////////////////////////

class  GCMoveErrorHandler {

public :

	// execute packet's handler
	static void execute(GCMoveError* pPacket, Player* pPlayer) throw(Error);

};

#endif
