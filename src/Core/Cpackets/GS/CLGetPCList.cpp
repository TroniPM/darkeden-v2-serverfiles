//////////////////////////////////////////////////////////////////////////////
// Filename    : CLGetPCList.cpp 
// Written By  : reiot@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CLGetPCList.h"

void CLGetPCList::read (SocketInputStream & iStream) 
	 
{
	__BEGIN_TRY
	__END_CATCH
}

void CLGetPCList::write (SocketOutputStream & oStream) const 
     
{
	__BEGIN_TRY
	__END_CATCH
}

void CLGetPCList::execute (Player* pPlayer) 
	 
{
	__BEGIN_TRY
		
	CLGetPCListHandler::execute (this , pPlayer);
		
	__END_CATCH
}

