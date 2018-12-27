//////////////////////////////////////////////////////////////////////
// 
// Filename    : BillingPlayer.h 
// Written by  : reiot@ewestsoft.com
// Description :
// 
//////////////////////////////////////////////////////////////////////

#ifndef __BILLING_PLAYER_H__
#define __BILLING_PLAYER_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Player.h"
#include "BillingInfo.h"

class CommonBillingPacket;

//////////////////////////////////////////////////////////////////////
//
// class BillingPlayer
//
//////////////////////////////////////////////////////////////////////

class BillingPlayer : public Player {

public :

	// constructor
	BillingPlayer ();
	BillingPlayer (Socket * pSocket);
	
	// destructor
	virtual ~BillingPlayer ();

	virtual void processInput () ;
	
	virtual void processOutput () ;
	
	// parse packet and execute handler for the packet
	virtual void processCommand () ;
	
	// send packet to player's output buffer
	virtual void sendPacket (Packet* pPacket);

	// disconnect
	// �÷��̾��� ������ ������ ��, ������� �����ϰ� �α׾ƿ����� ���� ��� ������ ������ 
	// �̹� ���� �����Ƿ� disconnect(DISCONNECTED) �� ����ؼ� ������ �����ؾ� �Ѵ�. �ݸ�, 
	// �����ϰ� �α׾ƿ��� �� ��쿡�� disconnect(UNDISCONNECTED) �� ����ؾ� �Ѵ�.
	virtual void disconnect (bool bDisconnected = DISCONNECTED) ;

	void setSocket ( Socket * pSocket );
	
	// get debug string
	virtual string toString () ;

public :
	void sendPayInit() throw( ProtocolException, Error );
	void sendPayCheck( CommonBillingPacket* pPacket ) throw( ProtocolException, Error );
	void sendPayLogin( Player* pPlayer ) throw( ProtocolException, Error );
	void sendPayLogout( Player* pPlayer ) throw( ProtocolException, Error );

	int getRetryCount() const { return m_RetryCount; }
	int getRetryValue() const { return m_RetryValue; }

	void resetRetryCount() { m_RetryCount = 0; }
	void resetRetryValue() { m_RetryValue = 0; }
	
protected :

	// ���� �ð��ȿ� ���� PayLogin �� ���� ����(Retry) �÷��̾� ��
	int m_RetryCount;
	// ���� �ð��ȿ� ���� PayLogin �� ���� ����(Retry) �÷��̾��� �� Retry ��
	int m_RetryValue;
};

#endif

