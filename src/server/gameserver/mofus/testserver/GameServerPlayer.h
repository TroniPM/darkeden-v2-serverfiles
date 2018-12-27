//////////////////////////////////////////////////////////////////////
// 
// Filename    : GameServerPlayer.h 
// Written by  : reiot@ewestsoft.com
// Description :
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GAME_SERVER_PLAYER_H__
#define __GAME_SERVER_PLAYER_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Player.h"

class MPacket;

//////////////////////////////////////////////////////////////////////
//
// class GameServerPlayer
//
//////////////////////////////////////////////////////////////////////

class GameServerPlayer : public Player {

public :

	// constructor
	GameServerPlayer ();
	GameServerPlayer (Socket * pSocket);
	
	// destructor
	virtual ~GameServerPlayer ();

	virtual void processInput () ;
	
	virtual void processOutput () ;
	
	// parse packet and execute handler for the packet
	virtual void processCommand () ;
	
	// disconnect
	// 플레이어의 연결을 종료할 때, 상대편이 적절하게 로그아웃하지 않을 경우 소켓의 연결이 
	// 이미 끊겨 있으므로 disconnect(DISCONNECTED) 를 사용해서 연결을 종료해야 한다. 반면, 
	// 정당하게 로그아웃을 한 경우에는 disconnect(UNDISCONNECTED) 를 사용해야 한다.
	virtual void disconnect (bool bDisconnected = DISCONNECTED) ;

	void sendPacket( MPacket* pPacket ) throw( ProtocolException, Error );
	
	// get/set socket
	//Socket* getSocket () throw () { return m_pSocket; }
	void setSocket (Socket* pSocket);

	// get/set player ID
	//string getID ()  { return m_ID; }
	//void setID (const string & id) throw () { m_ID = id; }

	// get debug string
	virtual string toString () ;
};

#endif
