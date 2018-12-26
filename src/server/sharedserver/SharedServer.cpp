//////////////////////////////////////////////////////////////////////
// 
// Filename    : SharedServer.cpp 
// Written By  : reiot@ewestsoft.com
// Description : ����� ������ ���� Ŭ����
// 
//////////////////////////////////////////////////////////////////////

// include files
#include "SharedServer.h"
#include "Assert.h"
#include "GameServerInfoManager.h"
#include "GameServerGroupInfoManager.h"
#include "GameServerManager.h"
#include "HeartbeatManager.h"
#include "database/DatabaseManager.h"
#include "PacketFactoryManager.h"
#include "PacketValidator.h"
#include "GameWorldInfoManager.h"
#include "GuildManager.h"
#include "ResurrectLocationManager.h"
#include "StringPool.h"

#include "LogClient.h"

#include "types/ServerType.h"
#ifdef __NETMARBLE_SERVER__
	#include "NetmarbleGuildRegisterThread.h"
#endif

//////////////////////////////////////////////////////////////////////
//
// constructor
//
// �ý��� �Ŵ����� constructor������ ���� �Ŵ��� ��ü�� �����Ѵ�.
//
//////////////////////////////////////////////////////////////////////
SharedServer::SharedServer ()
	
{
	__BEGIN_TRY
	
	// create database manager
	g_pDatabaseManager = new DatabaseManager();

	// create guild manager
	g_pGuildManager = new GuildManager();

	// create some info managers
	g_pGameServerInfoManager = new GameServerInfoManager();
	g_pGameServerGroupInfoManager = new GameServerGroupInfoManager();

	// create packet factory manager, packet validator
	// (Ŭ���̾�Ʈ �Ŵ����� ��������ŸŴ������� ���� ����, �ʱ�ȭ�Ǿ�� �Ѵ�.)
	g_pPacketFactoryManager = new PacketFactoryManager();
	g_pPacketValidator = new PacketValidator();
		
	// create inter-server communication manager
	g_pGameServerManager = new GameServerManager();

	// create client manager
	g_pHeartbeatManager = new HeartbeatManager();

	// create GameWorldInfoManager
	g_pGameWorldInfoManager = new GameWorldInfoManager();

	// create ResurrectLocationManager
	g_pResurrectLocationManager = new ResurrectLocationManager();

	g_pStringPool = new StringPool();

/*#ifdef __NETMARBLE_SERVER__
	g_pNetmarbleGuildRegisterThread = new NetmarbleGuildRegisterThread();
#endif*/

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// destructor
//
// �ý��� �Ŵ����� destructor������ ���� �Ŵ��� ��ü�� �����ؾ� �Ѵ�.
//
//////////////////////////////////////////////////////////////////////
SharedServer::~SharedServer ()
	
{
	__BEGIN_TRY
		
	SAFE_DELETE( g_pHeartbeatManager );
	SAFE_DELETE( g_pGameServerManager );
	SAFE_DELETE( g_pPacketValidator );
	SAFE_DELETE( g_pPacketFactoryManager );
	SAFE_DELETE( g_pGameServerInfoManager );
	SAFE_DELETE( g_pGameServerGroupInfoManager );
	SAFE_DELETE( g_pGuildManager );
	SAFE_DELETE( g_pDatabaseManager );
	SAFE_DELETE( g_pGameWorldInfoManager );
	SAFE_DELETE( g_pResurrectLocationManager );
	SAFE_DELETE( g_pStringPool );

/*#ifdef __NETMARBLE_SERVER__
	SAFE_DELETE( g_pNetmarbleGuildRegisterThread );
#endif*/

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// initialize game server
//
//////////////////////////////////////////////////////////////////////
void SharedServer::init ()
	 
{
	__BEGIN_TRY

	cout << "SharedServer::init() start" << endl;

	// ����Ÿ���̽��Ŵ����� �ʱ�ȭ�Ѵ�.
	g_pDatabaseManager->init();

	g_pStringPool->load();

	// guild manager �� �ʱ�ȭ�Ѵ�.
	g_pGuildManager->init();

	// initialize some info managers
	g_pGameServerInfoManager->init();
	g_pGameServerGroupInfoManager->init();
	
	g_pGameWorldInfoManager->init();

	// Ŭ���̾�Ʈ�Ŵ����� �ʱ�ȭ�ϱ� ����, ��Ŷ���丮�Ŵ���/��Ŷ�߸������͸� �ʱ�ȭ�Ѵ�.
	g_pPacketFactoryManager->init();
	g_pPacketValidator->init();

	// ������ ��� �Ŵ����� �ʱ�ȭ�Ѵ�.
	g_pGameServerManager->init();

	// ResurrectLocationManager �ʱ�ȭ
	g_pResurrectLocationManager->init();

/*#ifdef __NETMARBLE_SERVER__
	g_pNetmarbleGuildRegisterThread->init();
#endif*/
	
	// ������ �غ� ���� ���� ���� Ŭ���̾�Ʈ�Ŵ����� �ʱ�ȭ�����ν�,
	// ��Ʈ��ŷ�� ����Ѵ�.
	g_pHeartbeatManager->init();

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// start shared server
//
//////////////////////////////////////////////////////////////////////
void SharedServer::start ()
	 
{
	__BEGIN_TRY

	cout << "---------- Start SharedServer ---------" << endl;
	// ������ ��� �Ŵ����� �����Ѵ�.
	g_pGameServerManager->start();

	// �ݸ��� ��� ��� ������ ����
/*#ifdef __NETMARBLE_SERVER__
	g_pNetmarbleGuildRegisterThread->start();
#endif*/
		
	//
	// Ŭ���̾�Ʈ �Ŵ����� �����Ѵ�.
	//
	// *Reiot's Notes*
	//
	// ���� ���߿� ����Ǿ�� �Ѵ�. �ֳ��ϸ� ��Ƽ���������� �ƴ�
	// ���ѷ����� ���� �Լ��̱� �����̴�. ���� �� ������ �ٸ� �Լ���
	// ȣ���� ���, ������ ������ �ʴ���(�� ������ �߻����� �ʴ���)
	// �ٸ� �Ŵ����� ó�� ������ ������� �ʴ´�.	
	//
	g_pHeartbeatManager->start();

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// stop shared server
//
// stop ������ �����ϵ��� ����. ���� ������ ���� �ִ� �Ŵ�������
// stop ���Ѿ� �Ѵ�. ���� �ݴ��� ������ stop ��ų ��� null pointer
// ���� ������ �߻��� �� �ִ�.
//
//////////////////////////////////////////////////////////////////////
void SharedServer::stop ()
	 
{
	__BEGIN_TRY

	// ���߿� �� �κ��� �ڸ�Ʈȭ�ؾ� �Ѵ�.
	throw UnsupportedError();
		
	// 
	g_pHeartbeatManager->stop();
	
	//
	g_pGameServerManager->stop();

	__END_CATCH
}


//////////////////////////////////////////////////
// global variable declaration
//////////////////////////////////////////////////
SharedServer * g_pSharedServer = NULL;
