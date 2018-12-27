/////////////////////////////////////////////////////////////////////
//
// filename		: SBillingPlayer.h
//
/////////////////////////////////////////////////////////////////////

#ifndef __SBILLING_PLAYER__
#define __SBILLING_PLAYER__

// include file
#include "Types.h"
#include "Exception.h"
#include "Player.h"

// forward declaration
class PayUser;
class Packet;
class CBillingPacketHeader;
class CBillingPacketErrorBody;

class CBillingPacketResponseIntervalValidationBody;
class CBillingPacketResponseLoginBody;
class CBillingPacketResponseMinusPointBody;
class CBillingPacketResponseMinusMinuteBody;
class CBillingPacketResponseLogoutBody;

/////////////////////////////////////////////
// class SBillingPlayer
/////////////////////////////////////////////

class SBillingPlayer : public Player
{
public:
	// constructor & destructor
	SBillingPlayer();
	SBillingPlayer( Socket* pSocket );

	virtual ~SBillingPlayer();

public:
	
	// network read / write
	virtual void processInput() ;
	virtual void processOutput() ;

	// parse packet and execute handler for the packet
	virtual void processCommand() ;

	// send packet to player's output buffer
	virtual void sendPacket( Packet* pPacket ) ;

	// disconnect
	// 플레이어의 연결을 종료할 때, 상대편이 적절하게 로그아웃하지 않을 경우 소켓의 연결이
	// 이미 끊겨 있으므로 disconnect(DISCONNECTED) 를 사용하새 연결을 종료해야 한다.
	// 반면, 정장하게 로그아웃을 한 경우에는 disconnect(UNDISCONNECTED) 를 사용해야한다.
	virtual void disconnect( bool bDisconnected = DISCONNECTED ) ;

	void setSocket( Socket* pSocket );

	// get debug string
	virtual string toString() ;

public:
	void sendIntervalValidation() ;
	void sendLogin( PayUser* pPayUser ) ;
	void sendMinusPoint( PayUser* pPayUser ) ;
	void sendMinusMinute( PayUser* pPayUser ) ;
	void sendLogout( PayUser* pPayUser ) ;

public:
	// 패킷 처리용 함수들
	void executeError( CBillingPacketHeader& header, CBillingPacketErrorBody& body ) ;
	void executeIntervalValidation( CBillingPacketHeader& header, CBillingPacketResponseIntervalValidationBody& body ) ;
	void executeLogin( CBillingPacketHeader& header, CBillingPacketResponseLoginBody& body ) ;
	void executeMinusPoint( CBillingPacketHeader& header, CBillingPacketResponseMinusPointBody& body ) ;
	void executeMinusMinute( CBillingPacketHeader& header, CBillingPacketResponseMinusMinuteBody& body ) ;
	void executeLogout( CBillingPacketHeader& header, CBillingPacketResponseLogoutBody& body ) ;

public:
};

#endif

