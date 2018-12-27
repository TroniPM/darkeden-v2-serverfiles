//--------------------------------------------------------------------------------
// 
// Filename    : UCUpdateList.cpp
// Written By  : Reiot
// Description : 
// 
//////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------------------

// include files
#include "UCUpdateList.h"

//--------------------------------------------------------------------------------
// read from socket 
//--------------------------------------------------------------------------------
void UCUpdateList::read ( Socket * pSocket )
	
{
	__BEGIN_TRY

	if ( isFront() ) if ( !isOld() ) pSocket->receive( m_Key, szBYTE * 10 );
	m_pUpdateManager->read( pSocket );
	if ( !isFront() ) if ( !isOld() ) pSocket->receive( m_Key, szBYTE * 10 );

	__END_CATCH
}


//--------------------------------------------------------------------------------
// write to socket output stream
//--------------------------------------------------------------------------------
void UCUpdateList::write ( Socket * pSocket ) const
	
{
	__BEGIN_TRY

	if ( isFront() ) if ( !isOld() ) pSocket->send( m_Key, szBYTE * 10 );
	m_pUpdateManager->write( pSocket );
	if ( !isFront() ) if ( !isOld() ) pSocket->send( m_Key, szBYTE * 10 );
	
	__END_CATCH
}


//--------------------------------------------------------------------------------
// execute packet's handler
//--------------------------------------------------------------------------------
void UCUpdateList::execute ( Player * pPlayer ) 
	 
{
	__BEGIN_TRY
		
	UCUpdateListHandler::execute( this , pPlayer );
		
	__END_CATCH
}


//--------------------------------------------------------------------------------
// get debug string
//--------------------------------------------------------------------------------
string UCUpdateList::toString() const
	
{
	StringStream msg;

	msg << "UCUpdateList(" << eos
		<< m_pUpdateManager->toString()
		<< ")";

	return msg.toString();
}
