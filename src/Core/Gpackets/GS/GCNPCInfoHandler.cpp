//----------------------------------------------------------------------
//
// Filename    : GCNPCInfoHandler.cpp
// Written By  : Reiot
// Description : 
//
//----------------------------------------------------------------------

// include files
#include "GCNPCInfo.h"

#ifdef __GAME_CLIENT__

	#include "ClientPlayer.h"
	#include "PCSlayerInfo2.h"
	#include "PCVampireInfo2.h"
	#include "Cpackets/CGReady.h"

#endif

//----------------------------------------------------------------------
// Ŭ���̾�Ʈ�� ���� �����κ��� GCNPCInfo ��Ŷ�� �ް� �Ǹ�,
// ��Ŷ ���� �����͵��� Ŭ���̾�Ʈ�� ������ ��, ������ �ε���
// ���� ���� ���� ������ CGReady ��Ŷ�� ������ �ȴ�.
//----------------------------------------------------------------------
void GCNPCInfoHandler::execute ( GCNPCInfo * pPacket , Player * pPlayer )
	 
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_CLIENT__

#endif

	__END_DEBUG_EX __END_CATCH
}
