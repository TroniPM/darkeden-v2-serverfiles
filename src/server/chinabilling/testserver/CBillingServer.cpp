//////////////////////////////////////////////////////////////////////
// 
// Filename    : CBillingServer.cpp 
// Written By  : reiot@ewestsoft.com
// Description : �߱� ���� ����(�׽�Ʈ)�� ���� Ŭ����
// 
//////////////////////////////////////////////////////////////////////

// include files
#include "CBillingServer.h"
#include "Assert.h"
#include "GameServerManager.h"
#include "database/DatabaseManager.h"

#include "LogClient.h"

//////////////////////////////////////////////////////////////////////
//
// constructor
//
// �ý��� �Ŵ����� constructor������ ���� �Ŵ��� ��ü�� �����Ѵ�.
//
//////////////////////////////////////////////////////////////////////
CBillingServer::CBillingServer ()
	throw ( Error )
{
	__BEGIN_TRY
	
	// create inter-server communication manager
	g_pGameServerManager = new GameServerManager();

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// destructor
//
// �ý��� �Ŵ����� destructor������ ���� �Ŵ��� ��ü�� �����ؾ� �Ѵ�.
//
//////////////////////////////////////////////////////////////////////
CBillingServer::~CBillingServer ()
	throw ( Error )
{
	__BEGIN_TRY
		
	SAFE_DELETE( g_pGameServerManager );

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// initialize game server
//
//////////////////////////////////////////////////////////////////////
void CBillingServer::init ()
	 throw ( Error )
{
	__BEGIN_TRY

	cout << "CBillingServer::init() start" << endl;

	// ������ ��� �Ŵ����� �ʱ�ȭ�Ѵ�.
	g_pGameServerManager->init();

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// start shared server
//
//////////////////////////////////////////////////////////////////////
void CBillingServer::start ()
	 throw ( Error )
{
	__BEGIN_TRY

	cout << "---------- Start CBillingServer ---------" << endl;
	// ������ ��� �Ŵ����� �����Ѵ�.
	g_pGameServerManager->start();
		
	while ( true )
	{
		usleep( 100 );
	}

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
void CBillingServer::stop ()
	 throw ( Error )
{
	__BEGIN_TRY

	// ���߿� �� �κ��� �ڸ�Ʈȭ�ؾ� �Ѵ�.
	throw UnsupportedError();
		
	//
	g_pGameServerManager->stop();

	__END_CATCH
}


//////////////////////////////////////////////////
// global variable declaration
//////////////////////////////////////////////////
CBillingServer * g_pCBillingServer = NULL;
