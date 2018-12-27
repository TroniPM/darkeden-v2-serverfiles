//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGVerifyTime.h 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_VERIFY_TIME_H__
#define __CG_VERIFY_TIME_H__

// include files

//#ifdef __GAME_SERVER__
//#include "GamePlayer.h"
//#endif

#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class CGVerifyTime;
//
// Ŭ���̾�Ʈ�� �������� ������ VerifyTime ��Ŷ�̴�.
// ���ο� VerifyTime String ���� ����Ÿ �ʵ�� ������.
//
//////////////////////////////////////////////////////////////////////

class Player;
class GamePlayer;

class CGVerifyTime : public Packet {

public :
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read ( SocketInputStream & iStream ) ;
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write ( SocketOutputStream & oStream ) ;

	// execute packet's handler
	void execute ( Player * pPlayer ) ;

	// get packet id
	PacketID_t getPacketID ()  { return PACKET_CG_VERIFY_TIME; }
	
	// get packet's body size
	PacketSize_t getPacketSize ()  { return 0; }

	// get packet name
	string getPacketName ()  { return "CGVerifyTime"; }
	
	// get packet's debug string
	string toString () ;

private :
	
};


//////////////////////////////////////////////////////////////////////
//
// class CGVerifyTimeFactory;
//
// Factory for CGVerifyTime
//
//////////////////////////////////////////////////////////////////////

class CGVerifyTimeFactory : public PacketFactory {

public :
	
	// create packet
	Packet * createPacket ()  { return new CGVerifyTime(); }

	// get packet name
	string getPacketName ()  { return "CGVerifyTime"; }
	
	// get packet id
	PacketID_t getPacketID ()  { return Packet::PACKET_CG_VERIFY_TIME; }

	// get packet's max body size
	// message �� �ִ� ũ�⿡ ���� ������ �ʿ��ϴ�.
	PacketSize_t getPacketMaxSize ()  { return 0; }

};


//////////////////////////////////////////////////////////////////////
//
// class CGVerifyTimeHandler;
//
//////////////////////////////////////////////////////////////////////

class CGVerifyTimeHandler {

public :

	// execute packet's handler
	static void execute ( CGVerifyTime * pPacket , Player * pPlayer ) ;

	// ���ǵ��� ����ڸ� ��� �����Ѵ�.
	static void saveSpeedHackPlayer( Player* pPlayer );

};

#endif
