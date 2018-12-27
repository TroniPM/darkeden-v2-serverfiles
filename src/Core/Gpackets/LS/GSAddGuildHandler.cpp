//----------------------------------------------------------------------
//
// Filename    : GSAddGuildHandler.cpp
// Written By  : Reiot
// Description :
//
//----------------------------------------------------------------------

// include files
#include "GSAddGuild.h"
#include "Assert.h"

#ifdef __SHARED_SERVER__
	
	#include "Guild.h"
	#include "GuildManager.h"
	#include "GameServerManager.h"
	#include "Properties.h"

	#include "Spackets/SGAddGuildOK.h"
	#include "Spackets/SGAddGuildMemberOK.h"

#endif

//----------------------------------------------------------------------
// 
// GSAddGuildHandler::execute()
// 
//----------------------------------------------------------------------
void GSAddGuildHandler::execute ( GSAddGuild* pPacket, Player* pPlayer )
	 
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __SHARED_SERVER__

	Assert( pPacket != NULL );

	// ���� ����� �ƽ� ID + 1 �� ��� ID �� �ϰ� �ƽ� ID �� ���� ��Ų��
	GuildID_t GuildID = Guild::getMaxGuildID() + 1;
	Guild::setMaxGuildID( GuildID );

	ZoneID_t zoneID;

	//cout << pPacket->toString().c_str() << endl;

	// �ƽ� �� ID �� ���Ѵ�.
	if ( pPacket->getGuildRace() == Guild::GUILD_RACE_SLAYER )
	{
		zoneID = Guild::getMaxSlayerZoneID();
		Guild::setMaxSlayerZoneID( zoneID + 1 );
	}
	else if ( pPacket->getGuildRace() == Guild::GUILD_RACE_VAMPIRE )
	{
		zoneID = Guild::getMaxVampireZoneID();
		Guild::setMaxVampireZoneID( zoneID + 1 );
	}
	else if ( pPacket->getGuildRace() == Guild::GUILD_RACE_OUSTERS )
	{
		zoneID = Guild::getMaxOustersZoneID();
		Guild::setMaxOustersZoneID( zoneID + 1 );
	}
	else
	{
		return;
	}

	// Guild Object �� �����
	Guild* pGuild = new Guild();
	pGuild->setID( GuildID );
	pGuild->setName( pPacket->getGuildName() );
	pGuild->setRace( pPacket->getGuildRace() );
	pGuild->setState( pPacket->getGuildState() );
	pGuild->setServerGroupID( pPacket->getServerGroupID() );
	pGuild->setZoneID( zoneID );
	pGuild->setMaster( pPacket->getGuildMaster() );
	pGuild->setIntro( pPacket->getGuildIntro() );

	// ���� ��带 ��� �ִ´�
	pGuild->create();

	// ��� �Ŵ����� �߰��Ѵ�.
	g_pGuildManager->addGuild( pGuild );

	// �����͸� ��� ����� �߰��Ѵ�.
	GuildMember* pGuildMember = new GuildMember();
	pGuildMember->setGuildID( pGuild->getID() );
	pGuildMember->setName( pGuild->getMaster() );
	pGuildMember->setRank( GuildMember::GUILDMEMBER_RANK_MASTER );

	// DB �� Guild Member �� �����Ѵ�.
	pGuildMember->create();

	// ��忡 �߰��Ѵ�.
	pGuild->addMember( pGuildMember );

	// ���� ������ ���� ��Ŷ�� �����.
	SGAddGuildOK sgAddGuildOK;
	sgAddGuildOK.setGuildID( pGuild->getID() );
	sgAddGuildOK.setGuildName( pGuild->getName() );
	sgAddGuildOK.setGuildRace( pGuild->getRace() );
	sgAddGuildOK.setGuildState( pGuild->getState() );
	sgAddGuildOK.setServerGroupID( pGuild->getServerGroupID() );
	sgAddGuildOK.setGuildZoneID( pGuild->getZoneID() );
	sgAddGuildOK.setGuildMaster( pGuild->getMaster() );
	sgAddGuildOK.setGuildIntro( pGuild->getIntro() );

	// ���� ������ ��Ŷ�� ������.
	g_pGameServerManager->broadcast( &sgAddGuildOK );

	SGAddGuildMemberOK sgAddGuildMemberOK;
	sgAddGuildMemberOK.setGuildID( pGuildMember->getGuildID() );
	sgAddGuildMemberOK.setName( pGuildMember->getName() );
	sgAddGuildMemberOK.setGuildMemberRank( pGuildMember->getRank() );
	sgAddGuildMemberOK.setServerGroupID( pPacket->getServerGroupID() );

	// ���� ������ ��Ŷ�� ������.
	g_pGameServerManager->broadcast( &sgAddGuildMemberOK );

#endif
		
	__END_DEBUG_EX __END_CATCH
}
