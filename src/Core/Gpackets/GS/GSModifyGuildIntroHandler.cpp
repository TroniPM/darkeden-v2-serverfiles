//----------------------------------------------------------------------
//
// Filename    : GSModifyGuildIntroHandler.cpp
// Written By  : Reiot
// Description :
//
//----------------------------------------------------------------------

// include files
#include "GSModifyGuildIntro.h"
#include "Assert.h"

#ifdef __SHARED_SERVER__
	
	#include "Guild.h"
	#include "GuildManager.h"
	#include "GameServerManager.h"

	#include "Spackets/SGModifyGuildIntroOK.h"

#endif

//----------------------------------------------------------------------
// 
// GSModifyGuildIntroHandler::execute()
// 
//----------------------------------------------------------------------
void GSModifyGuildIntroHandler::execute ( GSModifyGuildIntro* pPacket, Player* pPlayer )
	 
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __SHARED_SERVER__

	Assert( pPacket != NULL );

	// ��带 �����´�.
	Guild* pGuild = g_pGuildManager->getGuild( pPacket->getGuildID() );
	if (pGuild==NULL) return;

	pGuild->saveIntro( pPacket->getGuildIntro() );

	// ���� ������ ���� ��Ŷ�� �����.
	SGModifyGuildIntroOK sgModifyGuildIntroOK;
	sgModifyGuildIntroOK.setGuildID( pGuild->getID() );
	sgModifyGuildIntroOK.setGuildIntro( pPacket->getGuildIntro() );

	// ���� ������ ��Ŷ�� ������.
	g_pGameServerManager->broadcast( &sgModifyGuildIntroOK );

#endif
		
	__END_DEBUG_EX __END_CATCH
}
