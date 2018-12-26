//----------------------------------------------------------------------
//
// Filename    : ZoneInfoManager.cpp
// Written By  : Reiot
// Description :
//
//----------------------------------------------------------------------

// include files
#include "ZoneInfoManager.h"
#include "database/DatabaseManager.h"
#include "database/Connection.h"
#include "database/Statement.h"
#include "database/Result.h"

//----------------------------------------------------------------------
// constructor
//----------------------------------------------------------------------
ZoneInfoManager::ZoneInfoManager () 
	throw ()
{
}
	
//----------------------------------------------------------------------
// destructor
//----------------------------------------------------------------------
ZoneInfoManager::~ZoneInfoManager () 
	throw ()
{
	// hashmap ���� �� pair �� second, �� ZoneInfo ��ü���� �����ϰ�
	// pair ��ü�� �״�� �д�. (ZoneInfo�� ���� �����Ǿ� �ִٴ� �Ϳ�
	// �����϶�. �� �ʻ������ �ؾ� �Ѵ�. �ϱ�, ZIM�� destruct �ȴٴ� ����
	// �α��� ������ �˴ٿ�ȴٴ� ���� �ǹ��ϴϱ�.. - -; )
	for ( HashMapZoneInfo::iterator itr = m_ZoneInfos.begin() ; 
		  itr != m_ZoneInfos.end() ; 
		  itr ++ ) {
		delete itr->second;
		itr->second = NULL;
	}

	// ���� �ؽ��ʾȿ� �ִ� ��� pair ���� �����Ѵ�.
	m_ZoneInfos.clear();
}
	

//----------------------------------------------------------------------
// initialize GSIM
//----------------------------------------------------------------------
void ZoneInfoManager::init ()
	
{
	__BEGIN_TRY

	// just load data from ZoneInfo table
	load();

	// just print to cout
	cout << toString() << endl;

	__END_CATCH
}

//----------------------------------------------------------------------
// load data from database
//----------------------------------------------------------------------
void ZoneInfoManager::load ()
	
{
	__BEGIN_TRY

	Statement * pStmt;

	try {

		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		Result * pResult = pStmt->executeQuery(
			"SELECT ZoneID , ZoneGroupID FROM ZoneInfo"
		);

		while ( pResult->next() ) {
			ZoneInfo * pZoneInfo = new ZoneInfo();
			pZoneInfo->setZoneID( pResult->getWORD(1) );
			pZoneInfo->setZoneGroupID( pResult->getWORD(2) );
			addZoneInfo( pZoneInfo );
		}

	} catch ( SQLQueryException & sqe ) {

		// �ʻ� ����!
		delete pStmt;

		throw Error(sqe.toString());
	}

	// �ʻ� ����!
	delete pStmt;

	__END_CATCH
}

//----------------------------------------------------------------------
// add info 
//----------------------------------------------------------------------
void ZoneInfoManager::addZoneInfo ( ZoneInfo * pZoneInfo ) 
	throw ( DuplicatedException )
{
	__BEGIN_TRY

	HashMapZoneInfo::iterator itr = m_ZoneInfos.find( pZoneInfo->getZoneID() );
	
	if ( itr != m_ZoneInfos.end() )
		throw DuplicatedException("duplicated zone id");

	m_ZoneInfos[ pZoneInfo->getZoneID() ] = pZoneInfo;

	__END_CATCH
}
	
//----------------------------------------------------------------------
// delete info
//----------------------------------------------------------------------
void ZoneInfoManager::deleteZoneInfo ( ZoneID_t zoneID )
	throw ( NoSuchElementException )
{
	__BEGIN_TRY
		
	HashMapZoneInfo::iterator itr = m_ZoneInfos.find( zoneID );
	
	if ( itr != m_ZoneInfos.end() ) {

		// ZoneInfo �� �����Ѵ�.
		delete itr->second;

		// pair�� �����Ѵ�.
		m_ZoneInfos.erase( itr );

	} else { // not found

		StringStream msg;
		msg << "ZoneID : " << zoneID;
		throw NoSuchElementException(msg.toString());

	}

	__END_CATCH
}
	
//----------------------------------------------------------------------
// get info
//----------------------------------------------------------------------
ZoneInfo * ZoneInfoManager::getZoneInfo ( ZoneID_t zoneID ) const
	throw ( NoSuchElementException )
{
	__BEGIN_TRY
		
	ZoneInfo * pZoneInfo = NULL;

	HashMapZoneInfo::const_iterator itr = m_ZoneInfos.find( zoneID );
	
	if ( itr != m_ZoneInfos.end() ) {

		pZoneInfo = itr->second;

	} else { // not found

		StringStream msg;
		msg << "ZoneID : " << zoneID;
		throw NoSuchElementException( msg.toString() );

	}

	return pZoneInfo;

	__END_CATCH
}

//----------------------------------------------------------------------
// get debug string
//----------------------------------------------------------------------
string ZoneInfoManager::toString () const
	throw ()
{
	__BEGIN_TRY

	StringStream msg;

	msg << "ZoneInfoManager(\n";

	if ( m_ZoneInfos.empty() ) {

		msg << "EMPTY";

	} else {

		//--------------------------------------------------
		// *OPTIMIZATION*
		//
		// for_each()�� ����� ��
		//--------------------------------------------------
		for ( HashMapZoneInfo::const_iterator itr = m_ZoneInfos.begin() ; 
			  itr != m_ZoneInfos.end() ; 
			  itr ++ )
			msg << itr->second->toString() << '\n';
	}

	msg << ")";

	return msg.toString();

	__END_CATCH
}

// global variable definition
ZoneInfoManager * g_pZoneInfoManager = NULL;
