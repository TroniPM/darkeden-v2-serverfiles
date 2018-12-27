//////////////////////////////////////////////////////////////////////
//
// Filename    : BillingPlayerManager.cpp
// Written By  : Reiot
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "BillingPlayerManager.h"
#include "BillingPlayer.h"
#include "CommonBillingPacket.h"
#include "Properties.h"
#include "LogClient.h"
#include "Assert.h"

//#include "ThreadManager.h"
//#include "ThreadPool.h"

#include <unistd.h>
#include "DB.h"
#include "Timeval.h"

#define __BEGIN_BILLING_TRY	try {
#define __END_BILLING_CATCH	} catch ( Throwable& t )								\
				{																	\
					cout << t.toString().c_str() << endl;							\
					filelog(LOGFILE_BILLING_PLAYER, "%s", t.toString().c_str());		\
																					\
					try {															\
						SAFE_DELETE( m_pBillingPlayer );							\
					} catch (Throwable& t) {										\
						filelog(LOGFILE_BILLING_PLAYER, "(delete)%s", t.toString().c_str());	\
					}	\
				}

//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
BillingPlayerManager::BillingPlayerManager () 
	
{
	__BEGIN_TRY

	m_pBillingPlayer = NULL;

	m_Mutex.setName( "BillingPlayerManager" );

	m_bForceDisconnect = false;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////
BillingPlayerManager::~BillingPlayerManager () 
	
{
	__BEGIN_TRY

	SAFE_DELETE(m_pBillingPlayer);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
// stop thread
//////////////////////////////////////////////////////////////////////
void BillingPlayerManager::stop () 
	
{
	__BEGIN_TRY

	throw UnsupportedError();

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
// main method
//////////////////////////////////////////////////////////////////////
void BillingPlayerManager::run () 
	
{
	__BEGIN_TRY
	try {

		// Player DB�� Connection�� �ϳ� ������� �д�.
		string host     = g_pConfig->getProperty("UI_DB_HOST");
		string db 	    = "DARKEDEN";
		string user     = g_pConfig->getProperty("UI_DB_USER");
		string password = g_pConfig->getProperty("UI_DB_PASSWORD");
		uint port		= 0;
		if ( g_pConfig->hasKey("UI_DB_PORT") )
			port = g_pConfig->getPropertyInt("UI_DB_PORT");

		Connection* pDistConnection = new Connection(host, db, user, password, port);
		g_pDatabaseManager->addDistConnection(((int)Thread::self()), pDistConnection);
		cout << "******************************************************" << endl;
		cout << " THREAD CONNECT UIIRIBUTION DB - for BillingSystem" << endl;
		cout << " TID Number = " << (int)Thread::self()<< endl;
		cout << "******************************************************" << endl;

		Timeval dummyQueryTime;
		getCurrentTime( dummyQueryTime );

		Timeval disconnectCheckTime;
		getCurrentTime( disconnectCheckTime );

		const string& 	BillingServerIP 	= g_pConfig->getProperty( "BillingServerIP" );
		uint 			BillingServerPort 	= g_pConfig->getPropertyInt( "BillingServerPort" );

		bool bFirstConnection = true;

		while ( true )
		{
			usleep( 100 );

			// ����Ǿ� ���� �ʴٸ� ������ �õ��Ѵ�.
			if ( m_pBillingPlayer == NULL )
			{
				Socket* pSocket = NULL;

				try
				{
					// create socket
					pSocket = new Socket( BillingServerIP, BillingServerPort );

					// connect
					pSocket->connect();

					// make nonblocking socket
					pSocket->setNonBlocking();

					// make no-linger socket
					pSocket->setLinger(0);

					__ENTER_CRITICAL_SECTION(m_Mutex)
					m_pBillingPlayer = new BillingPlayer( pSocket );
					__LEAVE_CRITICAL_SECTION(m_Mutex)

					pSocket = NULL;

					// ������ ������ ��� Init packet�� ������.
					if (bFirstConnection)
					{
					#ifdef __GAME_SERVER__
						sendPayInit();
					#endif
						bFirstConnection = false;
					}

					cout << "connection to billingServer established -  " 
						<< BillingServerIP.c_str() << ":" << BillingServerPort << endl;
					filelog(LOGFILE_BILLING_PLAYER, "----- connection established(%s:%d) -----", BillingServerIP.c_str(), BillingServerPort);
				} 
				catch ( Throwable& t )
				{
					cout << "connect to billingServer fail - "
						<< BillingServerIP.c_str() << ":" << BillingServerPort << endl;
					filelog(LOGFILE_BILLING_PLAYER, "connection failed(%s:%d)", BillingServerIP.c_str(), BillingServerPort);

					try {
						SAFE_DELETE( pSocket );
					} catch (Throwable& t) {
						filelog(LOGFILE_BILLING_PLAYER, "[0]%s", t.toString().c_str());
					}

					__ENTER_CRITICAL_SECTION(m_Mutex)
					
					try {
							SAFE_DELETE( m_pBillingPlayer ); 
					} catch (Throwable& t) {
						filelog(LOGFILE_BILLING_PLAYER, "[1]%s", t.toString().c_str());
					}
					__LEAVE_CRITICAL_SECTION(m_Mutex)

					// ���� ���ӽõ��ð�
					usleep( 1000000 );	// 1��
				}
			}

			// ������ ����Ǿ� �ִٸ� ������� ó���Ѵ�.
			__ENTER_CRITICAL_SECTION(m_Mutex)

			if ( m_pBillingPlayer != NULL )
			{
				__BEGIN_BILLING_TRY

				if ( m_pBillingPlayer->getSocket()->getSockError() )
				{
					try {
						SAFE_DELETE( m_pBillingPlayer );
					} catch ( Throwable& t )
					{
						filelog(LOGFILE_BILLING_PLAYER, "[1]%s", t.toString().c_str());
					}
				}
				else
				{
					m_pBillingPlayer->processInput();
					m_pBillingPlayer->processOutput();
					m_pBillingPlayer->processCommand();
				}

				__END_BILLING_CATCH
			}

			__LEAVE_CRITICAL_SECTION(m_Mutex)

			// dummy query
			Timeval currentTime;
			getCurrentTime(currentTime);

			if (dummyQueryTime < currentTime)
			{
				g_pDatabaseManager->executeDummyQuery( pDistConnection );

				// 1�ð� ~ 1�ð� 30�� ���̿��� dummy query �ð��� �����Ѵ�.
				// timeout�� ���� �ʰ� �ϱ� ���ؼ��̴�.
				dummyQueryTime.tv_sec += (60+rand()%30) * 60;
			}

			if ( m_pBillingPlayer != NULL )
			{
				if ( disconnectCheckTime < currentTime )
				{
					__ENTER_CRITICAL_SECTION(m_Mutex)

					// 1�� ���� 2��° �̻��� retry �� 30���� ������ ¥����.
					if ( m_pBillingPlayer->getRetryCount() > 30 )
						m_bForceDisconnect = true;

					m_pBillingPlayer->resetRetryCount();
					m_pBillingPlayer->resetRetryValue();

					__LEAVE_CRITICAL_SECTION(m_Mutex)

					disconnectCheckTime.tv_sec += 60;
				}

				if ( m_bForceDisconnect )
				{
					m_bForceDisconnect = false;
					filelog(LOGFILE_BILLING_PLAYER, "Disconnect Force" );

					try {
						SAFE_DELETE( m_pBillingPlayer );
					} catch (Throwable& t) {
						filelog(LOGFILE_BILLING_PLAYER, "(delete)%s", t.toString().c_str());
					}
				}
			}
		}
	}
	catch (Throwable & t)
	{
		filelog("billingPlayerManager.log", "BillingPlayerManager::run() 4 : %s", t.toString().c_str());

		cerr << t.toString() << endl;
	}
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
// send packet to billing server
//////////////////////////////////////////////////////////////////////
void BillingPlayerManager::sendPacket ( Packet* pPacket )
	
{
	__BEGIN_BILLING_TRY

	__ENTER_CRITICAL_SECTION(m_Mutex)
		
	if ( m_pBillingPlayer != NULL )
	{
		m_pBillingPlayer->sendPacket( pPacket );
	}

	__LEAVE_CRITICAL_SECTION(m_Mutex)
	
	__END_BILLING_CATCH
}

//////////////////////////////////////////////////////////////////////
// ���� ������ ó�� �� �� ������.
//////////////////////////////////////////////////////////////////////
void BillingPlayerManager::sendPayInit()
	
{
	__BEGIN_BILLING_TRY
	__ENTER_CRITICAL_SECTION(m_Mutex)
		
	if ( m_pBillingPlayer != NULL )
	{
		m_pBillingPlayer->sendPayInit();
		
		// �ٷ� ����������.
		m_pBillingPlayer->processOutput();
	}

	__LEAVE_CRITICAL_SECTION(m_Mutex)
	__END_BILLING_CATCH
}

//////////////////////////////////////////////////////////////////////
// ĳ������ ���� ���¸� ������.
//////////////////////////////////////////////////////////////////////
void BillingPlayerManager::sendPayCheck( CommonBillingPacket* pPacket )
	
{
	__BEGIN_BILLING_TRY
		
	if ( m_pBillingPlayer != NULL )
	{
		m_pBillingPlayer->sendPayCheck( pPacket );
	}

	__END_BILLING_CATCH
}

//////////////////////////////////////////////////////////////////////
// ĳ���Ͱ� ���ӿ� ó�� �����Ҷ� �����°�
//////////////////////////////////////////////////////////////////////
void BillingPlayerManager::sendPayLogin( Player* pPlayer ) 
	
{
	__BEGIN_BILLING_TRY
	__ENTER_CRITICAL_SECTION(m_Mutex)
		
	if ( m_pBillingPlayer != NULL )
	{
		m_pBillingPlayer->sendPayLogin( pPlayer );
	}

	__LEAVE_CRITICAL_SECTION(m_Mutex)
	__END_BILLING_CATCH
}

//////////////////////////////////////////////////////////////////////
// ĳ���Ͱ� ���ӿ��� ������ �����°�
//////////////////////////////////////////////////////////////////////
void BillingPlayerManager::sendPayLogout( Player* pPlayer ) 
	
{
	__BEGIN_BILLING_TRY
	__ENTER_CRITICAL_SECTION(m_Mutex)
		
	if ( m_pBillingPlayer != NULL )
	{
		m_pBillingPlayer->sendPayLogout( pPlayer );
	}

	__LEAVE_CRITICAL_SECTION(m_Mutex)
	__END_BILLING_CATCH
}


// global variable definition
BillingPlayerManager* g_pBillingPlayerManager = NULL;

