//----------------------------------------------------------------------
//
// Filename    : GSExpelGuildMemberHandler.cpp
// Written By  : Reiot
// Description :
//
//----------------------------------------------------------------------

// include files
#include "GSExpelGuildMember.h"
#include "Assert.h"

#ifdef __SHARED_SERVER__
	
	#include "Guild.h"
	#include "GuildManager.h"
	#include "GameServerManager.h"
	#include "Properties.h"
	#include "DB.h"

	#include "Spackets/SGExpelGuildMemberOK.h"
	#include "Spackets/SGDeleteGuildOK.h"

#endif

//----------------------------------------------------------------------
// 
// GSExpelGuildMemberHandler::execute()
// 
//----------------------------------------------------------------------
void GSExpelGuildMemberHandler::execute ( GSExpelGuildMember* pPacket, Player* pPlayer )
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __SHARED_SERVER__
	//cout << "GSExpelGuildMember received" << endl;

	Assert( pPacket != NULL );

	// �÷��̾ ���� ��带 �����´�.
	Guild* pGuild = g_pGuildManager->getGuild( pPacket->getGuildID() );
	//try { Assert( pGuild != NULL ); } catch ( Throwable& ) { return; }
	if (pGuild==NULL) return;

	// �÷��̾ ����� ������� Ȯ���Ѵ�.
	GuildMember* pGuildMember = pGuild->getMember( pPacket->getName() );
	//try { Assert( pGuildMember != NULL ); } catch ( Throwable& ) { return; }
	if (pGuildMember==NULL) return;

	// ��� Ż�� �α׸� �����.
	filelog( "GuildExit.log", "GuildID: %d, GuildName: %s, Expel: %s, By: %s", pGuild->getID(), pGuild->getName().c_str(), pPacket->getName().c_str(), pPacket->getSender().c_str() );

	///////////////////////////////////////////////////////////////////
	//  DB�� Slayer, Vampire, Ousters ���̺��� GuildID �� �ٲ۴�.
	///////////////////////////////////////////////////////////////////
	Statement* pStmt = NULL;
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

	// Guild Member �� expire ��Ų��.
	pGuildMember->expire();

	// Guild ���� �����Ѵ�.
	pGuild->deleteMember( pGuildMember->getName() );

	// ���� ������ ���� ��Ŷ�� �����.
	SGExpelGuildMemberOK sgExpelGuildMemberOK;
	sgExpelGuildMemberOK.setGuildID( pGuild->getID() );
	sgExpelGuildMemberOK.setName( pPacket->getName() );
	sgExpelGuildMemberOK.setSender( pPacket->getSender() );

	// ���� ������ ��Ŷ�� ������.
	g_pGameServerManager->broadcast( &sgExpelGuildMemberOK );

	// ��� �ο��� 5�� �̸��� �� ��� ��带 �����Ѵ�.
	if ( pGuild->getState() == Guild::GUILD_STATE_ACTIVE && pGuild->getActiveMemberCount() < MIN_GUILDMEMBER_COUNT )
	{
		// ��� ���� �α׸� �����.
		filelog( "GuildBroken.log", "GuildID: %d, GuildName: %s, MemberCount: %d, Expel: %s", pGuild->getID(), pGuild->getName().c_str(), pGuild->getActiveMemberCount(), pPacket->getName().c_str() );

		// ��� ��� expire and delete
		HashMapGuildMember& Members = pGuild->getMembers();
		HashMapGuildMemberItor itr = Members.begin();
		
		BEGIN_DB
		{
			pStmt = g_pDatabaseManager->getConnection( "DARKEDEN" )->createStatement();

			for ( ; itr != Members.end(); itr++ )
			{
				GuildMember* pGuildMember = itr->second;

				///////////////////////////////////////////////////////////////////
				//  DB�� Slayer, Vampire, Ousters ���̺��� GuildID �� �ٲ۴�.
				///////////////////////////////////////////////////////////////////
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

				// ��� ����� expire ��Ų��.
				pGuildMember->expire();
				// ������ DB���� �����Ѵ�.
				//pGuildMember->destroy();

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

#endif
		
	__END_DEBUG_EX __END_CATCH
}
