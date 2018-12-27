//////////////////////////////////////////////////////////////////////
//
// Filename    : StringStream.cc
// Written By  : reiot@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "StringStream.h"
#include <stdio.h>

//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
StringStream::StringStream () 
	
: m_Size(0), m_bInserted(false), m_Buffer("")
{
}

	
//////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////
StringStream::~StringStream () 
    
{
}

	
//////////////////////////////////////////////////////////////////////
// add string to stream
//////////////////////////////////////////////////////////////////////
StringStream & StringStream::operator << ( bool T ) 
	
{
	string buf( T == true ? "true" : "false" );

	m_Strings.push_back( buf );

	m_Size += buf.size();
	m_bInserted = true;

	return *this;
}

StringStream & StringStream::operator << ( char T ) 
	
{
	string buf(2,'\0');
	buf[0] = T;

	m_Strings.push_back( buf );

	m_Size += buf.size();
	m_bInserted = true;

	return *this;
}

StringStream & StringStream::operator << ( uchar T )
	
{
	string buf(2,0);
	buf[0] = T;

	m_Strings.push_back( buf );

	m_Size += buf.size();
	m_bInserted = true;

	return *this;
}

StringStream & StringStream::operator << ( short T )
	
{
	char buf[7];
	sprintf( buf , "%d" , T );

	string str(buf);

	m_Strings.push_back( str );

	m_Size += str.size();
	m_bInserted = true;

	return *this;
}

StringStream & StringStream::operator << ( ushort T )
	
{
	char buf[7];
	sprintf( buf , "%u" , T );

	string str(buf);

	m_Strings.push_back( str );

	m_Size += str.size();
	m_bInserted = true;

	return *this;
}

StringStream & StringStream::operator << ( int T )
	
{
	char buf[12];
	sprintf( buf , "%d" , T );
	
	string str(buf);

	m_Strings.push_back( str );

	m_Size += str.size();
	m_bInserted = true;

	return *this;
}

StringStream & StringStream::operator << ( uint T )
	
{	
	char buf[12];
	sprintf( buf , "%u" , T );
	
	string str(buf);

	m_Strings.push_back( str );

	m_Size += str.size();
	m_bInserted = true;

	return *this;
}

StringStream & StringStream::operator << ( long T )
	
{
	char buf[12];
	sprintf( buf , "%ld" , T );
	
	string str(buf);

	m_Strings.push_back( str );

	m_Size += str.size();
	m_bInserted = true;

	return *this;
}

StringStream & StringStream::operator << ( ulong T )
	
{	
	char buf[12];
	sprintf( buf , "%lu" , T );
	
	string str(buf);

	m_Strings.push_back( str );

	m_Size += str.size();
	m_bInserted = true;

	return *this;
}

StringStream & StringStream::operator << ( float T )
	
{
	char buf[12];
	sprintf( buf , "%f" , T );
	
	string str(buf);

	m_Strings.push_back( str );

	m_Size += str.size();
	m_bInserted = true;

	return *this;
}

StringStream & StringStream::operator << ( double T )
	
{
	char buf[22];
	sprintf( buf , "%f" , T );
	
	string str(buf);

	m_Strings.push_back( str );

	m_Size += str.size();
	m_bInserted = true;

	return *this;
}

StringStream & StringStream::operator << ( const char * buf )
	
{
	string str(buf);

	m_Strings.push_back( str );

	m_Size += str.size();
	m_bInserted = true;

	return *this;
}

StringStream & StringStream::operator << ( const string & str )
	
{
	m_Strings.push_back( str );

	m_Size += str.size();
	m_bInserted = true;

	return *this;
}


//////////////////////////////////////////////////////////////////////
// make string
//////////////////////////////////////////////////////////////////////
const string & StringStream::toString () const
	
{
	// �ϴ� ��Ʈ���� �ѹ� �����س�����, 
	// �״��� ȣ�⶧���� ���� �߰����� �ʴ� �� �״�� ����Ѵ�.
	if ( m_bInserted ) {
		
		m_bInserted = false;

		// �ӵ��� ���� �������� ���� ������ �ϴ� �޸𸮸� �� ��Ƴ��� �����Ѵ�.
		m_Buffer.reserve( m_Size );

		for ( list<string>::const_iterator itr = m_Strings.begin () ;
			  itr != m_Strings.end() ;
			  itr ++ ) {
			// ���ۿ� �ϳ��� �߰��Ѵ�.
			m_Buffer.append( *itr );
		}
	}

	return m_Buffer;
}
