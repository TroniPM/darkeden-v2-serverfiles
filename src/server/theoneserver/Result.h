//////////////////////////////////////////////////////////////////////////////
// File Name	: Result.h
// Written By	: Gday29@ewestsoft.com
// Description	: Definition of Result Class
//////////////////////////////////////////////////////////////////////////////

#ifndef __RESULT_H__
#define __RESULT_H__

#include "Types.h"
#include "Exception.h"
#include <sys/time.h>
#include <mysql/mysql.h>

//////////////////////////////////////////////////////////////////////////////
// forward declaration
//////////////////////////////////////////////////////////////////////////////
class Connection;
class Statement;

#define T_RESULT MYSQL_RES

//////////////////////////////////////////////////////////////////////////////
// class Result;
// Result �� ������ �ʿ䰡 ����. ����ڴ� Statement �� �����ϸ� �ȴ�.
//////////////////////////////////////////////////////////////////////////////

class Result 
{
public:
	Result(T_RESULT *, const string& statement) throw(Error);
	~Result() throw();

public:
	// ���� row�� �Ѿ��.
	bool next() throw(Error);
	
	// Ư�� �ʵ�(�÷�) ���� ������ �´�.
	char * getField(uint index) throw(OutOfBoundException, Error);
	char getChar(uint index) throw(OutOfBoundException, Error) { return(getField(index))[0]; }
	int getInt(uint index) throw(OutOfBoundException, Error) { return atoi(getField(index)); }
	uint getUInt(uint index) throw(OutOfBoundException, Error) { return(uint)atoi(getField(index)); }
	BYTE getBYTE(uint index) throw(OutOfBoundException, Error) { return(BYTE)atoi(getField(index)); }
	WORD getWORD(uint index) throw(OutOfBoundException, Error) { return(WORD)atoi(getField(index)); }
	DWORD getDWORD(uint index) throw(OutOfBoundException, Error) { return strtoul(getField(index), (char**)NULL, 10); }
	const char* getString(uint index) throw(OutOfBoundException, Error);

	// ���� ������� �����ϴ� row/column�� ���ڸ� �����Ѵ�.
	uint getRowCount()  { return m_RowCount; }
	uint getFieldCount()  { return m_FieldCount; }

	string getStatement(void) const { return m_Statement; }

private:
	T_RESULT*  m_pResult;    // ������� ��Ÿ���� MYSQL structure
	MYSQL_ROW  m_pRow;       // ���� ó���ϰ� �ִ� row
	uint       m_RowCount;   // ���� ����� �� row�� ����
	uint       m_FieldCount;
	string     m_Statement;  // � query���� ���� ����ΰ�...?
};

#endif // __RESULT_H__
