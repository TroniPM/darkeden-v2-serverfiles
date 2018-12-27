//////////////////////////////////////////////////////////////////////////////
// Filename    : CLQueryCharacterNameHandler.cpp
// Written By  : Reiot
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CLQueryCharacterName.h"

#ifdef __LOGIN_SERVER__
	#include "LoginPlayer.h"

	#include "DatabaseManager.h"
	#include "Connection.h"
	#include "Statement.h"
	#include "Result.h"
	#include "Assert.h"
	#include "GameWorldInfoManager.h"

	#include "Lpackets/LCQueryResultCharacterName.h"
#endif

bool isAvailableID(const char* pID);

//////////////////////////////////////////////////////////////////////////////
// DB �κ��� Ư�� �÷��̾� ���̵� ã�Ƽ� �� ���θ� Ŭ���̾�Ʈ�� �������ش�.
//////////////////////////////////////////////////////////////////////////////
void CLQueryCharacterNameHandler::execute (CLQueryCharacterName* pPacket , Player* pPlayer)
	 
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#ifdef __LOGIN_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	LoginPlayer* pLoginPlayer = dynamic_cast<LoginPlayer*>(pPlayer);

	WorldID_t WorldID = pLoginPlayer->getWorldID();

	Assert( WorldID <= g_pGameWorldInfoManager->getSize() );

	Statement* pStmt = NULL;

	try {

		pStmt = g_pDatabaseManager->getConnection( WorldID )->createStatement();

		Result* pResult = pStmt->executeQuery(
			"SELECT Name FROM Slayer WHERE Name = '%s'" , 
			pPacket->getCharacterName().c_str() 
		); 

		LCQueryResultCharacterName lcQueryResultCharacterName;

		//cout << "Query Result : " << pPacket->getCharacterName() << " is ";

		lcQueryResultCharacterName.setCharacterName(pPacket->getCharacterName());

		if (pResult->getRowCount() == 0) {
		
			lcQueryResultCharacterName.setExist(false);

			//cout << "not ";

		} else {

			lcQueryResultCharacterName.setExist(true);

		}

		//--------------------------------------------------------------------------------
		// ��ڿ� ���õ� �̸��� �ƴ��� �����Ѵ�.
		//--------------------------------------------------------------------------------
		// by sigi
		if (!isAvailableID(pPacket->getCharacterName().c_str()))
		{
			lcQueryResultCharacterName.setExist(true);
		}

		/*
		string text = pPacket->getCharacterName();

		list<string> InvalidTokenList;
		InvalidTokenList.push_back("������");
		InvalidTokenList.push_back("�����");
		InvalidTokenList.push_back("�����");
		InvalidTokenList.push_back("�");
		InvalidTokenList.push_back("��ȹ��");
		InvalidTokenList.push_back("������");
		InvalidTokenList.push_back("�׽���");
		InvalidTokenList.push_back("����");
		list<string>::const_iterator itr = InvalidTokenList.begin();
		for (; itr != InvalidTokenList.end(); itr++)
		{
			if (text.find(*itr) != string::npos)
			{
				lcQueryResultCharacterName.setExist(false);
			}
		}
		*/

		//cout << "exist..." << endl;
		
		pLoginPlayer->sendPacket(&lcQueryResultCharacterName);

		// ������ ���� �� �� �� �����Ƿ�, ������ LWFRP �̴�.
		// ������ �������� ���α׷��� ¥�� DOS ������ �� �� �����Ƿ�,
		// �ּ� �ð��� �־� �Ѵٴ� ���̴�.
		pLoginPlayer->setPlayerStatus(LPS_WAITING_FOR_CL_GET_PC_LIST);
			
		SAFE_DELETE(pStmt);
		//delete pStmt;		// 2002.1.16 by sigi
	} 
	catch (SQLQueryException & sqe) 
	{
		SAFE_DELETE(pStmt);
		throw;
	}
	
#endif
		
	__END_DEBUG_EX __END_CATCH
}
