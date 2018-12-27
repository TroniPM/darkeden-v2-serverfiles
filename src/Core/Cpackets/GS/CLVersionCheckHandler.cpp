//////////////////////////////////////////////////////////////////////////////
// Filename    : CLVersionCheckHandler.cpp
// Written By  : elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CLVersionCheck.h"

#ifdef __LOGIN_SERVER__
	#include "LoginPlayer.h"
	#include "DB.h"
	#include "Assert.h"

	#include "Lpackets/LCVersionCheckOK.h"
	#include "Lpackets/LCVersionCheckError.h"
#endif

//////////////////////////////////////////////////////////////////////////////
// �� ��Ŷ�� Ŭ���̾�Ʈ�� ���̵�� �н����带 ��ȣȭ�ؼ� 
// �α��� ������ �����Ѵ�. �α��� ������ �� ��Ŷ�� �޾Ƽ�
// �÷��̾��� ���̵�� �н����尡 ��Ȯ���� DB�κ��� �о
// ���� ��, �α����� ���� ���θ� �����Ѵ�.
//////////////////////////////////////////////////////////////////////////////
void CLVersionCheckHandler::execute (CLVersionCheck* pPacket , Player* pPlayer)
	 
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#ifdef __LOGIN_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	LoginPlayer* pLoginPlayer = dynamic_cast<LoginPlayer*>(pPlayer);
	Statement*   pStmt        = NULL;
	Result*      pResult      = NULL;

	BEGIN_DB
	{
		//----------------------------------------------------------------------
		// *CAUTION*
		// Server�� �ִ� Version Field�� UpdateServer�� �׻� ���Ͻ� �ؾ��Ѵ�.
		//----------------------------------------------------------------------

		pStmt   = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pResult = pStmt->executeQuery("SELECT Version, ServerVersion FROM ClientVersion");

		// ���� ��� ROW �� ������ 0 �̶�� ���� 
		// Update���� ���� Ŭ���̾�Ʈ�̴�.
		// ���� ���α׷��� �簡�� �ϰ� ������Ʈ�� �ϰ� �ؾ� �Ѵ�.
		Assert(pResult->getRowCount() != 0);
		pResult->next();

		DWORD Version       = pResult->getInt(1);
		DWORD ServerVersion       = pResult->getInt(2);
		DWORD ClientVersion = pPacket->getVersion();
		DWORD CServerVersion = pPacket->getServerVersion();

		if (Version == ClientVersion && ServerVersion == CServerVersion ) 
		{
			// �α��� ������ �˷��ش�.
			LCVersionCheckOK lcVersionCheckOK;
			pLoginPlayer->sendPacket(&lcVersionCheckOK);
		} 
		else 
		{
			LCVersionCheckError lcVersionCheckError;
			pLoginPlayer->sendPacket(&lcVersionCheckError);
			//pLoginPlayer->disconnect(DISCONNECTED);
		}

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

#endif

	__END_DEBUG_EX __END_CATCH
}
