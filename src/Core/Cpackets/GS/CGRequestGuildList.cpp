//////////////////////////////////////////////////////////////////////////////
// Filename    : CGRequestGuildList.cpp 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGRequestGuildList.h"


void CGRequestGuildList::read (SocketInputStream & iStream) 
	 
{
	__BEGIN_TRY
	
	iStream.read( m_GuildType );
		
	__END_CATCH
}

void CGRequestGuildList::write (SocketOutputStream & oStream) const 
     
{
	__BEGIN_TRY
	
	oStream.write( m_GuildType );
		
	__END_CATCH
}

void CGRequestGuildList::execute (Player* pPlayer) 
	 
{
	__BEGIN_TRY
		
	CGRequestGuildListHandler::execute(this , pPlayer);

	__END_CATCH
}

string CGRequestGuildList::toString () const
       
{
	__BEGIN_TRY
		
	StringStream msg;
    msg << "CGRequestGuildList("
		<< "GuildType : " << m_GuildType
		<< ")" ;
	return msg.toString();

	__END_CATCH
}
