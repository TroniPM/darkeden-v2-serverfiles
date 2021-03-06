//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGMove.h 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_MOVE_H__
#define __CG_MOVE_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////
//
// class CGMove;
//
//////////////////////////////////////////////////////////////////////

class CGMove : public Packet {

public:
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) ;
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID()  { return PACKET_CG_MOVE; }
	
	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static CGMovePacketSize 를 정의해서 리턴하라.
	PacketSize_t getPacketSize()  { return szCoord + szCoord + szDir; }

	// get packet name
	string getPacketName()  { return "CGMove"; }
	
	// get packet's debug string
	string toString() ;
	
public:

	// get/set X Coordicate
	Coord_t getX()  { return m_X; }
	void setX(Coord_t x)  { m_X = x; }

	// get/set Y Coordicate
	Coord_t getY()  { return m_Y; }
	void setY(Coord_t y)  { m_Y = y; }

	// get/set Direction
	Dir_t getDir()  { return m_Dir; }
	void setDir(Dir_t dir)  { m_Dir = dir; }
	
private :
	
	Coord_t m_X;			// X 좌표
	Coord_t m_Y;			// Y 좌표
	Dir_t m_Dir;			// 방향

};


//////////////////////////////////////////////////////////////////////
//
// class CGMoveFactory;
//
// Factory for CGMove
//
//////////////////////////////////////////////////////////////////////

class CGMoveFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket()  { return new CGMove(); }

	// get packet name
	string getPacketName()  { return "CGMove"; }
	
	// get packet id
	PacketID_t getPacketID()  { return Packet::PACKET_CG_MOVE; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static CGMovePacketSize 를 정의해서 리턴하라.
	PacketSize_t getPacketMaxSize()  { return szCoord + szCoord + szDir; }

};


//////////////////////////////////////////////////////////////////////
//
// class CGMoveHandler;
//
//////////////////////////////////////////////////////////////////////

class CGMoveHandler {
	
public:

	// execute packet's handler
	static void execute(CGMove* pPacket, Player* player) ;
};

#endif
