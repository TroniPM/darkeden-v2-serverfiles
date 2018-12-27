//--------------------------------------------------------------------------------
// 
// Filename    : UCRequestLoginMode.cpp
// Written By  : Reiot
// Description : 
// 
//////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------------------

// include files
#include "UCRequestLoginMode.h"

//--------------------------------------------------------------------------------
// read from socket input stream
//--------------------------------------------------------------------------------
void UCRequestLoginMode::read ( Socket * pSocket )
	
{
	__BEGIN_TRY

	//--------------------------------------------------------------------------------
	// read resource
	//--------------------------------------------------------------------------------
	pSocket->receive( &m_LoginMode, szBYTE );

	__END_CATCH
}


//--------------------------------------------------------------------------------
// write to socket output stream
//--------------------------------------------------------------------------------
void UCRequestLoginMode::write ( Socket * pSocket ) const
	
{
	__BEGIN_TRY

	//--------------------------------------------------------------------------------
	// write resource
	//--------------------------------------------------------------------------------
	pSocket->send( &m_LoginMode, szBYTE );

	__END_CATCH
}


//--------------------------------------------------------------------------------
// execute packet's handler
//--------------------------------------------------------------------------------
void UCRequestLoginMode::execute ( Player * pPlayer ) 
	 
{
	__BEGIN_TRY
		
	UCRequestLoginModeHandler::execute( this , pPlayer );
		
	__END_CATCH
}


//--------------------------------------------------------------------------------
// get debug string
//--------------------------------------------------------------------------------
string UCRequestLoginMode::toString () const
	
{
	StringStream msg;

	msg << "UCRequestLoginMode("
		<< (int)m_LoginMode
		<< ")";

	return msg.toString();
}
