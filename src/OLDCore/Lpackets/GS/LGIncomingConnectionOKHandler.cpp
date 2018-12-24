//--------------------------------------------------------------------------------
//
// Filename    : LGIncomingConnectionOKHandler.cpp
// Written By  : Reiot
// Description :
//
//--------------------------------------------------------------------------------

// include files
#include "LGIncomingConnectionOK.h"

#ifdef __GAME_SERVER__

	#include "GamePlayer.h"
	#include "IncomingPlayerManager.h"
	#include "Assert.h"
	#include "Statement.h"
	#include "DatabaseManager.h"
	#include "LogDef.h"

	#include "Gpackets/GCReconnectLogin.h"

#endif

//--------------------------------------------------------------------------------
// 
// LGIncomingConnectionOKHander::execute()
// 
// �α��� �����κ��� LGIncomingConnectionOK ��Ŷ�� ���ƿ���, ���� ������ �� �㰡�� 
// ��� �÷��̾ ���� �㰡���� ã�Ƴ��� �Ѵ�. �� ��, �� �÷��̾�� LCReconnectLogin
// ��Ŷ�� ������� �Ѵ�.
// 
//--------------------------------------------------------------------------------
void LGIncomingConnectionOKHandler::execute ( LGIncomingConnectionOK * pPacket )
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	try {	

		// �÷��̾� ���̵� ����ؼ� �÷��̾� ��ü�� �����Ѵ�.
//		__ENTER_CRITICAL_SECTION((*g_pIncomingPlayerManager))
		GamePlayer * pGamePlayer = NULL;

		try {

			pGamePlayer = g_pIncomingPlayerManager->getPlayer( pPacket->getPlayerID() );

		} catch ( NoSuchElementException ) {

			pGamePlayer = g_pIncomingPlayerManager->getReadyPlayer( pPacket->getPlayerID() );

		} 

		int fd = -1;
		Socket* pSocket = pGamePlayer->getSocket();
		if (pSocket!=NULL) fd = (int)pSocket->getSOCKET();



		if ( pGamePlayer->getPlayerStatus() == GPS_AFTER_SENDING_GL_INCOMING_CONNECTION ) 
		{
			FILELOG_INCOMING_CONNECTION("incomingDisconnect.log", "OK FD : %d, %s",
							fd, (pSocket==NULL? "NULL" : pSocket->getHost().c_str()) );

			/*
	        // Ŭ���̾�Ʈ���� ���� ������ �������϶�� �˷��ش�.
			GCReconnectLogin gcReconnectLogin;
			gcReconnectLogin.setLoginServerIP( pPacket->getHost() );
			gcReconnectLogin.setLoginServerPort( pPacket->getTCPPort() );
			gcReconnectLogin.setKey( pPacket->getKey() );

			// LCReconnectLogin ��Ŷ�� �����Ѵ�.
			pGamePlayer->sendPacket( &gcReconnectLogin );

			cout << "LGIncomingConnectionOKHandler Send Packet to Client Required Reconnect ServerIP : " << pPacket->getHost() << endl;
			*/

			// ������ �׳� �� Ÿ�ֿ̹� ��Ŷ�� ���´µ�..
			// Ÿ�̹� ������ ���������� ����� �ȵƴµ� client���� ���ӿ�û�� �ؿ��� ������
			// ©����..
			// GamePlayer�� �����صΰ�.. IncomingPlayerManager���� disconnect()�ɶ�
			// �����ص� packet�� client�� ������.
			GCReconnectLogin* gcReconnectLogin = new GCReconnectLogin;
			gcReconnectLogin->setLoginServerIP( pPacket->getHost() );
			gcReconnectLogin->setLoginServerPort( pPacket->getTCPPort() );
			gcReconnectLogin->setKey( pPacket->getKey() );

			pGamePlayer->setReconnectPacket( gcReconnectLogin );

			//cout << "LGIncomingConnectionOKHandler Store Packet : " << gcReconnectLogin->toString().c_str() << endl;
			//cout << "LGIncomingConnectionOKHandler Store Packet" << endl;
		}
		else
		{
			FILELOG_INCOMING_CONNECTION("incomingDisconnect.log", "Invalid FD : %d, %s, ps=%d",
							fd, (pSocket==NULL? "NULL" : pSocket->getHost().c_str()), 
							(int)pGamePlayer->getPlayerStatus());

			cout << "Invalid Player Status("
				<< (int)pGamePlayer->getPlayerStatus()
				<< ") must be AFTER_SENDING_LG_INCOMING_CONNECTION" << endl;
		}


		
		// �̷��� �� �θ�, 
		// GamePlayer->processCommand()���� isPenaltyFlag()üũ���� �ɷ���
		// ���� ���� IncomingPlayer->processCommands()���� �߸��� �ȴ�.
		pGamePlayer->setPenaltyFlag(PENALTY_TYPE_KICKED);
		pGamePlayer->setItemRatioBonusPoint(3);

		// ������ �����Ѵ�.
		//pGamePlayer->disconnect( UNDISCONNECTED );

		// LPM���� �����Ѵ�.
		//g_pIncomingPlayerManager->deletePlayer_NOBLOCKED( pGamePlayer->getSocket()->getSOCKET());

		// GamePlayer ��ü�� �����Ѵ�.
		//SAFE_DELETE(pGamePlayer);

		//__LEAVE_CRITICAL_SECTION((*g_pIncomingPlayerManager))
	} 
	catch ( NoSuchElementException & nsee ) 
	{
		cout << "Player not exist or already disconnected" << endl;
	}

#endif
		
	__END_DEBUG_EX __END_CATCH
}
