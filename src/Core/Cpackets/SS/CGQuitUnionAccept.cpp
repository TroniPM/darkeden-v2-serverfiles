//////////////////////////////////////////////////////////////////////////////
// Filename    : CGQuitUnionAccept.cpp 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGQuitUnionAccept.h"


void CGQuitUnionAccept::read (SocketInputStream & iStream) 
	 
{
	__BEGIN_TRY
		
	iStream.read( m_GuildID );

	__END_CATCH
}

void CGQuitUnionAccept::write (SocketOutputStream & oStream) const 
     
{
	__BEGIN_TRY
		
	oStream.write( m_GuildID );

	__END_CATCH
}

void CGQuitUnionAccept::execute (Player* pPlayer) 
	 
{
	__BEGIN_TRY
		
	CGQuitUnionAcceptHandler::execute(this , pPlayer);

	__END_CATCH
}

string CGQuitUnionAccept::toString () const
       
{
	__BEGIN_TRY
		
	StringStream msg;
    msg << "CGQuitUnionAccept("
		<< "GuildID:" << m_GuildID
		<< ")" ;
	return msg.toString();

	__END_CATCH
}
