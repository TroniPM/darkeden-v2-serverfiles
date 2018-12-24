//----------------------------------------------------------------------
//
// Filename    : GSQuitGuildHandler.cpp
// Written By  : Reiot
// Description :
//
//----------------------------------------------------------------------

// include files
#include "GSQuitGuild.h"
#include "Assert.h"

#ifdef __SHARED_SERVER__
	
	#include "Guild.h"
	#include "GuildManager.h"
	#include "GameServerManager.h"
	#include "Properties.h"
	#include "DB.h"
	#include "StringPool.h"

	#include "Spackets/SGQuitGuildOK.h"
	#include "Spackets/SGDeleteGuildOK.h"

#endif

//----------------------------------------------------------------------
// 
// GSQuitGuildHandler::execute()
// 
//----------------------------------------------------------------------
void GSQuitGuildHandler::execute ( GSQuitGuild* pPacket, Player* pPlayer )
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __SHARED_SERVER__

	Assert( pPacket != NULL );

	// �÷��̾ ���� ��带 �����´�.
	Guild* pGuild = g_pGuildManager->getGuild( pPacket->getGuildID() );
	//try { Assert( pGuild != NULL ); } catch ( Throwable& ) { return; }
	if (pGuild==NULL) return;

	// �÷��̾ ����� ������� Ȯ���Ѵ�.
	GuildMember* pGuildMember = pGuild->getMember( pPacket->getName() );
	//try { Assert( pGuildMember != NULL ); } catch ( Throwable& ) { return; }
	if (pGuildMember==NULL) return;

	Statement* pStmt = NULL;

	// ��� Ż�� �α׸� �����.
	GuildMemberRank_t rank = pGuildMember->getRank();
	if ( rank == GuildMember::GUILDMEMBER_RANK_NORMAL ||
		 rank == GuildMember::GUILDMEMBER_RANK_MASTER ||
		 rank == GuildMember::GUILDMEMBER_RANK_SUBMASTER )
		filelog( "GuildExit.log", "GuildID: %d, GuildName: %s, Quit: %s", pGuild->getID(), pGuild->getName().c_str(), pPacket->getName().c_str() );

	//////////////////////////////////////////////////////////////////////////////
	// ��尡 active ��� �� Ż���ϴ� �Ŵ�
	// wait ��� ���� �����ְ� Ż���ϴ� ����� �����Ͷ�� ��带 ��ҽ�Ų��.
	//////////////////////////////////////////////////////////////////////////////
	if ( pGuild->getState() == Guild::GUILD_STATE_ACTIVE )
	{
		// ��� �������� ��� ����
		if ( pGuildMember->getRank() == GuildMember::GUILDMEMBER_RANK_MASTER )
			return;

		// DB �� Slayer, Vampire, Ousters ���̺��� ��� ���̵� �ٲ۴�.
		BEGIN_DB
		{
			pStmt = g_pDatabaseManager->getConnection( "DARKEDEN" )->createStatement();
			
			if ( pGuild->getRace() == Guild::GUILD_RACE_SLAYER )
			{
				pStmt->executeQuery( "UPDATE Slayer SET GuildID = 99 WHERE Name = '%s'", pGuildMember->getName().c_str() );
			}
			else if ( pGuild->getRace() == Guild::GUILD_RACE_VAMPIRE )
			{
				pStmt->executeQuery( "UPDATE Vampire SET GuildID = 0 WHERE Name = '%s'", pGuildMember->getName().c_str() );
			}
			else if ( pGuild->getRace() == Guild::GUILD_RACE_OUSTERS )
			{
				pStmt->executeQuery( "UPDATE Ousters SET GuildID = 66 WHERE Name = '%s'", pGuildMember->getName().c_str() );
			}

			SAFE_DELETE( pStmt );
		}
		END_DB(pStmt)

		// Guild Member �� leave ��Ų��.
		pGuildMember->leave();

		// Guild ���� �����Ѵ�.
		pGuild->deleteMember( pGuildMember->getName() );

		// ���� ������ ���� ��Ŷ�� �����.
		SGQuitGuildOK sgQuitGuildOK;
		sgQuitGuildOK.setGuildID( pGuild->getID() );
		sgQuitGuildOK.setName( pPacket->getName() );

		// ���� ������ ��Ŷ�� ������.
		g_pGameServerManager->broadcast( &sgQuitGuildOK );

		// ��� �ο��� 5�� �̸��� �� ���
		if ( pGuild->getState() == Guild::GUILD_STATE_ACTIVE && pGuild->getActiveMemberCount() < MIN_GUILDMEMBER_COUNT )
		{
			// ����� �����.
			filelog( "GuildBroken.log", "GuildID: %d, GuildName: %s, MemberCount: %d, Quit: %s", pGuild->getID(), pGuild->getName().c_str(), pGuild->getActiveMemberCount(), pPacket->getName().c_str() );

			// ��� ��� expire and delete
			HashMapGuildMember& Members = pGuild->getMembers();
			HashMapGuildMemberItor itr = Members.begin();

			BEGIN_DB
			{
				pStmt = g_pDatabaseManager->getConnection( "DARKEDEN" )->createStatement();

				for ( ; itr != Members.end(); itr++ )
				{
					GuildMember* pGuildMember = itr->second;

					if ( pGuild->getRace() == Guild::GUILD_RACE_SLAYER )
					{
						pStmt->executeQuery( "UPDATE Slayer SET GuildID = 99 WHERE Name = '%s'", pGuildMember->getName().c_str() );
						pStmt->executeQuery( "INSERT INTO Messages ( Receiver, Message ) VALUES ( '%s', '%s' )", pGuildMember->getName().c_str(), g_pStringPool->c_str( STRID_TEAM_BROKEN ) );
					}
					else if ( pGuild->getRace() == Guild::GUILD_RACE_VAMPIRE )
					{
						pStmt->executeQuery( "UPDATE Vampire SET GuildID = 0 WHERE Name = '%s'", pGuildMember->getName().c_str() );
						pStmt->executeQuery( "INSERT INTO Messages ( Receiver, Message ) VALUES ( '%s', '%s' )", pGuildMember->getName().c_str(), g_pStringPool->c_str( STRID_CLAN_BROKEN ) );
					}
					else if ( pGuild->getRace() == Guild::GUILD_RACE_OUSTERS )
					{
						pStmt->executeQuery( "UPDATE Ousters SET GuildID = 0 WHERE Name = '%s'", pGuildMember->getName().c_str() );
						pStmt->executeQuery( "INSERT INTO Messages ( Receiver, Message ) VALUES ( '%s', '%s' )", pGuildMember->getName().c_str(), g_pStringPool->c_str( STRID_CLAN_BROKEN ) );
					}

					// ��� ����� expire ��Ų��.
					pGuildMember->expire();

					// ��� ����� ����
					SAFE_DELETE( pGuildMember );
				}
				
				SAFE_DELETE( pStmt );
			}
			END_DB(pStmt)

			Members.clear();

			// ��带 �����Ѵ�
			pGuild->setState( Guild::GUILD_STATE_BROKEN );
			pGuild->save();

			SAFE_DELETE( pGuild );
			g_pGuildManager->deleteGuild( pPacket->getGuildID() );

			// ��带 �����ϵ��� ��Ŷ�� ������.
			SGDeleteGuildOK sgDeleteGuildOK;
			sgDeleteGuildOK.setGuildID( pPacket->getGuildID() );

			g_pGameServerManager->broadcast( &sgDeleteGuildOK );
		}
	}
	else if ( pGuild->getState() == Guild::GUILD_STATE_WAIT )
	{
		if ( pGuildMember->getRank() == GuildMember::GUILDMEMBER_RANK_MASTER )
		{
			////////////////////////////////////////////////////////////
			// ��带 ��� ��Ų��.
			// ��� ��� expire and delete
			////////////////////////////////////////////////////////////
			HashMapGuildMember& Members = pGuild->getMembers();
			HashMapGuildMemberItor itr = Members.begin();

			BEGIN_DB
			{
				pStmt = g_pDatabaseManager->getConnection( "DARKEDEN" )->createStatement();

				for ( ; itr != Members.end(); itr++ )
				{
					GuildMember* pGuildMember = itr->second;

					string Table = "";
					string Message = "";
					Gold_t Gold = 0;

					if ( pGuild->getRace() == Guild::GUILD_RACE_SLAYER )
					{
						Table = "Slayer";
						Message = g_pStringPool->getString( STRID_TEAM_CANCEL );
					}
					else if ( pGuild->getRace() == Guild::GUILD_RACE_VAMPIRE )
					{
						Table = "Vampire";
						Message = g_pStringPool->getString( STRID_CLAN_CANCEL );
					}
					else if ( pGuild->getRace() == Guild::GUILD_RACE_OUSTERS )
					{
						Table = "Ousters";
						Message = g_pStringPool->getString( STRID_CLAN_CANCEL );
					}
					if ( pGuildMember->getRank() == GuildMember::GUILDMEMBER_RANK_MASTER )
						Gold = RETURN_SLAYER_MASTER_GOLD;
					else if ( pGuildMember->getRank() == GuildMember::GUILDMEMBER_RANK_SUBMASTER )
						Gold = RETURN_SLAYER_SUBMASTER_GOLD;

					if ( !Table.empty() && !Message.empty() && Gold != 0 )
					{
						// �޽����� �ִ´�.
						pStmt->executeQuery( "INSERT INTO Messages ( Receiver, Message ) VALUES ( '%s', '%s' )", pGuildMember->getName().c_str(), Message.c_str() );
						
						// ��Ϻ� ȯ���Ѵ�. ���� �÷������� ĳ���ʹ� DB ����Ÿ�� gameserver�� �ִ� ����Ÿ�� �ٸ����� �ֱ⶧���� �̷��� �ϸ� �ȵǴµ�, �ٽ� ���� �������� ���� ������Ʈ �Ѵ�.
						pStmt->executeQuery( "UPDATE %s SET Gold = Gold + %d WHERE Name = '%s'", Table.c_str(), (int)Gold, pGuildMember->getName().c_str() );
					}

					// ��� ����� expire ��Ų��.
					pGuildMember->expire();

					// ��� ����� ����
					SAFE_DELETE( pGuildMember );
				}
				
				SAFE_DELETE( pStmt );
			}
			END_DB(pStmt)

			Members.clear();

			// ��带 �����Ѵ�
			pGuild->setState( Guild::GUILD_STATE_CANCEL );
			pGuild->save();

			SAFE_DELETE( pGuild );

			g_pGuildManager->deleteGuild( pPacket->getGuildID() );

			// ��带 �����ϵ��� ��Ŷ�� ������.
			SGDeleteGuildOK sgDeleteGuildOK;
			sgDeleteGuildOK.setGuildID( pPacket->getGuildID() );

			g_pGameServerManager->broadcast( &sgDeleteGuildOK );
		}
		else if ( pGuildMember->getRank() == GuildMember::GUILDMEMBER_RANK_SUBMASTER )
		{
			//////////////////////////////////////////////////////////
			// ��Ÿ�� ��� ������ ��� ��Ų��.
			// Guild Member �� expire ��Ų��.
			//////////////////////////////////////////////////////////
			pGuildMember->expire();

			// Guild ���� �����Ѵ�.
			pGuild->deleteMember( pGuildMember->getName() );

			// ���� ������ ���� ��Ŷ�� �����.
			SGQuitGuildOK sgQuitGuildOK;
			sgQuitGuildOK.setGuildID( pGuild->getID() );
			sgQuitGuildOK.setName( pPacket->getName() );

			// ���� ������ ��Ŷ�� ������.
			g_pGameServerManager->broadcast( &sgQuitGuildOK );

		}
	}

#endif
		
	__END_DEBUG_EX __END_CATCH
}
