//----------------------------------------------------------------------
//
// Filename    : SGModifyGuildIntroOKHandler.cpp
// Written By  : Reiot
// Description :
//
//----------------------------------------------------------------------

// include files
#include "SGModifyGuildIntroOK.h"
#include "Properties.h"

#ifdef __GAME_SERVER__

	#include "DB.h"
	#include "Guild.h"
	#include "GuildManager.h"
	#include "Player.h"
	#include "Gpackets/GCSystemMessage.h"

#endif

//----------------------------------------------------------------------
// 
// SGModifyGuildIntroOKHandler::execute()
// 
//----------------------------------------------------------------------
void SGModifyGuildIntroOKHandler::execute ( SGModifyGuildIntroOK* pPacket )
	 
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	//cout << "SGModifyGuildIntro received" << endl;

	Assert( pPacket != NULL );

	// ��带 �����´�.
	Guild* pGuild = g_pGuildManager->getGuild( pPacket->getGuildID() );
	try { Assert( pGuild != NULL ); } catch ( Throwable& ) { return; }

	pGuild->setIntro( pPacket->getGuildIntro() );

#endif
		
	__END_DEBUG_EX __END_CATCH
}
