//--------------------------------------------------------------------------------
//
// Filename    : GCReconnectLoginHandler.cpp
// Written By  : Reiot
// Description : 
//
//--------------------------------------------------------------------------------

// include files
#include "GCReconnectLogin.h"

#ifdef __GAME_CLIENT__
	#include "ClientPlayer.h"
	#include "Cpackets/CGConnect.h"
#endif

//--------------------------------------------------------------------------------
// �α��μ����κ��� ���� ������ �ּҿ� ��Ʈ, �׸��� ����Ű�� ���� ���
// ���� ������ ������ ��, ����Ű�� ���� CGConnect ��Ŷ�� �����Ѵ�.
//--------------------------------------------------------------------------------
void GCReconnectLoginHandler::execute ( GCReconnectLogin * pPacket , Player * pPlayer )
	 
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
#ifdef __GAME_CLIENT__
#endif
	__END_DEBUG_EX __END_CATCH
}
