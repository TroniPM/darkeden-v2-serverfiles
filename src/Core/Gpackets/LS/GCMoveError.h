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
	GCMoveError()  {}
	GCMoveError(Coord_t x, Coord_t y)  : m_X(x), m_Y(y) {}
	

public :

    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) ;
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

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
	void setX(Coord_t x)  { m_X = x; }
	
	// get/set Y
	Coord_t getY()  { return m_Y; }
	void setY(Coord_t y)  { m_Y = y ; }

	void setXY(Coord_t x, Coord_t y)  { m_X = x; m_Y = y ; }

private : 

	Coord_t m_X;   // 현재 X 좌표
	Coord_t m_Y;   // 현재 Y 좌표

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
	Packet* createPacket()  { return new GCMoveError(); }

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
	static void execute(GCMoveError* pPacket, Player* pPlayer);

};

#endif
