//----------------------------------------------------------------------
//
// Filename    : GLIncomingConnectionHandler.cpp
// Written By  : Reiot
// Description :
//
//----------------------------------------------------------------------

// include files
#include "GLIncomingConnection.h"
#include "Properties.h"

#ifdef __LOGIN_SERVER__

	#include "ReconnectLoginInfo.h"
	#include "ReconnectLoginInfoManager.h"
	#include "GameServerManager.h"

	#include "Lpackets/LGIncomingConnectionError.h"
	#include "Lpackets/LGIncomingConnectionOK.h"

#endif

//----------------------------------------------------------------------
// 
// GLIncomingConnectionHander::execute()
// 
// ���� ������ �α��� �����κ��� GLIncomingConnection ��Ŷ�� �ް� �Ǹ�,
// ReconnectLoginInfo�� ���� �߰��ϰ� �ȴ�.
// 
//----------------------------------------------------------------------
void GLIncomingConnectionHandler::execute ( GLIncomingConnection * pPacket )
	 
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
	__BEGIN_DEBUG

#ifdef __LOGIN_SERVER__

	//--------------------------------------------------------------------------------
	//
	// ����Ű�� �����Ѵ�.
	//
	// *NOTE*
	//
	// ������ ����� �α��� �������� ����Ű�� �����ؼ� ���Ӽ����� ���� ��, Ŭ���̾�Ʈ��
	// �����ߴ�. �̷��� �� ��� CLSelectPCHandler::execute()���� ����Ű�� �����ϰ� 
	// GLIncomingConnectionOKHandler::execute()���� ����Ű�� Ŭ���̾�Ʈ�� ������ �Ǵµ�,
	// ó�� �޽�尡 �ٸ��Ƿ� Ű���� ��𿡼��� �����Ǿ�� �Ѵ�. ���� �ܼ��� ����� �α���
	// �÷��̾� ��ü�� �����ϸ� �Ǵµ�.. ���� �����ϴ�. �Ǵٸ� ����� ���� �������� �ٽ�
	// �α��� ������ Ű���� �ǵ����ִ� ���ε�, �̴� ��Ʈ��ũ�� Ű���� 2ȸ �պ��Ѵٴ�
	// ������ ���ʿ��ϴ�. 
	// 
	// ����, �α��� �������� �����ؼ� ���Ӽ����� �����ִ� ���� �ξ� ��������� �ȴ�.
	//
	// *TODO*
	//
	// �־��� ���, ���ó�Ʈ��ũ�� �����۸����ؼ� Ű���� ����� �� �ִ�. (�ϱ� �� ��Ʈ
	// �н����尡 ����� ���ɼ��� �ִµ�.. - -; �̷� �ž� SSL�� ��� �ϴ°Ű�..)
	// �̸� ����ؼ� GLIncomingConnectionOK ��Ŷ�� ��ȣȭ�Ǿ�� �Ѵ�.
	//
	// ���� Ű���� �����Ұ����ؾ� �Ѵ�. (������ �ڵ带 ���� ��������������.)
	//
	//--------------------------------------------------------------------------------

	DWORD authKey = rand() << ( time(0) % 10 ) + rand() >> ( time(0)% 10 );

	// CI ��ü�� �����Ѵ�.
	ReconnectLoginInfo * pReconnectLoginInfo = new ReconnectLoginInfo();
	pReconnectLoginInfo->setClientIP( pPacket->getClientIP() );
	pReconnectLoginInfo->setPlayerID( pPacket->getPlayerID() );
	pReconnectLoginInfo->setKey( authKey );

	//--------------------------------------------------------------------------------
	//
	// ���� �ð� + 30 �� �ĸ� expire time ���� �����Ѵ�.
	//
	// *TODO*
	//
	// expire period ���� Config ���Ͽ��� �������ָ� ���ڴ�.
	//
	//--------------------------------------------------------------------------------
	Timeval currentTime;
	getCurrentTime(currentTime);	
	currentTime.tv_sec += 30;
	pReconnectLoginInfo->setExpireTime( currentTime );

	// debug message
	cout << "+--------------------------------+" << endl
		 << "| Incoming Connection Infomation |" << endl
		 << "+--------------------------------+" << endl
		 << "ClientIP : " << pPacket->getClientIP() << endl
		 << "Auth Key : " << authKey << endl;
	cout << "���۵�3"<<endl;
	try 
	{
		// RLIM �� �߰��Ѵ�.
		g_pReconnectLoginInfoManager->addReconnectLoginInfo( pReconnectLoginInfo );

		// �α��� �������� �ٽ� �˷��ش�.
		LGIncomingConnectionOK lgIncomingConnectionOK;
		lgIncomingConnectionOK.setPlayerID( pPacket->getPlayerID() );
		lgIncomingConnectionOK.setTCPPort( g_pConfig->getPropertyInt("LoginServerPort") );
		lgIncomingConnectionOK.setKey( authKey );

		g_pGameServerManager->sendPacket( pPacket->getHost() , pPacket->getPort() , &lgIncomingConnectionOK );
	cout << "���۵�4"<<endl;
		//cout << "GLIncomingConnectionHandler Send Packet to ServerIP : " << pPacket->getHost() << endl;
	} 
	catch ( DuplicatedException & de ) 
	{
		//cout << "Duplicated Exception Throwed Step 1" << endl;
		// �������� ��� CI �� �����ϰ�, �α��� �������� GLIncomingConnectionError ��Ŷ�� �����Ѵ�.
		SAFE_DELETE(pReconnectLoginInfo);
		//cout << "Duplicated Exception Throwed Step 2" << endl;

		LGIncomingConnectionError lgIncomingConnectionError;
		lgIncomingConnectionError.setMessage( de.toString() );
		lgIncomingConnectionError.setPlayerID( pPacket->getPlayerID() );
		//cout << "Duplicated Exception Throwed Step 3" << endl;
	cout << "���۵�4 -1"<<endl;
		g_pGameServerManager->sendPacket( pPacket->getHost() , pPacket->getPort() , &lgIncomingConnectionError );
	cout << "���۵�4 -2"<<endl;
		//cout << "Duplicated Exception Throwed Step 4" << endl;

		//cout << "GLIncomingConnectionHandler Send Packet to ServerIP : " << pPacket->getHost() << endl;

	}
	
#endif
		
	__END_DEBUG
	__END_DEBUG_EX __END_CATCH
}
