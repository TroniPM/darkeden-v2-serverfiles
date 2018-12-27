//----------------------------------------------------------------------
//
// Filename    : SGExpelGuildMemberOKHandler.cpp
// Written By  : Reiot
// Description :
//
//----------------------------------------------------------------------

// include files
#include "SGExpelGuildMemberOK.h"
#include "Properties.h"

#ifdef __GAME_SERVER__

	#include "Guild.h"
	#include "GuildManager.h"
	#include "PCFinder.h"
	#include "Player.h"
	#include "PlayerCreature.h"
	#include "Zone.h"
	#include "StringPool.h"
	#include "Gpackets/GCSystemMessage.h"
	#include "Gpackets/GCModifyGuildMemberInfo.h"
	#include "Gpackets/GCOtherModifyInfo.h"

	#include <stdio.h>

#endif

//----------------------------------------------------------------------
// 
// SGExpelGuildMemberOKHandler::execute()
// 
//----------------------------------------------------------------------
void SGExpelGuildMemberOKHandler::execute ( SGExpelGuildMemberOK* pPacket)
	 
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	//cout << "SGExpelGuildMember received" << endl;

	Assert( pPacket != NULL );

	// ��带 �����´�.
	Guild* pGuild = g_pGuildManager->getGuild( pPacket->getGuildID() );
	try { Assert( pGuild != NULL ); } catch ( Throwable& ) { return; }

	// ��� ������� Ȯ���Ѵ�.
	GuildMember* pGuildMember = pGuild->getMember( pPacket->getName() );
	try { Assert( pGuildMember != NULL ); } catch ( Throwable& ) { return; }

	if ( pGuildMember->getRank() == GuildMember::GUILDMEMBER_RANK_WAIT )
	{
		//////////////////////////////////////////////////////////
		// ���� ���
		//////////////////////////////////////////////////////////
		
		// ��忡�� �����Ѵ�.
		pGuild->deleteMember( pGuildMember->getName() );

		// ������ �ִٸ� �޽����� ������.
		__ENTER_CRITICAL_SECTION((*g_pPCFinder))

		Creature* pCreature = g_pPCFinder->getCreature_LOCKED( pPacket->getName() );
		if ( pCreature != NULL && pCreature->isPC() )
		{
			Player* pPlayer = pCreature->getPlayer();
			Assert( pPlayer != NULL );

//			StringStream msg;
//			msg << pGuild->getName() << " ��� ���Խ�û�� ��ҵǾ����ϴ�.";

            char msg[100];
            if ( pGuild->getRace() == Guild::GUILD_RACE_SLAYER )
                sprintf( msg, g_pStringPool->c_str( STRID_TEAM_JOIN_DENY ), pGuild->getName().c_str() );
            else if ( pGuild->getRace() == Guild::GUILD_RACE_VAMPIRE )
                sprintf( msg, g_pStringPool->c_str( STRID_CLAN_JOIN_DENY ), pGuild->getName().c_str() );
            else if ( pGuild->getRace() == Guild::GUILD_RACE_OUSTERS )
                sprintf( msg, g_pStringPool->c_str( STRID_CLAN_JOIN_DENY ), pGuild->getName().c_str() );
			// ��� ���Խ�û��� �޽����� ������.
			GCSystemMessage gcSystemMessage;
			gcSystemMessage.setMessage( msg );
			pPlayer->sendPacket( &gcSystemMessage );
		}

		// ��ҽ�Ų ������� �޽����� ������.
		pCreature = g_pPCFinder->getCreature_LOCKED( pPacket->getSender() );
		if ( pCreature != NULL && pCreature->isPC() )
		{
			Player* pPlayer = pCreature->getPlayer();
			Assert( pPlayer != NULL );

//			StringStream msg;
//			msg << pPacket->getName() << "���� ��尡���� ����Ͽ����ϴ�.";

            char msg[100];
            if ( pGuild->getRace() == Guild::GUILD_RACE_SLAYER )
                sprintf( msg, g_pStringPool->c_str( STRID_TEAM_JOIN_DENY_2 ), pPacket->getName().c_str() );
            else if ( pGuild->getRace() == Guild::GUILD_RACE_VAMPIRE )
                sprintf( msg, g_pStringPool->c_str( STRID_CLAN_JOIN_DENY_2 ), pPacket->getName().c_str() );
            else if ( pGuild->getRace() == Guild::GUILD_RACE_OUSTERS )
                sprintf( msg, g_pStringPool->c_str( STRID_CLAN_JOIN_DENY_2 ), pPacket->getName().c_str() );

			GCSystemMessage gcSystemMessage;
			gcSystemMessage.setMessage( msg );
			pPlayer->sendPacket( &gcSystemMessage );
		}

		__LEAVE_CRITICAL_SECTION((*g_pPCFinder))
	}
	else
	{
		///////////////////////////////////////////////////////////
		// ��忡�� �߹��Ѵ�.
		///////////////////////////////////////////////////////////

		// ��忡�� �����Ѵ�.
		pGuild->deleteMember( pGuildMember->getName() );

		// ������ �ִٸ� �޽����� ������.
		__ENTER_CRITICAL_SECTION((*g_pPCFinder))

		Creature* pCreature = g_pPCFinder->getCreature_LOCKED( pPacket->getName() );
		if ( pCreature != NULL && pCreature->isPC() )
		{
			Player* pPlayer = pCreature->getPlayer();
			Assert( pPlayer != NULL );

			PlayerCreature* pPlayerCreature = dynamic_cast<PlayerCreature*>(pCreature);
			Assert( pPlayerCreature != NULL );

			if ( pPlayerCreature->isSlayer() )
			{
				pPlayerCreature->setGuildID( 99 );		// �����̾��� ���Ծ��� ������ ��� ID

				// Ŭ���̾�Ʈ�� ��� �߹��� �˸���.
				GCModifyGuildMemberInfo gcModifyGuildMember;
				gcModifyGuildMember.setGuildID( pPlayerCreature->getGuildID() );
				gcModifyGuildMember.setGuildName( "" );
				gcModifyGuildMember.setGuildMemberRank( GuildMember::GUILDMEMBER_RANK_DENY );
				pPlayer->sendPacket( &gcModifyGuildMember );
			}
			else if ( pPlayerCreature->isVampire() )
			{
				pPlayerCreature->setGuildID( 0 );		// �����̾��� ���Ծ��� ������ ��� ID

				// Ŭ���̾�Ʈ�� ��� �߹��� �˸���.
				GCModifyGuildMemberInfo gcModifyGuildMember;
				gcModifyGuildMember.setGuildID( pPlayerCreature->getGuildID() );
				gcModifyGuildMember.setGuildName( "" );
				gcModifyGuildMember.setGuildMemberRank( GuildMember::GUILDMEMBER_RANK_DENY );
				pPlayer->sendPacket( &gcModifyGuildMember );
			}
			else if ( pPlayerCreature->isOusters() )
			{
				pPlayerCreature->setGuildID( 66 );		// �ƿ콺���� ���Ծ��� ������ ��� ID

				// Ŭ���̾�Ʈ�� ��� �߹��� �˸���.
				GCModifyGuildMemberInfo gcModifyGuildMember;
				gcModifyGuildMember.setGuildID( pPlayerCreature->getGuildID() );
				gcModifyGuildMember.setGuildName( "" );
				gcModifyGuildMember.setGuildMemberRank( GuildMember::GUILDMEMBER_RANK_DENY );
				pPlayer->sendPacket( &gcModifyGuildMember );
			}

			// ��� �߹� �޽����� ������.
			GCSystemMessage gcSystemMessage;
//			gcSystemMessage.setMessage( "��忡�� �߹���߽��ϴ�." );

            if ( pGuild->getRace() == Guild::GUILD_RACE_SLAYER )
                gcSystemMessage.setMessage( g_pStringPool->getString( STRID_EXPEL_TEAM_MEMBER ) );
            else if ( pGuild->getRace() == Guild::GUILD_RACE_VAMPIRE )
                gcSystemMessage.setMessage( g_pStringPool->getString( STRID_EXPEL_CLAN_MEMBER ) );
            else if ( pGuild->getRace() == Guild::GUILD_RACE_OUSTERS )
                gcSystemMessage.setMessage( g_pStringPool->getString( STRID_EXPEL_CLAN_MEMBER ) );

			pPlayer->sendPacket( &gcSystemMessage );

			if ( pGuild->getState() == Guild::GUILD_STATE_ACTIVE )
			{
				// ������ �˸���.
				Zone* pZone = pCreature->getZone();
				Assert( pZone != NULL );

				GCOtherModifyInfo gcOtherModifyInfo;
				gcOtherModifyInfo.setObjectID( pCreature->getObjectID() );
				gcOtherModifyInfo.addShortData( MODIFY_GUILDID, pPlayerCreature->getGuildID() );

				pZone->broadcastPacket( pCreature->getX(), pCreature->getY(), &gcOtherModifyInfo, pCreature );
			}
		}

		// �߹��Ų ������� �޽����� ������.
		pCreature = g_pPCFinder->getCreature_LOCKED( pPacket->getSender() );
		if ( pCreature != NULL && pCreature->isPC() )
		{
			Player* pPlayer = pCreature->getPlayer();
			Assert( pPlayer != NULL );

//			StringStream msg;
//			msg << pPacket->getName() << "���� ��忡�� �߹��Ͽ����ϴ�.";

            char msg[100];
            if ( pGuild->getRace() == Guild::GUILD_RACE_SLAYER )
                sprintf( msg, g_pStringPool->c_str( STRID_EXPEL_TEAM_MEMBER_2 ), pPacket->getName().c_str() );
            else if ( pGuild->getRace() == Guild::GUILD_RACE_VAMPIRE )
                sprintf( msg, g_pStringPool->c_str( STRID_EXPEL_CLAN_MEMBER_2 ), pPacket->getName().c_str() );
            else if ( pGuild->getRace() == Guild::GUILD_RACE_OUSTERS )
                sprintf( msg, g_pStringPool->c_str( STRID_EXPEL_CLAN_MEMBER_2 ), pPacket->getName().c_str() );

			GCSystemMessage gcSystemMessage;
			gcSystemMessage.setMessage( msg );
			pPlayer->sendPacket( &gcSystemMessage );
		}

		__LEAVE_CRITICAL_SECTION((*g_pPCFinder))
	}

#endif

	__END_DEBUG_EX __END_CATCH
}
