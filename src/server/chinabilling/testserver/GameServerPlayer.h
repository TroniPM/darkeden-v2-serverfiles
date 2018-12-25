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

class CBillingPacketHeader;
class CBillingPacketRequestIntervalValidationBody;
class CBillingPacketRequestLoginBody;
class CBillingPacketRequestMinusPointBody;
class CBillingPacketRequestMinusMinuteBody;
class CBillingPacketRequestLogoutBody;

//////////////////////////////////////////////////////////////////////
//
// class GameServerPlayer
//
//////////////////////////////////////////////////////////////////////

class GameServerPlayer : public Player {

public :

	// constructor
	GameServerPlayer () throw (Error);
	GameServerPlayer (Socket * pSocket) throw ( Error );
	
	// destructor
	virtual ~GameServerPlayer () throw (Error);

	virtual void processInput () throw (IOException, Error);
	
	virtual void processOutput () throw (IOException, Error);
	
	// parse packet and execute handler for the packet
	virtual void processCommand () throw (IOException, Error);
	
	// send packet to player's output buffer
	virtual void sendPacket (Packet* pPacket) throw (ProtocolException, Error);

	// disconnect
	// �÷��̾��� ������ ������ ��, ������� �����ϰ� �α׾ƿ����� ���� ��� ������ ������ 
	// �̹� ���� �����Ƿ� disconnect(DISCONNECTED) �� ����ؼ� ������ �����ؾ� �Ѵ�. �ݸ�, 
	// �����ϰ� �α׾ƿ��� �� ��쿡�� disconnect(UNDISCONNECTED) �� ����ؾ� �Ѵ�.
	virtual void disconnect (bool bDisconnected = DISCONNECTED) throw (InvalidProtocolException, Error);
	
	// get/set socket
	//Socket* getSocket () throw () { return m_pSocket; }
	void setSocket (Socket* pSocket) throw ();

	// get/set player ID
	//string getID () const throw () { return m_ID; }
	//void setID (const string & id) throw () { m_ID = id; }

	// get debug string
	virtual string toString () ;

public:
	void executeIntervalValidation( CBillingPacketHeader& header, CBillingPacketRequestIntervalValidationBody& body ) throw ( IOException, Error );
	void executeLogin( CBillingPacketHeader& header, CBillingPacketRequestLoginBody& body ) throw ( IOException, Error );
	void executeMinusPoint( CBillingPacketHeader& header, CBillingPacketRequestMinusPointBody& body ) throw ( IOException, Error );
	void executeMinusMinute( CBillingPacketHeader& header, CBillingPacketRequestMinusMinuteBody& body ) throw ( IOException, Error );
	void executeLogout( CBillingPacketHeader& header, CBillingPacketRequestLogoutBody& body ) throw ( IOException, Error );
	
protected :

	/*
	// player id
	string m_ID;
	
	// TCP client socket
	Socket* m_pSocket;
	
	// buffered socket input stream
	SocketInputStream* m_pInputStream;

	// buffered socket output stream
	SocketOutputStream* m_pOutputStream;
	*/

};

#endif
