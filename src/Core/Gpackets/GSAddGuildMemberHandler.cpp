//----------------------------------------------------------------------
//
// Filename    : GSAddGuildMemberHandler.cpp
// Written By  :
// Description :
//
//----------------------------------------------------------------------

// include files
#include "GSAddGuildMember.h"
#include "Assert.h"

#ifdef __SHARED_SERVER__
	
	#include "Guild.h"
	#include "GuildManager.h"
	#include "GameServerManager.h"
	#include "DB.h"
	#include "StringPool.h"

	#include "Spackets/SGAddGuildMemberOK.h"
	#include "Spackets/SGModifyGuildOK.h"

#endif

//----------------------------------------------------------------------
// 
// GSAddGuildHandler::execute()
// 
//----------------------------------------------------------------------
void GSAddGuildMemberHandler::execute ( GSAddGuildMember* pPacket, Player* pPlayer )
	 
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __SHARED_SERVER__

	Assert( pPacket != NULL );

	GuildMember* pGuildMember = new GuildMember();
	pGuildMember->setGuildID( pPacket->getGuildID() );
	pGuildMember->setName( pPacket->getName() );
	pGuildMember->setRank( pPacket->getGuildMemberRank() );

	if ( pGuildMember->getRank() == GuildMember::GUILDMEMBER_RANK_WAIT )
	{
		pGuildMember->setRequestDateTime( VSDateTime::currentDateTime() );
	}

	// DB �� Guild Member �� �����Ѵ�.
	pGuildMember->create();

	// Guild Member Intro �� DB�� �����Ѵ�.
	pGuildMember->saveIntro( pPacket->getGuildMemberIntro() );

	// ��忡 �߰��Ѵ�.
	Guild* pGuild = g_pGuildManager->getGuild( pPacket->getGuildID() );
	pGuild->addMember( pGuildMember );

	// ���� ������ ���� ��Ŷ�� �����.
	SGAddGuildMemberOK sgAddGuildMemberOK;
	sgAddGuildMemberOK.setGuildID( pGuildMember->getGuildID() );
	sgAddGuildMemberOK.setName( pGuildMember->getName() );
	sgAddGuildMemberOK.setGuildMemberRank( pGuildMember->getRank() );
	sgAddGuildMemberOK.setServerGroupID( pPacket->getServerGroupID() );

	// ���� ������ ��Ŷ�� ������.
	g_pGameServerManager->broadcast( &sgAddGuildMemberOK );

	// ��� ��� ����̰� ������ 5�� �̻��� �Ǹ� ���� ��尡 �ȴ�.
	if ( pGuild->getState() == Guild::GUILD_STATE_WAIT && pGuild->getActiveMemberCount() > 4 )
	{
		HashMapGuildMember& Members = pGuild->getMembers();
		HashMapGuildMemberItor itr = Members.begin();
		for ( ; itr != Members.end(); itr++ )
		{
			pGuildMember = itr->second;

			///////////////////////////////////////////////////////////////////////////
			// DB�� Slayer, Vampire, Ousters ���̺��� GuildID�� �ٲ۴�.
			// DB�� Message�� �߰��Ѵ�.
			///////////////////////////////////////////////////////////////////////////
			Statement* pStmt = NULL;
			BEGIN_DB
			{
				pStmt = g_pDatabaseManager->getConnection( "DARKEDEN" )->createStatement();
				pStmt->executeQuery( "UPDATE GuildMember SET RequestDateTime=now() WHERE Name='%s'", pGuildMember->getName().c_str() );

				if ( pGuild->getRace() == Guild::GUILD_RACE_SLAYER )
				{
					pStmt->executeQuery( "UPDATE Slayer SET GuildID = %d WHERE Name = '%s'", pGuild->getID(), pGuildMember->getName().c_str() );

					if ( pGuildMember->getRank() == GuildMember::GUILDMEMBER_RANK_MASTER )
						pStmt->executeQuery( "INSERT INTO Messages ( Receiver, Message ) VALUES ( '%s', '%s' )", pGuildMember->getName().c_str(), g_pStringPool->c_str( STRID_TEAM_REGISTRATION_ACCEPT ) );
					else
					{
						pStmt->executeQuery( "INSERT INTO Messages ( Receiver, Message ) VALUES ( '%s', '%s' )", pGuildMember->getName().c_str(), g_pStringPool->c_str( STRID_TEAM_REGISTRATION_ACCEPT_2 ) );
					}
				}
				else if ( pGuild->getRace() == Guild::GUILD_RACE_VAMPIRE )
				{
					pStmt->executeQuery( "UPDATE Vampire SET GuildID = %d WHERE Name = '%s'", pGuild->getID(), pGuildMember->getName().c_str() );

					if ( pGuildMember->getRank() == GuildMember::GUILDMEMBER_RANK_MASTER )
						pStmt->executeQuery( "INSERT INTO Messages ( Receiver, Message ) VALUES ( '%s', '%s' )", pGuildMember->getName().c_str(), g_pStringPool->c_str( STRID_CLAN_REGISTRATION_ACCEPT ) );
					else
					{
						pStmt->executeQuery( "INSERT INTO Messages ( Receiver, Message ) VALUES ( '%s', '%s' )", pGuildMember->getName().c_str(), g_pStringPool->c_str( STRID_CLAN_REGISTRATION_ACCEPT_2 ) );
					}
				}
				else if ( pGuild->getRace() == Guild::GUILD_RACE_OUSTERS )
				{
					pStmt->executeQuery( "UPDATE Ousters SET GuildID = %d WHERE Name = '%s'", pGuild->getID(), pGuildMember->getName().c_str() );

					if ( pGuildMember->getRank() == GuildMember::GUILDMEMBER_RANK_MASTER )
						pStmt->executeQuery( "INSERT INTO Messages ( Receiver, Message ) VALUES ( '%s', '%s' )", pGuildMember->getName().c_str(), g_pStringPool->c_str( STRID_CLAN_REGISTRATION_ACCEPT ) );
					else
					{
						pStmt->executeQuery( "INSERT INTO Messages ( Receiver, Message ) VALUES ( '%s', '%s' )", pGuildMember->getName().c_str(), g_pStringPool->c_str( STRID_CLAN_REGISTRATION_ACCEPT_2 ) );
					}
				}


				SAFE_DELETE( pStmt );
			}
			END_DB(pStmt)

		}

		pGuild->setState( Guild::GUILD_STATE_ACTIVE );
		pGuild->save();

		SGModifyGuildOK sgModifyGuildOK;
		sgModifyGuildOK.setGuildID( pGuild->getID() );
		sgModifyGuildOK.setGuildState( pGuild->getState() );

		g_pGameServerManager->broadcast( &sgModifyGuildOK );
	}

#endif
		
	__END_DEBUG_EX __END_CATCH
}
