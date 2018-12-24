//////////////////////////////////////////////////////////////////////
//
// Filename    : ClientManager.cpp
// Written by  : reiot@ewestsoft.com
// Description : �α��� ������ Ŭ���̾�Ʈ �Ŵ���
//
//////////////////////////////////////////////////////////////////////

#include "DatabaseManager.h"
#include "ClientManager.h"
#include "Assert.h"
#include "LoginPlayerManager.h"
#include "ReconnectLoginInfoManager.h"
#include "Profile.h"
#include "PacketProfile.h"
#include "Timeval.h"
#include "Properties.h"

#include "GameWorldInfoManager.h"
#include "GameServerGroupInfoManager.h"

#ifdef __THAILAND_SERVER__
	
	#include "TimeChecker.h"

#endif

//////////////////////////////////////////////////////////////////////
//
// constructor
//
// ���� �Ŵ��� ��ü�� �����ϴ� ���̴�.
//
//////////////////////////////////////////////////////////////////////
ClientManager::ClientManager () 
	throw ( Error )
{
	__BEGIN_TRY

	// �α��� �÷��̾� �Ŵ����� �����Ѵ�.
	g_pLoginPlayerManager = new LoginPlayerManager();

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// destructor
//
// ���� �Ŵ��� ��ü�� �����ϴ� ���̴�.
//
//////////////////////////////////////////////////////////////////////
ClientManager::~ClientManager () 
	throw ( Error )
{
	__BEGIN_TRY

	// �α��� �÷��̾� �Ŵ����� �����Ѵ�.
	if ( g_pLoginPlayerManager != NULL ) {
		delete g_pLoginPlayerManager;
		g_pLoginPlayerManager = NULL;	
	}

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// ���� �Ŵ��� ��ü�� �ʱ�ȭ�ϰ�, �ڽ��� �ʱ�ȭ�Ѵ�.
//
//////////////////////////////////////////////////////////////////////
void ClientManager::init ()
	throw ( Error )
{
	__BEGIN_TRY

	g_pLoginPlayerManager->init();

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// ���񽺸� �����Ѵ�.
//
//////////////////////////////////////////////////////////////////////
void ClientManager::start ()
	throw ( Error )
{
	__BEGIN_TRY

	run();		// �ٷ� run() �޽�带 ȣ���Ѵ�. ^^;

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// �ڽ��� ���񽺸� �ߴ��� ��, ���� �Ŵ��� ��ü���� ���񽺸� �ߴܽ�Ų��.
//
//////////////////////////////////////////////////////////////////////
void ClientManager::stop ()
	throw ( Error )
{
	__BEGIN_TRY

	throw UnsupportedError("stopping manager not supported.");

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// Ŭ���̾�Ʈ �Ŵ����� ���� �����̴�.
//////////////////////////////////////////////////////////////////////
void ClientManager::run ()
	throw ( Error )
{
	__BEGIN_TRY

	Assert( g_pLoginPlayerManager != NULL );

	Timeval NextTime;
	getCurrentTime(NextTime);

	// GameWorldInfo, GameServerInfo ���� �ε��ϴ� �ð�
	Timeval ReloadNextTime = NextTime;
	// GameWorldInfo, GameServerInfo ���� �ε��ϴ� �ð� ����, �� ����
	int ReloadGap = g_pConfig->getPropertyInt("ServerInfoReloadTime") * 60;
	ReloadNextTime.tv_sec += ReloadGap;

	NextTime.tv_sec += 10;

	Timeval dummyQueryTime;
	getCurrentTime(dummyQueryTime);

	while ( true ) 
	{
		usleep(100);

		beginProfileEx("LS_MAIN");

		beginProfileEx("LPM_SELECT");
		g_pLoginPlayerManager->select();
		endProfileEx("LPM_SELECT");

		beginProfileEx("LPM_EXCEPTION");
		g_pLoginPlayerManager->processExceptions();
		endProfileEx("LPM_EXCEPTION");

		beginProfileEx("LPM_INPUT");
		g_pLoginPlayerManager->processInputs();
		endProfileEx("LPM_INPUT");

		beginProfileEx("LPM_COMMAND");
		g_pLoginPlayerManager->processCommands();
		endProfileEx("LPM_COMMAND");

		beginProfileEx("LPM_OUTPUT");
		g_pLoginPlayerManager->processOutputs();
		endProfileEx("LPM_OUTPUT");

		beginProfileEx("LPM_HEARTBEAT");
		g_pReconnectLoginInfoManager->heartbeat();
		endProfileEx("LPM_HEARTBEAT");

		endProfileEx("LS_MAIN");

		Timeval currentTime;
		getCurrentTime(currentTime);

		if (NextTime < currentTime)
		{
			//outputProfileEx(false, false);
			(g_ProfileSampleManager.getProfileSampleSet())->outputProfileToFile("Profile", false, false);

			NextTime.tv_sec = currentTime.tv_sec + 10;
			NextTime.tv_usec = currentTime.tv_usec;

			// ���ϸ��� �������� �����͸� �ʱ�ȭ���ش�.
			// ���� �����ͺ��ٴ� �ð��뿡 ���� �ð��� �����ϱ� ���ؼ�...
			initProfileEx();

			//g_PacketProfileManager.outputResultToFile("PacketProfile.txt");
			g_PacketProfileManager.init();
		}

		if ( ReloadNextTime < currentTime )
		{
			if ( g_pGameWorldInfoManager != NULL )
			{
				g_pGameWorldInfoManager->load();
			}

			if ( g_pGameServerGroupInfoManager != NULL )
			{
				g_pGameServerGroupInfoManager->load();
			}

			ReloadNextTime.tv_sec += ReloadGap;
		}

		// DB connection �� timeout ���� �������� �ʰ� ������ �ǹ̾��� ���������ش�.
		// by bezz. 2003.04.21
		if ( dummyQueryTime < currentTime )
		{
			g_pDatabaseManager->executeDummyQuery( g_pDatabaseManager->getConnection("DARKEDEN") );

			dummyQueryTime.tv_sec += (60+rand()%30) * 60;
		}
#ifdef __THAILAND_SERVER__
	
		g_pTimeChecker->heartbeat();
#endif
		
	}

	__END_CATCH
}
	

// global variable definition
ClientManager * g_pClientManager = NULL;
