//--------------------------------------------------------------------------------
//
// Filename    : LCDeletePCOKHandler.cpp
// Written By  : Reiot
// Description : 
//
//--------------------------------------------------------------------------------

// include files
#include "LCDeletePCOK.h"

#ifdef __GAME_CLIENT__
	#include "ClientPlayer.h"
	#include "Cpackets/CLGetPCList.h"
#endif

//--------------------------------------------------------------------------------
//
// PC �� ���������� �����ߴٴ� ���̴�.
//
//--------------------------------------------------------------------------------
void LCDeletePCOKHandler::execute ( LCDeletePCOK * pPacket , Player * pPlayer )
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_CLIENT__

	#if __LINUX__

		ClientPlayer * pClientPlayer = dynamic_cast<ClientPlayer*>(pPlayer);

		cout << "                            " << endl;
		cout << "+--------------------------+" << endl;
		cout << "| PC deleted successfully! |" << endl;
		cout << "+--------------------------+" << endl;
		cout << "                            " << endl;

		// �ٽ� PC LIST �� �޾ƿ;� �Ѵ�.
		CLGetPCList clGetPCList;
		pClientPlayer->sendPacket( &clGetPCList );	

		pClientPlayer->setPlayerStatus( CPS_AFTER_SENDING_CL_GET_PC_LIST );

	#elif __WINDOWS__

	#endif
	
#endif

	__END_DEBUG_EX __END_CATCH
}
