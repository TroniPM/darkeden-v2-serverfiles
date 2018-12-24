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
    void read ( SocketInputStream & iStream ) throw ( ProtocolException , Error );
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write ( SocketOutputStream & oStream ) const throw ( ProtocolException , Error );

	// execute packet's handler
	void execute ( Player * pPlayer ) throw ( ProtocolException , Error );

	// get packet id
	PacketID_t getPacketID () const throw () { return PACKET_CG_VERIFY_TIME; }
	
	// get packet's body size
	PacketSize_t getPacketSize () const throw () { return 0; }

	// get packet name
	string getPacketName () const throw () { return "CGVerifyTime"; }
	
	// get packet's debug string
	string toString () const throw ();

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
	Packet * createPacket () throw () { return new CGVerifyTime(); }

	// get packet name
	string getPacketName () const throw () { return "CGVerifyTime"; }
	
	// get packet id
	PacketID_t getPacketID () const throw () { return Packet::PACKET_CG_VERIFY_TIME; }

	// get packet's max body size
	// message �� �ִ� ũ�⿡ ���� ������ �ʿ��ϴ�.
	PacketSize_t getPacketMaxSize () const throw () { return 0; }

};


//////////////////////////////////////////////////////////////////////
//
// class CGVerifyTimeHandler;
//
//////////////////////////////////////////////////////////////////////

class CGVerifyTimeHandler {

public :

	// execute packet's handler
	static void execute ( CGVerifyTime * pPacket , Player * pPlayer ) throw ( ProtocolException , Error );

	// ���ǵ��� ����ڸ� ��� �����Ѵ�.
	static void saveSpeedHackPlayer( Player* pPlayer );

};

#endif
