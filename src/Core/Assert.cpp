//--------------------------------------------------------------------------------
// 
// Filename   : Assert.cpp 
// Written By : Reiot
//
//--------------------------------------------------------------------------------

// include files
#include "Types.h"
#include "Assert.h"
#include "Exception.h"
#include <time.h>

//--------------------------------------------------------------------------------
//
// __assert__
//
// �� �Լ������� __BEGIN_TRY , __END_CATCH�� wrapping�� �ʿ䰡 ����.
//
//--------------------------------------------------------------------------------
void __assert__ ( const char * file , uint line , const char * func , const char * expr )
	throw ( AssertionError )
{
	StringStream msg;
	
	msg << "\n"
		<< "Assertion Failed : " << file << " : " << line;

	if ( func )
		msg << " : " << func;

	time_t currentTime = time(0);
	
	msg << expr << " at " << ctime(&currentTime);
	
	ofstream ofile("assertion_failed.log",ios::app);
	ofile << msg.toString() << endl;
	ofile.close();

	throw AssertionError( msg.toString() );
}

//--------------------------------------------------------------------------------
//
// ���ο� Ư�� ������ BAN �ϰ�, �α׸� ����� �ڵ尡 �� �� ������?
//
//--------------------------------------------------------------------------------
void __protocol_assert__ ( const char * file , uint line , const char * func , const char * expr )
	throw ( InvalidProtocolException )
{
	StringStream msg;
	
	msg << "\n"
		<< "Protocol Assertion Failed : " << file << " : " << line;

	if ( func )
		msg << " : " << func;

	time_t currentTime = time(0);
	
	msg << expr << " at " << ctime(&currentTime);
	
	ofstream ofile("protocol_assertion_failed.log",ios::app);
	ofile << msg.toString() << endl;
	ofile.close();

	throw InvalidProtocolException( msg.toString() );
}
