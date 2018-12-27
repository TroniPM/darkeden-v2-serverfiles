/////////////////////////////////////////////////////////////////////////////
//
// filename		: CBillingPlayerManager.h
//
/////////////////////////////////////////////////////////////////////////////

#ifndef __CBILLING_PLAYER_MANAGER__
#define __CBILLING_PLAYER_MANAGER__

// include files
#include "Types.h"
#include "Exception.h"
#include "Thread.h"
#include "Socket.h"
#include "Mutex.h"
#include "CBillingInfo.h"

#ifdef __LOGIN_SERVER__
	#include "LoginPlayer.h"
#elif defined(__GAME_SERVER__)
	#include "GamePlayer.h"
#endif

class CBillingPlayer;

/////////////////////////////////////////////////////
// class CBillingPlayerManager
//
// �߱� ���� ������ ����� �����ϴ� ������
/////////////////////////////////////////////////////
class CBillingPlayerManager : public Thread
{
public:
	CBillingPlayerManager();
	~CBillingPlayerManager();

public:
	void init()  {}
	void stop();
	void run();

	// ���� ���� ��Ŷ ������ �Լ�
#ifdef __LOGIN_SERVER__
	void sendLogin( LoginPlayer* pLoginPlayer ) ;
#elif defined(__GAME_SERVER__)
	bool sendLogin( GamePlayer* pGamePlayer ) ;
	void sendIntervalValidation() ;
	bool sendMinusPoint( GamePlayer* pGamePlayer ) ;
	void sendMinusMinute( GamePlayer* pGamePlayer ) ;
	void sendLogout( GamePlayer* pGamePlayer ) ;
#endif

	void setForceDisconnect( bool bForceDisconnect = true ) { m_bForceDisconnect = bForceDisconnect; }

	int getVersionNumber() ;
	int getMinusIntervalInt() ;
	string getMinusInterval() ;

private:
	CBillingPlayer*		m_pCBillingPlayer;
	mutable Mutex		m_Mutex;
	mutable Mutex		m_SendMutex;
	bool				m_bForceDisconnect;
};

// global variable declaration
extern CBillingPlayerManager* g_pCBillingPlayerManager;

#endif

