//----------------------------------------------------------------------
//
// Filename    : SGModifyGuildOKHandler.cpp
// Written By  : Reiot
// Description :
//
//----------------------------------------------------------------------

// include files
#include "SGModifyGuildOK.h"
#include "Properties.h"

#ifdef __GAME_SERVER__

	#include "DB.h"
	#include "Guild.h"
	#include "GuildManager.h"
	#include "PCFinder.h"
	#include "Player.h"
	#include "PlayerCreature.h"
	#include "Zone.h"
	#include "ZoneInfoManager.h"
	#include "ZoneGroupManager.h"
	#include "Properties.h"
	#include "Gpackets/GCModifyGuildMemberInfo.h"
	#include "Gpackets/GCOtherModifyInfo.h"
	#include "Gpackets/GCSystemMessage.h"

#endif

//----------------------------------------------------------------------
// 
// SGModifyGuildOKHandler::execute()
// 
//----------------------------------------------------------------------
void SGModifyGuildOKHandler::execute ( SGModifyGuildOK* pPacket )
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	Guild* pGuild = g_pGuildManager->getGuild( pPacket->getGuildID() );
	Assert( pGuild != NULL );

	if ( pGuild->getState() == Guild::GUILD_STATE_WAIT && pPacket->getGuildState() == Guild::GUILD_STATE_ACTIVE )
	{
		/////////////////////////////////////////////////////////////
		// �� �߰�
		/////////////////////////////////////////////////////////////
/*		if ( pGuild->getServerGroupID() == g_pConfig->getPropertyInt( "ServerID" ) )
		{
			// �� ���� ������ ��� ����Ʈ�� �����.

			//////////////
			// Zone Info
			//////////////
			ZoneInfo* pZoneInfo = new ZoneInfo();
			pZoneInfo->setZoneID( pGuild->getZoneID() );
			pZoneInfo->setZoneGroupID( 2 );
			pZoneInfo->setZoneType( "NPC_SHOP" );
			pZoneInfo->setZoneLevel( 0 );
			pZoneInfo->setZoneAccessMode( "PUBLIC" );
			pZoneInfo->setZoneOwnerID( "" );
			pZoneInfo->setPayPlay( "" );
			if ( pGuild->getRace() == Guild::GUILD_RACE_SLAYER )
			{
				pZoneInfo->setSMPFilename( "team_hdqrs.smp" );
				pZoneInfo->setSSIFilename( "team_hdqrs.ssi" );
				string Name = "team - " + pGuild->getName();
				pZoneInfo->setFullName( Name );
				pZoneInfo->setShortName( Name );
			}
			else if ( pGuild->getRace() == Guild::GUILD_RACE_VAMPIRE )
			{
				pZoneInfo->setSMPFilename( "clan_hdqrs.smp" );
				pZoneInfo->setSSIFilename( "clan_hdqrs.ssi" );
				string Name = "clan - " + pGuild->getName();
				pZoneInfo->setFullName( Name );
				pZoneInfo->setShortName( Name );
			}

			g_pZoneInfoManager->addZoneInfo( pZoneInfo );
			
			/////////
			// Zone
			/////////
			Zone* pZone = new Zone( pGuild->getZoneID() );
			Assert( pZone != NULL );

			ZoneGroup* pZoneGroup = g_pZoneGroupManager->getZoneGroup(2);
			Assert( pZoneGroup != NULL );

			pZone->setZoneGroup( pZoneGroup );
			pZoneGroup->addZone( pZone );
			pZone->init();
		}
*/

		// ���� ���� ����
		pGuild->setState( Guild::GUILD_STATE_ACTIVE );

		HashMapGuildMember& Members = pGuild->getMembers();
		HashMapGuildMemberItor itr = Members.begin();
		for ( ; itr != Members.end(); itr++ )
		{
			GuildMember* pGuildMember = itr->second;

			// ����� ������ �ִٸ�
			__ENTER_CRITICAL_SECTION((*g_pPCFinder))

			Creature* pCreature = g_pPCFinder->getCreature_LOCKED( pGuildMember->getName() );
			if ( pCreature != NULL && pCreature->isPC() )
			{
				Player* pPlayer = pCreature->getPlayer();
				Assert( pPlayer != NULL );

				PlayerCreature* pPlayerCreature = dynamic_cast<PlayerCreature*>(pCreature);
				Assert( pPlayerCreature != NULL );

				// ��� ���̵� �ٲ��ش�.
				pPlayerCreature->setGuildID( pGuild->getID() );

				// Ŭ���̾�Ʈ�� ��� ���̵� �ٲ����� �˷��ش�.
				GCModifyGuildMemberInfo gcModifyGuildMemberInfo;
				gcModifyGuildMemberInfo.setGuildID( pGuild->getID() );
				gcModifyGuildMemberInfo.setGuildName( pGuild->getName() );
				gcModifyGuildMemberInfo.setGuildMemberRank( pGuildMember->getRank() );
				pPlayer->sendPacket( &gcModifyGuildMemberInfo );

				// ������ �˸���.
				Zone* pZone = pCreature->getZone();
				Assert( pZone != NULL );

				GCOtherModifyInfo gcOtherModifyInfo;
				gcOtherModifyInfo.setObjectID( pCreature->getObjectID() );
				gcOtherModifyInfo.addShortData( MODIFY_GUILDID, pPlayerCreature->getGuildID() );

				pZone->broadcastPacket( pCreature->getX(), pCreature->getY(), &gcOtherModifyInfo, pCreature );

				// ���� ��尡 �Ǿ����� �˸�
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
			}

			__LEAVE_CRITICAL_SECTION((*g_pPCFinder))
		}
	}

#endif
		
	__END_DEBUG_EX __END_CATCH
}
