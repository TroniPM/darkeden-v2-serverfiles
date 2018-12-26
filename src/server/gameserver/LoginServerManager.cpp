//////////////////////////////////////////////////////////////////////
//
// Filename    : LoginServerManager.cpp
// Written By  : Reiot
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "LoginServerManager.h"
#include "Properties.h"
#include "LogClient.h"
#include "Assert.h"
#include "TimeChecker.h"

#include "ThreadManager.h"
#include "ThreadPool.h"

#include "Datagram.h"
#include "DatagramPacket.h"

#include <unistd.h>
#include "DB.h"
#include "Timeval.h"

//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
LoginServerManager::LoginServerManager () 
	
: m_pDatagramSocket(NULL)
{
	__BEGIN_TRY

	m_Mutex.setName("LoginServerManager");

	// create datagram server socket
	while (true)
	{
		try
		{
			m_pDatagramSocket = new DatagramSocket(g_pConfig->getPropertyInt("GameServerUDPPort") );
			break;
		}
		catch ( BindException& be )
		{
			SAFE_DELETE( m_pDatagramSocket );
			cout << "LoginServerManager(" << g_pConfig->getPropertyInt("GameServerUDPPort") << ") : " << be.toString() << endl;
			sleep(1);
		}
	}

//	m_pDatagramSocket = new DatagramSocket(g_pConfig->getPropertyInt("GameServerUDPPort"));

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////
LoginServerManager::~LoginServerManager () 
	
{
	__BEGIN_TRY

	SAFE_DELETE(m_pDatagramSocket);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
// stop thread
//////////////////////////////////////////////////////////////////////
void LoginServerManager::stop () 
	
{
	__BEGIN_TRY

	throw UnsupportedError(__PRETTY_FUNCTION__);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
// main method
//////////////////////////////////////////////////////////////////////
void LoginServerManager::run () 
	throw ()
{
	try 
	{
		string host     = g_pConfig->getProperty("DB_HOST");
		string db       = g_pConfig->getProperty("DB_DB");
		string user     = g_pConfig->getProperty("DB_USER");
		string password = g_pConfig->getProperty("DB_PASSWORD");
		uint port		= 0;
		if ( g_pConfig->hasKey("DB_PORT") )
			port = g_pConfig->getPropertyInt("DB_PORT");

		Connection* pConnection = new Connection(host, db, user, password, port);
		g_pDatabaseManager->addConnection((int)Thread::self(), pConnection);
		cout << "************************************************************************" << endl;
		cout << "************************************************************************" << endl;
		cout << "************************************************************************" << endl;
		cout << "************************************************************************" << endl;
	    cout << "OPEN LOGIN DB" << endl;
		cout << "************************************************************************" << endl;
		cout << "************************************************************************" << endl;
		cout << "************************************************************************" << endl;

		Timeval dummyQueryTime;
		getCurrentTime( dummyQueryTime );

		while (true) 
		{
	        usleep(100);

			Datagram*       pDatagram       = NULL;
			DatagramPacket* pDatagramPacket = NULL;

			try 
			{
				// �����ͱ׷� ��ü�� �������.
				pDatagram = m_pDatagramSocket->receive();

				if (pDatagram!=NULL)	// �Ϻ�exception����. by sigi. 2002.5.17
				{
					//cout << "[Datagram] " << pDatagram->getHost() << ":" << pDatagram->getPort() << endl;
					pDatagram->read(pDatagramPacket);

					if (pDatagramPacket!=NULL)
					{
						//cout << "[DatagramPacket] " << pDatagram->getHost() << ":" << pDatagram->getPort() << endl;
						// ����� �����ͱ׷� ��Ŷ ��ü�� �����Ѵ�.
						__ENTER_CRITICAL_SECTION(m_Mutex)

						pDatagramPacket->execute(NULL);

						__LEAVE_CRITICAL_SECTION(m_Mutex)

						// �����ͱ׷� ��Ŷ ��ü�� �����Ѵ�.
						SAFE_DELETE(pDatagramPacket);
					}
			
					// �����ͱ׷� ��ü�� �����Ѵ�.
					SAFE_DELETE(pDatagram);
				}
			} 
			catch (ProtocolException & pe) 
			{
				cerr << "----------------------------------------------------------------------" << endl;
				cerr << "GameServerManager::run Exception Check(ProtocolException)" << endl;
				cerr << pe.toString() << endl;
				cerr << "----------------------------------------------------------------------" << endl;
				SAFE_DELETE(pDatagramPacket);
				SAFE_DELETE(pDatagram);

				// ������ ��ſ��� �������� ������ �߻��ϸ�, 
				// ���α׷��� �����̰ų� ��ŷ �õ��̴�.
				// �ϴ��� ���ڸ��� �ش�ǹǷ�.. ������ �����Ѵ�.
				//throw Error(pe.toString());

				filelog("LOGINSERVERMANAGER.log", "LoginServerManager::run() 1 : %s", pe.toString().c_str());
			} 
			catch (ConnectException & ce) 
			{
				cerr << "----------------------------------------------------------------------" << endl;
				cerr << "GameServerManager::run Exception Check(ConnectException)" << endl;
				cerr << ce.toString() << endl;
				cerr << "----------------------------------------------------------------------" << endl;
				SAFE_DELETE(pDatagramPacket);
				SAFE_DELETE(pDatagram);

				// ����.. ���� �̰�..
				// �ϴ� ������..
				//throw Error(ce.toString());

				filelog("LOGINSERVERMANAGER.log", "LoginServerManager::run() 2 : %s", ce.toString().c_str());
			} 
			catch (Throwable & t) 
			{
				cerr << "----------------------------------------------------------------------" << endl;
				cerr << "GameServerManager::run Exception Check(Throwable)" << endl;
				cerr << t.toString() << endl;
				cerr << "----------------------------------------------------------------------" << endl;
				SAFE_DELETE(pDatagramPacket);
				SAFE_DELETE(pDatagram);

				filelog("LOGINSERVERMANAGER.log", "LoginServerManager::run() 3 : %s", t.toString().c_str());
			}

			usleep(100);

			Timeval currentTime;
			getCurrentTime(currentTime);

			if (dummyQueryTime < currentTime)
			{
				g_pDatabaseManager->executeDummyQuery( pConnection );

				// 1�ð� ~ 1�ð� 30�� ���̿��� dummy query �ð��� �����Ѵ�.
				// timeout�� ���� �ʰ� �ϱ� ���ؼ��̴�.
				dummyQueryTime.tv_sec += (60+rand()%30) * 60;
			}

			// Ÿ�� üĿ ������Ʈ
			// ClientManager ������ ����� �� ClientManager �� ���� ���� ���
			// ���� �����Ƿ� ���⿡ �߰�
			g_pTimeChecker->heartbeat();
		}
	} 
	catch (Throwable & t) 
	{
		filelog("LOGINSERVERMANAGER.log", "LoginServerManager::run() 4 : %s", t.toString().c_str());

		cerr << t.toString() << endl;
	}
}

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void LoginServerManager::sendDatagram (Datagram* pDatagram)
	throw (ProtocolException , Error)
{
	__BEGIN_TRY

    m_pDatagramSocket->send(pDatagram);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
// send datagram packet to login server
//////////////////////////////////////////////////////////////////////
void LoginServerManager::sendPacket (const string& host , uint port , DatagramPacket* pPacket)
	throw (ProtocolException , Error)
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	try 
	{
		// �����ͱ׷� ��ü�� �ϳ� �ΰ�, ������ peer �� ȣ��Ʈ�� ��Ʈ�� �����Ѵ�.
		Datagram datagram;

		datagram.setHost(host);
		datagram.setPort(port);

		// �����ͱ׷� ��Ŷ�� �����ͱ׷��� ����ִ´�.
		datagram.write(pPacket);

		// �����ͱ׷� ������ ���ؼ� �����ͱ׷��� �����Ѵ�.
		m_pDatagramSocket->send(&datagram);
	} 
	catch (Throwable & t) 
	{
        //cerr << "====================================================================" << endl;
		//cerr << t.toString() << endl;
		//cerr << "====================================================================" << endl;
	}

	__END_DEBUG
	__END_CATCH
}

// global variable definition
LoginServerManager* g_pLoginServerManager = NULL;
