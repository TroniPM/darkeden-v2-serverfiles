//////////////////////////////////////////////////////////////////////////////
// Filename    : CLChangeServerHandler.cpp
// Written By  :
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CLChangeServer.h"

#ifdef __LOGIN_SERVER__
	#include "Assert.h"
	#include "LoginPlayer.h"
	#include "DatabaseManager.h"
	#include "GameServerInfoManager.h"
	#include "DB.h"
	#include "GameServerGroupInfoManager.h"
	#include "OptionInfo.h"

	#include "Lpackets/LCPCList.h"
#endif

//////////////////////////////////////////////////////////////////////////////
// Ŭ���̾�Ʈ�� PC �� ����Ʈ�� �޶�� ��û�ؿ���, �α��� ������ DB�κ���
// PC���� ������ �ε��ؼ� LCPCList ��Ŷ�� ��Ƽ� �����Ѵ�.
//////////////////////////////////////////////////////////////////////////////
void CLChangeServerHandler::execute (CLChangeServer* pPacket , Player* pPlayer)
	 
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __LOGIN_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	LoginPlayer* pLoginPlayer = dynamic_cast<LoginPlayer*>(pPlayer);

	ServerGroupID_t CurrentServerGroupID = pPacket->getServerGroupID();
	pLoginPlayer->setServerGroupID(CurrentServerGroupID);

	Statement* pStmt       = NULL;

	try
	{
		pStmt    = g_pDatabaseManager->getConnection( "DARKEDEN" )->createStatement();	

		//----------------------------------------------------------------------
		// ���� LCPCList ��Ŷ�� ���� ������
		//----------------------------------------------------------------------
		LCPCList lcPCList;

		pLoginPlayer->makePCList( lcPCList );
		pLoginPlayer->sendPacket(&lcPCList);
		pLoginPlayer->setPlayerStatus(LPS_PC_MANAGEMENT);

		pStmt->executeQuery("UPDATE Player set CurrentServerGroupID = %d WHERE PlayerID = '%s'", (int)pPacket->getServerGroupID(), pLoginPlayer->getID().c_str());

		// ���� ��� �� ������ ��ü�� �����Ѵ�.
		SAFE_DELETE(pStmt);
	}
	catch (SQLQueryException & sce) 
	{
		//cout << sce.toString() << endl;

		// ���� ��� �� ������ ��ü�� �����Ѵ�.
		SAFE_DELETE(pStmt);

		throw DisconnectException(sce.toString());
	}

#endif

	__END_DEBUG_EX __END_CATCH
}
