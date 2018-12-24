//////////////////////////////////////////////////////////////////////
// 
// Filename    : TheOneServer.cpp 
// Written By  : reiot@ewestsoft.com
// Description : �α��� ������ ���� Ŭ����
// 
//////////////////////////////////////////////////////////////////////

// include files
#include "TheOneServer.h"
#include "Assert.h"
#include "GameServerManager.h"
#include "database/DatabaseManager.h"
#include "PacketFactoryManager.h"
#include "UDPManager.h"

//////////////////////////////////////////////////////////////////////
//
// constructor
//
// �ý��� �Ŵ����� constructor������ ���� �Ŵ��� ��ü�� �����Ѵ�.
//
//////////////////////////////////////////////////////////////////////
TheOneServer::TheOneServer ()
	throw ( Error )
{
	__BEGIN_TRY
	
	// create database manager
	g_pDatabaseManager = new DatabaseManager();

	g_pPacketFactoryManager = new PacketFactoryManager();

	// create inter-server communication manager
	g_pGameServerManager = new GameServerManager();

	//g_pUDPManager = new UDPManager();

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// destructor
//
// �ý��� �Ŵ����� destructor������ ���� �Ŵ��� ��ü�� �����ؾ� �Ѵ�.
//
//////////////////////////////////////////////////////////////////////
TheOneServer::~TheOneServer ()
	throw ( Error )
{
	__BEGIN_TRY
		
	SAFE_DELETE(g_pGameServerManager);
	SAFE_DELETE(g_pPacketFactoryManager);
	SAFE_DELETE(g_pDatabaseManager);

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// initialize game server
//
//////////////////////////////////////////////////////////////////////
void TheOneServer::init ()
	 throw ( Error )
{
	__BEGIN_TRY

	cout << "Init DatabaseManager..." << endl;
	// ����Ÿ���̽��Ŵ����� �ʱ�ȭ�Ѵ�.
	g_pDatabaseManager->init();
	cout << "Init DatabaseManager Complete!" << endl;

	g_pPacketFactoryManager->init();

	// ������ ��� �Ŵ����� �ʱ�ȭ�Ѵ�.
	g_pGameServerManager->init();
	
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// start login server
//
//////////////////////////////////////////////////////////////////////
void TheOneServer::start ()
	 throw ( Error )
{
	__BEGIN_TRY

	// ������ ��� �Ŵ����� �����Ѵ�.
	g_pGameServerManager->start();
		
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// stop login server
//
// stop ������ �����ϵ��� ����. ���� ������ ���� �ִ� �Ŵ�������
// stop ���Ѿ� �Ѵ�. ���� �ݴ��� ������ stop ��ų ��� null pointer
// ���� ������ �߻��� �� �ִ�.
//
//////////////////////////////////////////////////////////////////////
void TheOneServer::stop ()
	 throw ( Error )
{
	__BEGIN_TRY

	g_pGameServerManager->stop();

	__END_CATCH
}


//////////////////////////////////////////////////
// global variable declaration
//////////////////////////////////////////////////
TheOneServer * g_pTheOneServer = NULL;
