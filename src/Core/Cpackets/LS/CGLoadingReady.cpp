//////////////////////////////////////////////////////////////////////////////
// Filename    : CGReady.cpp
// Written By  : Reiot
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGLoadingReady.h"

void CGLoadingReady::read (SocketInputStream & iStream)
	
{
	__BEGIN_TRY
	iStream.read(m_Type);
	__END_CATCH
}

void CGLoadingReady::write (SocketOutputStream & oStream) const
	
{
	__BEGIN_TRY
	oStream.write(m_Type);
	__END_CATCH
}

void CGLoadingReady::execute (Player* pPlayer) 
	 
{
	__BEGIN_TRY
		
	CGLoadingReadyHandler::execute(this , pPlayer);
		
	__END_CATCH
}
