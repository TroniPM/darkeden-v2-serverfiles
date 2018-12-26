//////////////////////////////////////////////////////////////////////////////
// Filename    : DatabaseManager.h
// Written By  : elca
// Description : ����Ÿ���̽� �Ŵ���
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
	void addConnection(int TID, Connection * pConnection) throw(DuplicatedException);

	Connection* getConnection(const string& ip) throw(NoSuchElementException);
	void	executeDummyQuery(Connection* pConnection);

private:
	// �� �����庰�� �����ϴ� DB ����
	hash_map<int, Connection*> m_Connections;

	// ���� ó�� �����Ǵ� �⺻ DB ����
	Connection* m_pDefaultConnection;

	mutable Mutex m_Mutex;
};

extern DatabaseManager * g_pDatabaseManager;

#endif
