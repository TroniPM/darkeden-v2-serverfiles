//////////////////////////////////////////////////////////////////////
//
// Filename    : GCTradeFinishHandler.cpp
// Written By  : �輺��
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GCTradeFinish.h"

void GCTradeFinishHandler::execute ( GCTradeFinish * pPacket , Player * pPlayer )
	 
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
	
#ifdef __GAME_CLIENT__
	//cout << pPacket->toString() << endl;
#endif

	__END_DEBUG_EX __END_CATCH
}
