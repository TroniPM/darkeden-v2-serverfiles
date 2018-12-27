//----------------------------------------------------------------------
//
// Filename    : GameServerGroupInfoManager.cpp
// Written By  : Reiot
// Description :
//
//----------------------------------------------------------------------

// include files
#include "GameServerGroupInfoManager.h"

#include "database/DatabaseManager.h"
#include "database/Connection.h"
#include "database/Statement.h"
#include "database/Result.h"
#include "database/DB.h"

//----------------------------------------------------------------------
// constructor
//----------------------------------------------------------------------
GameServerGroupInfoManager::GameServerGroupInfoManager () 
	
{
}
	
//----------------------------------------------------------------------
// destructor
//----------------------------------------------------------------------
GameServerGroupInfoManager::~GameServerGroupInfoManager () 
	
{
	// hashmap ���� �� pair �� second, �� GameServerGroupInfo ��ü���� �����ϰ�
	// pair ��ü�� �״�� �д�. (GameServerGroupInfo�� ���� �����Ǿ� �ִٴ� �Ϳ�
	// �����϶�. �� �ʻ������ �ؾ� �Ѵ�. �ϱ�, GSIM�� destruct �ȴٴ� ����
	// �α��� ������ �˴ٿ�ȴٴ� ���� �ǹ��ϴϱ�.. - -; )
	for( int i = 1 ; i < m_MaxWorldID; i++ ) {
		for ( HashMapGameServerGroupInfo::iterator itr = m_GameServerGroupInfos[i].begin() ; 
			  itr != m_GameServerGroupInfos[i].end() ; 
			  itr ++ ) {
			delete itr->second;
			itr->second = NULL;
		}

		// ���� �ؽ��ʾȿ� �ִ� ��� pair ���� �����Ѵ�.
		m_GameServerGroupInfos[i].clear();

	}

	SAFE_DELETE_ARRAY(m_GameServerGroupInfos);

}
	

//----------------------------------------------------------------------
// initialize GSIM
//----------------------------------------------------------------------
void GameServerGroupInfoManager::init ()
	
{
	__BEGIN_TRY

	// just load data from GameServerGroupInfo table
	load();

	// just print to cout
	cout << toString() << endl;

	__END_CATCH
}

//----------------------------------------------------------------------
// load data from database
//----------------------------------------------------------------------
void GameServerGroupInfoManager::load ()
	
{
	__BEGIN_TRY

	Statement * pStmt;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		Result* pResult = pStmt->executeQuery(
			"SELECT MAX(WorldID) FROM GameServerGroupInfo"
		);

		if (pResult->getRowCount() == 0)
		{
			throw Error("GameServerGroupInfo TABLE does not exist!");
		}

		pResult->next();
		m_MaxWorldID = pResult->getInt(1) + 2;

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	m_GameServerGroupInfos = new HashMapGameServerGroupInfo[m_MaxWorldID];

	try {

		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		Result * pResult = pStmt->executeQuery(
			"SELECT WorldID, GroupID, GroupName FROM GameServerGroupInfo"
		);

		while ( pResult->next() ) {
			GameServerGroupInfo * pGameServerGroupInfo = new GameServerGroupInfo();
			WorldID_t WorldID = pResult->getInt(1);
			pGameServerGroupInfo->setWorldID( WorldID );
			pGameServerGroupInfo->setGroupID( pResult->getInt(2) );
			pGameServerGroupInfo->setGroupName( pResult->getString(3) );
			addGameServerGroupInfo( pGameServerGroupInfo, WorldID );
		}

		// �ʻ� ����!
		delete pStmt;

	} catch ( SQLQueryException & sqe ) {

		// �ʻ� ����!
		delete pStmt;

		throw Error(sqe.toString());

	} catch ( Throwable & t ) {
		cout << t.toString() << endl;
	}

	__END_CATCH
}

//----------------------------------------------------------------------
// add info 
//----------------------------------------------------------------------
void GameServerGroupInfoManager::addGameServerGroupInfo ( GameServerGroupInfo * pGameServerGroupInfo, WorldID_t WorldID ) 
	
{
	__BEGIN_TRY

	HashMapGameServerGroupInfo::iterator itr = m_GameServerGroupInfos[WorldID].find( pGameServerGroupInfo->getGroupID() );
	
	if ( itr != m_GameServerGroupInfos[WorldID].end() )
		throw DuplicatedException("duplicated game-server nickname");

	m_GameServerGroupInfos[WorldID][ pGameServerGroupInfo->getGroupID() ] = pGameServerGroupInfo;

	__END_CATCH
}
	
//----------------------------------------------------------------------
// delete info
//----------------------------------------------------------------------
void GameServerGroupInfoManager::deleteGameServerGroupInfo ( const ServerGroupID_t GroupID, WorldID_t WorldID ) 
	
{
	__BEGIN_TRY
		
	HashMapGameServerGroupInfo::iterator itr = m_GameServerGroupInfos[WorldID].find( GroupID );
	
	if ( itr != m_GameServerGroupInfos[WorldID].end() ) {

		// GameServerGroupInfo �� �����Ѵ�.
		delete itr->second;

		// pair�� �����Ѵ�.
		m_GameServerGroupInfos[WorldID].erase( itr );

	} else {

		// �׷� ���Ӽ������� ��ü�� ã�� �� ���� ��
		throw NoSuchElementException();

	}

	__END_CATCH
}
	
//----------------------------------------------------------------------
// get GameServerGroupinfo by ServerGroupID
//----------------------------------------------------------------------
GameServerGroupInfo * GameServerGroupInfoManager::getGameServerGroupInfo ( const ServerGroupID_t GroupID, WorldID_t WorldID ) const
	
{
	__BEGIN_TRY

	if( WorldID >= m_MaxWorldID ) {
		// �׷� ���Ӽ������� ��ü�� ã�� �� ������ ��
		throw NoSuchElementException();
	}
		
	GameServerGroupInfo * pGameServerGroupInfo = NULL;

	HashMapGameServerGroupInfo::const_iterator itr = m_GameServerGroupInfos[WorldID].find( GroupID );
	
	if ( itr != m_GameServerGroupInfos[WorldID].end() ) {
		pGameServerGroupInfo = itr->second;
	} else {
		// �׷� ���Ӽ������� ��ü�� ã�� �� ������ ��
		throw NoSuchElementException();
	}

	return pGameServerGroupInfo;

	__END_CATCH
}

//----------------------------------------------------------------------
// get debug string
//----------------------------------------------------------------------
string GameServerGroupInfoManager::toString () const
	
{
	__BEGIN_TRY

	StringStream msg;

	msg << "GameServerGroupInfoManager(\n";

	for ( int i = 1; i < m_MaxWorldID ; i++ ) {

		if ( m_GameServerGroupInfos[i].empty() ) {

			msg << "EMPTY";

		} else {

			//--------------------------------------------------
			// *OPTIMIZATION*
			//
			// for_each()�� ����� ��
			//--------------------------------------------------
			for ( HashMapGameServerGroupInfo::const_iterator itr = m_GameServerGroupInfos[i].begin() ; 
				  itr != m_GameServerGroupInfos[i].end() ; 
				  itr ++ )
				msg << itr->second->toString() << '\n';
		}

	}

	msg << ")";

	return msg.toString();

	__END_CATCH
}

// global variable definition
GameServerGroupInfoManager * g_pGameServerGroupInfoManager = NULL;
