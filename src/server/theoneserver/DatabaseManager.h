//////////////////////////////////////////////////////////////////////////////
// Filename    : DatabaseManager.h
// Written By  : elca
// Description : 데이타베이스 매니저
//////////////////////////////////////////////////////////////////////////////

#ifndef __DATABASE_MANAGER_H__
#define __DATABASE_MANAGER_H__

#include "Types.h"
#include "Exception.h"
#include <hash_map>
#include "Connection.h"
#include "Mutex.h"

//////////////////////////////////////////////////////////////////////////////
// class DatabaseManager;
//////////////////////////////////////////////////////////////////////////////

class DatabaseManager 
{
public:
	DatabaseManager() ;
	~DatabaseManager() ;
	
public:
	void init();
	void addConnection(int TID, Connection * pConnection) ;

	Connection* getConnection(const string& ip) ;
	void	executeDummyQuery(Connection* pConnection);

private:
	// 각 쓰레드별로 존재하는 DB 연결
	hash_map<int, Connection*> m_Connections;

	// 제일 처음 생성되는 기본 DB 연결
	Connection* m_pDefaultConnection;

	mutable Mutex m_Mutex;
};

extern DatabaseManager * g_pDatabaseManager;

#endif
