//////////////////////////////////////////////////////////////////////////////
// Filename    : CGModifyNickname.cpp 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////
#include "CGModifyNickname.h"

CGModifyNickname::CGModifyNickname () 
     
{
	__BEGIN_TRY
	__END_CATCH
}

CGModifyNickname::~CGModifyNickname () 
    
{
	__BEGIN_TRY
	__END_CATCH
}

void CGModifyNickname::read (SocketInputStream & iStream) 
	 
{
	__BEGIN_TRY

	iStream.read( m_ItemObjectID );

	BYTE szSTR;
	iStream.read( szSTR );
	if ( szSTR != 0 ) iStream.read( m_Nickname, szSTR );

	__END_CATCH
}

void CGModifyNickname::write (SocketOutputStream & oStream) const 
     
{
	__BEGIN_TRY

	oStream.write( m_ItemObjectID );

	BYTE szSTR;
	szSTR = m_Nickname.size();
	oStream.write( szSTR );
	if ( szSTR != 0 ) oStream.write( m_Nickname );

	__END_CATCH
}

void CGModifyNickname::execute (Player* pPlayer) 
	 
{
	__BEGIN_TRY

	CGModifyNicknameHandler::execute (this , pPlayer);
		
	__END_CATCH
}

string CGModifyNickname::toString () 
	
{
	__BEGIN_TRY
		
	StringStream msg;
	msg << "CGModifyNickname("
		<< ")";
	return msg.toString();

	__END_CATCH
}
