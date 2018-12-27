//--------------------------------------------------------------------------------
//
// Filename    : LCRegisterPlayerErrorHandler.cpp
// Written By  : Reiot
// Description : 
//
//--------------------------------------------------------------------------------

// include files
#include "LCRegisterPlayerError.h"

#ifdef __GAME_CLIENT__
	#include "ClientPlayer.h"
	#include "Cpackets/CLRegisterPlayer.h"
#endif

//--------------------------------------------------------------------------------
//
//
//
//--------------------------------------------------------------------------------
void LCRegisterPlayerErrorHandler::execute ( LCRegisterPlayerError * pPacket , Player * pPlayer )
	 
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_CLIENT__

	ClientPlayer * pClientPlayer = dynamic_cast<ClientPlayer*>(pPlayer);

	cout << endl
		<< "+-------------------------+" << endl
		<< "| FAIL TO REGISTER PLAYER |" << endl
		<< "+-------------------------+" << endl
		<< endl
		<< pPacket->getMessage() << endl;

	cout << endl
		<< "+-----------------+" << endl
		<< "| REGISTER PLAYER |" << endl
		<< "+-----------------+" << endl
		<< endl;

	CLRegisterPlayer clRegisterPlayer;
	char cmd[80];

	cout << "���̵� : ";
	cin.getline(cmd,80);
	clRegisterPlayer.setID(cmd);

	cout << "�н����� : ";
	cin.getline(cmd,80);
	clRegisterPlayer.setPassword(cmd);

	cout << "�̸� : ";
	cin.getline(cmd,80);
	clRegisterPlayer.setName(cmd);

	cout << "���� (��/��) : ";
	cin.getline(cmd,80);
	Sex sex;
	if ( strcmp(cmd,"��") == 0 ) sex = MALE;
	if ( strcmp(cmd,"��") == 0 ) sex = FEMALE;
	else sex = MALE;
	cout << "Sex : " << Sex2String[sex] << endl;
	clRegisterPlayer.setSex(sex);

	clRegisterPlayer.setSSN("800101-2000111");
	clRegisterPlayer.setTelephone("02-222-3333");
	clRegisterPlayer.setCellular("011-222-3333");
	clRegisterPlayer.setZipCode("700-441");
	clRegisterPlayer.setAddress("����Ư���� �������� ���ǵ��� �缭�� 300����");
	clRegisterPlayer.setNation( KOREA );
	clRegisterPlayer.setEmail("jhkim@mbc.com");
	clRegisterPlayer.setHomepage("www.jhkim.com");
	clRegisterPlayer.setProfile("��ũ���� ���� ������");
	clRegisterPlayer.setPublic(false);

	cout << clRegisterPlayer.toString() << endl;

	// ��� ��Ŷ�� �����Ѵ�.
	pClientPlayer->sendPacket( &clRegisterPlayer );

	// �÷��̾��� ���¸� �ٲ۴�.
	pClientPlayer->setPlayerStatus( CPS_AFTER_SENDING_CL_REGISTER_PLAYER );

#endif
		
	__END_DEBUG_EX __END_CATCH
}
