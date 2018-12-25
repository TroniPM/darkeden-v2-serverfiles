/////////////////////////////////////////////////////////////////////
//
// filename		: CBillingPlayer.h
//
/////////////////////////////////////////////////////////////////////

#ifndef __CBILLING_PLAYER__
#define __CBILLING_PLAYER__

// include file
#include "Types.h"
#include "Exception.h"
#include "Player.h"

// forward declaration
class Packet;
class CBillingPacketHeader;
class CBillingPacketErrorBody;

#ifdef __LOGIN_SERVER__
	class LoginPlayer;
	class CBillingPacketResponseLoginBody;
#elif defined(__GAME_SERVER__)
	class GamePlayer;
	class CBillingPacketResponseIntervalValidationBody;
	class CBillingPacketResponseLoginBody;
	class CBillingPacketResponseMinusPointBody;
	class CBillingPacketResponseMinusMinuteBody;
	class CBillingPacketResponseLogoutBody;
#endif

/////////////////////////////////////////////
// class CBillingPlayer
/////////////////////////////////////////////

class CBillingPlayer : public Player
{
public:
	// constructor & destructor
	CBillingPlayer();
	CBillingPlayer( Socket* pSocket );

	virtual ~CBillingPlayer();

public:
	
	// network read / write
	virtual void processInput() throw ( IOException, Error );
	virtual void processOutput() throw ( IOException, Error );

	// parse packet and execute handler for the packet
	virtual void processCommand() throw ( IOException, Error );

	// send packet to player's output buffer
	virtual void sendPacket( Packet* pPacket ) throw ( ProtocolException, Error );

	// disconnect
	// �÷��̾��� ������ ������ ��, ������� �����ϰ� �α׾ƿ����� ���� ��� ������ ������
	// �̹� ���� �����Ƿ� disconnect(DISCONNECTED) �� ����ϻ� ������ �����ؾ� �Ѵ�.
	// �ݸ�, �����ϰ� �α׾ƿ��� �� ��쿡�� disconnect(UNDISCONNECTED) �� ����ؾ��Ѵ�.
	virtual void disconnect( bool bDisconnected = DISCONNECTED ) throw ( InvalidProtocolException, Error );

	void setSocket( Socket* pSocket );

	// get debug string
	virtual string toString() ;

public:

#ifdef __LOGIN_SERVER__
	void sendLogin( LoginPlayer* pLoginPlayer ) throw ( ProtocolException, Error );
#elif defined(__GAME_SERVER__)
	void sendIntervalValidation() throw ( ProtocolException, Error );
	void sendLogin( GamePlayer* pGamePlayer ) throw ( ProtocolException, Error );
	void sendMinusPoint( GamePlayer* pGamePlayer ) throw ( ProtocolException, Error );
	void sendMinusMinute( GamePlayer* pGamePlayer ) throw ( ProtocolException, Error );
	void sendLogout( GamePlayer* pGamePlayer ) throw ( ProtocolException, Error );
#endif

public:
	// ��Ŷ ó���� �Լ���
	void executeError( CBillingPacketHeader& header, CBillingPacketErrorBody& body ) throw ( IOException, Error );
#ifdef __LOGIN_SERVER__
	void executeLogin( CBillingPacketHeader& header, CBillingPacketResponseLoginBody& body ) throw ( IOException, Error );
#elif defined(__GAME_SERVER__)
	void executeIntervalValidation( CBillingPacketHeader& header, CBillingPacketResponseIntervalValidationBody& body ) throw ( IOException, Error );
	void executeLogin( CBillingPacketHeader& header, CBillingPacketResponseLoginBody& body ) throw ( IOException, Error );
	void executeMinusPoint( CBillingPacketHeader& header, CBillingPacketResponseMinusPointBody& body ) throw ( IOException, Error );
	void executeMinusMinute( CBillingPacketHeader& header, CBillingPacketResponseMinusMinuteBody& body ) throw ( IOException, Error );
	void executeLogout( CBillingPacketHeader& header, CBillingPacketResponseLogoutBody& body ) throw ( IOException, Error );
#endif

#ifdef __GAME_SERVER__
	// DB�� packet �α� �����
	void logPacket( CBillingPacketHeader* header, CBillingPacketResponseLoginBody* login, CBillingPacketResponseMinusPointBody* point, CBillingPacketResponseLogoutBody* logout, CBillingPacketErrorBody* error );
#endif

public:
#ifdef __GAME_SERVER__
	void checkSessionID( CBillingPacketHeader& header, GamePlayer* pGamePlayer ) throw ( IOException, Error );
#endif
};

#endif

