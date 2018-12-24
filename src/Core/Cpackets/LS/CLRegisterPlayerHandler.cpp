//////////////////////////////////////////////////////////////////////////////
// Filename    : CLRegisterPlayerHandler.cpp
// Written By  : Reiot
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CLRegisterPlayer.h"

#ifdef __LOGIN_SERVER__
	#include "LoginPlayer.h"
	#include "Assert.h"
	#include "DB.h"
    #include "GameServerGroupInfoManager.h"

	#include "Lpackets/LCRegisterPlayerError.h"
	#include "Lpackets/LCRegisterPlayerOK.h"
#endif

//////////////////////////////////////////////////////////////////////////////
// Ŭ���̾�Ʈ���� �÷��̾� ��� ������ ���� ���, ���������� �켱
// ���� ���̵� "guest"���� üũ�ϰ�, ������ ��Ŷ���� üũ�� ��,
// ����� ������ DB�� ����ϰ���, ������ �����Ѵ�.
//////////////////////////////////////////////////////////////////////////////
void CLRegisterPlayerHandler::execute (CLRegisterPlayer* pPacket , Player* pPlayer)
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#ifdef __LOGIN_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	__BEGIN_DEBUG

	LoginPlayer* pLoginPlayer = dynamic_cast<LoginPlayer*>(pPlayer);

	//cout << "Registering Player... " << endl;

	//----------------------------------------------------------------------
	// �α��� �÷��̾��� ���̵� guest ���� üũ�Ѵ�.
	//----------------------------------------------------------------------
//	if (pLoginPlayer->getID() != "guest")
//		throw InvalidProtocolException("must be guest user");

	//----------------------------------------------------------------------
	// �÷��̾� ���� ����
	// �� ��Ʈ���� ���� �� NULL ���θ� üũ�Ѵ�.
	//----------------------------------------------------------------------
	LCRegisterPlayerError lcRegisterPlayerError;

	try {

		//cout << "�÷��̾� ���� ���� : " << pPacket->toString() << endl;

		if (pPacket->getID() == "") {
			lcRegisterPlayerError.setErrorID(EMPTY_ID);	
			throw string("ID field is empty");
		}

		if (pPacket->getID().size() < 4) {
			lcRegisterPlayerError.setErrorID(SMALL_ID_LENGTH);	
			throw string("too small ID length");
		}

		if (pPacket->getPassword() == "") 
		{
			lcRegisterPlayerError.setErrorID(EMPTY_PASSWORD);	
			throw string("Password field is empty");
		}
		else
		{
			string password = pPacket->getPassword();
			if (password.find("\'") < password.size()) throw string("Invalid Password");
			if (password.find("'") < password.size()) throw string("Invalid Password");
			else if (password.find("\\") < password.size()) throw string("Invalid Password");
			else if (password.find("\"") < password.size()) throw string("Invalid Password");
			else if (password.find(";") < password.size()) throw string("Invalid Password");
		}

		if (pPacket->getPassword().size() < 6) {
			lcRegisterPlayerError.setErrorID(SMALL_PASSWORD_LENGTH);	
			throw string("too small password length");
		}

		if (pPacket->getName() == "") {
			lcRegisterPlayerError.setErrorID(EMPTY_NAME);	
			throw string("Name field is empty");
		}

		if (pPacket->getSSN() == "") {
			lcRegisterPlayerError.setErrorID(EMPTY_SSN);	
			throw string("SSN field is empty");
		}

	} catch (string & errstr) {

		pLoginPlayer->sendPacket(&lcRegisterPlayerError);

		//cout << lcRegisterPlayerError.toString() << endl;

		// �ϴ� ���۸� �÷����ϰ�, ������ �����Ѵ�.
		//
		// *TODO*
		// ���� ȸ���� ������ ��, �� ȸ������ ���� ��쿡�� ��� ������ �����ϵ��� �Ѵ�.
		//
		throw DisconnectException(lcRegisterPlayerError.toString());
	}
		

	//----------------------------------------------------------------------
	// ���� ����Ÿ���̽��� ����ϵ��� �Ѵ�.
	//----------------------------------------------------------------------

	Statement* pStmt;
	Result* pResult;

	try {

		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		//--------------------------------------------------------------------------------
		// ���̵� �ߺ� ���θ� üũ�Ѵ�.
		//--------------------------------------------------------------------------------
		pResult = pStmt->executeQuery("SELECT PlayerID FROM Player WHERE PlayerID = '%s'" , pPacket->getID().c_str());

		if (pResult->getRowCount() != 0) {
			lcRegisterPlayerError.setErrorID(ALREADY_REGISTER_ID);	
			throw DuplicatedException("�׷� ���̵� �̹� �����մϴ�.");
		}


		//--------------------------------------------------------------------------------
		// �ֹε�Ϲ�ȣ�� �����Ѵ�. ���߿�.. -_-;
		//--------------------------------------------------------------------------------


		//--------------------------------------------------------------------------------
		// �ֹε�Ϲ�ȣ �ߺ� ���θ� üũ�Ѵ�. 
		//--------------------------------------------------------------------------------
		pResult = pStmt->executeQuery("SELECT SSN FROM Player WHERE SSN = '%s'" , pPacket->getSSN().c_str());

		if (pResult->getRowCount() != 0) {
			lcRegisterPlayerError.setErrorID(ALREADY_REGISTER_SSN);
			throw DuplicatedException("�̹� ��ϵ� �ֹε�Ϲ�ȣ�Դϴ�.");
		}


		//--------------------------------------------------------------------------------
		// �÷��̾ ����Ѵ�.
		//--------------------------------------------------------------------------------
		pResult = pStmt->executeQuery(
			"INSERT INTO Player (PlayerID , Password , Name , Sex , SSN , Telephone , Cellular , Zipcode , Address , Nation , Email , Homepage , Profile , Pub) VALUES ('%s' , PASSWORD('%s') , '%s' , '%s' , '%s' , '%s' , '%s' , '%s' , '%s' , %d , '%s' , '%s' , '%s' , '%s')" ,
			pPacket->getID().c_str() , 
			pPacket->getPassword().c_str() , 
			pPacket->getName().c_str() , 
			Sex2String[ pPacket->getSex() ].c_str() , 
			pPacket->getSSN().c_str() , 
			pPacket->getTelephone().c_str() , 
			pPacket->getCellular().c_str() , 
			pPacket->getZipCode().c_str() , 
			pPacket->getAddress().c_str() , 
			(int)pPacket->getNation() ,
			pPacket->getEmail().c_str() , 
			pPacket->getHomepage().c_str() , 
			pPacket->getProfile().c_str() , 
			(pPacket->getPublic() == true) ? "PUBLIC" : "PRIVATE" 
		);
				
		// ������� �Դٸ�, DB�� �÷��̾ �� �߰��Ǿ��ٴ� �ǹ̰� �ȴ�.
		// �÷��̾�� ����� �� �Ǿ��ٴ� LCRegisterPlayerOK ��Ŷ�� ������.
		Assert(pResult == NULL);
		Assert(pStmt->getAffectedRowCount() == 1);

		// ����� �� ����Ʈ ������ �׷� ���̵� �޾ƿ´�.
		pResult = pStmt->executeQuery("SELECT CurrentWorldID, CurrentServerGroupID FROM Player WHERE PlayerID = '%s'" , pPacket->getID().c_str());

		if (pResult->getRowCount() == 0) {
			lcRegisterPlayerError.setErrorID(ETC_ERROR);
			throw SQLQueryException("���������� �����ͺ��̽��� �Է�, ��� ���� �ʾҽ��ϴ�.");
		}

		WorldID_t 		 WorldID = 0;
		ServerGroupID_t  ServerGroupID = 0;

		if (pResult->next()) throw SQLQueryException("�����ͺ��̽��� ġ������ ������ �ֽ��ϴ�.");

		WorldID = pResult->getInt(1);
		ServerGroupID = pResult->getInt(2);

		pLoginPlayer->setServerGroupID(ServerGroupID);

		LCRegisterPlayerOK lcRegisterPlayerOK;

		lcRegisterPlayerOK.setGroupName(g_pGameServerGroupInfoManager->getGameServerGroupInfo(ServerGroupID, WorldID)->getGroupName());

		string SSN = pPacket->getSSN();
		string preSSN;
		bool isChina = false;
		// �ѱ�
		if ( strstr(SSN.c_str(), "-") != NULL )
		{
			preSSN = SSN.substr(0, 6);
		}
		// �߱�
		else 
		{
			isChina = true;
			if (SSN.size() == 15)
			{
				preSSN = SSN.substr(6, 12);
			}
			else if (SSN.size() == 18)
			{
				preSSN = SSN.substr(8, 14);
			}
			else
			{
				// �̷� ���� ���ٰ� ������ -_- �� ��ư
			 	preSSN = SSN.substr(0, 6);
			}

			//add by zdj 2005.5.11
			//���ϴ����д���,������������
			preSSN = "781109";
		}
//        string preSSN = pPacket->getSSN().substr(0, 6).c_str();

		StringStream AdultSSN;

		time_t daytime = time(0);
		tm Timec;
		localtime_r( &daytime, &Timec );
		AdultSSN << Timec.tm_year - 20 << Timec.tm_mon << Timec.tm_mday;

		// �������� �ƴ��� �ֹε�� ��ȣ üũ
		if (atoi(preSSN.c_str()) <= atoi(AdultSSN.toString().c_str())) {
			lcRegisterPlayerOK.setAdult(true);
		} else {
			lcRegisterPlayerOK.setAdult(false);
		}

		// �߱��̸� ������ ����
		if ( isChina )
		{
			lcRegisterPlayerOK.setAdult(true);
		}

		pLoginPlayer->sendPacket(&lcRegisterPlayerOK);

		// �̸��� ��������� �Ѵ�.
		pLoginPlayer->setID(pPacket->getID());

		// ��Ͽ� �������� ���, CLGetPCList ��Ŷ�� ��ٸ���.
		pLoginPlayer->setPlayerStatus(LPS_WAITING_FOR_CL_GET_PC_LIST);

		SAFE_DELETE(pStmt);
	} 
	catch (DuplicatedException & de) 
	{
		SAFE_DELETE(pStmt);

		//cout << de.toString() << endl;

		//--------------------------------------------------------------------------------
		// ��� ���� ��Ŷ�� �����Ѵ�.
		//--------------------------------------------------------------------------------
		pLoginPlayer->sendPacket(&lcRegisterPlayerError);

		//--------------------------------------------------------------------------------
		// ���� ȸ���� ������Ų��. �ʹ� ���� �������� ���, ������ �����Ѵ�.
		//--------------------------------------------------------------------------------
		uint nFailed = pLoginPlayer->getFailureCount();

		//cout << pLoginPlayer->getID() << "'s Failure Count = " << ++nFailed << endl;

		if (nFailed > 3) 
			throw DisconnectException("too many failure");

		pLoginPlayer->setFailureCount(nFailed);

		// ��Ͽ� ������ ���, �ٽ� CLRegisterPlayer ��Ŷ�� ��ٸ���.
		pLoginPlayer->setPlayerStatus(LPS_WAITING_FOR_CL_REGISTER_PLAYER);

	} 
	catch (SQLQueryException & sqe) 
	{
		SAFE_DELETE(pStmt);

		// ��. SQL �����̵��� ����� �� �ȵǾ��ٴ� �Ҹ���.
		//cout << sqe.toString() << endl;

		//--------------------------------------------------------------------------------
		// ��� ���� ��Ŷ�� �����Ѵ�.
		//--------------------------------------------------------------------------------
		lcRegisterPlayerError.setErrorID(ETC_ERROR);

		pLoginPlayer->sendPacket(&lcRegisterPlayerError);

		//--------------------------------------------------------------------------------
		// ���� ȸ���� ������Ų��. �ʹ� ���� �������� ���, ������ �����Ѵ�.
		//--------------------------------------------------------------------------------
		uint nFailed = pLoginPlayer->getFailureCount();

		//cout << pLoginPlayer->getID() << "'s Failure Count = " << ++nFailed << endl;

		if (nFailed > 3) 
			throw DisconnectException("too many failure");

		pLoginPlayer->setFailureCount(nFailed);

		// ��Ͽ� ������ ���, �ٽ� CLRegisterPlayer ��Ŷ�� ��ٸ���.
		pLoginPlayer->setPlayerStatus(LPS_WAITING_FOR_CL_REGISTER_PLAYER);

	}

	__END_DEBUG

#endif
		
	__END_DEBUG_EX __END_CATCH
}
