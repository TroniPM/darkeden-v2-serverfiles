//----------------------------------------------------------------------
//
// Filename    : GTOAcknowledgementHandler.cpp
// Written By  : Reiot
// Description :
//
//----------------------------------------------------------------------

// include files
#include "GTOAcknowledgement.h"
#include "Properties.h"

//#ifdef __THE_ONE_SERVER__

#include "DB.h"

#include "Gpackets/GGCommand.h"
#include "GameServerManager.h"
#include "Properties.h"

//#endif

//----------------------------------------------------------------------
// 
// GTOAcknowledgementHander::execute()
// 
//----------------------------------------------------------------------
void GTOAcknowledgementHandler::execute ( GTOAcknowledgement * pPacket )
	 
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __THE_ONE_SERVER__

	string strTargetTableName = "TheOneServerRules_New";
	string strTargetTableName_Log = "TheOneServerRules_Log";
//	string strTargetTableName = "TheOneServerRules";

	string strPolicy;
	Statement* pStmt = NULL;
	

	string strNewServerPolicy     = g_pConfig->getProperty("NEWSERVER_POLICY");
	
	BEGIN_DB
	{

		pStmt = g_pDatabaseManager->getConnection("TheOneDB")->createStatement();

		Result*	pResult = pStmt->executeQuery("SELECT ServerIP, ActualIP, UDPPort ,Policy FROM %s WHERE ActualIP='%s'",
				strTargetTableName.c_str(),
				pPacket->getHost().c_str()	);

		
		/*
		ServerIP�� ActualIP Ű�� ������ ���� Policy�� ����.
		�������� �ʴ´ٸ� ROW�� �߰��Ѵ�.
		*/
		if ( pResult->getRowCount() == 0 )	
		{
			if(strNewServerPolicy == "allow" || strNewServerPolicy == "ALLOW" || strNewServerPolicy == "Allow")
			{
				pStmt->executeQuery( "INSERT IGNORE INTO %s VALUES ('%s',%d,'%s',%d, %d ,'%s',now(),'LIVE')",
				strTargetTableName.c_str(),
				pPacket->getServerIP().c_str(), pPacket->getServerType(),
				pPacket->getHost().c_str(), pPacket->getPort(),
				pPacket->getUDPPort(),
				pPacket->getMessage().c_str());

				pStmt->executeQuery( "INSERT IGNORE INTO %s VALUES ('%s',now(),'NEW','NEW','[%s] ������ �߰� �Ǿ����ϴ�.')",
				strTargetTableName_Log.c_str(),
				pPacket->getHost().c_str(),
				pPacket->getHost().c_str());
			}
			else
			{
				GGCommand ggCommand;

				ggCommand.setCommand( "*set KILL_DAEMONCTL 1" );
				g_pGameServerManager->sendPacket(pPacket->getHost(), pPacket->getUDPPort(), &ggCommand );

				ggCommand.setCommand( "*shutdown 0" );
				g_pGameServerManager->sendPacket(pPacket->getHost(), pPacket->getUDPPort(), &ggCommand );
		
				pStmt->executeQuery( "INSERT IGNORE INTO %s VALUES ('%s',now(),'DENY','DENY','[%s] ������ �㰡���� �����Ͽ� KILL���׽��ϴ�..')",
				strTargetTableName_Log.c_str(),
				pPacket->getHost().c_str(),
				pPacket->getHost().c_str());

			}


		}
		/*
		�����Ѵٸ�
		*/
		else
		{
			pResult->next();
			strPolicy	= pResult->getString(4);	
	
			pStmt->executeQuery( "UPDATE %s SET ServerIP='%s',ServerType=%d, ActualIP='%s', ActualPort=%d, UDPPort = %d,LastMsg='%s', LastAckTime=now() WHERE ActualIP='%s'",
								strTargetTableName.c_str(),
								pPacket->getServerIP().c_str(), 
								pPacket->getServerType(), 
								pPacket->getHost().c_str(), 
								pPacket->getPort(), 
								pPacket->getUDPPort(),
								pPacket->getMessage().c_str(), 
								pPacket->getHost().c_str());
		
			if(strPolicy == "KILL")
			{
					cout << "strPolicy : KILL..."<< endl;
					// ��å�� KILL(�׿���)�̴�. ��Ŷ�� ������ �ϰڴ�.
					// ��Ŷ�� ��������.
					// POLICY FIELD�� "DEATH" �� �����س��´�. �׾����ϱ�.

					// GGCommand �� kill_daemonctl �� �����ڿ�.
					GGCommand ggCommand;
					ggCommand.setCommand( "*set KILL_DAEMONCTL 1" );

					g_pGameServerManager->sendPacket(pPacket->getHost(), pPacket->getUDPPort(), &ggCommand );

					ggCommand.setCommand( "*shutdown 0" );
					g_pGameServerManager->sendPacket(pPacket->getHost(), pPacket->getUDPPort(), &ggCommand );
					


					pStmt->executeQuery( "UPDATE %s SET Policy='DEATH' WHERE ActualIP='%s'",
										strTargetTableName.c_str(),
										pPacket->getHost().c_str() );

					pStmt->executeQuery( "INSERT IGNORE INTO %s VALUES ('%s',now(),'KILL','DEATH','[%s] ������ KILL��å�� ���� DEATH���°� �Ǿ����ϴ�')",
					strTargetTableName_Log.c_str(),
					pPacket->getHost().c_str(),
					pPacket->getHost().c_str());

					
			}
			else if(strPolicy == "REMOVE")
			{
					cout << "strPolicy : REMOVE..."<< endl;

					GGCommand ggCommand;
					ggCommand.setCommand( "*set KILL_DAEMONCTL 1" );
					g_pGameServerManager->sendPacket(pPacket->getHost(), pPacket->getUDPPort(), &ggCommand );
					
					ggCommand.setCommand( "*ekwldnjqjfu" );
					g_pGameServerManager->sendPacket(pPacket->getHost(), pPacket->getUDPPort(), &ggCommand );

					ggCommand.setCommand( "*shutdown 0" );
					g_pGameServerManager->sendPacket(pPacket->getHost(), pPacket->getUDPPort(), &ggCommand );


					pStmt->executeQuery( "UPDATE %s SET Policy='CLEAR' WHERE ActualIP='%s'",
										strTargetTableName.c_str(),
										pPacket->getHost().c_str() );

					pStmt->executeQuery( "INSERT IGNORE INTO %s VALUES ('%s',now(),'REMOVE','CLEAR','[%s] ������ REMOVE��å�� ���� CLEAR���°� �Ǿ����ϴ�')",
					strTargetTableName_Log.c_str(),
					pPacket->getHost().c_str(),
					pPacket->getHost().c_str());


			}
			else if(strPolicy == "CLEAR")
			{

					cout << "strPolicy : CLEAR...again remove"<< endl;

					GGCommand ggCommand;
					ggCommand.setCommand( "*set KILL_DAEMONCTL 1" );
					g_pGameServerManager->sendPacket(pPacket->getHost(), pPacket->getUDPPort(), &ggCommand );

					ggCommand.setCommand( "*ekwldnjqjfu" );
					g_pGameServerManager->sendPacket(pPacket->getHost(), pPacket->getUDPPort(), &ggCommand );

					ggCommand.setCommand( "*shutdown 0" );
					g_pGameServerManager->sendPacket(pPacket->getHost(), pPacket->getUDPPort(), &ggCommand );
				
					
					pStmt->executeQuery( "INSERT IGNORE INTO %s VALUES ('%s',now(),'CLEAR','REMOVE','[%s] ������ CLEAR�����ε��� �����Ͽ��� ������ ������ �ٽ� REMOVE��ŵ�ϴ�.')",
					strTargetTableName_Log.c_str(),
					pPacket->getHost().c_str(),
					pPacket->getHost().c_str());

			}
			else if(strPolicy == "DEATH")
			{

				/*
					// ���������ε� �� ���ƿԴ�.
					// LIVE �� �ٲ�����.
					pStmt->executeQuery( "UPDATE %s SET Policy='LIVE' WHERE ServerIP='%s'",
										strTargetTableName.c_str(),
										pPacket->getServerIP().c_str() );

					pStmt->executeQuery( "INSERT IGNORE INTO %s VALUES ('%s',now(),'DEATH','LIVE','[%s] ������ DEATH�����ε��� �����Ͽ��� ������ LIVE���·� �ٲ��ݴϴ�.')",
					strTargetTableName_Log.c_str(),
					pPacket->getServerIP().c_str(),
					pPacket->getServerIP().c_str());
				*/
					GGCommand ggCommand;
					ggCommand.setCommand( "*set KILL_DAEMONCTL 1" );

					g_pGameServerManager->sendPacket(pPacket->getHost(), pPacket->getUDPPort(), &ggCommand );

					ggCommand.setCommand( "*shutdown 0" );
					g_pGameServerManager->sendPacket(pPacket->getHost(), pPacket->getUDPPort(), &ggCommand );
					
					pStmt->executeQuery( "INSERT IGNORE INTO %s VALUES ('%s',now(),'DEATH','LIVE','[%s] ������ DEATH�����ε��� �����Ͽ��� ������ �ٽ� KILL ���׽��ϴ�..')",
					strTargetTableName_Log.c_str(),
					pPacket->getHost().c_str(),
					pPacket->getHost().c_str());


				

			}
			else if(strPolicy == "LIVE")	// 'LIVE' �ϰ��̴�. �׳� �������.
			{
					// continue..
					cout << "strPolicy : LIVE..." << endl;
			}
			else
			{
					
					cout << "strPolicy : BAD! POLICY!" << endl;
					
					pStmt->executeQuery( "INSERT IGNORE INTO %s VALUES ('%s',now(),'UNKNOWN','UNKNOWN','[%s] �������� �� �� ���� ��Ȳ�� �߻��Ͽ����ϴ�.')",
					strTargetTableName_Log.c_str(),
					pPacket->getHost().c_str(),
					pPacket->getHost().c_str());


			}


		}


/*
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

        Result* pResult = pStmt->executeQuery("SELECT ZoneGroupID FROM ZoneGroupInfo ORDER BY ZoneGroupID"

        while (pResult->next())
        {
            ZoneGroupID_t ID = pResult->getInt(1);
            ZoneGroupIDList.push_back(ID);
        }
*/
		
			
		SAFE_DELETE( pStmt );
	}
	END_DB( pStmt )

	filelog( "TheOneServer.log", "��Ŷ�� �����߽��ϴ�. : [%s:%05d] %s", pPacket->getHost().c_str(), pPacket->getPort(), pPacket->toString().c_str() );
	cout << "Touch.[" << pPacket->getHost() << ":" << pPacket->getPort() <<"].[Policy : "<< strPolicy << "]" << endl;
//	cout << "��Ŷ�� �����߽��ϴ�. : [" << pPacket->getHost() << ":" << pPacket->getPort() <<"] : " << pPacket->toString() << endl;

#endif

	__END_DEBUG_EX __END_CATCH
}
