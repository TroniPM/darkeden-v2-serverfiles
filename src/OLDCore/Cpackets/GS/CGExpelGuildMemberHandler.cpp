//////////////////////////////////////////////////////////////////////////////
// Filename    : CGExpelGuildMemberHandler.cpp
// Written By  :
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CGExpelGuildMember.h"

#ifdef __GAME_SERVER__
	#include "Gpackets/GSExpelGuildMember.h"
	#include "Guild.h"
	#include "GuildManager.h"
	#include "Player.h"
	#include "PlayerCreature.h"
	#include "Slayer.h"
	#include "Vampire.h"
	#include "SharedServerManager.h"
	#include "SystemAvailabilitiesManager.h"
#endif	// __GAME_SERVER__

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGExpelGuildMemberHandler::execute (CGExpelGuildMember* pPacket , Player* pPlayer)
	 throw (Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	PlayerCreature* pPlayerCreature = dynamic_cast<PlayerCreature*>(pPlayer);
	Assert( pPlayerCreature != NULL );

	SYSTEM_ASSERT(SYSTEM_GUILD);

	// ��带 �����´�.
	Guild* pGuild = g_pGuildManager->getGuild( pPacket->getGuildID() );
	try { Assert( pGuild != NULL ); } catch ( Throwable& t ) { return; }

	// �÷��̾ ����� ������������ Ȯ���Ѵ�.
	if ( pGuild->getMaster() != pPlayerCreature->getName() )
	{
		// �����Ͱ� �ƴϴ�. ����
		return;
	}

	GSExpelGuildMember gsExpelGuildMember;
	gsExpelGuildMember.setGuildID( pGuild->getID() );
	gsExpelGuildMember.setName( pPlayerCreature->getName() );
	gsExpelGuildMember.setSender( pPlayerCreature->getName() );

	g_pSharedServerManager->sendPacket( &gsExpelGuildMember );

#endif	// __GAME_SERVER__
		
	__END_DEBUG_EX __END_CATCH
}

