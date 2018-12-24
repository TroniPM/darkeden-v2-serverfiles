//////////////////////////////////////////////////////////////////////////////
// Filename    : CLGetWorldListHandler.cpp
// Written By  : Reiot
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CLGetWorldList.h"

#ifdef __LOGIN_SERVER__
	#include "LoginPlayer.h"
	#include "Assert.h"
	#include "DB.h"
	#include "GameWorldInfoManager.h"
	#include "WorldInfo.h"

	#include "Lpackets/LCWorldList.h"
#endif

//////////////////////////////////////////////////////////////////////////////
// Ŭ���̾�Ʈ�� ������ ����Ʈ�� �޶�� ��û�ؿ���, �α��� ������ DB�κ���
// �������� ������ �ε��ؼ� LCWorldList ��Ŷ�� ��Ƽ� �����Ѵ�.
//////////////////////////////////////////////////////////////////////////////
void CLGetWorldListHandler::execute (CLGetWorldList* pPacket , Player* pPlayer)
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __LOGIN_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);
	//cout << "Start execute" << endl;

	LoginPlayer* pLoginPlayer = dynamic_cast<LoginPlayer*>(pPlayer);

	try 
	{
		int Num = g_pGameWorldInfoManager->getSize();

		//cout << "WorldNum : " << Num << endl;

		WorldInfo* aWorldInfo[Num];

		for(int i = 1 ; i < Num + 1; i++) 
		{
			WorldInfo* pWorldInfo = new WorldInfo();
			GameWorldInfo* pGameWorldInfo = g_pGameWorldInfoManager->getGameWorldInfo(i);
			pWorldInfo->setID(pGameWorldInfo->getID());
			pWorldInfo->setName(pGameWorldInfo->getName());

			// by bezz. 2002.12.20 
			pWorldInfo->setStat(pGameWorldInfo->getStatus());

			aWorldInfo[i] = pWorldInfo;

			// Ʈ����(2) ����
			//if (i==2) pWorldInfo->setStat(WORLD_CLOSE);

			//cout << "AddWorld : " << pWorldInfo->getName() << endl;
		}

		LCWorldList lcWorldList;

		Statement * pStmt = NULL;

		BEGIN_DB
		{
			pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

			Result * pResult = pStmt->executeQuery("SELECT CurrentWorldID FROM Player where PlayerID='%s'" , pLoginPlayer->getID().c_str() );

			if( pResult->next() ) {
				lcWorldList.setCurrentWorldID( pResult->getInt(1) );
			}

			SAFE_DELETE(pStmt); // by sigi
		}
		END_DB(pStmt) // by sigi

		for(int k = 1; k < Num + 1; k++) 
		{
			lcWorldList.addListElement(aWorldInfo[k]);
		}

		pLoginPlayer->sendPacket(&lcWorldList);
	
//		pLoginPlayer->setPlayerStatus(LPS_PC_MANAGEMENT);
	} 
	catch (Throwable & t) 
	{
		//cout << t.toString() << endl;
	}
	//cout << "End execute" << endl;

#endif

	__END_DEBUG_EX __END_CATCH
}
