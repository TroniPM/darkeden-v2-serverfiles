//----------------------------------------------------------------------
//
// Filename    : SGDeleteGuildOKHandler.cpp
// Written By  : Reiot
// Description :
//
//----------------------------------------------------------------------

// include files
#include "SGDeleteGuildOK.h"

#ifdef __GAME_SERVER__

	#include "Assert.h"
	#include "DB.h"
	#include "Guild.h"
	#include "GuildManager.h"
	#include "PCFinder.h"
	#include "Player.h"
	#include "PlayerCreature.h"
	#include "Properties.h"
	#include "Zone.h"
	#include "ResurrectLocationManager.h"
	#include "Gpackets/GCSystemMessage.h"
	#include "Gpackets/GCModifyInformation.h"
	#include "Gpackets/GCModifyGuildMemberInfo.h"
	#include "Gpackets/GCOtherModifyInfo.h"

	#include "GuildUnion.h"
#endif

//----------------------------------------------------------------------
// 
// SGDeleteGuildOKHandler::execute()
// 
//----------------------------------------------------------------------
void SGDeleteGuildOKHandler::execute ( SGDeleteGuildOK* pPacket )
	 
{
	__BEGIN_TRY

#ifdef __GAME_SERVER__

	// ��� ����Ʈ�� �ִ� ����� warp ��Ų��.
	// ��� ����Ʈ�� �����Ѵ�.
	// ��� warp�� ��� ����Ʈ ���� �� �ٸ� �����忡�� ZoneGroup Thread ���ο��� �Ͼ�� �ؾ� ��Ż�� ���� �� �ϴ�.
	// �ϴ��� �� �д�. Portal �� �����Ƿ� �ٽ� �� �� ���� ���̴�.
	
	Assert( pPacket != NULL );

	// ��带 �����´�.
	Guild* pGuild = g_pGuildManager->getGuild( pPacket->getGuildID() );
	try { Assert( pGuild != NULL ); } catch ( Throwable& ) { return; }


	// ��� Ȱ�� ���� ���¿����� ��ü���� ��� ���� ���¿����� ��ü���� �����Ѵ�.
	if ( pGuild->getState() == Guild::GUILD_STATE_ACTIVE )
	{
		HashMapGuildMember& Members = pGuild->getMembers();
		HashMapGuildMemberItor itr = Members.begin();

		for ( ; itr != Members.end(); itr++ )
		{
			GuildMember* pGuildMember = itr->second;

			// ������ ������
			__ENTER_CRITICAL_SECTION((*g_pPCFinder))

			Creature* pCreature = g_pPCFinder->getCreature_LOCKED( pGuildMember->getName() );
			if ( pCreature != NULL && pCreature->isPC() )
			{
				Player* pPlayer = pCreature->getPlayer();
				Assert( pPlayer != NULL );

				PlayerCreature* pPlayerCreature = dynamic_cast<PlayerCreature*>(pCreature);
				Assert( pPlayerCreature != NULL );

				// Slayer, Vampire �� ��� ���̵� �ٲ۴�.
				if ( pPlayerCreature->isSlayer() )
				{
					pPlayerCreature->setGuildID( 99 );		// �����̾� ���Ծ��� ������ ��� ID

					// Ŭ���̾�Ʈ�� ��� ���̵� �ٲ����� �˸���.
					GCModifyGuildMemberInfo gcModifyGuildMemberInfo;
					gcModifyGuildMemberInfo.setGuildID( pPlayerCreature->getGuildID() );
					gcModifyGuildMemberInfo.setGuildName( "" );
					gcModifyGuildMemberInfo.setGuildMemberRank( GuildMember::GUILDMEMBER_RANK_DENY );
					pPlayer->sendPacket( &gcModifyGuildMemberInfo );
				}
				else if ( pPlayerCreature->isVampire() )
				{
					pPlayerCreature->setGuildID( 0 );		// �����̾� ���Ծ��� ������ ��� ID

					// Ŭ���̾�Ʈ�� ��� ���̵� �ٲ����� �˸���.
					GCModifyGuildMemberInfo gcModifyGuildMemberInfo;
					gcModifyGuildMemberInfo.setGuildID( pPlayerCreature->getGuildID() );
					gcModifyGuildMemberInfo.setGuildName( "" );
					gcModifyGuildMemberInfo.setGuildMemberRank( GuildMember::GUILDMEMBER_RANK_DENY );
					pPlayer->sendPacket( &gcModifyGuildMemberInfo );
				}
				else if ( pPlayerCreature->isOusters() )
				{
					pPlayerCreature->setGuildID( 66 );		// �ƿ콺���� ���Ծ��� ������ ��� ID

					// Ŭ���̾�Ʈ�� ��� ���̵� �ٲ����� �˸���.
					GCModifyGuildMemberInfo gcModifyGuildMemberInfo;
					gcModifyGuildMemberInfo.setGuildID( pPlayerCreature->getGuildID() );
					gcModifyGuildMemberInfo.setGuildName( "" );
					gcModifyGuildMemberInfo.setGuildMemberRank( GuildMember::GUILDMEMBER_RANK_DENY );
					pPlayer->sendPacket( &gcModifyGuildMemberInfo );
				}

				// ������ Ŭ���̾�Ʈ�� ��� ���̵� �ٲ����� �˸���.
				GCOtherModifyInfo gcOtherModifyInfo;
				gcOtherModifyInfo.setObjectID( pCreature->getObjectID() );
				gcOtherModifyInfo.addShortData( MODIFY_GUILDID, pPlayerCreature->getGuildID() );

				Zone* pZone = pCreature->getZone();
				Assert( pZone != NULL );

				pZone->broadcastPacket( pCreature->getX(), pCreature->getY(), &gcOtherModifyInfo, pCreature );
			}

			__LEAVE_CRITICAL_SECTION((*g_pPCFinder))

			// Guild Member ��ü�� �����Ѵ�.
			SAFE_DELETE( pGuildMember );
		}

		// ��� ��� ���� �����Ѵ�.
		Members.clear();

		// ��� �Ŵ������� ��带 �����Ѵ�.
		g_pGuildManager->deleteGuild( pGuild->getID() );

		// ��� ��ü�� �����Ѵ�.
		SAFE_DELETE( pGuild );
	}
	else if ( pGuild->getState() == Guild::GUILD_STATE_WAIT )
	{
		HashMapGuildMember& Members = pGuild->getMembers();
		HashMapGuildMemberItor itr = Members.begin();

		Statement* pStmt = NULL;
		Result* pResult = NULL;

		BEGIN_DB
		{
			pStmt = g_pDatabaseManager->getConnection( "DARKEDEN" )->createStatement();
			
			for ( ; itr != Members.end(); itr++ )
			{
				GuildMember* pGuildMember = itr->second;

				// ������ ������
				__ENTER_CRITICAL_SECTION((*g_pPCFinder))

				Creature* pCreature = g_pPCFinder->getCreature_LOCKED( pGuildMember->getName() );
				if ( pCreature != NULL && pCreature->isPC() )
				{
					Player* pPlayer = pCreature->getPlayer();
					Assert( pPlayer != NULL );

					PlayerCreature* pPlayerCreature = dynamic_cast<PlayerCreature*>(pCreature);
					Assert( pPlayerCreature != NULL );

					// ��Ϻ� ȯ���Ѵ�.
					Gold_t Gold = pPlayerCreature->getGold();
					if ( pGuildMember->getRank() == GuildMember::GUILDMEMBER_RANK_MASTER )
					{
						Gold = min( Gold + (uint)RETURN_SLAYER_MASTER_GOLD, (long unsigned int)2000000000 );
					}
					else if ( pGuildMember->getRank() == GuildMember::GUILDMEMBER_RANK_SUBMASTER )
					{
						Gold = min( Gold + (uint)RETURN_SLAYER_SUBMASTER_GOLD, (long unsigned int)2000000000 );
					}

					pPlayerCreature->setGoldEx( Gold );

					GCModifyInformation gcModifyInformation;
					gcModifyInformation.addLongData( MODIFY_GOLD, Gold );
					pPlayer->sendPacket( &gcModifyInformation );

					// �޽����� ������.
					pResult = pStmt->executeQuery( "SELECT Message FROM Messages WHERE Receiver = '%s'", pCreature->getName().c_str() );

					while ( pResult->next() )
					{
						GCSystemMessage message;
						message.setMessage( pResult->getString(1) );
						pPlayer->sendPacket( &message );
					}

					pStmt->executeQuery( "DELETE FROM Messages WHERE Receiver = '%s'", pCreature->getName().c_str() );
				}

				__LEAVE_CRITICAL_SECTION((*g_pPCFinder))

				// ��� ��� ��ü�� �����Ѵ�.
				SAFE_DELETE( pGuildMember );
			}

			// ��� ��� �ؽ� ���� �����.
			Members.clear();

			// ��� �Ŵ������� ��带 �����Ѵ�.
			g_pGuildManager->deleteGuild( pGuild->getID() );
			GuildUnionManager::Instance().removeMasterGuild( pGuild->getID());

			// ��� ��ü�� �����Ѵ�.
			SAFE_DELETE( pGuild );

			SAFE_DELETE( pStmt );
		}
		END_DB(pStmt)
	}

#endif
		
	__END_CATCH
}
