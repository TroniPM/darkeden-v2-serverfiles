//----------------------------------------------------------------------
//
// Filename    : GSModifyGuildMemberHandler.cpp
// Written By  : Reiot
// Description :
//
//----------------------------------------------------------------------

// include files
#include "GSModifyGuildMember.h"
#include "Assert.h"

#ifdef __SHARED_SERVER__
	
	#include "Guild.h"
	#include "GuildManager.h"
	#include "GameServerManager.h"
	#include "Properties.h"
	#include "DB.h"
	#include "StringPool.h"

	#include <stdio.h>

	#include "Spackets/SGModifyGuildMemberOK.h"

#endif

//----------------------------------------------------------------------
// 
// GSModifyGuildMemberHandler::execute()
// 
//----------------------------------------------------------------------
void GSModifyGuildMemberHandler::execute ( GSModifyGuildMember* pPacket, Player* pPlayer )
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __SHARED_SERVER__
	//cout << "GSModifyGuildMember received" << endl;

	Assert( pPacket != NULL );

	// ��带 �����´�.
	Guild* pGuild = g_pGuildManager->getGuild( pPacket->getGuildID() );
	//try { Assert( pGuild != NULL ); } catch ( Throwable& ) { return; }
	if (pGuild==NULL) return;

	// ����� ������� Ȯ���Ѵ�.
	GuildMember* pGuildMember = pGuild->getMember( pPacket->getName() );
	//try { Assert( pGuildMember != NULL ); } catch ( Throwable& ) { return; }
	if (pGuildMember==NULL) return;

	// ��������� ��� ���������� Ȯ���Ѵ�. ( ��� �����͸� �ٲܶ��� ���� )
	if ( pGuild->getMaster() != pPacket->getSender() 
		&& pPacket->getGuildMemberRank() != GuildMember::GUILDMEMBER_RANK_MASTER )
		return;

	if ( pGuildMember->getRank() == GuildMember::GUILDMEMBER_RANK_WAIT &&
		 pPacket->getGuildMemberRank() == GuildMember::GUILDMEMBER_RANK_NORMAL )
	{
		///////////////////////////////////////////////////////////////////////////////////////
		// ��� ��� ������ ������ ���, DB�� Slayer, Vampire, Ousters ���̺��� GuildID �� �ٲ۴�.
		///////////////////////////////////////////////////////////////////////////////////////
		Statement* pStmt = NULL;

		BEGIN_DB
		{
			pStmt = g_pDatabaseManager->getConnection( "DARKEDEN" )->createStatement();
			
			if ( pGuild->getRace() == Guild::GUILD_RACE_SLAYER )
			{
				pStmt->executeQuery( "UPDATE Slayer SET GuildID = %d WHERE Name = '%s'", pGuild->getID(), pGuildMember->getName().c_str() );
				pStmt->executeQuery( "INSERT INTO Messages ( Receiver, Message ) VALUES ( '%s', '%s' )", pGuildMember->getName().c_str(), g_pStringPool->c_str( STRID_TEAM_JOIN_ACCEPT ) );
			}
			else if ( pGuild->getRace() == Guild::GUILD_RACE_VAMPIRE )
			{
				pStmt->executeQuery( "UPDATE Vampire SET GuildID = %d WHERE Name = '%s'", pGuild->getID(), pGuildMember->getName().c_str() );
				pStmt->executeQuery( "INSERT INTO Messages ( Receiver, Message ) VALUES ( '%s', '%s' )", pGuildMember->getName().c_str(), g_pStringPool->c_str( STRID_CLAN_JOIN_ACCEPT ) );
			}
			else if ( pGuild->getRace() == Guild::GUILD_RACE_OUSTERS )
			{
				pStmt->executeQuery( "UPDATE Ousters SET GuildID = %d WHERE Name = '%s'", pGuild->getID(), pGuildMember->getName().c_str() );
				pStmt->executeQuery( "INSERT INTO Messages ( Receiver, Message ) VALUES ( '%s', '%s' )", pGuildMember->getName().c_str(), g_pStringPool->c_str( STRID_CLAN_JOIN_ACCEPT ) );
			}

			SAFE_DELETE( pStmt );
		}
		END_DB(pStmt)

		// Guild Member ������ �����Ѵ�.
		pGuild->modifyMemberRank( pGuildMember->getName(), pPacket->getGuildMemberRank() );
	}
	else if ( pGuildMember->getRank() != GuildMember::GUILDMEMBER_RANK_MASTER
			&& pPacket->getGuildMemberRank() == GuildMember::GUILDMEMBER_RANK_MASTER )
	{
		// ��帶������ ��ũ�� ���� ��帶���Ͱ� �Ǵ� ����� ���� ��ũ�� �ٲ��ش�.
		pGuild->modifyMemberRank( pGuild->getMaster(), pGuildMember->getRank() );
		// �� ��帶������ ��ũ�� �����Ѵ�.
		pGuild->modifyMemberRank( pGuildMember->getName(), pPacket->getGuildMemberRank() );
		// ��� ������Ʈ�� �� ��� ����Ʈ�� �����Ѵ�.
		pGuild->setMaster( pGuildMember->getName() );

		// DB�� �����Ѵ�.
		char field[30];
		sprintf( field, "Master='%s'", pGuildMember->getName().c_str() );
		pGuild->tinysave( field );
	}
	else if ( pGuildMember->getRank() == GuildMember::GUILDMEMBER_RANK_NORMAL
			&& pPacket->getGuildMemberRank() == GuildMember::GUILDMEMBER_RANK_SUBMASTER )
	{
		// �� �α�帶������ ��ũ�� �����Ѵ�.
		pGuild->modifyMemberRank( pGuildMember->getName(), pPacket->getGuildMemberRank() );
	}
	else
	{
		return;
	}

	// ���� ������ ���� ��Ŷ�� �����.
	SGModifyGuildMemberOK sgModifyGuildMemberOK;
	sgModifyGuildMemberOK.setGuildID( pGuild->getID() );
	sgModifyGuildMemberOK.setName( pPacket->getName() );
	sgModifyGuildMemberOK.setGuildMemberRank( pGuildMember->getRank() );
	sgModifyGuildMemberOK.setSender( pPacket->getSender() );

	// ���� ������ ��Ŷ�� ������.
	g_pGameServerManager->broadcast( &sgModifyGuildMemberOK );

#endif
		
	__END_DEBUG_EX __END_CATCH
}
