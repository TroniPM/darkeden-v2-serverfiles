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
	BillingPlayer () throw (Error);
	BillingPlayer (Socket * pSocket) throw ( Error );
	
	// destructor
	virtual ~BillingPlayer () throw (Error);

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

	void setSocket ( Socket * pSocket ) throw ();
	
	// get debug string
	virtual string toString () const throw (Error);

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

