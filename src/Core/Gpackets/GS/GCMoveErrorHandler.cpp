//////////////////////////////////////////////////////////////////////
//
// Filename    : GCMoveErrorHandler.cc
// Written By  : elca@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GCMoveError.h"

#ifdef __GAME_CLIENT__
	#include "ClientPlayer.h"
#endif

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCMoveErrorHandler::execute ( GCMoveError * pPacket , Player * pPlayer )
	 
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#ifdef __GAME_CLIENT__

	ClientPlayer * pClientPlayer = dynamic_cast<ClientPlayer*>(pPlayer);

	pClientPlayer->setX( pPacket->getX() );
	pClientPlayer->setY( pPacket->getY() );

	//cout << "Move Back To (" << (int)pPacket->getX() << "," << (int)pPacket->getY() << ")" << endl;
	
#elif __WINDOWS__

	AfxMessageBox( pPacket->toString().c_str() );

#endif

	__END_DEBUG_EX __END_CATCH
}
