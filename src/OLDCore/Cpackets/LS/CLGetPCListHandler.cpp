//////////////////////////////////////////////////////////////////////////////
// Filename    : CLGetPCListHandler.cpp
// Written By  : Reiot
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CLGetPCList.h"

#ifdef __LOGIN_SERVER__
	#include "LoginPlayer.h"
	#include "Assert.h"
	#include "DB.h"
	#include "GameServerInfoManager.h"
	#include "OptionInfo.h"

	#include "Lpackets/LCPCList.h"
#endif

//////////////////////////////////////////////////////////////////////////////
// Ŭ���̾�Ʈ�� PC �� ����Ʈ�� �޶�� ��û�ؿ���, �α��� ������ DB�κ���
// PC���� ������ �ε��ؼ� LCPCList ��Ŷ�� ��Ƽ� �����Ѵ�.
//////////////////////////////////////////////////////////////////////////////
void CLGetPCListHandler::execute (CLGetPCList* pPacket , Player* pPlayer)
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __LOGIN_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	LoginPlayer* pLoginPlayer = dynamic_cast<LoginPlayer*>(pPlayer);

	pLoginPlayer->setPlayerStatus(LPS_PC_MANAGEMENT);


	//----------------------------------------------------------------------
	// ���� LCPCList ��Ŷ�� ����� ������
	//----------------------------------------------------------------------
	LCPCList lcPCList;
	pLoginPlayer->makePCList( lcPCList );
	pLoginPlayer->sendPacket(&lcPCList);
	pLoginPlayer->setPlayerStatus(LPS_PC_MANAGEMENT);


#endif

	__END_DEBUG_EX __END_CATCH
}
