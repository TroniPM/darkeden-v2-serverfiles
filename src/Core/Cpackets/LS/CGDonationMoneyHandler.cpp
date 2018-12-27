//////////////////////////////////////////////////////////////////////////////
// Filename    : CGDonationMoneyHandler.cpp
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGDonationMoney.h"

#ifdef __GAME_SERVER__
	#include "DB.h"
	#include "Assert.h"
	#include "GamePlayer.h"
	#include "PlayerCreature.h"
	#include "NicknameBook.h"
	#include "Guild.h"
	#include "GuildManager.h"
	#include "EffectDonation200501.h"
	#include "VariableManager.h"
	#include "Properties.h"

	#include "Gpackets/GCNPCResponse.h"
	#include "Gpackets/GCModifyInformation.h"
#endif

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGDonationMoneyHandler::execute (CGDonationMoney* pPacket , Player* pPlayer)
	 
{
	__BEGIN_TRY

#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	Assert( pGamePlayer != NULL );

	Creature* pCreature = pGamePlayer->getCreature();
	Assert( pCreature != NULL );

	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);
	Assert( pPC != NULL );

	// ��� ��Ŷ
	GCNPCResponse gcNPCResponse;

	// Dimension ID
	static int dimensionID = g_pConfig->getPropertyInt( "Dimension" );
	// ���� ID
	static int worldID = g_pConfig->getPropertyInt( "WorldID" );

	// affectWorldID
	static int affectWorldID = dimensionID * 3 + worldID;

	// ��� Ƚ��
	int sumBeforePersonal = 0;
	int sumAfterPersonal = 0;
	int sumBeforeGuild = 0;
	int sumAfterGuild = 0;

	// ��� �̺�Ʈ�� Ȱ��ȭ�� �������� Ȯ���Ѵ�.
	if ( g_pVariableManager->getVariable( DONATION_EVENT_200501 ) != 1 )
	{
		return;
	}

	// ���� ������� Ȯ��
	if ( pPC->getGold() < pPacket->getGold() )
	{
		gcNPCResponse.setCode( NPC_RESPONSE_NOT_ENOUGH_MONEY );
		pPlayer->sendPacket( &gcNPCResponse );
		return;
	}

	// �δ� ���� ���
	pPC->decreaseGoldEx( pPacket->getGold() );

	// �ٲ� �ݾ��� ������.
	GCModifyInformation gcModifyInformation;
	gcModifyInformation.addLongData( MODIFY_GOLD, pPC->getGold() );
	pPlayer->sendPacket( &gcModifyInformation );

	// ���ݱ����� ��� ȸ���� ���Ѵ�.
	{
		Statement* pStmt = NULL;
		Result* pResult = NULL;

		BEGIN_DB
		{
			pStmt = g_pDatabaseManager->getDistConnection( "PLAYER_DB" )->createStatement();
			pResult = pStmt->executeQuery( "SELECT COUNT(*) FROM DonationPersonal200501 WHERE Name = '%s' AND WorldID = %d", pCreature->getName().c_str(), affectWorldID );

			if ( pResult->next() )
			{
				sumBeforePersonal = pResult->getInt(1);
			}

			pResult = pStmt->executeQuery( "SELECT COUNT(*) FROM DonationGuild200501 WHERE Name = '%s' AND WorldID = %d", pCreature->getName().c_str(), affectWorldID );

			if ( pResult->next() )
			{
				sumBeforeGuild = pResult->getInt(1);
			}
		}
		END_DB( pStmt )
	}

	// ��� ������ ������ ���̽��� ����Ѵ�.
	{
		Statement* pStmt = NULL;

		if ( pPacket->getDonationType() == DONATION_TYPE_200501_PERSONAL )
		{
			BEGIN_DB
			{
				pStmt = g_pDatabaseManager->getDistConnection( "PLAYER_DB" )->createStatement();
				pStmt->executeQuery( "INSERT INTO DonationPersonal200501 VALUES ( '%s', '%s', %d, %u, now() )",
											pGamePlayer->getID().c_str(),
											pCreature->getName().c_str(),
											affectWorldID,
											pPacket->getGold() );
			}
			END_DB( pStmt )
		}
		else if ( pPacket->getDonationType() == DONATION_TYPE_200501_GUILD )
		{
			BEGIN_DB
			{
				pStmt = g_pDatabaseManager->getDistConnection( "PLAYER_DB" )->createStatement();
				pStmt->executeQuery( "INSERT INTO DonationGuild200501 VALUES ( %u, '%s', '%s', '%s', %d, %u, now() )",
											pPC->getGuildID(),
											pPC->getGuildName().c_str(),
											pGamePlayer->getID().c_str(),
											pCreature->getName().c_str(),
											affectWorldID,
											pPacket->getGold() );
			}
			END_DB( pStmt )
		}
		else
		{
			return;
		}
	}

	// ���ݱ����� ��� ȸ���� ���Ѵ�.
	{
		Statement* pStmt = NULL;
		Result* pResult = NULL;

		BEGIN_DB
		{
			pStmt = g_pDatabaseManager->getDistConnection( "PLAYER_DB" )->createStatement();
			pResult = pStmt->executeQuery( "SELECT COUNT(*) FROM DonationPersonal200501 WHERE Name = '%s' AND WorldID = %d", pCreature->getName().c_str(), affectWorldID );

			Packet* pNicknamePacket = NULL;

			if ( pResult->next() )
			{
				sumAfterPersonal = pResult->getInt(1);

				// �� ������ �߰��ؾߵǴ� ���
				if ( sumAfterPersonal == 1  && sumBeforePersonal != sumAfterPersonal )
				{
					NicknameBook* pNicknameBook = pPC->getNicknameBook();
					Assert( pNicknameBook != NULL );

					pNicknameBook->addNewNickname( "���� �� ���� ��������" );
					pNicknamePacket = pNicknameBook->getNicknameBookListPacket();
				}
				else if ( sumAfterPersonal == 3 && sumBeforePersonal != sumAfterPersonal )
				{
					NicknameBook* pNicknameBook = pPC->getNicknameBook();
					Assert( pNicknameBook != NULL );

					pNicknameBook->addNewNickname( "���������� ���� �����" );
					pNicknamePacket = pNicknameBook->getNicknameBookListPacket();
				}
				else if ( sumAfterPersonal == 5 && sumBeforePersonal != sumAfterPersonal )
				{
					NicknameBook* pNicknameBook = pPC->getNicknameBook();
					Assert( pNicknameBook != NULL );

					pNicknameBook->addNewNickname( "������ ����� �ƴ�" );
					pNicknamePacket = pNicknameBook->getNicknameBookListPacket();
				}
			}

			pResult = pStmt->executeQuery( "SELECT COUNT(*) FROM DonationGuild200501 WHERE Name = '%s' AND WorldID = %d", pCreature->getName().c_str(), affectWorldID );

			if ( pResult->next() )
			{
				sumAfterGuild = pResult->getInt(1);

				// �� ������ �߰��ؾߵǴ� ���
				if ( sumAfterGuild == 1 && sumBeforeGuild != sumAfterGuild )
				{
					NicknameBook* pNicknameBook = pPC->getNicknameBook();
					Assert( pNicknameBook != NULL );

					pNicknameBook->addNewNickname( "������ ������ ����ô�" );
					pNicknamePacket = pNicknameBook->getNicknameBookListPacket();
				}
				else if ( sumAfterGuild == 3 && sumBeforeGuild != sumAfterGuild )
				{
					NicknameBook* pNicknameBook = pPC->getNicknameBook();
					Assert( pNicknameBook != NULL );

					pNicknameBook->addNewNickname( "���� ������ ����ô�" );
					pNicknamePacket = pNicknameBook->getNicknameBookListPacket();
				}
				else if ( sumAfterGuild == 5 && sumBeforeGuild != sumAfterGuild )
				{
					NicknameBook* pNicknameBook = pPC->getNicknameBook();
					Assert( pNicknameBook != NULL );

					pNicknameBook->addNewNickname( "����� ��õ�� �����" );
					pNicknamePacket = pNicknameBook->getNicknameBookListPacket();
				}
			}

			if ( pNicknamePacket != NULL )
			{
				pGamePlayer->sendPacket( pNicknamePacket );
				SAFE_DELETE( pNicknamePacket );
			}
		}
		END_DB( pStmt )
	}


	// ����Ʈ�� �߰��Ѵ�.
	if ( !pPC->isFlag( Effect::EFFECT_CLASS_DONATION_200501 ) )
	{
		EffectDonation200501* pEffect = new EffectDonation200501( pPC );
		pPC->addEffect( pEffect );
		// ������ affect �Ѵ�. �ȿ��� ��ε�ĳ���� ���� ó���� �Ѵ�.
		pEffect->affect();
	}

	// ��� ����� �˸���.
	gcNPCResponse.setCode( NPC_RESPONSE_SHOW_DONATION_COMPLETE_DIALOG );
	pPlayer->sendPacket( &gcNPCResponse );
	
#endif

	__END_CATCH
}

