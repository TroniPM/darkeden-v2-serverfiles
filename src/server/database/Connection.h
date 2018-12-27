//////////////////////////////////////////////////////////////////////
//
// File Name 	: Connection.h
// Written by	: Gday29@ewestsoft.com
// Description	: ����Ÿ���̽����� ������ ����ϴ� Ŭ����
//
//////////////////////////////////////////////////////////////////////

#ifndef __CONNECTION_H__
#define __CONNECTION_H__

// include files
#include "Types.h"
#include "Exception.h"
#include <mysql/mysql.h>
#include "Mutex.h"

// forward declaration
class Statement;

//////////////////////////////////////////////////////////////////////
//
// class Connection;
//
// ������ ���̽��� �����ϰ�, �����Ѵ�.
//
//////////////////////////////////////////////////////////////////////

class Connection {

public:
	
	// constructor
    Connection();

	// constructor(1-time connection)
    Connection(string host, string db, string user, string password, uint port = 0) throw(SQLConnectException, Error);
    
	// destructor
	~Connection();

    // close the connection to database
	void close() throw(SQLConnectException, Error);
	
	// ����Ÿ���̽��� ������ �õ��Ѵ�.
	void connect(string host, string db, string user, string password, uint port = 0) throw(SQLConnectException);

	// ����Ÿ���̽��� ������ �õ��Ѵ�.
	void connect() throw(SQLConnectException);
	
	// check the connection 
	bool isConnected()  { return m_bConnected; }
	bool operator !()  { return m_bConnected == false; }
	
	// Statement ��ü�� �����ؼ� �����Ѵ�.
	Statement * createStatement() ;	
	
	// get the MYSQL object
	MYSQL * getMYSQL()  { return &m_Mysql; }
	
	// get MS's host name(ip)
	string getHost()  { return m_Host; }

	// get MS's service port
	uint getPort()  { return m_Port; }

	// get database name
	string getDatabase()  { return m_Database; }

	// get user id 
	string getUser()  { return m_User; }

	// get user password
	string getPassword()  { return m_Password; }

	// get connection's name
	string getName()  { return m_Name; }

	// set connection's name
	void setName(string name)  { m_Name = name; }

	// get/set busy status
	bool isBusy(void)  { return m_bBusy;}
	void setBusy(bool busy=true)  { m_bBusy = busy;}

	// get error
	string getError()  { return mysql_error(&m_Mysql); }

	// lock/unlock
	void lock()  { m_Mutex.lock(); }
	void unlock()  { m_Mutex.unlock(); }
	
private:
	
	// ??
    MYSQL m_Mysql;

	// is connected?
	bool m_bConnected;

	// DBMS �� ��Ǵ� ȣ��Ʈ ��
	string m_Host;

	// DBMS �� ���� ��Ʈ
	uint m_Port;

	// ����Ÿ���̽� �̸�
	string m_Database;

	// ����� ���̵�
	string m_User;

	// ����� �н�����
	string m_Password;

	// connection name(DatabaseManager ���� ����� Ű��)
	string m_Name;

	// ���� ������� Ŀ�ؼ��ΰ�?
	bool m_bBusy;

	// ���� ������ ���� ���� lock
	Mutex m_Mutex;

};

#endif // __CONNECTION_H__
