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
	// �÷��̾��� ������ ������ ��, ������� �����ϰ� �α׾ƿ����� ���� ��� ������ ������ 
	// �̹� ���� �����Ƿ� disconnect(DISCONNECTED) �� ����ؼ� ������ �����ؾ� �Ѵ�. �ݸ�, 
	// �����ϰ� �α׾ƿ��� �� ��쿡�� disconnect(UNDISCONNECTED) �� ����ؾ� �Ѵ�.
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
