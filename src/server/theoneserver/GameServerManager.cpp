//////////////////////////////////////////////////////////////////////
//
// Filename    : GameServerManager.cpp
// Written By  : Reiot
// Description :
//
//////////////////////////////////////////////////////////////////////

#include "GameServerManager.h"
#include "Properties.h"
#include "Datagram.h"
#include "DatagramPacket.h"
#include <unistd.h>
#include "DB.h"
#include "Properties.h"

#include "Lpackets/LGKickCharacter.h"

//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
GameServerManager::GameServerManager () 
	throw ( Error )
: m_pDatagramSocket(NULL)
{
	__BEGIN_TRY

	// create datagram server socket
	m_pDatagramSocket = new DatagramSocket(g_pConfig->getPropertyInt("TheOneServerUDPPort") );

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////
GameServerManager::~GameServerManager () 
	throw ( Error )
{
	__BEGIN_TRY

	SAFE_DELETE( m_pDatagramSocket );

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
// main method
//////////////////////////////////////////////////////////////////////
void GameServerManager::run () 
	throw (Error)
{
	try 
	{
		string host     = g_pConfig->getProperty("DB_HOST");
		string db       = g_pConfig->getProperty("DB_NAME");
		string user     = g_pConfig->getProperty("DB_USER");
		string password = g_pConfig->getProperty("DB_PASSWORD");

		Connection* pConnection = new Connection(host, db, user, password);
		g_pDatabaseManager->addConnection((int)Thread::self(), pConnection);

		while ( m_bRunning ) 
		{
			Datagram*       pDatagram       = NULL;
			DatagramPacket* pDatagramPacket = NULL;
				
			try 
			{
				// �����ͱ׷� ��ü�� �������.
				cout << "wait recv.." << endl;
				pDatagram = m_pDatagramSocket->receive();

				cout << "recved.." << endl;
				if (pDatagram!=NULL)	// �Ϻ� exception����. by sigi. 2002.5.17
				{
					// �����ͱ׷� ��Ŷ ��ü�� �������.
					pDatagram->read( pDatagramPacket );

					if (pDatagramPacket!=NULL)
					{
						// ����� �����ͱ׷� ��Ŷ ��ü�� �����Ѵ�.
						pDatagramPacket->execute(NULL);

						// �����ͱ׷� ��Ŷ ��ü�� �����Ѵ�.
						SAFE_DELETE(pDatagramPacket);
						pDatagramPacket = NULL;
					}

					// �����ͱ׷� ��ü�� �����Ѵ�.
					SAFE_DELETE(pDatagram);
					pDatagram = NULL;
				}
			} 
			catch ( ProtocolException & pe ) 
			{
				cout << "GameServerManager::run Exception Check(ProtocolException)" << endl;
				cout << pe.toString() << endl;

				// ������ ��ſ��� �������� ������ �߻��ϸ�, 
				// ���α׷��� �����̰ų� ��ŷ �õ��̴�.
				// �ϴ��� ���ڸ��� �ش�ǹǷ�.. ������ �����Ѵ�.
				//throw Error( pe.toString() );
				SAFE_DELETE(pDatagramPacket);
				SAFE_DELETE(pDatagram);
			} 
			catch ( ConnectException & ce ) 
			{
				cout << "GameServerManager::run Exception Check(ConnectException)" << endl;
				cout << ce.toString() << endl;

				// ����.. ���� �̰�..
				// �ϴ� ������..
				//throw Error( ce.toString() );
				SAFE_DELETE(pDatagramPacket);
				SAFE_DELETE(pDatagram);
			}
			catch ( Throwable & t )
			{
				cout << "GameServerManager::run Exception Check(ConnectException)" << endl;
				cout << t.toString() << endl;
				SAFE_DELETE(pDatagramPacket);
				SAFE_DELETE(pDatagram);
			}
			usleep(100);
			


		}

		cout << "GameServerManager thread exiting... " << endl;
		//::exit(1);
		//
		
	} 
	catch ( Throwable & t ) 
	{
		cout << "GameServerManager thread exiting... : " << t.toString() << endl;
	}
}


//////////////////////////////////////////////////////////////////////
// send datagram to datagram-socket
//////////////////////////////////////////////////////////////////////
void GameServerManager::sendDatagram ( Datagram * pDatagram )
	throw ( ConnectException , Error )
{
	__BEGIN_TRY

	try 
	{
		m_pDatagramSocket->send( pDatagram );
	} 
	catch ( ConnectException & t ) 
	{
		cout << "GameServerManager::sendDatagram Exception Check!!" << endl;
		cout << t.toString() << endl;
		throw ConnectException( "GameServerManager::sendDatagram ������ ������");
	}

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// send datagram-packet to datagram-socket
//////////////////////////////////////////////////////////////////////
void GameServerManager::sendPacket ( string host , uint port , DatagramPacket * pPacket )
	throw ( ConnectException , Error )
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	try {

//	try 
//	{
		// �����ͱ׷� ��ü�� �ϳ� �ΰ�, ������ peer �� ȣ��Ʈ�� ��Ʈ�� �����Ѵ�.
		Datagram datagram;

		datagram.setHost(host);
		datagram.setPort(port);

		// �����ͱ׷� ��Ŷ�� �����ͱ׷��� ����ִ´�.
		datagram.write(pPacket);

		// �����ͱ׷� ������ ���ؼ� �����ͱ׷��� �����Ѵ�.
		m_pDatagramSocket->send( &datagram );
//	}
//	catch ( ConnectException & t ) 
//	{
//		cout << "GameServerManager::sendDatagram Exception Check!!" << endl;
//		cout << t.toString() << endl;
//		throw ConnectException( "GameServerManager::sendDatagram ������ ������");
//	}

	} catch ( Throwable & t ) {
		cout << "====================================================================" << endl;
		cout << t.toString() << endl;
		cout << "====================================================================" << endl;
	}

	__END_DEBUG
	__END_CATCH
}


// global variable definition
GameServerManager * g_pGameServerManager = NULL;
