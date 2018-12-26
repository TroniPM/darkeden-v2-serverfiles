//////////////////////////////////////////////////////////////////////
//
// File Name 	: Statement.h
// Written by	: Gday29@ewestsoft.com
// Description	: SQL ���� �����..
//
//////////////////////////////////////////////////////////////////////

#ifndef __STATEMENT_H__
#define __STATEMENT_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Connection.h"

// forward declaration
class Result;

//////////////////////////////////////////////////////////////////////
//
// class Statement;
//
// SQL���� ����� ��� �����Ѵ�.
//
//////////////////////////////////////////////////////////////////////

class Statement {

public:
	
	// constructor
	Statement() ; 

	// constructor
    Statement(char * fmt, ...);

	// destructor
	~Statement() ;

public:
    
	// ������ ������ SQL ���� ������ �����Ѵ�.
    Result * executeQuery() throw(SQLQueryException, Error);
	
	// SQL ���� �޾Ƽ� �����Ѵ�.
	Result * executeQuery(char *,...) throw(SQLQueryException, Error);
	Result * executeQuery(const string& sqlStatement) throw(SQLQueryException, Error);
	
	// get SQL statement
	string getStatement()  { return m_Statement; }

	// SQL ���� �����Ѵ�.
	void setStatement(char * fmt, ...);

	// get connection object
	Connection * getConnection()  { return m_pConnection; }

	// set connection object
	void setConnection(Connection * pConnection) throw() { m_pConnection = pConnection; }

	// get warning/error string
	string getError()  
	{ 
		return(m_pConnection == NULL) ?("Not Associated with Connection Object") :(m_pConnection->getError()); 
	}

	// get affected rows
	uint getAffectedRowCount()  { return m_nAffectedRows; }

	// get insert id
	uint getInsertID() ;

	
private:
	
	// Connection
	Connection * m_pConnection;

	// SQL Statement�
	string m_Statement;

	// Query Result 
	Result * m_pResult;

	// insert, update, delete ���� �� ������ ���� row �� ����
	uint m_nAffectedRows;

};

#endif // __STATEMENT_H__
