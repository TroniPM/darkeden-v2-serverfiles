//----------------------------------------------------------------------
//
// Filename    : GCUpdateInfoHandler.cpp
// Written By  : Reiot
// Description : 
//
//----------------------------------------------------------------------

// include files
#include "GCUpdateInfo.h"

#ifdef __GAME_CLIENT__

	#include "ClientPlayer.h"
	#include "PCSlayerInfo2.h"
	#include "PCVampireInfo2.h"
	#include "Cpackets/CGReady.h"

#endif

//----------------------------------------------------------------------
// Ŭ���̾�Ʈ�� ���� �����κ��� GCUpdateInfo ��Ŷ�� �ް� �Ǹ�,
// ��Ŷ ���� �����͵��� Ŭ���̾�Ʈ�� ������ ��, ������ �ε���
// ���� ���� ���� ������ CGReady ��Ŷ�� ������ �ȴ�.
//----------------------------------------------------------------------
void GCUpdateInfoHandler::execute ( GCUpdateInfo * pPacket , Player * pPlayer )
	 
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_CLIENT__

	ClientPlayer * pClientPlayer = dynamic_cast<ClientPlayer*>(pPlayer);

	//cout << pPacket->toString() << endl;

	//--------------------------------------------------
	// ������ �ε��� �����Ѵ�.
	//--------------------------------------------------
	pClientPlayer->setPlayerStatus( CPS_WAITING_FOR_LOADING );

		// ... �ε� �ε� ... 

	//--------------------------------------------------
	// ���� ������ CGReady ��Ŷ�� ������.
	//--------------------------------------------------
	CGReady cgReady;
	pClientPlayer->sendPacket( &cgReady );
	pClientPlayer->setPlayerStatus( CPS_WAITING_FOR_GC_SET_POSITION );

#endif

	__END_DEBUG_EX __END_CATCH
}
