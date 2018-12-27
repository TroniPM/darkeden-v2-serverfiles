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
	// �÷��̾��� ������ ������ ��, ������� �����ϰ� �α׾ƿ����� ���� ��� ������ ������
	// �̹� ���� �����Ƿ� disconnect(DISCONNECTED) �� ����ϻ� ������ �����ؾ� �Ѵ�.
	// �ݸ�, �����ϰ� �α׾ƿ��� �� ��쿡�� disconnect(UNDISCONNECTED) �� ����ؾ��Ѵ�.
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
	// ��Ŷ ó���� �Լ���
	void executeError( CBillingPacketHeader& header, CBillingPacketErrorBody& body ) ;
	void executeIntervalValidation( CBillingPacketHeader& header, CBillingPacketResponseIntervalValidationBody& body ) ;
	void executeLogin( CBillingPacketHeader& header, CBillingPacketResponseLoginBody& body ) ;
	void executeMinusPoint( CBillingPacketHeader& header, CBillingPacketResponseMinusPointBody& body ) ;
	void executeMinusMinute( CBillingPacketHeader& header, CBillingPacketResponseMinusMinuteBody& body ) ;
	void executeLogout( CBillingPacketHeader& header, CBillingPacketResponseLogoutBody& body ) ;

public:
};

#endif

