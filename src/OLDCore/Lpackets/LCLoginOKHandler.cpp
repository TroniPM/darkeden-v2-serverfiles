//----------------------------------------------------------------------
//
// Filename    : LCLoginOKHandler.cpp
// Written By  : Reiot
// Description : 
//
//----------------------------------------------------------------------

// include files
#include "LCLoginOK.h"

#ifdef __GAME_CLIENT__

	#include "ClientPlayer.h"
	#include "Cpackets/CLGetPCList.h"

#endif

//----------------------------------------------------------------------
//
// �α��� �����κ��� ���̵�� �н������� ������ �޾Ҵٴ� �Ҹ���.
//
// ���� �α��� �������� PC �� ����Ʈ�� ��û�ϴ� ��Ŷ�� �����ϸ� �ȴ�.
//
//----------------------------------------------------------------------
void LCLoginOKHandler::execute ( LCLoginOK * pPacket , Player * pPlayer )
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_CLIENT__

	ClientPlayer * pClientPlayer = dynamic_cast<ClientPlayer*>(pPlayer);

	CLGetPCList clGetPCList;

	pClientPlayer->sendPacket( &clGetPCList );
	
	// �÷��̾��� ���¸� �ٲ۴�.
	pClientPlayer->setPlayerStatus( CPS_AFTER_SENDING_CL_GET_PC_LIST );

#endif

	__END_DEBUG_EX __END_CATCH
}
