//----------------------------------------------------------------------
//
// Filename    : SGModifyGuildMemberOKHandler.cpp
// Written By  : Reiot
// Description :
//
//----------------------------------------------------------------------

// include files
#include "SGModifyGuildMemberOK.h"
#include "Properties.h"

#ifdef __GAME_SERVER__

	#include "DB.h"
	#include "Guild.h"
	#include "GuildManager.h"
	#include "PCFinder.h"
	#include "Player.h"
	#include "PlayerCreature.h"
	#include "Zone.h"
	#include "StringPool.h"
	#include "Gpackets/GCModifyGuildMemberInfo.h"
	#include "Gpackets/GCOtherModifyInfo.h"
	#include "Gpackets/GCSystemMessage.h"

	#include <stdio.h>

#endif

//----------------------------------------------------------------------
// 
// SGModifyGuildMemberOKHandler::execute()
// 
//----------------------------------------------------------------------
void SGModifyGuildMemberOKHandler::execute ( SGModifyGuildMemberOK* pPacket )
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	//cout << "SGModifyGuildMember received" << endl;

	Assert( pPacket != NULL );

	// ��带 �����´�.
	Guild* pGuild = g_pGuildManager->getGuild( pPacket->getGuildID() );
	try { Assert( pGuild != NULL ); } catch ( Throwable& ) { return; }

	// ��� ������� Ȯ���Ѵ�.
	GuildMember* pGuildMember = pGuild->getMember( pPacket->getName() );
	try { Assert( pGuildMember != NULL ); } catch ( Throwable& ) { return; }

	if ( pGuildMember->getRank() == GuildMember::GUILDMEMBER_RANK_WAIT &&
		 pPacket->getGuildMemberRank() == GuildMember::GUILDMEMBER_RANK_NORMAL )
	{
		////////////////////////////////////////////////////////////////////////////
		// ��� ���� ��û�� ������ ����̴�.
		////////////////////////////////////////////////////////////////////////////

		// ����� ������ �����Ѵ�.
		pGuild->modifyMemberRank( pGuildMember->getName(), pPacket->getGuildMemberRank() );

		// ������ �ִٸ� �޽����� ������.
		__ENTER_CRITICAL_SECTION((*g_pPCFinder))

		Creature* pCreature = g_pPCFinder->getCreature_LOCKED( pGuildMember->getName() );
		if ( pCreature != NULL && pCreature->isPC() )
		{
			PlayerCreature* pPlayerCreature = dynamic_cast<PlayerCreature*>(pCreature);
			Assert( pPlayerCreature != NULL );

			// ���� ��� ID�� ����Ѵ�.
			pPlayerCreature->setGuildID( pGuildMember->getGuildID() );

			Player* pPlayer = pCreature->getPlayer();
			Assert( pPlayer != NULL );

			Zone* pZone = pCreature->getZone();
			Assert( pZone != NULL );

			// �ٲ� ��� ID ������ �����ش�.
			GCModifyGuildMemberInfo gcModifyGuildMemberInfo;
			gcModifyGuildMemberInfo.setGuildID( pGuild->getID() );
			gcModifyGuildMemberInfo.setGuildName( pGuild->getName() );
			gcModifyGuildMemberInfo.setGuildMemberRank( pGuildMember->getRank() );
			pPlayer->sendPacket( &gcModifyGuildMemberInfo );

			// ��� ���� ���� �޽����� ������.
			Statement* pStmt = NULL;
			Result* pResult = NULL;
			
			BEGIN_DB
			{
				pStmt = g_pDatabaseManager->getConnection( "DARKEDEN" )->createStatement();
				pResult = pStmt->executeQuery( "SELECT Message FROM Messages WHERE Receiver = '%s'", pGuildMember->getName().c_str() );

				while ( pResult->next() )
				{
					GCSystemMessage gcSystemMessage;
					gcSystemMessage.setMessage( pResult->getString(1) );
					pPlayer->sendPacket( &gcSystemMessage );
				}

				pStmt->executeQuery( "DELETE FROM Messages WHERE Receiver = '%s'", pGuildMember->getName().c_str() );

				SAFE_DELETE( pStmt );
			}
			END_DB(pStmt)

			// ������ ��� ������ �˸���.
			GCOtherModifyInfo gcOtherModifyInfo;
			gcOtherModifyInfo.setObjectID( pCreature->getObjectID() );
			gcOtherModifyInfo.addShortData( MODIFY_GUILDID, pGuildMember->getGuildID() );

			pZone->broadcastPacket( pCreature->getX(), pCreature->getY(), &gcOtherModifyInfo );
		}
		// ������ ������� �޽����� ������.
		pCreature = g_pPCFinder->getCreature_LOCKED( pPacket->getSender() );
		if ( pCreature != NULL && pCreature->isPC() )
		{
			Player* pPlayer = pCreature->getPlayer();
			Assert( pPlayer != NULL );

//			StringStream msg;
//			msg << pGuildMember->getName() << "���� ��� ������ �����Ͽ����ϴ�.";

            char msg[100];
            if ( pGuild->getRace() == Guild::GUILD_RACE_SLAYER )
                sprintf( msg, g_pStringPool->c_str( STRID_ACCEPT_TEAM_JOIN ), pGuildMember->getName().c_str() );
            else if ( pGuild->getRace() == Guild::GUILD_RACE_VAMPIRE )
                sprintf( msg, g_pStringPool->c_str( STRID_ACCEPT_CLAN_JOIN ), pGuildMember->getName().c_str() );
            else if ( pGuild->getRace() == Guild::GUILD_RACE_OUSTERS )
                sprintf( msg, g_pStringPool->c_str( STRID_ACCEPT_CLAN_JOIN ), pGuildMember->getName().c_str() );

			GCSystemMessage gcSystemMessage;
			gcSystemMessage.setMessage( msg );
			pPlayer->sendPacket( &gcSystemMessage );
		}

		__LEAVE_CRITICAL_SECTION((*g_pPCFinder))
	}
	else if ( pGuildMember->getRank() != GuildMember::GUILDMEMBER_RANK_MASTER &&
		 	pPacket->getGuildMemberRank() == GuildMember::GUILDMEMBER_RANK_MASTER )
	{
		///////////////////////////////////////////////////////////
		// ��� �����͸� �����Ѵ�.
		///////////////////////////////////////////////////////////

		string sMaster = pGuild->getMaster();

		// ��帶������ ��ũ�� ���� ��帶���Ͱ� �Ǵ� ����� ���� ��ũ�� �ٲ��ش�.
		pGuild->modifyMemberRank( sMaster, pGuildMember->getRank() );
		// �� ��帶������ ��ũ�� �����Ѵ�.
		pGuild->modifyMemberRank( pGuildMember->getName(), pPacket->getGuildMemberRank() );
		// ��� ������Ʈ�� �� ��� ����Ʈ�� �����Ѵ�.
		pGuild->setMaster( pGuildMember->getName() );

		// ������ �ִٸ� �޽����� ������.
		__ENTER_CRITICAL_SECTION((*g_pPCFinder))

		// �� ��帶���Ͱ� ���Ӽ����� �ִٸ� �� ������ �����ش�.
		Creature* pCreature = g_pPCFinder->getCreature_LOCKED( pGuildMember->getName() );
		if ( pCreature != NULL && pCreature->isPC() )
		{
			PlayerCreature* pPlayerCreature = dynamic_cast<PlayerCreature*>(pCreature);
			Assert( pPlayerCreature != NULL );

			Player* pPlayer = pCreature->getPlayer();
			Assert( pPlayer != NULL );

			// �ٲ� ��� ID ������ �����ش�.
			GCModifyGuildMemberInfo gcModifyGuildMemberInfo;
			gcModifyGuildMemberInfo.setGuildID( pGuild->getID() );
			gcModifyGuildMemberInfo.setGuildName( pGuild->getName() );
			gcModifyGuildMemberInfo.setGuildMemberRank( pGuildMember->getRank() );
			pPlayer->sendPacket( &gcModifyGuildMemberInfo );
		}

		// ������ ��帶���Ͱ� ���Ӽ����� �ִٸ� �� ������ �����ش�.
		pCreature = g_pPCFinder->getCreature_LOCKED( sMaster );
		if ( pCreature != NULL && pCreature->isPC() )
		{
			PlayerCreature* pPlayerCreature = dynamic_cast<PlayerCreature*>(pCreature);
			Assert( pPlayerCreature != NULL );

			Player* pPlayer = pCreature->getPlayer();
			Assert( pPlayer != NULL );

			// �ٲ� ��� ID ������ �����ش�.
			GCModifyGuildMemberInfo gcModifyGuildMemberInfo;
			gcModifyGuildMemberInfo.setGuildID( pGuild->getID() );
			gcModifyGuildMemberInfo.setGuildName( pGuild->getName() );
			gcModifyGuildMemberInfo.setGuildMemberRank( pGuildMember->getRank() );
			pPlayer->sendPacket( &gcModifyGuildMemberInfo );
		}

		// �渶�� �ٲ� ������� �޽����� ������.
		pCreature = g_pPCFinder->getCreature_LOCKED( pPacket->getSender() );
		if ( pCreature != NULL && pCreature->isPC() )
		{
			Player* pPlayer = pCreature->getPlayer();
			Assert( pPlayer != NULL );

//			StringStream msg;
//			msg << pGuild->getName() << "�� �����͸� " << sMaster << " ���� "
//				<< pGuildMember->getName() << " ���� �����Ͽ����ϴ�.";

			char msg[200];
			sprintf( msg, g_pStringPool->c_str( STRID_MODIFY_GUILD_MASTER ),
							pGuild->getName().c_str(), sMaster.c_str(), pGuildMember->getName().c_str() );

			GCSystemMessage gcSystemMessage;
			gcSystemMessage.setMessage( msg );
			pPlayer->sendPacket( &gcSystemMessage );
		}

		__LEAVE_CRITICAL_SECTION((*g_pPCFinder))
	}
	else
	{
		///////////////////////////////////////////////////////////
		// ����� ������ �����Ѵ�.
		///////////////////////////////////////////////////////////
		pGuild->modifyMemberRank( pGuildMember->getName(), pPacket->getGuildMemberRank() );

		// ������ �ִٸ� �޽����� ������.
		__ENTER_CRITICAL_SECTION((*g_pPCFinder))

		Creature* pCreature = g_pPCFinder->getCreature_LOCKED( pGuildMember->getName() );
		if ( pCreature != NULL && pCreature->isPC() )
		{
			Player* pPlayer = pCreature->getPlayer();
			Assert( pPlayer != NULL );

			GCSystemMessage gcSystemMessage;
            if ( pGuild->getRace() == Guild::GUILD_RACE_SLAYER )
                gcSystemMessage.setMessage( g_pStringPool->getString( STRID_TEAM_RIGHT_CHANGED ) );
            else if ( pGuild->getRace() == Guild::GUILD_RACE_VAMPIRE )
                gcSystemMessage.setMessage( g_pStringPool->getString( STRID_CLAN_RIGHT_CHANGED ) );
            else if ( pGuild->getRace() == Guild::GUILD_RACE_OUSTERS )
                gcSystemMessage.setMessage( g_pStringPool->getString( STRID_CLAN_RIGHT_CHANGED ) );

			pPlayer->sendPacket( &gcSystemMessage );
		}

		// �����Ų ������� �޽����� ������.
		pCreature = g_pPCFinder->getCreature_LOCKED( pPacket->getSender() );
		if ( pCreature != NULL && pCreature->isPC() )
		{
			Player* pPlayer = pCreature->getPlayer();
			Assert( pPlayer != NULL );

//			StringStream msg;
//			msg << pGuildMember->getName() << "���� ��� ������ ����Ǿ����ϴ�.";

            char msg[100];
            if ( pGuild->getRace() == Guild::GUILD_RACE_SLAYER )
                sprintf( msg, g_pStringPool->c_str( STRID_TEAM_RIGHT_CHANGED_2 ), pGuildMember->getName().c_str() );
            else if ( pGuild->getRace() == Guild::GUILD_RACE_VAMPIRE )
                sprintf( msg, g_pStringPool->c_str( STRID_CLAN_RIGHT_CHANGED_2 ), pGuildMember->getName().c_str() );
            else if ( pGuild->getRace() == Guild::GUILD_RACE_OUSTERS )
                sprintf( msg, g_pStringPool->c_str( STRID_CLAN_RIGHT_CHANGED_2 ), pGuildMember->getName().c_str() );


			GCSystemMessage gcSystemMessage;
			gcSystemMessage.setMessage( msg );
			pPlayer->sendPacket( &gcSystemMessage );
		}

		__LEAVE_CRITICAL_SECTION((*g_pPCFinder))
	}

#endif
		
	__END_DEBUG_EX __END_CATCH
}
