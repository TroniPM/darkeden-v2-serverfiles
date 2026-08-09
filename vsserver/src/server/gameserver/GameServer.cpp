//////////////////////////////////////////////////////////////////////////////
// Filename    : GameServer.cpp 
// Written By  : reiot@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#include <time.h>
#include <signal.h>
#include <unistd.h>

#include "GameServer.h"
#include "Assert.h"
#include "ThreadManager.h"
#include "ClientManager.h"
#include "ObjectManager.h"
#include "LoginServerManager.h"
#include "SharedServerManager.h"
#include "LogClient.h"
#include "SystemAPI.h"

#include "PacketFactoryManager.h"
#include "PacketValidator.h"
#include "DatabaseManager.h"
#include "GameServerInfoManager.h"
#include "SharedServerManager.h"
#include "BillingPlayerManager.h"

#include "chinabilling/CBillingInfo.h"
#ifdef __CONNECT_CBILLING_SYSTEM__
	#include "chinabilling/CBillingPlayerManager.h"
#endif

#include "mofus/Mofus.h"
#ifdef __MOFUS__
	#include "mofus/MPlayerManager.h"
	#include "mofus/MPacketManager.h"
#endif

#include "SMSServiceThread.h"
#include "GDRLairManager.h"


////////////////////////////////////////////////////////////////////////////////
// constructor
////////////////////////////////////////////////////////////////////////////////

GameServer::GameServer ()
	throw (Error)
{
	__BEGIN_TRY
	
	try 
	{
		// create database manager
		g_pDatabaseManager = new DatabaseManager();

		// create object manager
		g_pObjectManager = new ObjectManager();
		
		// create packet factory manager , packet validator
		g_pPacketFactoryManager = new PacketFactoryManager();
		g_pPacketValidator = new PacketValidator();

		// create thread manager
		g_pThreadManager = new ThreadManager();

		// create login server manager
		g_pLoginServerManager = new LoginServerManager();

		// create shared server manager
		g_pSharedServerManager = new SharedServerManager();

		// create billing player manager
#ifdef __CONNECT_BILLING_SYSTEM__
		g_pBillingPlayerManager = new BillingPlayerManager();
#endif
	
		// create china billing player manager
#ifdef __CONNECT_CBILLING_SYSTEM__
		g_pCBillingPlayerManager = new CBillingPlayerManager();
#endif
	
#ifdef __MOFUS__
        g_pMPlayerManager = new MPlayerManager();
        g_pMPacketManager = new MPacketManager();
#endif

		// create client manager
		g_pClientManager = new ClientManager();

		// create login server manager
		g_pGameServerInfoManager = new GameServerInfoManager();
	
	} 
	catch (Throwable & t) 
	{
		//cout << t.toString() << endl;
		throw;
	}

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// destructor
// stop()�� ��ġ�� �ʰ� ���� ������ ����Ǵ� ���� üũ����� �Ѵ�.
//////////////////////////////////////////////////////////////////////////////

GameServer::~GameServer ()
	throw (Error)
{
	__BEGIN_TRY

	SAFE_DELETE(g_pClientManager);
	SAFE_DELETE(g_pObjectManager);
	SAFE_DELETE(g_pPacketValidator);
	SAFE_DELETE(g_pPacketFactoryManager);
	SAFE_DELETE(g_pLoginServerManager);
	SAFE_DELETE(g_pSharedServerManager);
#ifdef __CONNECT_BILLING_SYSTEM__
	SAFE_DELETE(g_pBillingPlayerManager);
#endif
#ifdef __CONNECT_CBILLING_SYSTEM__
	SAFE_DELETE(g_pCBillingPlayerManager);
#endif
#ifdef __MOFUS__
    SAFE_DELETE(g_pMPlayerManager);
    SAFE_DELETE(g_pMPacketManager);
#endif
	SAFE_DELETE(g_pGameServerInfoManager);
	SAFE_DELETE(g_pThreadManager);
	SAFE_DELETE(g_pDatabaseManager);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// initialize game server
//////////////////////////////////////////////////////////////////////////////

void GameServer::init ()
	 throw (Error)
{
	__BEGIN_TRY

	sysinit();
	cout << "GameServer::init() : System Initialization Success..." << endl;

	// gCurrentTime�� �����Ѵ�.
	setCurrentTime();

	// ����Ÿ���̽��Ŵ����� �ʱ�ȭ�Ѵ�.
	g_pDatabaseManager->init();
	cout << "GameServer::init() : DatabaseManager Initialization Success..." << endl;

	// ����Ÿ���̽��Ŵ����� ���ؼ� ������Ʈ�Ŵ����� �ʱ�ȭ�Ѵ�. 
	g_pObjectManager->init();
	g_pObjectManager->load();
	cout << "GameServer::init() : ObjectManager Initialization Success..." << endl;

	// ������Ʈ �Ŵ����� ������� ������Ŵ����� �ʱ�ȭ�Ѵ�.
	// (Ư�� ZoneThreadPool�� ZoneGroupManager�� ���� �ʱ�ȭ�Ǿ�� �Ѵ�.
	g_pThreadManager->init();
	cout << "GameServer::init() : ThreadManager Initialization Success..." << endl;
		
	// Ŭ���̾�Ʈ�Ŵ����� �ʱ�ȭ�ϱ� ����, ��Ŷ���丮�Ŵ���/��Ŷ�߸������͸� �ʱ�ȭ�Ѵ�.
	g_pPacketFactoryManager->init();
	cout << "GameServer::init() : PacketFactoryManager Initialization Success..." << endl;

	g_pPacketValidator->init();
	cout << "GameServer::init() : PacketValidator Initialization Success..." << endl;

	// ���� ������ ��� �غ� ����.
	g_pLoginServerManager->init();
	cout << "GameServer::init() : LoginServerManager Initialization Success..." << endl;
	
	// shared server ���� ��� �غ� ����.
	g_pSharedServerManager->init();
	cout << "GameServer::init() : SharedServerManager Initialization Success..." << endl;

#ifdef __CONNECT_BILLING_SYSTEM__
	// shared server ���� ��� �غ� ����.
	g_pBillingPlayerManager->init();
	cout << "GameServer::init() : BillingPlayerManager Initialization Success..." << endl;
#endif

#ifdef __CONNECT_CBILLING_SYSTEM__
	// china billing server ���� ��� �غ� ����.
	g_pCBillingPlayerManager->init();
	cout << "GameServer::init() : CBillingPlayerManager Initialization Success..." << endl;
#endif

#ifdef __MOFUS__
    g_pMPacketManager->init();
    cout << "GameServer::init() : MPacketManager Initialization Success..." << endl;

    g_pMPlayerManager->init();
    cout << "GameServer::init() : MPlayerManager Initialization Success..." << endl;
#endif

	g_pGameServerInfoManager->init();
	cout << "GameServer::init() : GameServerInfoManager Initialization Success..." << endl;

	// ������ �غ� ���� ���� ���� Ŭ���̾�Ʈ�Ŵ����� �ʱ�ȭ�����ν�,
	// ��Ʈ��ŷ�� ����Ѵ�.
	g_pClientManager->init();
	cout << "GameServer::init() : ClientManager Initialization Success..." << endl;
	
	// �ʱ�ȭ�� ���� ����, �ܼ� ����� ���߰� ��׶���� ����.
	//goBackground();

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// start game server
//////////////////////////////////////////////////////////////////////////////

void GameServer::start ()
	 throw (Error)
{
	__BEGIN_TRY
		
	cout << ">>> STARTING THREAD MANAGER..." << endl;
	g_pThreadManager->start();
	
	cout << ">>> STARTING LOGIN SERVER MANAGER..." << endl;
	g_pLoginServerManager->start();

	cout << ">>> STARTING SHARED SERVER MANAGER..." << endl;
	g_pSharedServerManager->start();

#ifdef __CONNECT_BILLING_SYSTEM__
	cout << ">>> STARTING BILLING PLAYER MANAGER..." << endl;
	g_pBillingPlayerManager->start();
#endif

#ifdef __CONNECT_CBILLING_SYSTEM__
	cout << ">>> STARTING CBILLING PLAYER MANAGER..." << endl;
	g_pCBillingPlayerManager->start();
#endif

#ifdef __MOFUS__
    g_pMPlayerManager->start();
    cout << ">>> STARTING MOFUS PLAYER MANAGER..." << endl;
#endif
	
	//add by zdj
	//cout << ">>> STARTING SMS SERVICE THREAD..." << endl;
	//SMSServiceThread::Instance().start();

//	cout << ">>> STARTING Gilles De Rais Lair Manager THREAD..." << endl;
	GDRLairManager::Instance().init();
	GDRLairManager::Instance().start();

	// Ŭ���̾�Ʈ �Ŵ����� �����Ѵ�.
	// *Reiot's Notes*
	// ���� ���߿� ����Ǿ�� �Ѵ�. �ֳ��ϸ� ��Ƽ���������� �ƴ�
	// ���ѷ����� ���� �Լ��̱� �����̴�. ���� �� ������ �ٸ� �Լ���
	// ȣ���� ���, ������ ������ �ʴ���(�� ������ �߻����� �ʴ���)
	// ������� �ʴ´�.	
	cout << ">>> ALL INITIALIZATIONS ARE COMPLETED SUCCESSFULLY." << endl;
	cout << ">>> STARTING ClientManager->start() INFINITE LOOP..." << endl;

	log(LOG_SYSTEM, "", "", "Game Server Started");

	// �׽�Ʈ by sigi. 2002.12.26
	// NOTA (2026-08-07): a chamada testGameServer() foi REMOVIDA porque a lib
	// de testes (libGameServerTest.a) não é mais linkada no gameserver — o
	// libcppunit.a da imagem woody tem ABI incompatível (std::string nativa
	// vs _STL::basic_string do STLport) e causa undefined reference no link.
	// Os testes cppunit não são usados em runtime; para rodá-los seria preciso
	// recompilar o cppunit com STLport e religar -lGameServerTest.

	try {

		g_pClientManager->start();

	} catch (Throwable& t) {
		filelog("GameServerError.txt", "%s", t.toString().c_str());
		throw;
	}

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// stop game server
//
// stop ������ �����ϵ��� ����. ���� ������ ���� �ִ� �Ŵ�������
// stop ���Ѿ� �Ѵ�. ���� �ݴ��� ������ stop ��ų ��� null pointer
// ���� ������ �߻��� �� �ִ�.
//
// ����, ������ ���� �Ŵ������� �����ؾ� �Ѵ�.
//////////////////////////////////////////////////////////////////////////////

void GameServer::stop ()
	 throw (Error)
{
	__BEGIN_TRY
		
	//
	// stop client manager
	//
	// ���� ���� Ŭ���̾�Ʈ �Ŵ����� ������Ŵ���ν� ���̻� �� ������ 
	// ���� �ʵ��� �Ѵ�.
	//
	g_pClientManager->stop();
	
	//
	// stop thread manager
	//
	// �״���, ������Ŵ����� ���������ν� ������ ����ڵ��� ���̻� ó������
	// �ʰ� ���� �������� �ѾƳ���. �̶� ������ �Ŵ����� ���� ������Ǯ����
	// stop�� �����Ҷ� �����ϰ� �� �Ǿ�� �Ѵ�.
	//
	g_pThreadManager->stop();
	
	//
	// stop object manager
	//
	// ���� ��� ����ڵ��� ������ ����Ǿ����Ƿ�, ���� �� �� ���� ���� ����
	// ȯ����� ����Ÿ���̽��� �����ϵ��� �Ѵ�.
	//
	//g_pObjectManager->save();

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// �ý��� ������ �ʱ�ȭ
//////////////////////////////////////////////////////////////////////////////

void GameServer::sysinit()
	throw (Error)
{
	__BEGIN_TRY

	// rand() �� ���� �ʱ�ȭ
	srand(time(0));

	signal(SIGPIPE , SIG_IGN);	// �̰Ŵ� ���� �߻��� ��
	signal(SIGALRM , SIG_IGN);	// �˶� �ϴ� ���� ����, ���ǻ�
	signal(SIGCHLD , SIG_IGN);	// fork �ϴ� ���� ����, ���ǻ�

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// ���߿� �ַܼ� ����� �ʿ䰡 ������ ��ŭ �������� �Ǹ�, 
// �� �Լ��� ȣ���ϵ��� �Ѵ�.
//////////////////////////////////////////////////////////////////////////////

void GameServer::goBackground ()
	throw (Error)
{
	__BEGIN_TRY

	int forkres = SystemAPI::fork_ex();

	if (forkres == 0) {
		// case of child process
		close(0);
		close(1);
		close(2);
	} else {
		// case of parent process
		exit(0);
	}

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// global variable declaration
//////////////////////////////////////////////////////////////////////////////
GameServer* g_pGameServer = NULL;
