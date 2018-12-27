//////////////////////////////////////////////////////////////////////////////
// Filename    : CGWhisperHandler.cc
// Written By  : reiot@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CGWhisper.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
	#include "Creature.h"
	#include "PCFinder.h"
	#include "LogNameManager.h"

	#include "Gpackets/GCWhisper.h"
	#include "Gpackets/GCWhisperFailed.h"
	#include "Gpackets/GGServerChat.h"

	#include "DB.h"

	#include "GameServerInfoManager.h"
	#include "LoginServerManager.h"
	#include "Properties.h"

#endif

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGWhisperHandler::execute (CGWhisper* pPacket , Player* pPlayer)
	 
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);

	try 
	{
		Player* pTargetPlayer = NULL;
		
		Creature* pCreature = pGamePlayer->getCreature();

		bool Success = false;
			
		// �̸����� ����ڸ� ã�ƿ´�.
		__ENTER_CRITICAL_SECTION((*g_pPCFinder))
			
		Creature* pTargetCreature = g_pPCFinder->getCreature_LOCKED(pPacket->getName());

		// NoSuch����. by sigi. 2002.5.2
		if (pTargetCreature != NULL) 
		{
			// ä�� �α׸� �����. by sigi. 2002.10.30
			if (LogNameManager::getInstance().isExist( pCreature->getName() ))
			{
				filelog("chatLog.txt", "[Whisper] %s --> %s> %s", 
						pCreature->getName().c_str(), 
						pTargetCreature->getName().c_str(), 
						pPacket->getMessage().c_str());
			}

			pTargetPlayer = pTargetCreature->getPlayer();
			Assert(pTargetPlayer != NULL);
			Success = true;

			if (pGamePlayer->isPenaltyFlag(PENALTY_TYPE_MUTE)) {
				Success = false;
			}

			// ����ڸ� ���������� ã������ Message ����
			if (Success) {
				if (((GamePlayer*)pTargetPlayer)->getPlayerStatus() == GPS_NORMAL) {

					if (pCreature != NULL && pTargetCreature != NULL) {
						// �������� Ŭ���̾�Ʈ�� �����ϹǷ� GC- ��Ŷ�� ����ؾ� �Ѵ�.
						GCWhisper gcWhisper;
					
						// ũ��ó �̸��� �޽����� ��Ŷ�� �����Ѵ�.
						gcWhisper.setName(pCreature->getName());	
						gcWhisper.setColor( pPacket->getColor() );
						gcWhisper.setMessage(pPacket->getMessage());
						gcWhisper.setRace(pCreature->getRace());
						pTargetPlayer->sendPacket(&gcWhisper);

					} else {
						GCWhisperFailed gcWhisperFailed;
						pGamePlayer->sendPacket(&gcWhisperFailed);
					}
				}
			}

			// �׷� ����ڰ� ���ų� �̸��� �߸� �־����� Failed
		} 
		else 
		{

			/*inthesky*/
			/*	DB�� ������ ����ڸ� ã�´�. DB���� ������ ������ Player, Logon ������, ServerID ������ �ǁٴ�?
			 *	ã���� �ش���Ӽ����� GGServerChat ��Ŷ�� �����Ѵ� (sender, Color, Message, Race(����), 
			 *	GGServerChat ��Ŷ�� ���� ������ ����� �̸����� �÷��̾ ã�Ƽ� GCWhisper��Ŷ�� ����� ���.
			 *	������ ����(Failed������).
			 *	����ڰ� �ִ� ���ٴ� DB������ �Ǵ�����. DB�� �ŷڵ���..??????
			 */
			Statement* pStmt = NULL;
			Result* pResult = NULL;
			
			bool 				bServerFind	= false;
			ServerGroupID_t		CurrentServerGroupID;		
        	string				LogOn;		
			string				PlayerID;

			try 
			{
    	        BEGIN_DB
        	    {
           	    	pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

					// ũ�����̸����� Slayer���̺��� PlayerID �� ã�´�.
			//add by viva 
					if(pPacket->getName().find('\'')>0 || pPacket->getName().find(' ')>0)
						//pPacket->getName() = "";
			//end
					pResult = pStmt->executeQuery("SELECT PlayerID FROM Slayer WHERE Name='vivaqq'");
					
					else
						
					pResult = pStmt->executeQuery("SELECT PlayerID FROM Slayer WHERE Name='%s'",pPacket->getName().c_str());
					
					if ( pResult->next() )		
					{
						PlayerID				= pResult->getString( 1 );
						SAFE_DELETE(pStmt);

						// ã�� PlayerID�� Player���̺��� ServerGroupID�� LogOn������ ã�´�.
						pStmt	= g_pDatabaseManager->getDistConnection("USERINFO")->createStatement();
						pResult	= pStmt->executeQuery("SELECT CurrentServerGroupID, LogOn FROM Player WHERE PlayerID='%s'",PlayerID.c_str());
					
						// Player ������ ã�Ҵ�.
						if ( pResult->next() )
						{
							CurrentServerGroupID	= pResult->getInt	( 1 );
							LogOn					= pResult->getString( 2 );

							// �������� �����϶� bServerFind�� true flag
							if ( LogOn == "GAME" )
							{
								bServerFind = true;
								SAFE_DELETE(pStmt);
							}
						}
						else { SAFE_DELETE(pStmt); }
					}
					else { SAFE_DELETE(pStmt); }
					
					if(bServerFind)			// ã������
					{
						/*	GGServerChat ��Ŷ�� ����
						 *	���...���Ӽ�����..
						 *  pCreature->getName() = ������ ũ���� �̸�	
						 *	pPacket->getName() = �޴� ũ���� �̸�
						 *	PlayerID	= �޴� ũ���� ����
						 *	pPacket->getColor()	= ���ڻ�	
						 *	pPacket->getMessage() = �޼���
						 *  pCreature->getRace() = ������ ũ���� ����
						 * */

										
						GameServerInfo*	pGameServerInfo = g_pGameServerInfoManager->getGameServerInfo(1,CurrentServerGroupID,g_pConfig->getPropertyInt( "WorldID" ));
						if ( pGameServerInfo != NULL )
						{
							GGServerChat ggServerChat;
							ggServerChat.setSender	(pCreature->getName()		);
							ggServerChat.setReceiver(pPacket->getName()	);
							ggServerChat.setColor	(pPacket->getColor()		);
							ggServerChat.setMessage	(pPacket->getMessage()		);
							ggServerChat.setRace	(pCreature->getRace()		);
							
							g_pLoginServerManager->sendPacket( pGameServerInfo->getIP(), pGameServerInfo->getUDPPort(), &ggServerChat );
						}
						else
						{
							GCWhisperFailed gcWhisperFailed;
							pGamePlayer->sendPacket(&gcWhisperFailed);
						}
					}
					else
					{
						GCWhisperFailed gcWhisperFailed;
		                pGamePlayer->sendPacket(&gcWhisperFailed);
					}

	            }
    	        END_DB(pStmt)
        	} catch(...) { /* write log plz */ }
			
		}

		__LEAVE_CRITICAL_SECTION((*g_pPCFinder))
	} 
	catch(Throwable & t) 
	{
		//cout << t.toString() << endl;
		GCWhisperFailed gcWhisperFailed;
		pGamePlayer->sendPacket(&gcWhisperFailed);
	}

#endif
		
	__END_DEBUG_EX __END_CATCH
}
