//////////////////////////////////////////////////////////////////////////////
// Filename    : CGReady.cpp
// Written By  : Reiot
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGLoadingGearReady.h"

void CGLoadingGearReady::read (SocketInputStream & iStream)
	
{
	__BEGIN_TRY
	__END_CATCH
}

void CGLoadingGearReady::write (SocketOutputStream & oStream) const
	
{
	__BEGIN_TRY
	__END_CATCH
}

void CGLoadingGearReady::execute (Player* pPlayer) 
	 
{
	__BEGIN_TRY
		
	CGLoadingGearReadyHandler::execute(this , pPlayer);
		
	__END_CATCH
}