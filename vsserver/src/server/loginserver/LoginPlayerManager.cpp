//////////////////////////////////////////////////////////////////////
//
// Filename    : LoginPlayerManager.cpp
// Written by  : reiot@ewestsoft.com
// Description : �α��� ������ Ŭ���̾�Ʈ �Ŵ���
//
//////////////////////////////////////////////////////////////////////

// include files
#include <stdio.h>
#include "LoginPlayerManager.h"
#include "Assert.h"
#include "SocketAPI.h"
#include "Socket.h"
#include "LoginPlayer.h"
#include "LogClient.h"
#include <algorithm>
#include "Properties.h"
#include "ReconnectLoginInfoManager.h"
#include "gameserver/billing/BillingInfo.h"
#include "DB.h"


//////////////////////////////////////////////////////////////////////
//
// constructor
//
// ���� �Ŵ��� ��ü�� �����ϴ� ���̴�. (�׷���, ����. - -;)
//
//////////////////////////////////////////////////////////////////////
LoginPlayerManager::LoginPlayerManager () 
	throw ( Error )
: m_pServerSocket(NULL), m_ServerFD(INVALID_SOCKET), m_MinFD(-1), m_MaxFD(-1)
{
	__BEGIN_TRY

	m_Mutex.setName("LoginPlayerManager");

	g_pReconnectLoginInfoManager = new ReconnectLoginInfoManager();

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// destructor
//
// ���� �Ŵ��� ��ü�� �����ϴ� ���̴�. (�׷���, ����. - -;)
//
//////////////////////////////////////////////////////////////////////
LoginPlayerManager::~LoginPlayerManager () 
	throw ( Error )
{
	__BEGIN_TRY

	if ( m_pServerSocket != NULL ) {
		m_pServerSocket->close();
		delete m_pServerSocket;
		m_pServerSocket = NULL;
	}

	// base class�� PlayerManager�� destructor���� ������ ��� �÷��̾����
	// ������ ����, ��ü�� �����ϹǷ� �Ű澲�� �ʾƵ� �ȴ�.
	//
    if ( g_pReconnectLoginInfoManager!= NULL ) {
		delete g_pReconnectLoginInfoManager;
		g_pReconnectLoginInfoManager = NULL;
	}

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// ���� �Ŵ��� ��ü�� �ʱ�ȭ�ϰ�, �ڽ��� �ʱ�ȭ�Ѵ�.
//
//////////////////////////////////////////////////////////////////////
void LoginPlayerManager::init ()
	throw ( Error )
{
	__BEGIN_TRY

	// ���ε�ɶ����� ��õ�
	while ( 1 )
	{
		try {
			// ���� ������ �����Ѵ�.
			m_pServerSocket = new ServerSocket( g_pConfig->getPropertyInt("LoginServerPort") );
			// ���������� ���ε�Ǹ� ������.
			break;
		} catch ( BindException & be ) {

			SAFE_DELETE( m_pServerSocket );
			cout << be.toString() << eos;
			usleep(1000);
		}
	}

	// ���� ���� ��ũ���͸� �����Ѵ�.
	m_ServerFD = m_pServerSocket->getSOCKET();

	// fd_set ���� 0 ���� �ʱ�ȭ�Ѵ�.
	FD_ZERO( &m_ReadFDs[0] );
	FD_ZERO( &m_WriteFDs[0] );
	FD_ZERO( &m_ExceptFDs[0] );

	// ���� ������ �Ҵ�.
	FD_SET( m_ServerFD , &m_ReadFDs[0] );

	// set min/max fd
	m_MaxFD = m_MinFD = m_ServerFD;

	// m_Timeout �� �ʱ�ȭ�Ѵ�.
	// ���߿��� �� �ֱ� ���� �ɼ����� ó���ϵ��� ����.
	// ZonePlayerManager�� ���ؼ� �� �����ϴ�.....
	m_Timeout[0].tv_sec = 0;
	m_Timeout[0].tv_usec = 0;

    //--------------------------------------------------------------------------------
    // Player.LogOn �� �������ش�.
    //--------------------------------------------------------------------------------
    Statement* pStmt = NULL;
    Statement* pStmt2 = NULL;
    try
    {
        pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
        pStmt2 = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		Result* pResult = pStmt->executeQuery("SELECT PlayerID from Player WHERE LogOn = 'LOGON' AND CurrentLoginServerID=%d", g_pConfig->getPropertyInt("LoginServerID"));

		// �׹濡�� ����ֵ� �������ش�.
		// ����~ by sigi 2002.5.31
		while (pResult->next())
		{
			string playerID = pResult->getString(1);

			//cout << "delete from PCRoomUserInfo " << playerID.c_str() << eos;

			pStmt2->executeQuery( "DELETE FROM PCRoomUserInfo WHERE PlayerID='%s'",
										playerID.c_str());

			//cout << "delete ok" << eos;
		}

        pStmt->executeQuery("UPDATE Player SET LogOn = 'LOGOFF' WHERE LogOn = 'LOGON' AND CurrentLoginServerID=%d", g_pConfig->getPropertyInt("LoginServerID"));

        SAFE_DELETE(pStmt);
        SAFE_DELETE(pStmt2);
    }
    catch ( SQLQueryException & sqe )
    {
        SAFE_DELETE(pStmt);
        SAFE_DELETE(pStmt2);
        throw Error(sqe.toString());
    }

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
// select()�� ����ؼ� I/O Multiplexing �� �Ѵ�.
//////////////////////////////////////////////////////////////////////
void LoginPlayerManager::select ()
	throw ( Error )
{
	__BEGIN_TRY

	__ENTER_CRITICAL_SECTION(m_Mutex)

	// m_Timeout[0] �� m_Timeout[1] ���� �����Ѵ�.
	m_Timeout[1].tv_sec  = m_Timeout[0].tv_sec;
	m_Timeout[1].tv_usec = m_Timeout[0].tv_usec;

	// m_XXXFDs[0] �� m_XXXFDs[1] ���� �����Ѵ�.
	m_ReadFDs[1]   = m_ReadFDs[0];
	m_WriteFDs[1]  = m_WriteFDs[0];
	m_ExceptFDs[1] = m_ExceptFDs[0];

	try {

		// ���� m_XXXFDs[1] �� ������ select() �� ȣ���Ѵ�.
		SocketAPI::select_ex( m_MaxFD + 1 , &m_ReadFDs[1] , &m_WriteFDs[1] , &m_ExceptFDs[1] , &m_Timeout[1] );

	} catch ( TimeoutException ) {
		// do nothing
	} catch ( InterruptedException & ie ) 
	{
		// �ñ׳��� �� ���� ����~~
		log(LOG_LOGINSERVER, "", "", ie.toString());
	}

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
// Ȥ�ø� OOB ����Ÿ�� ó���Ѵ�.
//////////////////////////////////////////////////////////////////////
void LoginPlayerManager::processExceptions ()
	throw ( Error )
{
	__BEGIN_TRY

	__ENTER_CRITICAL_SECTION(m_Mutex)

	for ( int i = m_MinFD ; i <= m_MaxFD ; i ++ ) {

		if ( FD_ISSET( i , &m_ExceptFDs[1] ) && i != m_ServerFD ) {

			Assert( m_pPlayers[i] != NULL );

			StringStream msg;
			msg << "OOB from " << m_pPlayers[i]->toString();
			log(LOG_LOGINSERVER_ERROR, "", "", msg.toString());
			cout << msg.toString() << eos;

			// ��� ���۸� �÷����Ѵ�.
			m_pPlayers[i]->disconnect(UNDISCONNECTED);

			// �÷��̾� ��ü�� �����Ѵ�.
			delete m_pPlayers[i];	

			// �÷��̾� �Ŵ������� �÷��̾ �����Ѵ�.
			deletePlayer_NOLOCKED( i );		
		}
	}

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
// ������ ��� �÷��̾���� �Է��� ������ �Է� ���ۿ� �����Ѵ�.
//////////////////////////////////////////////////////////////////////
void LoginPlayerManager::processInputs ()
	throw ( Error )
{
	__BEGIN_TRY

	__ENTER_CRITICAL_SECTION(m_Mutex)

	for ( int i = m_MinFD ; i <= m_MaxFD ; i ++ ) {

		if ( FD_ISSET( i , &m_ReadFDs[1] ) ) {

			if ( i == m_ServerFD ) {

				// ���� ������ ���, ���ο� ������ ���Դٴ� ���̴�.
				acceptNewConnection();

			} else {

				cerr << "DBG processInputs: fd=" << i << " pronto p/ leitura, player=" << (m_pPlayers[i] ? "OK" : "NULL") << endl;
				Assert( m_pPlayers[i] != NULL );

				try {

					if (m_pPlayers[i]->getSocket()->getSockError())
					{
						// �̹� ������ ���� �����̹Ƿ�, ��� ���۸� �÷������� �ʾƾ� �Ѵ�.
						m_pPlayers[i]->disconnect(DISCONNECTED);

						// �÷��̾� ��ü�� �����Ѵ�.
						delete m_pPlayers[i];	

						// �÷��̾� �Ŵ������� �÷��̾ �����Ѵ�.
						deletePlayer_NOLOCKED( i );
					}
					else
					{
						m_pPlayers[i]->processInput();
					}

				} catch ( ConnectException & ce ) {

					// Blocking �����̹Ƿ� ConnectException �� Error�� ������ � ���ܵ� �߻����� �ʴ´�.

					cerr << "DBG processInputs CATCH ConnectException: " << ce.toString() << endl;
					cout << ce.toString() << eos;
					log(LOG_LOGINSERVER_ERROR, "", ce.toString());

					// �̹� ������ ���� �����̹Ƿ�, ��� ���۸� �÷������� �ʾƾ� �Ѵ�.
					m_pPlayers[i]->disconnect(DISCONNECTED);

					// �÷��̾� ��ü�� �����Ѵ�.
					delete m_pPlayers[i];	

					// �÷��̾� �Ŵ������� �÷��̾ �����Ѵ�.
					deletePlayer_NOLOCKED( i );

				} 
			}
		}
	}

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
// ������ ��� �÷��̾���� �Է� ��Ŷ�� ó���Ѵ�.
//////////////////////////////////////////////////////////////////////
void LoginPlayerManager::processCommands ()
	throw ( Error )
{
	__BEGIN_TRY

	__ENTER_CRITICAL_SECTION(m_Mutex)

	// m_pPlayers[i] != NULL �� Ȯ���� i != m_ServerFD ���� �����Ƿ�
	// �� ������ �տ��ٰ� �д�. 

	for ( int i = m_MinFD ; i <= m_MaxFD ; i ++ ) 
	{
		if ( m_pPlayers[i] != NULL && i != m_ServerFD ) 
		{
			try 
			{

#ifdef __CONNECT_BILLING_SYSTEM__

				//LoginPlayer* pLoginPlayer = dynamic_cast<LoginPlayer*>(m_pPlayers[i]);

				// ���� ���� �ý��ۿ��� �������� �ʾҴٸ�..
				// �ѹ��� ������ �Ա�� �ɷ� ����. �ֵ��(������) ��û. by bezz. 2003.04.21
				//if (!pLoginPlayer->isBillingLoginVerified())
				//{
					//pLoginPlayer->sendBillingLogin();
				//}
#endif

				m_pPlayers[i]->processCommand();
			} 
			catch ( ProtocolException & pe ) 
			{
				//--------------------------------------------------
				// ProtocolException�� �������� 3 ������ �ִ�.
				//
				// - InvalidProtocolException : �������� ����
				// - DisconnectException : ������ �����Ŵ
				// - InsufficiendDataException : ��Ŷ�� �κ������θ� ��������
				//
				// �� ��� Ŭ���̾�Ʈ���� ������ ���ӵǾ� �ִ� ����
				// �̹Ƿ�, disconnect�� UNDISCONNECTED �Ķ���͸� ����ؼ� 
				// ��� ���۸� �÷�������� �Ѵ�. 
				//
				//--------------------------------------------------
			
				cerr << "DBG processCommands CATCH ProtocolException: " << pe.toString() << endl;
				cout << pe.toString() << eos;
				log(LOG_LOGINSERVER_ERROR, "", "", pe.toString());

				m_pPlayers[i]->disconnect(UNDISCONNECTED);

				// �÷��̾� ��ü�� �����Ѵ�.
				delete m_pPlayers[i];

				// �÷��̾� �Ŵ������� �÷��̾ �����Ѵ�.
				deletePlayer_NOLOCKED(i);
			}
			// �輺�ο� ���� �߰�...
			catch (ConnectException &ce)
			{
				cout << ce.toString() << eos;
				log(LOG_LOGINSERVER_ERROR, "", "", ce.toString());

				m_pPlayers[i]->disconnect(DISCONNECTED);

				// �÷��̾� ��ü�� �����Ѵ�.
				delete m_pPlayers[i];

				// �÷��̾� �Ŵ������� �÷��̾ �����Ѵ�.
				deletePlayer_NOLOCKED(i);
			}
		}
	}

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
// ������ ��� �÷��̾���� ����� Ŭ���̾�Ʈ�� �����Ѵ�.
//////////////////////////////////////////////////////////////////////
void LoginPlayerManager::processOutputs ()
	throw ( Error )
{
	__BEGIN_TRY

	__ENTER_CRITICAL_SECTION(m_Mutex)

	for ( int i = m_MinFD ; i <= m_MaxFD ; i ++ ) {

		if ( FD_ISSET( i , &m_WriteFDs[1] ) && i != m_ServerFD ) {

			Assert( m_pPlayers[i] != NULL );

			try {

				m_pPlayers[i]->processOutput();

			} catch ( ConnectException & ce ) {	

				cout << ce.toString() << eos;
				log(LOG_LOGINSERVER_ERROR, "", "", ce.toString());

				// �̹� ������ ���� �����̹Ƿ�, ��� ���۸� �÷������� �ʾƾ� �Ѵ�.
				m_pPlayers[i]->disconnect(DISCONNECTED);

				// �÷��̾� ��ü�� �����Ѵ�.
				delete m_pPlayers[i];	

				// �÷��̾� �Ŵ������� �÷��̾ �����Ѵ�.
				deletePlayer_NOLOCKED( i );

			} catch ( ProtocolException & pe ) {
				cout << pe.toString() << eos;
				log(LOG_LOGINSERVER_ERROR, "", "", pe.toString());

				// �̹� ������ ���� �����̹Ƿ�, ��� ���۸� �÷������� �ʾƾ� �Ѵ�.
				m_pPlayers[i]->disconnect(DISCONNECTED);

				// �÷��̾� ��ü�� �����Ѵ�.
				delete m_pPlayers[i];	

				// �÷��̾� �Ŵ������� �÷��̾ �����Ѵ�.
				deletePlayer_NOLOCKED( i );
			}

		}
	}

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	__END_CATCH
}
	

//////////////////////////////////////////////////////////////////////
//
// accept new connection
//
// select ��ݿ����� nonblocking ������ ������� �ʴ´�.
//
// �α��� ������ �⺻������ ��� ����õ��� �޾Ƶ��δ�. 
// �� BAN DB�� ��ϵ� IP�κ����� ������ �޾Ƶ����� �ʴ´�.
//
//////////////////////////////////////////////////////////////////////
void LoginPlayerManager::acceptNewConnection ()
	throw ( Error )
{
	__BEGIN_TRY

	// ����ŷ ������� connection�� ��ٸ� ���
	// ���ϵǴ� ���� ���� NULL�� �� �� ����.
	// ���� NonBlockingIOException�� �߻��� �� ����.
	Socket * client = NULL;
	
	try {
		client = m_pServerSocket->accept();
	} catch (Throwable& t) {
	}
		
	// ConnectException �� �߻��� ���ɼ��� �ִ�. (������ �߻��ߴ�.)	
	// ���� ���ο��� CE �� �߻��� ���, NULL �� �����ϱ� ������..
	// NULL �� üũ�ؼ�, ��������� �Ѵ�.
	if ( client == NULL )
		return;
		

	if (client->getSockError())
	{
		delete client;
		return;
	}

	client->setNonBlocking();

	if (client->getSockError())
	{
		delete client;
		return;
	}

	StringStream msg;
	msg << "NEW CONNECTION FROM [" << client->getHost().c_str() << ":" << client->getPort() << "]";
	log(LOG_LOGINSERVER, "", "", msg.toString());
	cerr << "DBG acceptNewConnection: NEW CONNECTION FROM " << client->getHost() << ":" << client->getPort() << endl;

	//--------------------------------------------------
	// BAN DB�� �����ؼ� ���� IP�� �ùٸ��� Ȯ���غ���.
	//--------------------------------------------------
	/*
	if ( g_pBanManager->isBanned( client->getHost() ) ) {
		client->send("You are banned. Bye~\n",23);
		client->close();
		delete client;
	}

	*/

	// set socket option ( !NonBlocking, NoLinger )
	client->setLinger(0);
		
	// Ŭ���̾�Ʈ ������ �Ķ���ͷ� ����ؼ� �÷��̾� ��ü�� �����Ѵ�.
	LoginPlayer * pPlayer = new LoginPlayer( client );

	// set player status to PLAYER_LOGON
	Assert( pPlayer->getPlayerStatus() == LPS_NONE );
	pPlayer->setPlayerStatus( LPS_BEGIN_SESSION );
		
	// LoginPlayerManager�� ����Ѵ�.
	addPlayer_NOLOCKED(pPlayer);
				
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
//
// Ư�� �÷��̾ �Ŵ����� �߰��Ѵ�.
//
// �α��� ���������� �÷��̾� �迭�� ���ؼ� ���� �����尡 ���� �����Ƿ�
// locking �� �� �ʿ䰡 ����.
//
//////////////////////////////////////////////////////////////////////
void LoginPlayerManager::addPlayer_NOLOCKED ( Player * pPlayer ) 
	throw ( DuplicatedException , Error )
{
	__BEGIN_TRY

	PlayerManager::addPlayer(pPlayer);

	SOCKET fd = pPlayer->getSocket()->getSOCKET();

	cerr << "DBG addPlayer_NOLOCKED: fd=" << fd << " min=" << m_MinFD << " max=" << m_MaxFD << " serverFD=" << m_ServerFD << endl;

	// m_MinFD , m_MaxFD �� �������Ѵ�.
	m_MinFD = min( fd , m_MinFD );
	m_MaxFD = max( fd , m_MaxFD );

	// ��� fd_set �� fd ��Ʈ�� on ��Ų��.
	// m_XXXFDs[1] �� �������� ó�����ָ� �ȴ�.
	FD_SET( fd , &m_ReadFDs[0] );
	FD_SET( fd , &m_WriteFDs[0] );
	FD_SET( fd , &m_ExceptFDs[0] );

	__END_CATCH
}


//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
void LoginPlayerManager::addPlayer ( Player * pPlayer ) 
	throw ( DuplicatedException , Error )
{
	__ENTER_CRITICAL_SECTION(m_Mutex)

		addPlayer_NOLOCKED(pPlayer);

	__LEAVE_CRITICAL_SECTION(m_Mutex)
}


//--------------------------------------------------------------------------------
//
// Ư�� �÷��̾ �Ŵ������� �����Ѵ�.
//
// �α��� ���������� �÷��̾� �迭�� ���ؼ� ���� �����尡 ���� �����Ƿ�
// locking �� �� �ʿ䰡 ����.
//
//--------------------------------------------------------------------------------
void LoginPlayerManager::deletePlayer_NOLOCKED ( SOCKET fd ) 
	throw ( OutOfBoundException , NoSuchElementException , Error )
{
	__BEGIN_TRY

	PlayerManager::deletePlayer(fd);

	Assert( m_pPlayers[fd] == NULL );

	// m_MinFD , m_MaxFD �� �������Ѵ�.
	// fd == m_MinFD && fd == m_MaxFD �� ���� ù��° if ���� ó���ȴ�.
	if ( fd == m_MinFD ) {

		// �տ������� ���� ���� fd �� ã�´�.
		// m_MinFD �ڸ��� ���� NULL �� �Ǿ� ������ �����϶�.
		int i = m_MinFD;
		for ( ; i <= m_MaxFD ; i ++ ) {
			if ( m_pPlayers[i] != NULL || i == m_ServerFD ) {
				m_MinFD = i;	
				break;
			}
		}

		// ������ m_MinFD�� ã�� ������ ���,
		// �̶����� m_MinFD == m_MaxFD �� ����̴�.
		// �̶����� �� �� -1 �� ����������.
		if ( i > m_MaxFD )
			m_MinFD = m_MaxFD = -1;

	} else if ( fd == m_MaxFD ) {

		// �ڿ������� ���� ū fd �� ã�´�.
		// ServerFD �� ������ ��! ( ServerFD �� ��� Player �����ʹ� NULL �̴�. )
		int i = m_MaxFD;
		for ( ; i >= m_MinFD ; i -- ) {
			if ( m_pPlayers[i] != NULL || i == m_ServerFD ) {
				m_MaxFD = i;
				break;
			}
		}

		// ������ m_MinFD�� ã�� ������ ���,
		if ( i < m_MinFD ) {
			throw UnknownError("m_MinFD & m_MaxFD problem.");
		}
	}

	// ��� fd_set �� fd ��Ʈ�� off ��Ų��.
	// m_XXXFDs[1]�� ���ľ� �ϴ� ������, ���� ó������ ��ü�� �������µ���
	// ó������ Ȯ���� �ֱ� �����̴�.
	FD_CLR( fd , &m_ReadFDs[0] );
	FD_CLR( fd , &m_ReadFDs[1] );
	FD_CLR( fd , &m_WriteFDs[0] );
	FD_CLR( fd , &m_WriteFDs[1] );
	FD_CLR( fd , &m_ExceptFDs[0] );
	FD_CLR( fd , &m_ExceptFDs[1] );

	__END_CATCH
}

//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
void LoginPlayerManager::deletePlayer ( SOCKET fd ) 
	throw ( OutOfBoundException , NoSuchElementException , Error )
{
	__ENTER_CRITICAL_SECTION(m_Mutex)

		deletePlayer_NOLOCKED(fd);

	__LEAVE_CRITICAL_SECTION(m_Mutex)
}


//----------------------------------------------------------------------
// �α��� ������ ������ Ư�� �÷��̾ �˻��Ѵ�.
//----------------------------------------------------------------------
LoginPlayer * LoginPlayerManager::getPlayer_NOLOCKED ( const string & id ) const
	throw ( NoSuchElementException , Error )
{
	__BEGIN_TRY

	LoginPlayer * pLoginPlayer = NULL;

	//cout << "m_MinFD : " << m_MinFD << eos;
	//cout << "m_MaxFD : " << m_MaxFD << eos;

	for ( int i = m_MinFD ; i <= m_MaxFD ; i ++ ) 
	{
		if ( m_pPlayers[i] != NULL ) 
		{
			//cout << "[" << i << "] : " << m_pPlayers[i]->toString() << eos;
			//cout << "[" << i << "] : " << m_pPlayers[i]->getID().c_str() << eos;

			if ( m_pPlayers[i]->getID() == id ) 
			{
				pLoginPlayer = dynamic_cast<LoginPlayer*>(m_pPlayers[i]);
				//cout << "Found OK" << eos;
				break;
			}
		}
	}

	if ( pLoginPlayer == NULL ) throw NoSuchElementException("�׷� ���̵� ���� �÷��̾�� �������� �ʽ��ϴ�.");

	return pLoginPlayer;

	__END_CATCH
}


//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
LoginPlayer * LoginPlayerManager::getPlayer ( const string & id ) const
	throw ( NoSuchElementException , Error )
{

	LoginPlayer * pPlayer;

	__ENTER_CRITICAL_SECTION(m_Mutex)

	pPlayer = getPlayer_NOLOCKED(id);

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	return pPlayer;
}


//--------------------------------------------------------------------------------
// �α��� ������ ������ ��� �÷��̾�鿡�� Ư�� ��Ŷ�� �����Ѵ�.
//--------------------------------------------------------------------------------
void LoginPlayerManager::broadcastPacket ( Packet * pPacket )
	throw ( Error )
{
	__BEGIN_TRY

	for ( int i = m_MinFD ; i <= m_MaxFD ; i ++ ) {
		if ( m_pPlayers[i] != NULL ) {
			m_pPlayers[i]->sendPacket(pPacket);
		}
	}

	__END_CATCH
}


//--------------------------------------------------------------------------------
// �α��� ������ ������ Ư�� �÷��̾�� Ư�� ��Ŷ�� ������.
//--------------------------------------------------------------------------------
void LoginPlayerManager::sendPacket ( const string & id , Packet * pPacket )
	throw ( Error )
{
	__BEGIN_TRY

	for ( int i = m_MinFD ; i <= m_MaxFD ; i ++ ) 
	{
		if ( m_pPlayers[i] != NULL ) 
		{
			//cout << "[" << i << "] ID : " << m_pPlayers[i]->getID() << eos;
			if ( m_pPlayers[i]->getID() == id ) 
			{
				m_pPlayers[i]->sendPacket(pPacket);
				break;
			}
		}
	}

	__END_CATCH
}



//////////////////////////////////////////////////////////////////////
// get debug string
//////////////////////////////////////////////////////////////////////
string LoginPlayerManager::toString () const
	throw ()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "LoginPlayerManager(nPlayers:" << size() << ")";
	return msg.toString();

	__END_CATCH
}



// global variable definition
LoginPlayerManager * g_pLoginPlayerManager = NULL;
