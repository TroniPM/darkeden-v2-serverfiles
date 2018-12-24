//--------------------------------------------------------------------------------
// 
// Filename    : ThreadManager.cc
// Written By  : Reiot
// 
//--------------------------------------------------------------------------------

// include files
#include "ThreadManager.h"
#include "ThreadPool.h"
#include "ZoneGroupThread.h"
#include "Assert.h"
#include "LogClient.h"
#include "ZoneGroupManager.h"
#include "Properties.h"
#include "DB.h"


//--------------------------------------------------------------------------------
// constructor
//--------------------------------------------------------------------------------
ThreadManager::ThreadManager () 
     throw (Error)
: m_pZoneGroupThreadPool(NULL)
{
	__BEGIN_TRY
		
	// ��������Ǯ�� �����Ѵ�.
	m_pZoneGroupThreadPool = new ThreadPool();

	__END_CATCH
}

	
//--------------------------------------------------------------------------------
//
// destructor
//
// Stop()�� ���� �ʾ��� ��� ������Ѿ� �Ѵ�. State ������ �����ұ�?
//
//--------------------------------------------------------------------------------
ThreadManager::~ThreadManager () 
     throw (Error)
{
	__BEGIN_TRY

	SAFE_DELETE(m_pZoneGroupThreadPool);

	__END_CATCH
}


//--------------------------------------------------------------------------------
//
// ������ �Ŵ����� �ʱ�ȭ�Ѵ�.
//
// ���� ������Ǯ�� ��������� ����, ��Ͻ�Ų��.
//
// *CAUTION*
//
// �翬��, ������ �Ŵ����� �ʱ�ȭ�ϱ� ����, ���׷�Ŵ����� �ʱ�ȭ�ؾ� �Ѵ�.
//
//--------------------------------------------------------------------------------
void ThreadManager::init () 
     throw (Error)
{
	__BEGIN_TRY
		
	// �� �����带 ����Ѵ�.
	Statement* pStmt   = NULL;
	Result*    pResult = NULL;

	BEGIN_DB
	{
		pStmt   = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pResult = pStmt->executeQuery("SELECT ZoneGroupID FROM ZoneGroupInfo");

		while (pResult->next()) 
		{
			ZoneGroupID_t zoneGroupID = pResult->getInt(1);
			ZoneGroupThread* pZoneGroupThread = new ZoneGroupThread(g_pZoneGroupManager->getZoneGroup(zoneGroupID));
			m_pZoneGroupThreadPool->addThread(pZoneGroupThread);
		}

		SAFE_DELETE(pStmt);
	} 
	END_DB(pStmt)

	__END_CATCH
}
	

//--------------------------------------------------------------------------------
//
// activate sub thread pools
//
// ���� ������ Ǯ�� Ȱ��ȭ��Ų��. 
//
//--------------------------------------------------------------------------------
void ThreadManager::start () 
     throw (Error)
{
	__BEGIN_TRY

	// Zone Thread Pool �� Ȱ��ȭ��Ų��.
	m_pZoneGroupThreadPool->start();
	
	__END_CATCH
}
	

//--------------------------------------------------------------------------------
//
// deactivate sub thread pools
//
// ���� ������ Ǯ�� �����Ų��.
//
//--------------------------------------------------------------------------------
void ThreadManager::stop () 
     throw (Error)
{
	__BEGIN_TRY

	throw UnsupportedError();

	__END_CATCH
}


//--------------------------------------------------------------------------------
// global variable definition
//--------------------------------------------------------------------------------
ThreadManager* g_pThreadManager = NULL;
